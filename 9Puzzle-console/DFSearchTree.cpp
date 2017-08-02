#include "DFSearchTree.h"

DFSearchTree::DFSearchTree(Node & aOriginal, Node & aSolved) :SearchTree(aOriginal, aSolved)
{
	fFrontier.push(&aOriginal);
}

void DFSearchTree::Generate()
{
	//std::cout << "Nodes in the search map :      ";
	while (!fFrontier.empty())
	{
		std::vector<Node> newNodes = ExpandNode(*fFrontier.top());
		fFrontier.pop();
		for (int i = 0; i < newNodes.size(); i++)
		{
			bool repeated = SearchTree::CheckRepeated(newNodes[i].getHash());
			if (!repeated)
			{
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
		//if (SearchTree::Nodes().size() % 5000 == 1) std::cout << ".";
		//for (int i = 5; i > 0;i--) std::cout << "\b";
		//std::cout << setw(5) << SearchTree::Nodes().size();
	}
}

int DFSearchTree::getFrontierCount()
{
	return fFrontier.size();
}
