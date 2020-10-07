#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"
#include "MissionEnd.h"

void DoGameSetup()
{
	// For mission 4, morale is unlocked.
	TethysGame::FreeMoraleLevel(-1);

	// Force the day/night cycle.
    TethysGame::SetDaylightEverywhere(0);
    GameMap::SetInitialLightLevel(32);
    TethysGame::SetDaylightMoves(1);

	// Next, we'll setup the in-game music
	SongIds X04Songs[] = { songEden11, songPlymth12, songEden31, songEden33, songEP51, songPlymth21 };
	TethysGame::SetMusicPlayList(6, 1, X04Songs);
}

void SetupMiscObjects()
{
	// The mining beacons exist regardless of # of players, so I stuck ore placement in here.
	TethysGame::CreateBeacon(mapMiningBeacon, 43 + 31, 72 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 76 + 31, 72 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 78 + 31, 46 - 1, 0, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 43 + 31, 34 - 1, 0, 1, -1);

	TethysGame::CreateBeacon(mapMiningBeacon, 32 + 31, 78 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 71 + 31, 83 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 25 + 31, 30 - 1, 1, 1, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 90 + 31, 42 - 1, 1, 1, -1);

	TethysGame::CreateBeacon(mapFumarole, 19 + 31, 23 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 97 + 31, 45 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 51 + 31, 76 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 16 + 31, 60 - 1, -1, -1, -1);

	TethysGame::CreateBeacon(mapMagmaVent, 36 + 31, 14 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 97 + 31, 71 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 71 + 31, 22 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapMagmaVent, 20 + 31, 75 - 1, -1, -1, -1);
	

	// Extra beacons
	TethysGame::CreateBeacon(mapMiningBeacon, 72 + 31, 120 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 103 + 31, 25 - 1, 1, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 30 + 31, 120 - 1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 117 + 31, 111 - 1, 1, 2, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 29 + 31, 7 - 1, 0, 2, -1);
}

void SetLavaAllowed()
{
	int x, y,
		tile;
	
	LOCATION mapsize(512,512);                         // create a point wayoff the map
	mapsize.Clip();                                      // clip it, so we have the mapsize

	for (y = 0; y < mapsize.y; y++)                          // run through all rows
	{
		for (x = 0; x < mapsize.x; x++)                    // check every tile on each row
		{
			// Get current tile's cell type
			tile = GameMap::GetCellType(LOCATION(x, y));
			
			// Set all M2/S1/S2 tiles to allow lava
			if (tile == cellSlowPassible1 ||
				tile == cellSlowPassible2 ||
				tile == cellMediumPassible2)
			{
				GameMap::SetLavaPossible(LOCATION(x, y), true);
			}
		}
	}

	// Manually mark these
	GameMap::SetLavaPossible(LOCATION(244+31, 73-1), TRUE);
	GameMap::SetLavaPossible(LOCATION(244+31, 74-1), TRUE);
	GameMap::SetLavaPossible(LOCATION(244+31, 75-1), TRUE);
	GameMap::SetLavaPossible(LOCATION(233+31, 21-1), TRUE);
	GameMap::SetLavaPossible(LOCATION(233+31, 22-1), TRUE);

} // end SetAllLava

void SetupDisasters()
{
	CreateTimeTrigger(1, 0, 4100, 4900, "Quakes");
	CreateTimeTrigger(1, 0, 5200, 5600, "Storms");
	CreateTimeTrigger(1, 1, 61001, "PrepVolcano1");
	CreateTimeTrigger(1, 1, 63007, "PrepVolcano2");
}

Export void PrepVolcano1()
{
	// Set lava flow animation
	SouthWestFlowAni(244+31, 72-1);

	// Set follow-up
	CreateTimeTrigger(1, 1, 7200, "EruptVolcano1");
}

Export void PrepVolcano2()
{
	// Set lava flow animation
	SouthFlowAni(233+31, 20-1);

	// Set follow-up
	CreateTimeTrigger(1, 1, 6000, "EruptVolcano2");
}

Export void EruptVolcano1()
{
	// Set eruption
	TethysGame::SetEruption(244+31, 73-1, 200);

	// Just an added touch.
	SetDefeatAvi("MPBL.AVI");

	// Set follow-up
	CreateTimeTrigger(1, 1, 1000, "StopVolcano1");
}

Export void EruptVolcano2()
{
	// Set eruption
	TethysGame::SetEruption(233+31, 21-1, 200);

	// Set follow-up
	CreateTimeTrigger(1, 1, 1000, "StopVolcano2");
}

Export void StopVolcano1()
{
	// Stop lava flow animation
	SouthWestFlowStopAni(244+31, 72-1);
}

Export void StopVolcano2()
{
	// stop lava flow animation
	SouthFlowStopAni(233+31, 20-1);
}

Export void Quakes()
{
	TethysGame::SetEarthquake(TethysGame::GetRand(139)+31+52, TethysGame::GetRand(128)-1, TethysGame::GetRand(2)+1);
}

Export void Storms()
{
	LOCATION start,
		     end;

	switch (TethysGame::GetRand(3))
	{
		case 0:
			start.x = 79 + (TethysGame::GetRand(7) - TethysGame::GetRand(12));
			start.y = 7 + (TethysGame::GetRand(4) - TethysGame::GetRand(6));
			end.x = 136;
			end.y = 123;
			break;
		case 1:
			start.x = 227 + (TethysGame::GetRand(13) - TethysGame::GetRand(13));
			start.y = 123 + (TethysGame::GetRand(4) - TethysGame::GetRand(4));
			end.x = 145;
			end.y = 5;
			break;
		case 2:
			start.x = 23 + (TethysGame::GetRand(11) - TethysGame::GetRand(8));
			start.y = 39 + (TethysGame::GetRand(9) - TethysGame::GetRand(6));
			if (TethysGame::GetRand(2) == 0)
			{
				end.x = 90+31;
				end.y = 128;
			}
			else
			{
				end.x = 256+31;
				end.y = TethysGame::GetRand(128);
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

// Functions for setting up volcano animations
void SouthEastFlowAni ( int x, int y)
{
	GameMap::SetTile(LOCATION(x, y), 0x489);
	GameMap::SetTile(LOCATION(x, y+1), 0x4A0);
	GameMap::SetTile(LOCATION(x+1, y+1), 0x4AB);
	GameMap::SetTile(LOCATION(x+1, y), 0x494);
}
void SouthFlowAni( int x, int y)
{
	GameMap::SetTile(LOCATION(x, y), 0x474);
	GameMap::SetTile(LOCATION(x, y+1), 0x47E);
}

void SouthWestFlowAni ( int x, int y)
{
	GameMap::SetTile(LOCATION(x+1, y), 0x453);
	GameMap::SetTile(LOCATION(x, y), 0x447);
	GameMap::SetTile(LOCATION(x, y+1), 0x45E);
	GameMap::SetTile(LOCATION(x+1, y+1), 0x469);
}

// Functions for stopping volcano animations
void SouthEastFlowStopAni ( int x, int y)
{
	GameMap::SetTile(LOCATION(x, y), 0x490);
	GameMap::SetTile(LOCATION(x, y+1), 0x4A8);
	GameMap::SetTile(LOCATION(x+1, y+1), 0x4B2);
	GameMap::SetTile(LOCATION(x+1, y), 0x49C);
}
void SouthFlowStopAni( int x, int y)
{
	GameMap::SetTile(LOCATION(x, y), 0x47B);
	GameMap::SetTile(LOCATION(x, y+1), 0x486);
}

void SouthWestFlowStopAni ( int x, int y)
{
	GameMap::SetTile(LOCATION(x+1, y), 0x45A);
	GameMap::SetTile(LOCATION(x, y), 0x44F);
	GameMap::SetTile(LOCATION(x, y+1), 0x465);
	GameMap::SetTile(LOCATION(x+1, y+1), 0x470);
}