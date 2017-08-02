#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Node.h"
#include <string>
#include "SearchTree.h"
#include "GBFSearchTree.h"

using namespace std;

class AStarSearchTree : public GBFSearchTree
{
private:
	void CalculateCost(Node& toCalculate);
public:
	// the default constructor
	AStarSearchTree(Node & aOriginal, Node & aSolved);

	//member function
	void Generate();
	int getFrontierCount();

	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);

};