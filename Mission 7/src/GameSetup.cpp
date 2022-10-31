#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types.h>
#include <vector>

#include "GameSetup.h"
#include "MissionEnd.h"
#include "Bases.h"

void DoGameSetup()
{
	// For mission 7, morale starts locked at fair because the starting base is in rough shape, but that doesn't last long.
	TethysGame::ForceMoraleOK(-1);
	CreateTimeTrigger(1, 1, 5700, "UnsteadyMorale");

	// Force the day/night cycle.
    TethysGame::SetDaylightEverywhere(0);
    GameMap::SetInitialLightLevel(12);
    TethysGame::SetDaylightMoves(1);

	// Next, we'll setup the in-game music
	SongIds X07Songs[] = { songEden11, songEP41, songEP43, songEden33, songStatic04, songEP61 };
	TethysGame::SetMusicPlayList(6, 0, X07Songs);
}

Export void UnsteadyMorale()
{
	TethysGame::FreeMoraleLevel(-1);
}