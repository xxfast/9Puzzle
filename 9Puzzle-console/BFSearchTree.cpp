#include "BFSearchTree.h"
#include <iomanip>

BFSearchTree::BFSearchTree(Node & aOriginal, Node & aSolved) :SearchTree(aOriginal, aSolved)
{
	fFrontier.push(&aOriginal);
}

void BFSearchTree::Generate()
{
	while (!fFrontier.empty())
	{
 		std::vector<Node> newNodes = ExpandNode(*fFrontier.front());
		for (int i = 0; i < newNodes.size(); i++)
		{ 
			if (!SearchTree::CheckRepeated(newNodes[i].getHash()))
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
		fFrontier.pop();
	}
}

int BFSearchTree::getFrontierCount()
{
	return fFrontier.size();
}

