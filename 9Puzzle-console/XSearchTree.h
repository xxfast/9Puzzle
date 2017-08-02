#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Node.h"
#include <string>
#include "SearchTree.h"
#include "GBFSearchTree.h"

using namespace std;

class XSearchTree : public GBFSearchTree
{
private:
	void CalculateCost(Node& toCalculate);
	bool compare_nodes(const Node* a, const Node* b);
public:
	// the default constructor
	XSearchTree(Node & aOriginal, Node & aSolved);

	//member function
	void Generate();
	int getFrontierCount();

	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);
};