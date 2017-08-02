#include "Solver.h"

Solver::Solver(int aR, int aC)
{
	/* Default Constructor assumes the following
		~ -bfs is set (using BFS SearchStrategy)
		~ -random set to true (random solvable sequence) -for quick test
		~ -s {solved-state} set to default (solved state is assumed to be incremental reading order)
	*/

	int* lSequence = new int[aR*aC];
	int* lInputSequence = randomSolvableSequence(aR, aC, RANDOME_MOVES);
	for (int i=0; i < aR*aC; i++) lSequence[i] = lInputSequence[i];

	int* lSolvedSequence = new int[aR*aC];

	for (int i = 0; i < aR*aC - 1; i++)
		lSolvedSequence[i] = i + 1;
	lSolvedSequence[aR*aC - 1] = 0;

	Solver(aR,aC,lSequence, lSolvedSequence,bfs);
}

Solver::Solver(int aR, int aC, SearchStrategy aStrategy)
{
	/* This Constructor assumes the following
	~ -random set to true (random solvable sequence) -for quick test
	~ -s {solved-state} set to default (solved state is assumed to be incremental reading order)
	*/
	int* lSequence = new int[aR*aC];
	int* lInputSequence = randomSolvableSequence(aR, aC, RANDOME_MOVES);
	for (int i = 0; i < aR*aC; i++)
		lSequence[i] = *(lInputSequence + i);

	int* lSolvedSequence = new int[aR*aC];

	for (int i = 0; i < aR*aC - 1; i++)
		lSolvedSequence[i] = i + 1;
	lSolvedSequence[aR*aC - 1] = 0;

	init(aR, aC, lSequence, lSolvedSequence, aStrategy);
}

Solver::Solver(int aR, int aC, int aSequence[])
{
	/* This Constructor assumes the following
	~ -bfs is set (using BFS SearchStrategy)
	~ -s {solved-state} set to default (solved state is assumed to be incremental reading order)
	*/

	int* lSolvedSequence = new int[aR*aC];

	for (int i = 0; i < aR*aC - 1; i++)
		lSolvedSequence[i] = i + 1;
	lSolvedSequence[aR*aC - 1] = 0;

	init(aR, aC, aSequence, lSolvedSequence, bfs);
}

Solver::Solver(int aR, int aC, int aSequence[], SearchStrategy aStrategy)
{
	/* This Constructor assumes the following
	~ -s {solved-state} set to default (solved state is assumed to be incremental reading order)
	*/

	int* lSolvedSequence = new int[aR*aC];

	for (int i = 0; i < aR*aC - 1; i++)
		lSolvedSequence[i] = i + 1;
	lSolvedSequence[aR*aC - 1] = 0;

	init(aR, aC, aSequence, lSolvedSequence, aStrategy);
}

Solver::Solver(int aR, int aC, int aSequence[], int aSolvedSequence[], SearchStrategy aStrategy)
{
	init(aR,aC, aSequence, aSolvedSequence, aStrategy);
}

void Solver::init(int aR, int aC, int aSequence[], int aSolvedSequence[], SearchStrategy aStrategy)
{
	/* This is the Full constructor, this assumes nothing */

	//Check if the sequence is valid
	//if (sizeof(aSequence) != aR*aC) throw runtime_error("Invalid input sequence!");
	//if (sizeof(aSolvedSequence) != aR*aC) throw runtime_error("Invalid solved sequence!");

	//Checking if the puzzles are valid
	Puzzle lPuzzle(aR, aC, aSequence);
	Puzzle lSolved(aR, aC, aSolvedSequence);
	if (!lPuzzle.isValidPuzzle())  throw ("Invalid input puzzle! " + (lPuzzle.areThereDuplicates()) ? "\n - duplcates found" : "" + (!lPuzzle.areThereNull()) ? "\n - no empty tills found" : "" + (lPuzzle.areThereExceeds()) ? "\n - tiles exceeding maximum value found" : "");
	if (!lSolved.isValidPuzzle())  throw ("Invalid solved puzzle! " + (lPuzzle.areThereDuplicates()) ? "\n - duplcates found" : "" + (!lPuzzle.areThereNull()) ? "\n - no empty tills found" : "" + (lPuzzle.areThereExceeds()) ? "\n - tiles exceeding maximum value found" : "");

	/*
	Checking if a valid stategy
	~ Defaults to BFS
	*/
	SearchStrategy lUserStrategy;
	if (aStrategy == dfs) lUserStrategy = SearchStrategy::dfs;
	else if (aStrategy == bfs) lUserStrategy = SearchStrategy::bfs;
	else if (aStrategy == gbfs) lUserStrategy = SearchStrategy::gbfs;
	else if (aStrategy == astar) lUserStrategy = SearchStrategy::astar;
	else if (aStrategy == xs) lUserStrategy = SearchStrategy::xs;
	else SearchStrategy::bfs;

	fStrategy = aStrategy;

	//Preparing the initial node and solved node
	Node* lOriginalNode = new Node(lPuzzle);
	Node* lSolvedNode = new Node(lSolved);

	//Instantiating the Tree based on strategy

	switch (lUserStrategy)
	{
	case bfs:
		fTree = new BFSearchTree(*lOriginalNode, *lSolvedNode);
		break;
	case dfs:
		fTree = new DFSearchTree(*lOriginalNode, *lSolvedNode);
		break;
	case gbfs:
		fTree = new GBFSearchTree(*lOriginalNode, *lSolvedNode);
		break;
	case astar:
		fTree = new AStarSearchTree(*lOriginalNode, *lSolvedNode);
		break;
	case xs:
		fTree = new XSearchTree(*lOriginalNode, *lSolvedNode);
		break;
	}


	//Push statistic
	string StrategyString[] = { "BFS", "DFS", "GBFS", "A*", "XS" };
	fStatistics["strategy"] = StrategyString[lUserStrategy];
}

void Solver::Solve()
{
	cout << "Solving" << endl;
	SearchTree& solvedTree = *fTree;
	clock_t start = clock(), diff; //start clock
	solvedTree.Generate();
	diff = clock() - start; //stop clock
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	std::vector<TileDirection> d = solvedTree.Resolve(solvedTree.getSolved());

	fStatistics["time"] = to_string((msec / (1000)))+ "secs " + to_string(msec % (1000))+ "ms";
	fStatistics["nodes"] = to_string(solvedTree.Nodes().size());
	fStatistics["frontiers"] = to_string(solvedTree.getFrontierCount());
	fStatistics["steps"] = to_string(d.size() - 1);

	string tempDirection = "";
	string directions[] = { "UP", "LEFT", "DOWN", "RIGHT" };

	for (int j = d.size() - 2; j >= 0; j--)
	{
		tempDirection += (char)(d[j].fN + 'A');
		tempDirection += " - "+directions[d[j].fD]+"\n";
	}
	fStatistics["moves"] = tempDirection;
}

std::ostream & operator<<(std::ostream & aOStream, Solver & aObject)
{
	map<string, string>::iterator it;

	for (it = aObject.fStatistics.begin(); it != aObject.fStatistics.end(); it++)
	{
		if(it->first!="moves")
			aOStream << it->first << " : "<< it->second << std::endl;
	}

	cout << endl << "moves: " << endl << aObject.fStatistics["moves"];

	return aOStream;
}

std::ostream & operator>>(Solver & aObject, std::ostream & aOStream)
{
	aOStream << "Requested a " << aObject.fTree->getSolved().getState().fNRows << "x" << aObject.fTree->getSolved().getState().fNCols << " puzzle" << endl;

	aOStream << "Solving using ";
	switch (aObject.fStrategy)
	{
	case bfs:
		aOStream << "BFS (Breath-first search)" << endl;
		break;
	case dfs:
		aOStream << "DFS (Depth-first search)" << endl;
		break;
	case gbfs:
		aOStream << "GBFS (Greedy-best-first search)" << endl;
		break;
	case astar:
		aOStream << "A* (A-Star search)" << endl;
		break;
	case xs:
		aOStream << "XS (X search)" << endl;
		break;
	}

	//What it looks like
	SearchTree& solvedTree = *aObject.fTree;
	Puzzle lPuzzle = solvedTree.Nodes().front().getState();
	aOStream << endl << lPuzzle << endl;
	
	//To look like 
	aOStream << endl << "to" << endl;
	lPuzzle = solvedTree.getSolved().getState();
	aOStream << endl << lPuzzle << endl;

	return aOStream;
}

map<string, string>& Solver::GetStatistics()
{
	return fStatistics;
}

std::vector<TileDirection> Solver::GetDirections()
{
	return fTree->Resolve(fTree->getSolved());
}

SearchTree & Solver::operator()()
{
	SearchTree& solvedTree = *fTree;
	return solvedTree;
}

//Private Members

int* Solver::randomSolvableSequence(int aR, int aC, int aMoves)
{
	srand(time(0)); //set time as seed

	int* lSequence = new int[aR*aC];
	for (int i = 0; i < aR*aC - 1; i++)
		lSequence[i] = i + 1;
	lSequence[aR*aC - 1] = 0;

	Puzzle lRandomSolvable(aR, aC, lSequence);
	Direction lDirections[4] = { Direction::up,Direction::left,Direction::down,Direction::right };
	int move = 0;
	int premove = 0;
	//Move the puzzle random amount of times
	int randomNumberOfMoves = aMoves; //(rand() % 50 + 20);
	for (int i = 0; i<randomNumberOfMoves; i++)
	{
		while (premove != move)
		{
			move = (rand() % 4);
		}
		premove = move;
		Direction randomDirection = lDirections[(rand() % 4)];
		if (!lRandomSolvable.Move(lRandomSolvable.operator()(0), randomDirection))
			i--;
	}
	cout << endl;

	int i = 0;
	for (int r = 0; r < aR; r++)
	{
		for (int c = 0; c < aC; c++)
		{
			lSequence[i] = lRandomSolvable.fTiles[r][c].fValue;
			i++;
		}
	}

	return lSequence;
}

