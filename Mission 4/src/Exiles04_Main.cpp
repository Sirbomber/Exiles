// Exiles Co-op Campaign Mission #04
// Players: 4
// Gametype: Co-op (Midas)
// Map: exiles_04.map
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

Export char MapName[]			= "exiles_04.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #04 - Contingency";
Export char TechtreeName[]		= "cooptech.txt";
Export AIModDesc DescBlock	    = { MultiMidas, 4, 10, 0 };

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
    // Initialization stuff goes in InitProc.  Mind-blowing.
	SetLavaAllowed();
    DoGameSetup();      // Handles morale settings and the playlist
	SetupMiscObjects();
	
	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
	    if (!Player[i].IsHuman() && numAI < 0)
	    {
	        numAI = i;
	    }
	}

	// Set all human players as allies
	for (int i = 0; i < numAI; i++)
	{
		// Give players the appropriate tech level.
		SetMissionTechLevel(4, i);
		for (int j = 0; j < numAI; j++)
		{
			if (i != j)
				Player[i].AllyWith(j);
		}
	}

	DoRandomBases();    // Randomize and place bases

	SetupVictory(numAI);     // Creates victory and defeat conditions
	SetupFailure(numAI);
	SetupWreckCheck();
	SetupDisasters();   // Some minor quakes and storms.  Game-ending volcano around mark 570.

	SetupAI();

	SetupTechShare();

	SetVictoryAvi("MPBW.AVI");
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
