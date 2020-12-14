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
			//|| !SetNukePatch(true)
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
		//SetNukePatch(false);
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

// Testing
#ifdef _DEBUG
int origTiles[256][64];
UnitEx drawControl;
UnitEx lightControl;
bool showZones = false;
bool showMap = false;
#endif

// Used for victory/defeat conditions
char string[100];
int numETsNeeded = 0;

Export int InitProc()
{
#ifdef _DEBUG
	// For testing purposes only
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			origTiles[x][y] = GameMap::GetTile(LOCATION(x + 32, y));
		}
	}
#endif
    DoGameSetup();
	SetupMiscObjects();

	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
	    if (!Player[i].IsHuman() && X5AI::numAI < 0)
	    {
			X5AI::numAI = i;
			break;
	    }
	}

	for (int i = 0; i < X5AI::numAI; i++)
	{
		// Center player view
		Player[i].CenterViewOn(13 + 31, 10 - 1);

		// Give players the appropriate tech level.
		SetMissionTechLevel(5, i);
		
		// Set alliances
		Player[i].AllyWith(X5AI::numAI + 1);
		Player[X5AI::numAI + 1].AllyWith(i);
		for (int j = 0; j < X5AI::numAI; j++)
		{
			if (i != j)
			{
				Player[i].AllyWith(j);
			}
		}
	}

	SetupVictory(X5AI::numAI);     // Creates victory and defeat conditions
	SetupFailure(X5AI::numAI);

	// Civilian base
	UnitEx Unit1;
	SetupFriendlyBase(X5AI::numAI + 1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(4 + 31, 4 - 1), X5AI::numAI + 1, mapSupernova, 0);
	Unit1.DoSelfDestruct();
	
	// Play intro cutscene (and spawn player units)
	CreateTimeTrigger(1, 1, 1, "Intro1");
	CreateTimeTrigger(1, 1, 101, "Intro2");

	// Setup AI zones (note: there is some overlap between zones)
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 1 - 1, 61 + 31, 6 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 7 - 1, 54 + 31, 29 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 30 - 1, 50 + 31, 37 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 38 - 1, 54 + 31, 47 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(1 + 31, 48 - 1, 56 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(55 + 31, 12 - 1, 58 + 31, 17 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(57 + 31, 50 - 1, 73 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(74 + 31, 54 - 1, 85 + 31, 63 - 1));
	X5AI::zones[0].AddRectToZone(MAP_RECT(86 + 31, 61 - 1, 87 + 31, 63 - 1));

	X5AI::zones[1].AddRectToZone(MAP_RECT(50 + 31, 1 - 1, 87 + 31, 8 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(56 + 31, 9 - 1, 75 + 31, 11 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(59 + 31, 12 - 1, 73 + 31, 17 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(56 + 31, 18 - 1, 64 + 31, 23 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(67 + 31, 22 - 1, 83 + 31, 23 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(55 + 31, 24 - 1, 86 + 31, 31 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(51 + 31, 30 - 1, 54 + 31, 34 - 1));
	X5AI::zones[1].AddRectToZone(MAP_RECT(55 + 31, 32 - 1, 80 + 31, 37 - 1));

	X5AI::zones[2].AddRectToZone(MAP_RECT(55 + 31, 38 - 1, 91 + 31, 48 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(74 + 31, 49 - 1, 93 + 31, 52 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(92 + 31, 46 - 1, 92 + 31, 48 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(81 + 31, 32 - 1, 86 + 31, 37 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(87 + 31, 36 - 1, 89 + 31, 37 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(86 + 31, 53 - 1, 100 + 31, 56 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(88 + 31, 57 - 1, 101 + 31, 63 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(94 + 31, 51 - 1, 95 + 31, 52 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(67 + 31, 22 - 1, 83 + 31, 23 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(65 + 31, 24 - 1, 86 + 31, 31 - 1));
	X5AI::zones[2].AddRectToZone(MAP_RECT(54 + 31, 32 - 1, 80 + 31, 37 - 1));

	X5AI::zones[3].AddRectToZone(MAP_RECT(89 + 31, 1 - 1, 105 + 31, 33 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(77 + 31, 10 - 1, 88 + 31, 19 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(84 + 31, 20 - 1, 88 + 31, 23 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(106 + 31, 16 - 1, 109 + 31, 33 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(110 + 31, 24 - 1, 114 + 31, 33 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(115 + 31, 29 - 1, 116 + 31, 30 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(92 + 31, 34 - 1, 114 + 31, 40 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(102 + 31, 41 - 1, 117 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(118 + 31, 46 - 1, 120 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(121 + 31, 54 - 1, 128 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(129 + 31, 60 - 1, 129 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(93 + 31, 47 - 1, 101 + 31, 47 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(96 + 31, 48 - 1, 101 + 31, 50 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(87 + 31, 24 - 1, 88 + 31, 32 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(115 + 31, 40 - 1, 116 + 31, 40 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(88 + 31, 56 - 1, 101 + 31, 63 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(93 + 31, 41 - 1, 101 + 31, 46 - 1));
	X5AI::zones[3].AddRectToZone(MAP_RECT(106 + 31, 1 - 1, 120 + 31, 8 - 1));

	X5AI::zones[4].AddRectToZone(MAP_RECT(99 + 31, 1 - 1, 143 + 31, 15 - 1));
	X5AI::zones[4].AddRectToZone(MAP_RECT(144 + 31, 1 - 1, 146 + 31, 1 - 1));
	X5AI::zones[4].AddRectToZone(MAP_RECT(110 + 31, 16 - 1, 143 + 31, 21 - 1));
	X5AI::zones[4].AddRectToZone(MAP_RECT(114 + 31, 22 - 1, 140 + 31, 27 - 1));
	X5AI::zones[4].AddRectToZone(MAP_RECT(123 + 31, 28 - 1, 130 + 31, 30 - 1));
	X5AI::zones[4].AddRectToZone(MAP_RECT(131 + 31, 28 - 1, 138 + 31, 31 - 1));

	X5AI::zones[5].AddRectToZone(MAP_RECT(115 + 31, 31 - 1, 147 + 31, 37 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(119 + 31, 31 - 1, 122 + 31, 31 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(119 + 31, 38 - 1, 124 + 31, 47 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(122 + 31, 48 - 1, 147 + 31, 53 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(134 + 31, 46 - 1, 141 + 31, 47 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(129 + 31, 54 - 1, 147 + 31, 56 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(132 + 31, 57 - 1, 147 + 31, 63 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(125 + 31, 38 - 1, 127 + 31, 38 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(149 + 31,  1 - 1, 256 + 31, 30 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(148 + 31, 31 - 1, 256 + 31, 63 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(145 + 31, 38 - 1, 147 + 31, 38 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(141 + 31, 29 - 1, 148 + 31, 30 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(142 + 31, 23 - 1, 148 + 31, 28 - 1));
	X5AI::zones[5].AddRectToZone(MAP_RECT(146 + 31, 6 - 1, 148 + 31, 22 - 1));

	// ESG zone
	X5AI::zones[6].AddRectToZone(MAP_RECT(169 + 31, 1 - 1, 256 + 31, 14 - 1));
	X5AI::zones[6].AddRectToZone(MAP_RECT(175 + 31, 15 - 1, 256 + 31, 18 - 1));

	// Light Tower detection zone
	X5AI::zones[7].AddRectToZone(MAP_RECT(184 + 31, 43 - 1, 201 + 31, 52 - 1));
	X5AI::zones[7].AddRectToZone(MAP_RECT(186 + 31, 41 - 1, 199 + 31, 42 - 1));
	X5AI::zones[7].AddRectToZone(MAP_RECT(188 + 31, 39 - 1, 197 + 31, 40 - 1));
	X5AI::zones[7].AddRectToZone(MAP_RECT(192 + 31, 38 - 1, 194 + 31, 38 - 1));
	
	// AI units
	SetupHostilePatrols(X5AI::numAI);

	// Create victory condition
	for (int i = 0; i < X5AI::numAI; i++)
	{
		numETsNeeded += Player[i].Difficulty();
	}
	if (numETsNeeded < 2)
	{
		numETsNeeded = 1;
		CreateVictoryCondition(1, 1, CreateEscapeTrigger(1, 1, -1, 247 + 31, 9 - 1, 9, 9, 1, mapEvacuationTransport, mapAny, -1, "None"), "At least one Evacuation Transport must reach the rendezvous beacon at (251, 13).");
	}
	else
	{
		// "All 2" sounds wrong so for single player on hard difficulty say "both"
		if (numETsNeeded == 2 && X5AI::numAI == 1)
		{
			scr_snprintf(string, 100, "Both Evacuation Transports must reach the rendezvous beacon at (251, 13).", numETsNeeded);
		}
		else if (numETsNeeded >= X5AI::numAI * 2)
		{
			scr_snprintf(string, 100, "All %d Evacuation Transports must reach the rendezvous beacon at (251, 13).", numETsNeeded);
		}
		else
		{
			scr_snprintf(string, 100, "At least %d Evacuation Transports must reach the rendezvous beacon at (251, 13).", numETsNeeded);
		}
		CreateVictoryCondition(1, 1, CreateEscapeTrigger(1, 1, -1, 247 + 31, 9 - 1, 9, 9, numETsNeeded, mapEvacuationTransport, mapAny, -1, "None"), string);
	}

	SetVictoryAvi("MEBW.AVI");
	SetDefeatAvi("MEBL.AVI");

	CreateTimeTrigger(1, 1, 18700, "Sunrise");

	// Force RCC effect
	TethysGameEx::SetRCCEffect(rccForce);

	return 1; // return 1 if OK; 0 on failure

}

// ----------------------------------------------------------------------------

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
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(14 + 31, 24 - 1));
	}
	if (Player[1].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 7 - 1), 1, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(16 + 31, 24 - 1));
	}
	if (Player[2].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 10 - 1), 2, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(18 + 31, 24 - 1));
	}
	if (Player[3].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 13 - 1), 3, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
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
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(14 + 31, 23 - 1));
	}
	if (Player[1].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 7 - 1), 1, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(16 + 31, 23 - 1));
	}
	if (Player[2].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 10 - 1), 2, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(18 + 31, 23 - 1));
	}
	if (Player[3].IsHuman())
	{
		TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(19 + 31, 13 - 1), 3, mapAtheistBuildingExplosion, 4);
		internalUnit = &(*unitArray)[Unit1.unitID];
		internalUnit->flags &= ~UNIT_ISEDEN;
		internalUnit->flags |= UNIT_HASSPECIALTARGET;
		Unit1.DoMove(LOCATION(20 + 31, 23 - 1));
	}

	// Wait, then spawn reinforcements
	CreateTimeTrigger(1, 1, 230, "SpawnPlayerConvoy");

	// Let the player know exactly how much they screwed up if they let a transport die.
	CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapEvacuationTransport, mapAny, 2, cmpLower, "LostEvacTrans1");
	CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapEvacuationTransport, mapAny, 0, cmpEqual, "LostEvacTrans2");

	// Now that the convoy has spawned, set failure condition.
	CreateTimeTrigger(1, 0, 10, "CheckFailure");
}

Export void CheckFailure()
{
	Unit Unit1;
	int totalETs = 0;
	for (int i = 0; i < X5AI::numAI; i++)
	{
		PlayerUnitEnum findETs(i);
		while (findETs.GetNext(Unit1))
		{
			if (Unit1.IsLive() && Unit1.GetType() == mapEvacuationTransport)
			{
				totalETs++;
			}
		}
	}

	if (totalETs < numETsNeeded)
	{
		CreateFailureCondition(1, 1, CreateTimeTrigger(1, 1, 1, "None"), "Convoy destroyed");
	}
}

Export void SpawnPlayerConvoy()
{
	// Intro cutscene - have player escort units "arrive" from off the map
	UnitEx Unit1;
	map_id weapon;
	
	for (int i = 0; i < X5AI::numAI; i++)
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
			switch (Player[i].Difficulty())
			{
			case 0:
				// High: 3 Lynx, 1 Scouts
-				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(4 + 31, 42 - 1 + i), i, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));

				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(3 + 31, 42 - 1 + i), i, weapon, 0);
				Unit1.DoMove(LOCATION(21 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2 + 31, 42 - 1 + i), i, weapon, 0);
				Unit1.DoMove(LOCATION(20 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 42 - 1 + i), i, weapon, 0);
				Unit1.DoMove(LOCATION(19 + 31, 29 - 1 + (i * 2)));
				break;
			case 1:
				// Medium: 2 Lynx, 1 Scout
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 42 - 1 + i), i, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));

				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2 + 31, 42 - 1 + i), i, weapon, 0);
				Unit1.DoMove(LOCATION(21 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 42 - 1 + i), i, weapon, 0);
				Unit1.DoMove(LOCATION(20 + 31, 29 - 1 + (i * 2)));
				break;
			case 2:
				// Low: 1 Lynx, 1 Scout
				TethysGame::CreateUnit(Unit1, mapScout, LOCATION(2 + 31, 42 - 1 + i), i, mapNone, 0);
				Unit1.DoMove(LOCATION(22 + 31, 29 - 1 + (i * 2)));
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 42 - 1 + i), i, weapon, 0);
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
		if (Unit1.IsVehicle() && Unit1.IsLive() && Unit1.OwnerID() < X5AI::numAI)
		{
			X5AI::stealthedUnits.push_back(Unit1);

			// Setting this flag will prevent the AI from auto-firing on undetected units.
			OP2Unit *internalUnit;
			internalUnit = &(*unitArray)[Unit1.unitID];
			internalUnit->flags |= UNIT_HASSPECIALTARGET;
			Unit1.SetOppFiredUpon(1);
		}
	}
}

Export void Sunrise()
{
	TethysGame::SetDaylightMoves(1);
	TethysGameEx::ResetCheatedGame();
	CreateTimeTrigger(1, 1, 528, "Blight");
}

Export void Blight()
{
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
	TethysGame::SetMicrobeSpreadSpeed(185);
	TethysGame::AddMessage((2 + 31) * 32, (int)(42.5 * 32), "Microbe growth detected!", -1, sndSavnt278);

	CreatePointTrigger(1, 0, X5AI::numAI, 256 + 31, 63 - 1, "AiUnitsEscape");
}

Export void AiUnitsEscape()
{
	UnitEx Unit1;
	InRectEnumerator AtEdge(MAP_RECT(255 + 31, 63 - 1, 257 + 31, 64 - 1));
	while (AtEdge.GetNext(Unit1))
	{
		if (Unit1.OwnerID() == X5AI::numAI && Unit1.IsLive())
		{
			Unit1.DoPoof();
		}
	}
}

Export void LostEvacTrans1()
{
	TethysGame::AddMessage(-1, -1, "8 Children, 13 Workers, 4 Scientists have died", TethysGame::LocalPlayer(), sndBeep8);
}

Export void LostEvacTrans2()
{
	TethysGame::AddMessage(-1, -1, "7 Children, 12 Workers, 6 Scientists have died", TethysGame::LocalPlayer(), sndBeep8);
}

#ifdef _DEBUG
void Test_DrawZones()
{
	if (drawControl.IsLive())
	{
		if (drawControl.GetLights() && !showZones)
		{
			showZones = true;
			for (int y = 0; y < 64; y++)
			{
				for (int x = 0; x < 256; x++)
				{
					GameMap::SetTile(LOCATION(x + 32, y), 0);
				}
			}

			for (int i = 0; i < X5AI::NUMZONES; i++)
			{
				std::list<MAP_RECT> t = X5AI::zones[i].test_GetZones();
				for (std::list<MAP_RECT>::iterator it = t.begin(); it != t.end(); it++)
				{
					MAP_RECT r = *it;
					for (int y = r.y1; y <= r.y2; y++)
					{
						for (int x = r.x1; x <= r.x2; x++)
						{
							GameMap::SetTile(LOCATION(x, y), (GameMap::GetTile(LOCATION(x, y)) + i + 1) * 100);
						}
					}
				}
			}
		}
		else if (!drawControl.GetLights() && showZones)
		{
			showZones = false;
			for (int y = 0; y < 64; y++)
			{
				for (int x = 0; x < 256; x++)
				{
					GameMap::SetTile(LOCATION(x + 32, y), origTiles[x][y]);
				}
			}
		}
	}
	else
	{
		TethysGame::CreateUnit(drawControl, mapTiger, LOCATION(250 + 31, 60 - 1), 0, mapThorsHammer, 0);
	}
}

void Test_ToggleDaylight()
{
	if (lightControl.IsLive())
	{
		if (lightControl.GetLights() && !showMap)
		{
			showMap = true;
			TethysGame::SetDaylightEverywhere(1);
		}
		else if (!lightControl.GetLights() && showMap)
		{
			showMap = false;
			TethysGame::SetDaylightEverywhere(false);
		}
	}
	else
	{
		TethysGame::CreateUnit(lightControl, mapTiger, LOCATION(250 + 31, 59 - 1), 0, mapAcidCloud, 0);
	}
}
#endif

Export void AIProc()
{
	// Testing
#ifdef _DEBUG
	Test_DrawZones();
	Test_ToggleDaylight();
#endif

	// Try to detect player units
	X5AI::DetectPlayerUnits();

	// If a player unit escapes pursuit or dies, remove it from the detected units list.
	X5AI::ForgetPlayerUnits();

	// AI group update cycles
	X5AI::GroupManagement();
}

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}

Export void None()
{
}

// -------------------------------------------------------------
