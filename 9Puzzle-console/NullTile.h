#pragma once
#include <iostream>
#include "Tile.h"

class NullTile : public Tile
{
private:
public:
	// the default constructor (initializes all member variables) 
	NullTile(int aR, int aC);
	NullTile(const NullTile& aCopy);

	//Movement in 2D plane , returns false if unable to.
	bool MoveUp() const;
	bool MoveRight() const;
	bool MoveDown() const;
	bool MoveLeft() const;
};