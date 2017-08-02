#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "Node.h"
#include <string>
#include <time.h>
#include <map>

using namespace std;

enum SearchStrategy {bfs,dfs,gbfs,astar,xs};

class SearchTree 
{
protected:
	Node& fSolved;
private:
	std::list<Node> fNodes;
	map<string, bool> fHashMap;
	bool directionOutOfBound(Direction aDirection, Puzzle& aPuzzle, int nullID);

public:
	// the default constructor
	SearchTree(Node& aOriginal, Node& aSolved);

	//member functions
	virtual void Generate() = 0;
	std::vector<Node> ExpandNode(Node& aToExpand);
	bool CheckRepeated(string aHashToCheck);
	std::vector<TileDirection> Resolve(Node& node);

	//getters and setters
	Node& getSolved();
	void AddHash(string aHash);
	virtual int getFrontierCount() = 0;

	//operators
	list<Node>& Nodes(); //node list selector
	
	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, SearchTree& aObject);

};