#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"
#include "Globals.h"

int numAI = -1;

void DoGameSetup()
{
	// Permanent darkness on this one.
	TethysGame::SetDaylightEverywhere(0);
	TethysGame::SetDaylightMoves(0);
	GameMap::SetInitialLightLevel(-32);

	// Next, we'll setup the in-game music
	SongIds X02Songs[] = { songEP51, songEP52, songEP41, songEden11 };
	TethysGame::SetMusicPlayList(4, 0, X02Songs);

	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		if (!Player[i].IsHuman() && numAI < 0)
		{
			numAI = i;
		}
	}

	// Automatically ally all human players with one another (and the AI "player" that disabled structures get transferred to)
	for (int i = 0; i < numAI; i++)
	{
		for (int j = 0; j < numAI; j++)
		{
			if (i != j)
			{
				Player[i].AllyWith(j);
			}
			Player[i].AllyWith(numAI + 1);
			Player[numAI + 1].AllyWith(i);
		}
	}

	// Setup AI
	SetupAI();
}

void SetupMiscObjects()
{
	Unit Unit1;
	TethysGame::PlaceMarker(Unit1, 12 + 31, 59 - 1, Circle);
}

void SetupInitRes(int pNo)
{
	// Give the player some free bonus upgrades based on difficulty level.
	// These will not transfer to the next level.
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Player[pNo].MarkResearchComplete(4002);		// Weapon damage upgrade
	case 1:
		Player[pNo].MarkResearchComplete(4001);		// Lynx speed upgrade
	case 2:
		Player[pNo].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant (just in case you didn't already get it)
		break;
	}
}
