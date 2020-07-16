#include <Outpost2DLL.h>
#include <HFL.h>

#include "GameSetup.h"

void DoGameSetup()
{
	// Unit mission - morale setting irrelevant

	// Game should start just as the sun sets.  Day/night cycle will be locked at night
	// until [a time limit/a certain checkpoint is reached] (at which point the Blight will spawn).
    TethysGame::SetDaylightEverywhere(0);
    GameMap::SetInitialLightLevel(-96);
    TethysGame::SetDaylightMoves(0);

	// Next, we'll setup the in-game music.  Something appropriately low-key and somber.
	SongIds X05Songs[] = { songEden11, songPlymth12, songEden31, songEden33, songEP51, songPlymth21 }; // currently copied from X04 -- update!
	TethysGame::SetMusicPlayList(6, 1, X05Songs);
}

void SetupMiscObjects()
{
	// Target/beacon
	Unit Unit1;
	TethysGame::PlaceMarker(Unit1, 251+31, 13-1, Circle); // temp coordinates
}

void SetupDisasters()
{
	//CreateTimeTrigger(1, 0, 4100, 4900, "Quakes");
	//CreateTimeTrigger(1, 0, 5200, 5600, "Storms");
}
