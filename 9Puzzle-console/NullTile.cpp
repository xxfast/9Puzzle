#include "NullTile.h"

using namespace std;

NullTile::NullTile(int aR, int aC):Tile(aR,aC, 0)
{
}

NullTile::NullTile(const NullTile & aCopy) : Tile((Tile)aCopy)
{
}

//Movement related code
bool NullTile::MoveUp() const
{
	return true;
}

bool NullTile::MoveRight() const
{
	return true;
}

bool NullTile::MoveDown() const
{
	return true;
}

bool NullTile::MoveLeft() const
{
	return true;
}


