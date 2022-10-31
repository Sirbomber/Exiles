// Exiles Co-op Campaign Mission #07
// Players: 4
// Gametype: Co-op (Midas)
// Map: exiles_07.map
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

Export char MapName[]			= "exiles_07.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #07 - Enigma";
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
		SetNukePatch(false);
		SetMessageHook(false, NULL);

		HFLCleanup();
	}

	return TRUE;
}

// -----------------------------------------------------------------------

extern int numEden = -1;
extern int numPlym = -1;

Export int InitProc()
{
    DoGameSetup();      // Handles morale settings and the playlist
	
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
		SetMissionTechLevel(7, i);
		for (int j = 0; j < numEden; j++)
		{
			if (i != j)
			{
				Player[i].AllyWith(j);
			}
		}
	}

	SetupVictory(numEden);			// Setup the "all other players" first objective, so it appears at the bottom of the objectives list.
	SetupAI();
	//SetupAI_Eden();					// Set Eden AI tech level, create base/initial units, and define AI groups
	//SetupAI_Plym();					// Set Plymouth AI tech level and create the first few units that exist just to get shot at a bit.
	DoRandomBases();					// Create player bases.
	SetupFailure(numEden);			// Create defeat conditions.
	//SetupDisasters();   // To do.

	if (Player[TethysGame::LocalPlayer()].IsEden())
	{
		SetVictoryAvi("E4.AVI");
		SetDefeatAvi("MEUL.AVI");
	}
	else
	{
		SetVictoryAvi("MPUW.AVI");
		SetDefeatAvi("MPUL.AVI");
	}

	return 1; // return 1 if OK; 0 on failure

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

// -------------------------------------------------------------
