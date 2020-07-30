// Exiles Co-op Campaign Mission #03
// Players: 4
// Gametype: Co-op (Midas)
// Map: exiles_03.map
// Techtree: Cooptech
// Created by: Sirbomber

// To do: Refactor the code for this mission.  Update it to use DisasterCreator (fun fact: this mission inspired me to make DisasterCreator!).
// This code wasn't as rough as the code for mission 1/2 so I passed on refactoring it for now.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Outpost2DLL.h>
#include <OP2Helper.h>

#include <hfl.h>
#include "Patcher.h"
#include "Patches.h"

#include "SaveLoad.h"
#include "ChatCommands.h"
#include "MissionEnd.h"

#include "Bases.h"
#include "Objectives.h"
#include "GameSetup.h"
#include "AI.h"

// ----------------------------------------------------------------------------

Export char MapName[]			= "exiles_03.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #03 - Siege";
Export char TechtreeName[]		= "cooptech.txt";
Export AIModDesc DescBlock	    = { MultiMidas, 4, 5, 0 };

Export int DescBlockEx[] = { 1, 0, 0, 0, 0, 0, 0, 0 }; // Add one extra player slot for AI

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

extern int numAI = -1;

Export int InitProc()
{
    DoGameSetup();
    DoRandomBases();

	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
	    if (!Player[i].IsHuman() && numAI < 0)
	    {
	        numAI = i;
	    }
	}

	for (int i = 0; i < numAI; i++)
	{
		// Give players the appropriate tech level.
		SetMissionTechLevel(3, i);

		for (int j = 0; j < numAI; j++)
		{
			if (i != j)
				Player[i].AllyWith(j);
		}
	}

	SetupVictory(numAI);
	SetupFailure(numAI);
	SetupDisasters();
	SetupAI();

	// Post-mission cutscene setup
	SetVictoryAvi("MPUW.AVI");
	if (Player[TethysGame::LocalPlayer()].IsEden())
	{
		SetDefeatAvi("MEUL.AVI");
	}
	else
	{
		SetDefeatAvi("MPUL.AVI");
	}

	return 1; // return 1 if OK; 0 on failure

}

// ----------------------------------------------------------------------------

Export void AIProc()
{
}

void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}

Export void None()
{
	//
}

// -------------------------------------------------------------
