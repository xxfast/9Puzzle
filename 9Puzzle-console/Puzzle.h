#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

struct Tile
{
	int fR;
	int fC;
	int fValue;
	int fN; 
};


enum Direction { up=0, left=1, down=2, right=3 };

class Puzzle
{
private:
	bool checkBounds(Tile destination) const;

public:
	int fNRows;
	int fNCols;
	std::vector<std::vector<Tile> > fTiles;
	int fNullCount;
	
	// the default constructor (initializes all member variables) 
	Puzzle(int aNRows, int aNCols, int sequence[]);
	//copy constuctor
	Puzzle(const Puzzle& toCopy);

	//Setters
	bool Move(Tile aTile, Direction aDirection);

	//Getters
	bool areThereDuplicates() const;
	bool areThereExceeds() const;
	bool areThereNull() const;
	bool isValidPuzzle() const;
	bool isSolved() const;
	std::string getHash() const;

	//member functions
	void swapPlaces(Tile& aTile1, Tile& aTile2);

	//operators
	Tile operator()(int r, int c); //Tile selector
	Tile operator()(int i); //NullTile selector

	//friends
	friend std::ostream& operator<<(std::ostream& aOStream, const Puzzle& aObject);
	friend bool operator==(Puzzle& aLHS,Puzzle& aRHS);
};