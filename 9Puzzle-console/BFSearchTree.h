#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Node.h"
#include <string>
#include "SearchTree.h"

using namespace std;

class BFSearchTree : public SearchTree
{
private:
	queue<Node*> fFrontier;
public:
	// the default constructor
	BFSearchTree(Node & aOriginal, Node & aSolved);

	//member function
	void Generate();
	int getFrontierCount();

	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);

};