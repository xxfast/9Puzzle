#include "GBFSearchTree.h"

int GBFSearchTree::CalculateDisplacedTiles(Node & toCalculate)
{
	int lHeau = 0;
	for (int r = 0; r < toCalculate.getState().fNRows; r++)
		for (int c = 0; c < toCalculate.getState().fNCols; c++) 
			if (!(toCalculate.getState().fTiles[r][c].fValue == fSolved.getState().fTiles[r][c].fValue)) lHeau++;
	return lHeau;
}

int GBFSearchTree::CalculateManhattanDistance(Node& toCalculate)
{
	int lHeau = 0;
	int rl = toCalculate.getState().fNRows;
	int rc = toCalculate.getState().fNCols;
	for (int r1 = 0; r1 < rl; r1++) // current
	{
		for (int c1 = 0; c1 < rc; c1++)
		{
			bool breakLoop = false;
			for (int r2 = 0; r2 < rl && !breakLoop; r2++) //goal
			{
				for (int c2 = 0; c2 < rc && !breakLoop; c2++)
				{
					if (!(r1==r2 && c1==c2))
					{
						Tile lthisVal = toCalculate.getState().operator()(r1, c1);
						Tile lIsVal = fSolved.getState().operator()(r2, c2);
						if (lthisVal.fValue == lIsVal.fValue)
						{
							int lDesinationR = abs(lthisVal.fR-lIsVal.fR);
							int lDestinationC = abs(lthisVal.fC - lIsVal.fC);
							int temp = (lDesinationR + lDestinationC);
							if (temp > 0)
							{
								lHeau += temp;
								breakLoop = true;
							}
						}
					}
				}
			}
		}
	}
	return lHeau;
}

void GBFSearchTree::CalculateCost(Node & toCalculate)
{
	toCalculate.setCost(CalculateHeuristic(toCalculate));
}

GBFSearchTree::GBFSearchTree(Node & aOriginal, Node & aSolved) : SearchTree(aOriginal,aSolved)
{
	CalculateCost(aOriginal);
	fFrontier.push(&aOriginal);
}

bool compaire_node(const Node* a, const Node* b)
{
	return a->getCost() < b->getCost();
}

void GBFSearchTree::Generate()
{
	//std::cout << "Nodes in the search map :      ";
	while (!fFrontier.empty())
	{
		Node& front = *fFrontier.front();
		std::vector<Node> newNodes = ExpandNode(front);
		for (int i = 0; i < newNodes.size(); i++)
		{
			bool repeated = SearchTree::CheckRepeated(newNodes[i].getHash());
			if (!repeated)
			{
				newNodes[i].setCost(front.getCost() + 1); //+1 in undoed in CalculateCost()
				CalculateCost(newNodes[i]);
				SearchTree::Nodes().push_back(newNodes[i]);
				SearchTree::AddHash(newNodes[i].getHash());
				Node& lastNode = SearchTree::Nodes().back();
				fFrontier.push(&lastNode); 
				if (newNodes[i] == fSolved)
				{
					SearchTree::fSolved = SearchTree::Nodes().back();
					return;
				}
			}
		}
		fFrontier.pop();

		//sort the frontiers on the order of cost
		list<Node*> tempList;
		int tempSize = fFrontier.size();
		for (int q = 0; q < tempSize;q++)
		{
			tempList.push_back(fFrontier.front());
			fFrontier.pop();
		}
		tempList.sort(compaire_node);
		for (std::list<Node*>::iterator it = tempList.begin(); it != tempList.end(); it++)
		{
			fFrontier.push(*it);
		}

		//if (SearchTree::Nodes().size() % 5000 == 1) std::cout << ".";
		//for (int i = 5; i > 0;i--) std::cout << "\b";
		//std::cout << setw(5) << SearchTree::Nodes().size();

		//printing frontiers
		//std::cout << "Order of frontiers" << endl;

	}
}


int GBFSearchTree::getFrontierCount()
{
	return fFrontier.size();
}

int GBFSearchTree::CalculateHeuristic(Node & aToCalculate)
{
	//Using Manhatten Distance and Displaced
	return CalculateDisplacedTiles(aToCalculate) + CalculateManhattanDistance(aToCalculate);
}
