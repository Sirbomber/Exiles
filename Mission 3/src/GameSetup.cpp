#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "GameSetup.h"

void DoGameSetup()
{
	// For mission 3, morale will always be forced at fair.
	TethysGame::ForceMoraleOK(-1);

	// Force the day/night cycle.
    TethysGame::SetDaylightEverywhere(0);
    GameMap::SetInitialLightLevel(32);
    TethysGame::SetDaylightMoves(1);

	// Next, we'll setup the in-game music
	SongIds X03Songs[] = { songEden21, songPlymth33, songStatic04, songEP41, songEP43, songEden31 };
	TethysGame::SetMusicPlayList(6, 1, X03Songs);
}

void SetupDisasters()
{
	CreateTimeTrigger(1, 0, 2700, 4100, "Storms");
}

void Storms()
{
	LOCATION start,
		     end;

	switch (TethysGame::GetRand(3))
	{
		case 0:
			start.x = 60 + (TethysGame::GetRand(7) - TethysGame::GetRand(12));
			start.y = 6 + (TethysGame::GetRand(4) - TethysGame::GetRand(6));
			end.x = 136;
			end.y = 54 + (TethysGame::GetRand(10) - TethysGame::GetRand(14));
			break;
		case 1:
			start.x = 34 + (TethysGame::GetRand(13) - TethysGame::GetRand(13));
			start.y = 41 + (TethysGame::GetRand(9) - TethysGame::GetRand(9));
			end.x = 88 + (TethysGame::GetRand(16) - TethysGame::GetRand(20));
			end.y = 128;
			break;
		case 2:
			start.x = 116 + (TethysGame::GetRand(11) - TethysGame::GetRand(8));
			start.y = 115 + (TethysGame::GetRand(9) - TethysGame::GetRand(6));
			if (TethysGame::GetRand(2) == 0)
			{
				end.x = TethysGame::GetRand(128);
				end.y = 0;
			}
			else
			{
				end.x = -1;
				end.y = TethysGame::GetRand(101);
			}
			break;
		default:
			start.x = 100;
			start.y = 100;
			end.x = 100;
			end.y = 100;
			break;
	}

	TethysGame::SetLightning(start.x+31, start.y-1, TethysGame::GetRand(3)+5, end.x+31, end.y-1);
}
