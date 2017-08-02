#include "Node.h";

using namespace std;

Node::Node (Puzzle& aPuzzle) :fState(aPuzzle)
{
	//fNID = "O";
	fCost = 0;
	fHash = aPuzzle.getHash();
}

Node::Node(Puzzle& aPuzzle, Node* aParent) :fState(aPuzzle), fParent(aParent)
{
	fHash = aPuzzle.getHash();
	fCost = fParent->getCost();
}

Puzzle& Node::getState()
{
	return fState;
}

std::string Node::getHash()
{
	return fHash;
}

Node * Node::getParent()
{
	return fParent;
}

TileDirection Node::getDirection()
{
	return fDirection;
}

int Node::getCost() const
{
	return fCost;
}

void Node::setCost(int aCost)
{
	fCost = aCost;
}

void Node::linkNode(Node* aLink)
{
	fParent = aLink;
}

void Node::addDirection(int aTileN, Direction aDirection)
{
	fDirection = { aTileN ,aDirection };
}

std::ostream & operator<<(std::ostream & aOStream, Node & aObject)
{
	//aOStream << "[" << aObject.fNID << "]" << " node " << "linked to {" << (aObject.fParent)->fNID << "}" ;
	aOStream << aObject.getHash() << ((aObject.getState().isSolved()) ? "(Solved)" : "") << endl;
	return aOStream;
}

bool operator==(Node & aLHS,const Node & aRHS)
{
	return aLHS.fHash==aRHS.fHash;
}

bool operator<(Node & aLHS, Node& aRHS)
{
	return (aLHS.fCost < aRHS.fCost);
}
