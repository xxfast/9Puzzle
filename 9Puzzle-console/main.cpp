#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Puzzle.h"
#include "main.h"
#include "Solver.h"
#include "SearchTree.h"
#include "BFSearchTree.h"
#include "DFSearchTree.h"
#include "GBFSearchTree.h"
#include "AStarSearchTree.h"

#define MIN_TILE_SIZE 50
#define MAX_TILE_SIZE 100

//3 3 5 1 6 4 3 8 2 0 7 -render
//3 3 6 7 4 1 5 3 8 0 2 -s 3 4 2 1 8 7 6 0 5 -render
using namespace std;

void manual()
{
	cout << "Usage: 9Puzzle rows cols [-random] {sequence} [-s {solved-state}] [-bfs|dfs|bgfs|astar|x] [-render] " << endl;
	cout << "\trows \t\t\t" << ": number of rows of the puzzle to solve" << endl;
	cout << "\tcols \t\t\t" << ": number of columns of the puzzle to solve" << endl;
	cout << "\t[-random] \t\t" << ": feeling lazy? solvable random sequence of numbers (optional)" << endl;
	cout << "\t{sequence} \t\t" << ": sequence of tiles in reading order, 0 denoting empty slot(s)" << endl;
	cout << "\t[-s {solved-state}] \t" << ": sequence of tiles of the solved state, in reading order (optional)" << endl;
	cout << "\t[-bfs|dfs|bgfs|astar] \t" << ": algorithm to search (optional - defaults to bfs)" << endl;
	cout << "\t[-render] \t\t" << ": render the solve (optional - defaults to false)" << endl;
	cout << endl;
	cout << "--- Batch Mode" << endl;
	cout << "Usage: 9Puzzle <filepath> [-bfs|dfs|bgfs|astar] [-render] " << endl;
	cout << "\t<filepath> \t\t\t" << ": batch file path" << endl;
	cout << "\t[-bfs|dfs|bgfs|astar] \t" << ": algorithm to search (optional - defaults to bfs)" << endl;
	cout << "\t[-render] \t\t" << ": render the solve (optional - defaults to false)" << endl;
}

std::vector<string> split(string str, char delimiter)
{
	std::vector<string> lToReturn;
	stringstream ss(str);
	string tok;
	while (getline(ss, tok, delimiter))
		lToReturn.push_back(tok);
	return lToReturn;
}

int main(int argc, char* argv[])
{
	cout << "9PuzzleI/O - by xxfast " << endl;

	if (argc < 2)
	{
		cerr << "Missing argument!" << endl;
		cerr << "Usage: 9Puzzle <rows> <cols> [-random] {sequence} [-s {solved-state}] -bfs|dfs|bgfs|astar|xs [-limit] [-render] " << endl;
		cerr << " - Use 9Puzzle help for complete manual" << endl;
		return 1;
	}

	// Print Manual if asked

	string input = argv[1];
	if (input == "help" || input == "man")
	{
		manual();
		return 1;
	}

	//check for batch mode
	bool batchMode = false;
	
	input = argv[1];
	size_t found = input.find(".txt");

	ifstream lInputFile;
	if (found != std::string::npos)
	{
		batchMode = true;
		lInputFile.open(argv[1], ifstream::in);
		if (!lInputFile.good())
		{
			cerr << "Invalid File! "<< input << endl;
			cout << "Usage: 9Puzzle <filepath> [-bfs|dfs|bgfs|astar|xs] [-render] " << endl;
			cerr << " - Use 9Puzzle help for complete manual" << endl;
			return 1;
		}
	}

	//Handling argument input

	//User requested puzzle size
	int lR, lC;
	if (!batchMode)
	{
		lR = atoi(argv[1]);
		lC = atoi(argv[2]);
	}
	else
	{
		lInputFile >> input;
		std::vector<string> inputs = split(input,'x');
		lR = atoi(inputs[0].c_str());
		lC = atoi(inputs[1].c_str());
	}

	int* lSequence = new int[lR*lC];
	int* lSolvedSequence = new int[lR*lC];
	
	if (!batchMode) if(argc>=4) input = argv[3];

	//User feeling lazy, wants a solvable random sequence
	bool lRandom = false;
		
	if (!batchMode)
		lRandom = (input == "-random");

	//User provided a sequence
	if (!lRandom)
	{
		if (!batchMode)
		{
			for (int i = 0; i < lR*lC; i++)
				lSequence[i] = atoi(argv[i + 3]);
		}
		else 
		{
			for (int i = 0; i < lR*lC; i++)
			{
				lInputFile >> input;
				lSequence[i] = atoi(input.c_str());
			}
		}
	}
		
	//User also provided a solved state for non-random sequence
	bool expectSolved = false;
	if (!lRandom)
	{
		if (!batchMode)
		{
			input = argv[3 + (lR*lC)];
			expectSolved = (input == "-s");
			if (expectSolved)
				for (int i = 0; i < lR*lC; i++)
					lSolvedSequence[i] = atoi(argv[3 + lR*lC + 1 + i]);
		}
		else
		{
			for (int i = 0; i < lR*lC; i++)
			{
				lInputFile >> input;
				lSolvedSequence[i] = atoi(input.c_str());
			}
			expectSolved = true;
		}
	}
	//Should I render?
	input = argv[argc - 1];
	bool lRender = (input == "-render");

	//User asked for a strategy
	SearchStrategy lUserStrategy = SearchStrategy::bfs;
	if (lRender)
		input = argv[argc - 2];
	else
		input = argv[argc - 1];
	if (input == "-dfs") lUserStrategy = SearchStrategy::dfs;
	else if (input == "-bfs") lUserStrategy = SearchStrategy::bfs;
	else if (input == "-gbfs") lUserStrategy = SearchStrategy::gbfs;
	else if (input == "-astar") lUserStrategy = SearchStrategy::astar;
	else if (input.find("x")!= std::string::npos) lUserStrategy = SearchStrategy::xs;
	else SearchStrategy::bfs;

	//Generate solvers!
	Solver* lAgent;

	try
	{
		if (lRandom)
		{
			lAgent = new Solver(lR, lC, lUserStrategy);
		}
		else
		{
			if (!expectSolved)
			{
				lAgent = new Solver(lR, lC, lSequence, lUserStrategy);
			}
			else
			{
				lAgent = new Solver(lR, lC, lSequence, lSolvedSequence, lUserStrategy);
			}
		}
	}
	catch (const char* e) 
	{
		cerr << e <<endl;
		return 1;
	}
	//Outputing the request
	*lAgent >> cout;
	lAgent->Solve();
	//Outputing the statisics
	cout << *lAgent;

	return 0;
}

