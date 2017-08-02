#include "SearchTree.h";

using namespace std;

SearchTree::SearchTree(Node& aOriginal, Node& aSolved) :fSolved(aSolved)
{
	fNodes.push_back(aOriginal);
	fHashMap[(fNodes.begin())->getHash()] = true;
}

bool SearchTree::directionOutOfBound(Direction aDirection, Puzzle& aPuzzle, int nullID)
{
	Tile& lNullTile = aPuzzle.operator()(nullID);
	int lR = lNullTile.fR;
	int lC = lNullTile.fC;
	switch (aDirection)
	{
	case Direction::up:
		if (lR == 0) return true;
		break;
	case Direction::left:
		if (lC == 0) return true;
		break;
	case down:
		if (lR == aPuzzle.fNRows - 1) return true;
		break;
	case Direction::right:
		if (lC == aPuzzle.fNCols - 1) return true;
		break;
	}
	return false;
}

std::vector<Node> SearchTree::ExpandNode(Node& aToExpand)
{
	Direction lDirections[4] = {Direction::up,Direction::left,Direction::down,Direction::right};
	Puzzle lCurrentPuzzle = aToExpand.getState();
	std::vector<Node> newNodes;
	//Expand for each null tile
	for (int i = 0; i < lCurrentPuzzle.fNullCount;i++)
	{
		//Expand in each direction
		for each (Direction d in lDirections)
		{
			if (directionOutOfBound(d, aToExpand.getState(),i)) continue;
			Puzzle lCopyOfPuzzle (lCurrentPuzzle);
			Tile nullTile = lCopyOfPuzzle.operator()(i);
			lCopyOfPuzzle.Move(nullTile, d);
			Node* newNode = new Node (lCopyOfPuzzle, &aToExpand);
			newNode->addDirection(i,d);
			//newNode->setCost(aToExpand.getCost()+1);
			newNodes.push_back(*newNode);
		}
	}

	return newNodes;
}

Node & SearchTree::getSolved()
{
	return fSolved;
}

void SearchTree::AddHash(string aHash)
{
	fHashMap[aHash] = true;
}

bool SearchTree::CheckRepeated(string aHashToCheck)
{
	return fHashMap[aHashToCheck];
}

std::vector<TileDirection> SearchTree::Resolve(Node & node)
{
	std::vector<TileDirection> directions;
	directions.push_back(node.getDirection());
	Node* parent = node.getParent();
	do
	{
		directions.push_back(parent->getDirection());
		parent = parent->getParent();
	} while (parent != NULL);
	return directions;
}



list<Node>& SearchTree::Nodes()
{
	return fNodes;
}

std::ostream & operator<<(std::ostream & aOStream, SearchTree & aObject)
{
	
	return aOStream;
}
