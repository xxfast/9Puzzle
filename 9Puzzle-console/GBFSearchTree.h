#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include "Node.h"
#include <string>
#include "SearchTree.h"

using namespace std;

class GBFSearchTree : public SearchTree
{
protected:
	int CalculateDisplacedTiles(Node& toCalculate);
	int CalculateManhattanDistance(Node& toCalculate);
	//To be overidden by A*
	virtual void CalculateCost(Node& toCalculate);
	queue<Node*> fFrontier;
private:
public:
	// the default constructor
	GBFSearchTree(Node & aOriginal, Node & aSolved);

	//member function
	void Generate();
	int getFrontierCount();
	int CalculateHeuristic(Node& aToCalculate);
	
	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);

};