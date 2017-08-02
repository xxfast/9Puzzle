#include "XSearchTree.h"

XSearchTree::XSearchTree(Node & aOriginal, Node & aSolved) : GBFSearchTree(aOriginal, aSolved)
{
}

bool XSearchTree::compare_nodes(const Node* a, const Node* b)
{
	return a->getCost() < b->getCost();
}

void XSearchTree::Generate()
{
	GBFSearchTree::Generate();
}

int XSearchTree::getFrontierCount()
{
	return fFrontier.size();
}

void XSearchTree::CalculateCost(Node & toCalculate)
{
	toCalculate.setCost(CalculateHeuristic(toCalculate) + toCalculate.getParent()->getCost());
}