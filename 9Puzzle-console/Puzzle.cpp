#include "Puzzle.h"

Puzzle::Puzzle(int aNRows, int aNCols, int sequence[]) :fNRows(aNRows), fNCols(aNCols), fNullCount(0)
{
	//Generating the cells
	int i = 0;
	fTiles.resize(aNRows);
	for (int r = 0; r < fNRows; r++ )
	{
		fTiles[r].resize(aNCols);
		for (int c = 0; c < fNCols; c++)
		{
			fTiles[r][c] = {r, c, sequence[i++],-1};
			if (fTiles[r][c].fValue == 0)
			{
				fTiles[r][c].fN = fNullCount;
				fNullCount++;
			}
		}
	}
}

Puzzle::Puzzle(const Puzzle & toCopy):fNRows(toCopy.fNRows),fNCols(toCopy.fNCols), fNullCount(0)
{
	fTiles.resize(fNRows);
	for (int r = 0; r < toCopy.fNRows; r++)
	{
		fTiles[r].resize(fNCols);
		for (int c = 0; c < toCopy.fNCols; c++)
		{
			fTiles[r][c] = toCopy.fTiles[r][c];
			if (fTiles[r][c].fValue == 0)
			{
				fNullCount++;
			}
		}
	}
 	int i = 0;
}

void Puzzle::swapPlaces(Tile& aTile1, Tile& aTile2)
{
	int tempVal = aTile1.fValue;
	int NVal = aTile1.fN;
	aTile1.fValue = aTile2.fValue;
	aTile1.fN = aTile2.fN;
	aTile2.fValue = tempVal;
	aTile2.fN = NVal;
}

bool Puzzle::checkBounds(Tile destination) const
{
	return destination.fR>=0 && destination.fR<=fNRows-1 
		&& destination.fC>=0 && destination.fC<=fNCols-1;
}

bool Puzzle::Move(Tile aTile, Direction aDirection)
{
	//asuming aTile is a always a 0 tile
	if (aTile.fValue != 0) return false;
	Tile lTarget;
	switch (aDirection)
	{
	case up:
		lTarget = { aTile.fR - 1,aTile.fC };
		break;
	case right:
		lTarget = { aTile.fR,aTile.fC +1 };
		break;
	case down:
		lTarget = { aTile.fR + 1 ,aTile.fC};
		break;
	case left:
		lTarget = { aTile.fR,aTile.fC -1 };
		break;
	default:
		return false;
		break;
	}
	if (!checkBounds(lTarget)) return false;
	swapPlaces(fTiles[aTile.fR][aTile.fC], fTiles[lTarget.fR][lTarget.fC]);
	return true;
}

bool Puzzle::areThereExceeds() const
{
	int maxTileNumber = (fNRows * fNCols) - 1;
	for (int r = 0; r < fNRows; r++)
	{
		for (int c = 0; c < fNCols; c++)
		{
			if (fTiles[r][c].fValue>maxTileNumber)
			{
				return true;
			}
		}
	}
	return false;
}

bool Puzzle::areThereNull() const
{
	for (int r = 0; r < fNRows; r++)
	{
		for (int c = 0; c < fNCols; c++)
		{
			if (fTiles[r][c].fValue==0)
			{
				return true;
			}
		}
	}
	return false;
}

bool Puzzle::areThereDuplicates() const
{
	for (int r1 = 0; r1 < fNRows; r1++)
	{
		for (int c1 = 0; c1 < fNCols; c1++)
		{
			for (int r2 = 0; r2 < fNRows; r2++)
			{
				for (int c2 = 0; c2 < fNCols; c2++)
				{
					if (!((r1 == r2) && (c1 == c2)))
					{
						if (fTiles[r1][c1].fValue == fTiles[r2][c2].fValue)
						{
							if(fTiles[r1][c1].fValue != 0)
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Puzzle::isValidPuzzle() const
{
	return (!areThereDuplicates() && 
			!areThereExceeds() && 
			areThereNull());
}

bool Puzzle::isSolved() const
{
	int lPreVal = 0;
	bool reachedMax = false;
	for (int r = 0; r < fNRows; r++)
	{
		for (int c = 0; c < fNCols; c++)
		{
			if (fTiles[r][c].fValue != lPreVal + 1)
			{
				if (fTiles[r][c].fValue != 0)
				{
					return false;
				}
			}
			lPreVal = fTiles[r][c].fValue;
		}
	}
	return true;
}

std::string Puzzle::getHash() const
{
	std::string Result = "";
	std::string out = "";
	for (int r = 0; r < fNRows; r++)
	{
		for (int c = 0; c < fNCols; c++)
		{
			std::stringstream convert;
			convert << fTiles[r][c].fValue;
			Result = convert.str();
			out+= Result;
		}
	}
	return out;
}

//Tile Selector
Tile Puzzle::operator()(int r, int c)
{
	return fTiles[r][c];
}

//i'th NullTile Selector
Tile Puzzle::operator()(int i)
{
	for (int r = 0; r < fNRows; r++)
	{
		for (int c = 0; c < fNCols; c++)
		{
			if (fTiles[r][c].fN == i)
			{
				return fTiles[r][c];
			}
		}
	}
} 


std::ostream & operator<<(std::ostream & aOStream, const Puzzle & aObject)
{
	int width = std::to_string(aObject.fNRows * aObject.fNCols).size()+1;
	for (int r = 0; r < aObject.fNRows; r++)
	{
		for (int c = 0; c < aObject.fNCols; c++)
		{

			aOStream << std::setw(width) << aObject.fTiles[r][c].fValue ;
		}
		aOStream << std::endl;
	}
	return aOStream;
}

bool operator==(Puzzle & aLHS, Puzzle & aRHS)
{
	if (aLHS.fNCols != aRHS.fNCols) return false;
	if (aLHS.fNRows != aRHS.fNRows) return false;
	
	for (int r = 0; r < aRHS.fNRows; r++)
	{
		for (int c = 0; c < aRHS.fNCols; c++)
		{
			if (!(aLHS.fTiles[r][c].fValue == aRHS.fTiles[r][c].fValue))
			{
				return false;
			}
		}
	}
	return true;
}
