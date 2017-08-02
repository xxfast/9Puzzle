#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "SearchTree.h"
#include "BFSearchTree.h"
#include "DFSearchTree.h"
#include "GBFSearchTree.h"
#include "AStarSearchTree.h"
#include "XSearchTree.h"

using namespace std;

#define RANDOME_MOVES 42

class Solver 
{
private:
	SearchTree* fTree;
	SearchStrategy fStrategy;
	map<string, string> fStatistics;
	void Solver::init(int aR, int aC, int aSequence[], int aSolvedSequence[], SearchStrategy aStrategy);
	int* Solver::randomSolvableSequence(int aR, int aC, int aMoves);
public:
	// all constructors
	Solver(int aR, int aC);
	Solver(int aR, int aC, int aSequence[]);
	Solver(int aR, int aC, SearchStrategy aStrategy);
	Solver(int aR, int aC, int aSequence[], SearchStrategy aStrategy);
	Solver(int aR, int aC, int aSequence[], int aSolvedSequence[], SearchStrategy aStrategy);

	//member function
	void Solve();
	map<string,string>& GetStatistics();
	std::vector<TileDirection> GetDirections();

	//operators
	SearchTree& operator()();

	//friend operators
	friend std::ostream& operator<<(std::ostream& aOStream, Solver& aObject); //Results Printer
	friend std::ostream& operator>>(Solver& aObject, std::ostream& aOStream); //Request Printer

};