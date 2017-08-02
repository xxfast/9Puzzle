#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Node.h"
#include <string>
#include "SearchTree.h"

using namespace std;

class DFSearchTree : public SearchTree
{
private:
	stack<Node*> fFrontier;

public:
	// the default constructor
	DFSearchTree(Node & aOriginal, Node & aSolved);

	//member function
	void Generate();
	int getFrontierCount();

	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);

};