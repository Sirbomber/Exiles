#include <Outpost2DLL.h>
#include <HFL.h>

#include "GameSetup.h"

void DoGameSetup()
{
	// Game begins with the map in complete darkness.  Day/night cycle will be locked at night
	// until time "runs out" (at which point the Blight will spawn and AI units will begin moving eastward).
    TethysGame::SetDaylightEverywhere(0);
    GameMap::SetInitialLightLevel(-96);
    TethysGame::SetDaylightMoves(0);

	// Next, we'll setup the in-game music.  Something appropriately low-key and somber (then loop on the panic track)
	SongIds X05Songs[] = { songPlymth11, songStatic03, songEP62 };
	TethysGame::SetMusicPlayList(3, 2, X05Songs);
}

void SetupMiscObjects()
{
	// Target/beacon
	Unit Unit1;
	TethysGame::PlaceMarker(Unit1, 251+31, 13-1, Circle);
}
