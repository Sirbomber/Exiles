// Exiles Co-op Campaign Mission #02
// Players: 4
// Gametype: Co-op (Midas)
// Map: ply05.map
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

#include "SaveLoad.h"
#include "ChatCommands.h"
#include "MissionEnd.h"

#include "GameSetup.h"

// ----------------------------------------------------------------------------

Export char MapName[]			= "ply05.map";
Export char LevelDesc[]		    = "4P, COOP, Exiles Mission #02 - Sabotage";
Export char TechtreeName[]		= "cooptech.txt";
Export AIModDesc DescBlock	    = { MultiMidas, 4, 4, 1 };

Export int DescBlockEx[] = { 2, 0, 0, 0, 0, 0, 0, 0 }; // Add two extra player slots for the AIs

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

Export int InitProc()
{
	DoGameSetup();
	SetupMiscObjects();
	DoRandomBases();
	SetupVictory();
	SetupFailure();

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
	//
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
