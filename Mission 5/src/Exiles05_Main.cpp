// Exiles Co-op Campaign Mission #05
// Players: 4
// Gametype: Co-op (Midas)
// Map: exiles_05.map
// Techtree: Cooptech
// Created by: Sirbomber

#include <windows.h>

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <OP2Types\OP2Units.h>
#include <HFL.h>
#include <list>
#include <Patches.h>

#include "Bases.h"
#include "Objectives.h"
#include "GameSetup.h"
#include "AI.h"
#include "SaveLoad.h"
#include "ChatCommands.h"
#include "MissionEnd.h"

// ----------------------------------------------------------------------------

Export char MapName[]			= "exiles_05.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #05 - Rescue";
Export char TechtreeName[]		= "cooptech.txt";
Export AIModDesc DescBlock	    = { MultiMidas, 4, 10, 1 };

Export int DescBlockEx[] = { 2, 0, 0, 0, 0, 0, 0, 0 }; // Add two extra player slots for AI

HINSTANCE hInstDLL = NULL;

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    //DWORD oldAttr;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		g_hInst = hInstDLL = hinstDLL;				// This needs to get set for cutscenes to properly blank out the rest of the window at mission end.

		if (HFLInit() == HFLCANTINIT
			|| !SetMissionEndHook(true, MissionEnd)
			|| !SetNukePatch(true)
			|| !SetMessageHook(true, ProcessChatCommands))
		{
			return false;
		}
	}

	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		// Unlock Dans_RULE_UIFrame (locked by PlayAvi)
		LockWindowUpdate(NULL);

		SetMissionEndHook(false, NULL);
		SetNukePatch(false);
		SetMessageHook(false, NULL);

		HFLCleanup();

		std::list<UnitGroup*>::iterator aigIt = X5AI::aiGroups.begin();
		while (aigIt != X5AI::aiGroups.end())
		{
			delete *aigIt;
			aigIt++;
		}
	}

	

    return TRUE;
}

// -----------------------------------------------------------------------

extern int numAI = -1;

Export int InitProc()
{
    // Initialization stuff goes in InitProc.  Mind-blowing.
    DoGameSetup();      // Handles morale settings and the playlist
	SetupMiscObjects();

	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
	    if (!Player[i].IsHuman() && numAI < 0)
	    {
	        numAI = i;
			break;
	    }
	}

	for (int i = 0; i < numAI; i++)
	{
		// Center player view
		Player[i].CenterViewOn(13 + 31, 10 - 1);

		// Give players the appropriate tech level.
		SetMissionTechLevel(5, i);
		

		// Set alliances
		Player[i].AllyWith(numAI + 1);
		Player[numAI + 1].AllyWith(i);
		for (int j = 0; j < numAI; j++)
		{
			if (i != j)
			{
				Player[i].AllyWith(j);
			}
		}
	}

	//DoRandomBases();    // Randomize and place bases

	SetupVictory(numAI);     // Creates victory and defeat conditions
	SetupFailure(numAI);

	SetupDisasters();

	// Civilian base
	UnitEx Unit1;
	SetupFriendlyBase(numAI + 1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(4 + 31, 4 - 1), numAI + 1, mapSupernova, 0);
	Unit1.DoSelfDestruct();

	// Test player units
	Player[0].GoEden(); // TEST REMOVE ME
	
	// Play intro cutscene (and spawn player units)
	CreateTimeTrigger(1, 1, 1, "Intro1");
	CreateTimeTrigger(1, 1, 101, "Intro2");

	// Setup AI zones (note: there is some overlap between zones)
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 1 - 1, 61 + 31, 6 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 7 - 1, 54 + 31, 29 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 30 - 1, 50 + 31, 37 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 38 - 1, 54 + 31, 47 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 48 - 1, 56 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(53 + 31, 12 - 1, 58 + 31, 17 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(57 + 31, 50 - 1, 73 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(74 + 31, 53 - 1, 84 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(74 + 31, 53 - 1, 85 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(86 + 31, 61 - 1, 89 + 31, 63 - 1));

	X5AI::zones[1].AddRectToZone(MAP_RECT(50 + 31, 1 - 1, 87 + 31, 8 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(56 + 31, 9 - 1, 75 + 31, 11 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(59 + 31, 12 - 1, 73 + 31, 17 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(56 + 31, 18 - 1, 64 + 31, 23 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(67 + 31, 22 - 1, 83 + 31, 23 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(55 + 31, 24 - 1, 86 + 31, 31 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(51 + 31, 30 - 1, 54 + 31, 34 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(55 + 31, 32 - 1, 80 + 31, 37 - 1));

	X5AI::zones[2].AddRectToZone(MAP_RECT(55 + 31, 38 - 1, 91 + 31, 48 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(74 + 31, 48 - 1, 93 + 31, 52 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(92 + 31, 47 - 1, 92 + 31, 48 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(81 + 31, 32 - 1, 86 + 31, 37 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(87 + 31, 36 - 1, 89 + 31, 37 - 1));

	/* Old Zones
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 1 - 1, 60 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(55 + 31, 50 - 1, 73 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(74 + 31, 53 - 1, 85 + 31, 63 - 1));

	X5AI::zones[1].AddRectToZone(MAP_RECT(40 + 31, 1 - 1, 87 + 31, 8 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(40 + 31, 9 - 1, 76 + 31, 20 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(49 + 31, 21 - 1, 86 + 31, 35 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(81 + 31, 50 - 1, 54 + 31, 33 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(61 + 31, 36 - 1, 89 + 31, 49 - 1));

	X5AI::zones[2].AddRectToZone(MAP_RECT(97 + 31, 21 - 1, 76 + 31, 7 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(89 + 31, 1 - 1, 142 + 31, 27 - 1));

	X5AI::zones[3].AddRectToZone(MAP_RECT(124 + 31, 24 - 1, 256 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(149 + 31, 1 - 1, 236 + 31, 54 - 1));
	*/

	// Zone drawing test code -- remove me!
	for (int i = 99; i < 3; i++)
	{
		std::list<MAP_RECT> t = X5AI::zones[i].test_GetZones();
		for (std::list<MAP_RECT>::iterator it = t.begin(); it != t.end(); it++)
		{
			MAP_RECT r = *it;
			for (int y = r.y1; y <= r.y2; y++)
			{
				for (int x = r.x1; x <= r.x2; x++)
				{
					GameMap::SetTile(LOCATION(x, y), i*100);
				}
			}
		}
	}
	// AI units
	SetupHostilePatrols(numAI);

	// Populate unit lists (temp)
	PlayerUnitEnum aiEnum(numAI);
	while (aiEnum.GetNext(Unit1))
	{
		X5AI::aiUnits.push_back(Unit1);
	}
	
	CreateVictoryCondition(1, 1, CreateEscapeTrigger(1, 1, -1, 247 + 31, 9 - 1, 9, 9, 1, mapEvacuationTransport, mapAny, -1, "None"), "At least one Evacuation Transport must reach the rendezvous beacon at (251, 13).");

	SetVictoryAvi("MEBW.AVI");
	SetDefeatAvi("MEBL.AVI");

	// Test
	CreateTimeTrigger(1, 1, 17000, "Sunrise");
	//CreateTimeTrigger(1, 1, 1700, "Sunrise");

	return 1; // return 1 if OK; 0 on failure

}

// ----------------------------------------------------------------------------

struct AiControlZone
{
	std::list<UnitEx> aiUnitsInZone;
	std::list<UnitEx> detectedPlayerUnitsInZone;
	std::list<MAP_RECT> zoneAreas;
};

Export void Intro1()
{
	// Intro cutscene - blow up the AI tokamak and idle the base.
	UnitEx Unit1;
	InRectEnumerator civBaseEnum(MAP_RECT(1+31,1-1, 25+31, 21-1));
	while (civBaseEnum.GetNext(Unit1))
	{
		if (!Unit1.IsVehicle())
		{
			if (Unit1.GetType() == mapTokamak)
			{
				Unit1.DoDeath();
			}
			else
			{
				Unit1.DoIdle();
			}
		}
	}
}

Export void Intro2()
{
	// Intro cutscene - "unload" convoy from garage and give to players.
	UnitEx Unit1;
	OP2Unit *internalUnit;
	if (Player[0].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 4 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(14 + 31, 24 - 1));
	}
	if (Player[1].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 7 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(16 + 31, 24 - 1));
	}
	if (Player[2].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 10 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(18 + 31, 24 - 1));
	}
	if (Player[3].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 13 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(20 + 31, 24 - 1));
	}

	// Wait, then spawn second set of ETs
	CreateTimeTrigger(1, 1, 88, "Intro3");
}

Export void Intro3()
{
	// Intro cutscene - "unload" the second set of evac transports
	UnitEx Unit1;
	OP2Unit *internalUnit;
	if (Player[0].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 4 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(14 + 31, 23 - 1));
	}
	if (Player[1].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 7 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(16 + 31, 23 - 1));
	}
	if (Player[2].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 10 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(18 + 31, 23 - 1));
	}
	if (Player[3].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 13 - 1), 0, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		Unit1.DoMove(LOCATION(20 + 31, 23 - 1));
	}

	// Wait, then spawn reinforcements
	CreateTimeTrigger(1, 1, 230, "SpawnPlayerConvoy");

	// Now that the convoy has spawned, set failure condition.
	CreateFailureCondition(1, 1, CreateCountTrigger(1, 1, -1, mapEvacuationTransport, mapAny, 0, cmpEqual, "None"), "Convoy destroyed");
}

Export void SpawnPlayerConvoy()
{
	// Intro cutscene - have player escort units "arrive" from off the map
	UnitEx Unit1;
	map_id weapon;
	
	for (int i = 0; i < numAI; i++)
	{
		// Make sure the player hasn't already left the game for some reason
		if (Player[i].IsHuman())
		{
			// Determine player weapons
			if (Player[i].IsEden())
			{
				weapon = mapLaser;
			}
			else
			{
				weapon = mapMicrowave;
			}

			// Spawn vehicles based on difficulty.
			switch (Player[0].Difficulty())
			{
			case 0:
				// High: 4 Lynx, 2 Scouts
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(6 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(5 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(21 + 31, 29 - 1 + (i * 2)));

				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(4 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(18 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(3 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(17 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(16 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(15 + 31, 29 - 1 + (i * 2)));
				break;
			case 1:
				// Medium: 2 Lynx, 2 Scouts
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(4 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(21 + 31, 29 - 1 + (i * 2)));

				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(18 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 42 - 1 + i), 0, weapon, 0);
				Unit1.DoMove(LOCATION(17 + 31, 29 - 1 + (i * 2)));
				break;
			case 2:
				// Low: 2 Scouts
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(2 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(1 + 31, 42 - 1 + i), 0, mapNone, 0);
				Unit1.DoMove(LOCATION(21 + 31, 29 - 1 + (i * 2)));
				break;
			}
		}
	}
	TethysGame::AddMessage(6 * 32, 40 * 32, "Reinforcements ready.", -1, sndSavnt205);

	// All player units have spawned; add them to the undiscovered units list.
	InRectEnumerator playerUnits(MAP_RECT(1 + 31, 1 - 1, 34 + 31, 63 - 1));
	while (playerUnits.GetNext(Unit1))
	{
		if (Unit1.IsVehicle() && Unit1.IsLive() && Unit1.OwnerID() < numAI)
		{
			X5AI::stealthedUnits.push_back(Unit1);
		}
	}
}

Export void Sunrise()
{
	TethysGame::SetDaylightMoves(1);
	TethysGameEx::ResetCheatedGame();
	//CreateTimeTrigger(1, 1, 5280, "Blight");
	CreateTimeTrigger(1, 1, 528, "Blight");

	// Set alternate playlist
	SongIds X05Songs_Crisis[] = { songEP62 }; // currently copied from X04 -- update!
	TethysGame::SetMusicPlayList(1, 0, X05Songs_Crisis);
}

Export void Blight()
{
	// Option 1: Top/middle of map
	/*
	GameMap::SetVirusUL(LOCATION(141 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(142 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(143 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(144 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(145 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(146 + 31, 1 - 1), 1);
	GameMap::SetVirusUL(LOCATION(141 + 31, 2 - 1), 1);
	GameMap::SetVirusUL(LOCATION(142 + 31, 2 - 1), 1);
	GameMap::SetVirusUL(LOCATION(143 + 31, 2 - 1), 1);
	TethysGame::SetMicrobeSpreadSpeed(280);
	TethysGame::AddMessage((142 + 31) * 32, 1 * 32, "Microbe growth detected!", -1, sndSavnt278);
	*/

	// Option 2: Start zone
	GameMap::SetVirusUL(LOCATION(1 + 31, 42 - 1), 1);
	GameMap::SetVirusUL(LOCATION(1 + 31, 43 - 1), 1);
	GameMap::SetVirusUL(LOCATION(1 + 31, 44 - 1), 1);
	GameMap::SetVirusUL(LOCATION(1 + 31, 45 - 1), 1);
	GameMap::SetVirusUL(LOCATION(2 + 31, 42 - 1), 1);
	GameMap::SetVirusUL(LOCATION(2 + 31, 43 - 1), 1);
	GameMap::SetVirusUL(LOCATION(2 + 31, 44 - 1), 1);
	GameMap::SetVirusUL(LOCATION(2 + 31, 45 - 1), 1);
	GameMap::SetVirusUL(LOCATION(3 + 31, 42 - 1), 1);
	GameMap::SetVirusUL(LOCATION(3 + 31, 43 - 1), 1);
	GameMap::SetVirusUL(LOCATION(3 + 31, 44 - 1), 1);
	GameMap::SetVirusUL(LOCATION(3 + 31, 45 - 1), 1);
	GameMap::SetVirusUL(LOCATION(4 + 31, 43 - 1), 1);
	GameMap::SetVirusUL(LOCATION(4 + 31, 44 - 1), 1);
	TethysGame::SetMicrobeSpreadSpeed(180);
	TethysGame::AddMessage((2 + 31) * 32, (int)(42.5 * 32), "Microbe growth detected!", -1, sndSavnt278);
}

Export void AIProc()
{
	// AI group update cycles
	std::list<UnitGroup*>::iterator aigIt = X5AI::aiGroups.begin();
	while (aigIt != X5AI::aiGroups.end())
	{
		(*aigIt)->GroupStatusUpdate();
		aigIt++;
	}

	// Check all undetected player units to see if their lights are on
	std::list<UnitEx>::iterator i = X5AI::stealthedUnits.begin();
	while (i != X5AI::stealthedUnits.end())
	{
		// Unit is dead; remove it from the list.
		if (!i->IsLive())
		{
			X5AI::stealthedUnits.erase(i++);
		}

		else
		{
			// Lights are on, add it to the detected units list
			if (i->GetLights() /*|| (int)pActualDaylightPos == i->Location().x*/)
			{
				X5AI::detectedUnits.push_back(*i);
				X5AI::stealthedUnits.erase(i++);
			}
			else
			{
				i++;
			}
		}
		
	}

	// Check undetected player units to see if they're in range of a unit (player or AI owned) with its lights on.


	// Send the AI after nearby detected units
	i = X5AI::aiUnits.begin();
	while (i != X5AI::aiUnits.end())
	{
		if (!i->IsLive())
		{
			X5AI::aiUnits.erase(i++);
		}
		else
		{
			std::list<UnitEx>::iterator j = X5AI::detectedUnits.begin();
			while (j != X5AI::detectedUnits.end())
			{
				if (!j->IsLive())
				{
					X5AI::detectedUnits.erase(j++);
				}
				else
				{
					if (X5AI::GetUnitZone(*i) == X5AI::GetUnitZone(*j))
					{
						i->Unit::DoAttack(*j);
					}
					j++;
				}
			}
			i++;
		}
	}

}

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}

/* Is this not needed anymore?
int StatusProc()
{
	return 0; // must return 0
}
*/

Export void None()
{
}

// -------------------------------------------------------------
