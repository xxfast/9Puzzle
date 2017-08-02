#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Puzzle.h"
#include <string>

using namespace std;

struct TileDirection
{
	int fN;
	Direction fD;
};

class Node
{
private:
	//string fNID;
	Node* fParent = NULL; //no parent for the first node :(
	Puzzle fState;
	int fCost;
	TileDirection fDirection;
	string fHash;
public:
	Node(Puzzle& aPuzzle); //Original node
	Node(Puzzle& aPuzzle, Node* aParent);

	//Getters and setters
	Puzzle& getState();
	std::string getHash();
	Node* getParent();
	TileDirection getDirection();
	int getCost() const;
	void setCost(int aCost);

	// Member functions
	void linkNode(Node* aLink);
	void addDirection(int aTileN, Direction aDirection);

	//friends
	friend std::ostream& operator<<(std::ostream& aOStream, Node& aObject);
	friend bool operator==(Node& aLHS, const Node& aRHS);
	friend bool operator<(Node& aLHS, Node& aRHS);

};