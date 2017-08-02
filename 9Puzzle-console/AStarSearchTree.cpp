#include "AStarSearchTree.h"

void AStarSearchTree::CalculateCost(Node & toCalculate)
{
	toCalculate.setCost(CalculateHeuristic(toCalculate) + toCalculate.getCost());
}

AStarSearchTree::AStarSearchTree(Node & aOriginal, Node & aSolved): GBFSearchTree(aOriginal, aSolved)
{

}

bool compare_nodes(const Node* a, const Node* b)
{
	return a->getCost() < b->getCost();
}

void AStarSearchTree::Generate()
{
	GBFSearchTree::Generate();
}

int AStarSearchTree::getFrontierCount()
{
	return fFrontier.size();
}
