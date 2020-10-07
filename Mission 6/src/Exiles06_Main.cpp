// Exiles Co-op Campaign Mission #06
// Players: 4
// Gametype: Co-op (Midas)
// Map: eden10.map
// Techtree: Cooptech
// Created by: Sirbomber

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <Patches.h>

#include <OP2Types.h>
#include <Outpost2App.h>
#include <string>

#include "Bases.h"
#include "Objectives.h"
#include "GameSetup.h"
#include "AI.h"
#include "SaveLoad.h"
#include "ChatCommands.h"
#include "MissionEnd.h"

// ----------------------------------------------------------------------------

Export char MapName[]			= "eden10.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #06 - Uprising";
Export char TechtreeName[]		= "cooptech.txt";
Export AIModDesc DescBlock	    = { MultiMidas, 4, 11, 0 };

Export int DescBlockEx[] = { 2, 0, 0, 0, 0, 0, 0, 0 };	// Add two extra player slots for the AIs

HINSTANCE hInstDLL = NULL;
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
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
	}

	return TRUE;
}

// -----------------------------------------------------------------------

Trigger DeadCC, FailDeadCC;

void TestStuff()
{
	// Test
	Player[0].GoEden();
	UnitEx Unit1;
	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(41 + 31, 53 - 1), 0, mapNone, 0);
	Unit1.DoSetLights(1);
	Player[0].CenterViewOn(50 + 31, 50 - 1);
	TethysGame::ForceMoraleGreat(-1);

	TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(34 + 31, 62 - 1), 0, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(38 + 31, 62 - 1), 1, mapThorsHammer, 0);
	OP2Unit *internalUnit = &(*unitArray)[Unit1.unitID];
	internalUnit->flags |= UNIT_ISEMPED;
	internalUnit->Vehicle.timerEMP = 300;
	for (int i = 0; i < 2; i++)
	{
		int oX = 70 + (i * 10);
		int oY = 78;

		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31, oY - 1), 0, mapCommandCenter, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 1, oY - 1), 0, mapStructureFactory, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 2, oY - 1), 0, mapCommonOreSmelter, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 3, oY - 1), 0, mapCommonOreSmelter, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 4, oY - 1), 0, mapTokamak, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 5, oY - 1), 0, mapTokamak, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 6, oY - 1), 0, mapVehicleFactory, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31, oY - 1 + 1), 0, mapNursery, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 1, oY - 1 + 1), 0, mapUniversity, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 2, oY - 1 + 1), 0, mapAgridome, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 3, oY - 1 + 1), 0, mapAgridome, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 4, oY - 1 + 1), 0, mapResidence, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 5, oY - 1 + 1), 0, mapResidence, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 6, oY - 1 + 1), 0, mapMedicalCenter, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31, oY - 1 + 2), 0, mapAgridome, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 1, oY - 1 + 2), 0, mapRareStorage, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(oX + 31 + 2, oY - 1 + 2), 0, mapNone, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 3, oY - 1 + 2), 0, mapMagmaWell, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 4, oY - 1 + 2), 0, mapStandardLab, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 5, oY - 1 + 2), 0, mapAdvancedLab, 0);
		Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(oX + 31 + 6, oY - 1 + 2), 0, mapGORF, 0);
		Unit1.DoSetLights(1);
	}
}

extern int numEden = -1;
extern int numPlym = -1;
int capturedCCs = 0;

Export int InitProc()
{
	TestStuff();		// Remove me!

	SetLavaAllowed();
    DoGameSetup();      // Handles morale settings and the playlist
	//SetupMiscObjects();
	
	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
	    if (!Player[i].IsHuman() && numEden < 0)
	    {
			numEden = i;
			numPlym = i + 1;
	    }
	}

	// Set all human players as allies
	for (int i = 0; i < numEden; i++)
	{
		// Give players the appropriate tech level.
		SetMissionTechLevel(6, i);
		for (int j = 0; j < numEden; j++)
		{
			if (i != j)
				Player[i].AllyWith(j);
		}
	}
	/*
	DoRandomBases();    // Randomize and place bases

	SetupVictory(numEden);     // Creates victory and defeat conditions
	SetupFailure(numEden);
	SetupDisasters();   // Some minor quakes and storms.  Game-ending volcano around mark 570.

	*/

	SetupAI();

	SetVictoryAvi("MPBW.AVI");
	if (Player[TethysGame::LocalPlayer()].IsEden())
	{
		SetDefeatAvi("MEUL.AVI");
	}
	else
	{
		SetDefeatAvi("MPUL.AVI");
	}

	DeadCC = CreateTimeTrigger(1, 0, 50, "CheckDeadCCs");

	return 1; // return 1 if OK; 0 on failure

}

Export void CheckDeadCCs()
{
	int numCCs = 0;
	Unit Next;
	PlayerBuildingEnum CheckCCs(numEden, mapCommandCenter);
	while (CheckCCs.GetNext(Next))
	{
		if (Next.IsLive() && Next.OwnerID() == numEden)
		{
			numCCs++;
		}
	}

	if (numCCs < numEden)
	{
		CreateFailureCondition(1, 1, CreateTimeTrigger(1, 1, 1, "None"), "AI CC Died");
	}
}

// ----------------------------------------------------------------------------

Export void AIProc()
{
	//
}

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}


Export void None()
{
}

Export void CapturedCC()
{
	capturedCCs++;
	if (capturedCCs >= /*numEden*/2)
	{
		// Shut down the "fail if AI CC destroyed" checks
		DeadCC.Destroy();

		//int i[4] = { 0, 1, 2, 3 };
		int i[2] = { 0, 1 };
		RandomizeList(autosize(i));

		// Transfer control of the colony over to the players
		//TransferColony(i[0], MAP_RECT(20 + 31, 34 - 1, 52 + 31, 75 - 1));
		//TransferColony(i[1], MAP_RECT(55 + 31, 37 - 1, 93 + 31, 70 - 1));

		TransferColony(2, MAP_RECT(20 + 31, 34 - 1, 52 + 31, 75 - 1));
		TransferColony(1, MAP_RECT(55 + 31, 37 - 1, 93 + 31, 70 - 1));
		TransferColony(0, MAP_RECT(21 + 31, 71 - 1, 72 + 31, 105 - 1));

		Trigger trig = CreateResearchTrigger(1, 1, 10204, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Completely research Solar Power.");
		TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	}
	else
	{
		TethysGame::AddMessage(-1, -1, "Command Center successfully infilitrated.", -1, sndBeep8);
	}
}

void TransferColony(int pNo, MAP_RECT zone)
{
	UnitEx Unit1, Unit2, Unit3;
	int hp;
	map_id type;
	LOCATION loc;
	InRectEnumerator colony1(zone);

	SetupInitRes(pNo);

	// Transfer buildings
	while (colony1.GetNext(Unit1))
	{
		// You'd think the "is in rect" check wouldn't be necessary when enumerating on units in a rect.  You'd be wrong.
		if (Unit1.IsBuilding() && zone.Check(Unit1.Location()))
		{
			if (Player[pNo].IsHuman())
			{
				hp = Unit1.GetDamage();
				type = Unit1.GetType();
				loc = Unit1.Location();

				Unit1.DoPoof();
				TethysGame::CreateUnit(Unit2, type, loc, pNo, mapNone, 0);
				Unit2.SetDamage(hp);

				if (type == mapCommandCenter)
				{
					TethysGame::AddMessage(loc.x * 32, loc.y * 32, "The colony is now under our control!", pNo, sndBeep8);
				}
				else if (type == mapStructureFactory)
				{
					Unit2.SetFactoryCargo(0, mapRareOreSmelter, mapNone);
					Unit2.SetFactoryCargo(1, mapResidence, mapNone);
					if (Player[pNo].Difficulty() == 0)
					{
						Unit2.SetFactoryCargo(2, mapVehicleFactory, mapNone);
					}
				}
				else if (type == mapGarage)
				{
					TethysGame::CreateUnit(Unit3, mapConVec, LOCATION(loc.x,loc.y), pNo, mapNone, 2);
					Unit3.DoSetLights(1);
					TethysGame::CreateUnit(Unit3, mapConVec, LOCATION(loc.x + 1, loc.y + 1), pNo, mapNone, 1);
					Unit3.DoSetLights(1);
				}
				else if (type == mapVehicleFactory)
				{
					TethysGame::CreateUnit(Unit3, mapCargoTruck, LOCATION(loc.x + 2, loc.y + 1), pNo, mapNone, 0);
					Unit3.DoSetLights(1);
					TethysGame::CreateUnit(Unit3, mapCargoTruck, LOCATION(loc.x + 2, loc.y), pNo, mapNone, 0);
					Unit3.DoSetLights(1);
					TethysGame::CreateUnit(Unit3, mapCargoTruck, LOCATION(loc.x + 2, loc.y - 1), pNo, mapNone, 0);
					Unit3.DoSetLights(1);
					TethysGame::CreateUnit(Unit3, mapCargoTruck, LOCATION(loc.x + 2, loc.y - 2), pNo, mapNone, 7);
					Unit3.DoSetLights(1);
				}
			}
			else
			{
				Unit1.DoDeath();
			}
		}
	}
}
// -------------------------------------------------------------
