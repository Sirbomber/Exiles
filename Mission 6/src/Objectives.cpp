#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "Objectives.h"
#include "AI.h"

extern int numEden;

Trigger OtherPlayers;
bool hasEdward[4],
     hasSkydock[4],
     hasIonDrive[4],
	 hasFusionDrive[4],
	 hasFueling[4],
	 hasCommand[4],
	 hasHabitat[4],
	 noEden;			// Set if no human players are Eden.  This will fail the mission if the AI captures a truck.
int wreckageStatus[5];	// 0 = on the ground; 1 = in truck; 2 = completed; 3 = fail the mission
UnitEx wreckageTrucks[5];

void SetupFailure(int pAI)
{
	Trigger trig[4], group;
	int i;
	noEden = true;

	// Defeat (at least one player has no operational CCs)
	for (i = 0; i < 4; i++)
	{
		if (i < pAI)
		{
			trig[i] = CreateOperationalTrigger(1, 0, i, mapCommandCenter, 0, cmpEqual, "None");
			if (!Player[i].IsEden())
			{
				noEden = false;
			}
		}
		else
		{
			trig[i] = CreateResearchTrigger(0, 1, 5000, i, "None");
		}
	}
	group = CreateSetTrigger(1, 0, pAI, pAI, "None", trig[0], trig[1], trig[2], trig[3]);
	CreateFailureCondition(1, 0, group, "If everyone loses his/her CC, it's game over");

	CreateTimeTrigger(1, 0, 10, "WreckageFailureCheck");
}

Export void WreckageFailureCheck()
{
	for (int i = 0; i < 5; i++)
	{
		if (wreckageStatus[i] == 3)
		{
			Trigger trig = CreateTimeTrigger(1, 1, 1, "None");
			CreateFailureCondition(1, 0, trig, "Wreckage Lost");
			return;
		}
	}
}

void SetupVictory(int pAI)
{
	Trigger trig;

	// "All other players"
	CreateTimeTrigger(1, 0, 10, "OtherPlayersCheck");
	OtherPlayers = CreateTimeTrigger(0, 0, 1, "None");
	CreateVictoryCondition(1, 0, OtherPlayers, "All players must complete their objectives.");

	// Evac Transports
	trig = CreateEvacTrigger(1, 0, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Have enough Evacuation Transports for your population.");

	// Research Explosive Charges
	trig = CreateResearchTrigger(1, 1, 7102, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Explosive Charges.");

	// GeoCons (E) or MHDs (P)
	if (Player[TethysGame::LocalPlayer()].IsEden())
	{
		// Research Geothermal Power
		trig = CreateResearchTrigger(1, 1, 6115, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Completely research Geothermal Power.");
	}
	else
	{
		// Research Magnetohydrodynamics
		trig = CreateResearchTrigger(1, 1, 6107, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Completely research Magnetohydrodynamics.");
	}

	// Research Scout-class Drive Train Refit
	trig = CreateResearchTrigger(1, 1, 7206, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Scout-class Drive Train Refit.");

	// Research Space Program
	trig = CreateResearchTrigger(1, 1, 6405, TethysGame::LocalPlayer(), "NewObj_SpaceStuff");
	CreateVictoryCondition(1, 0, trig, "Completely research the Space Program.");

	// Fifth wreckage piece
	trig = CreateResearchTrigger(1, 1, 8005, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Recover Conestoga wreckage at (50, 112).");

	// Fourth wreckage piece
	trig = CreateResearchTrigger(1, 1, 8004, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Recover Conestoga wreckage at (61, 29).");

	// Third wreckage piece
	trig = CreateResearchTrigger(1, 1, 8003, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Recover Conestoga wreckage at (116, 112).");

	// Second wreckage piece
	trig = CreateResearchTrigger(1, 1, 8002, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Recover Conestoga wreckage at (100, 5).");

	// First wreckage piece
	trig = CreateResearchTrigger(1, 1, 8001, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Recover Conestoga wreckage at (176, 57).");

	// Setup starship component check hacks
	switch (pAI)
	{
		// 4 player game
		case 4:
			CreateCountTrigger(1, 1, 3, mapEDWARDSatellite, mapNone, 1, cmpGreaterEqual, "P4_Edward");
			CreateCountTrigger(1, 1, 3, mapSkydock, mapNone, 1, cmpGreaterEqual, "P4_Skydock");
			CreateCountTrigger(1, 1, 3, mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "P4_IonDrive");
			CreateCountTrigger(1, 1, 3, mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "P4_FusionDrive");
			CreateCountTrigger(1, 1, 3, mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "P4_Fueling");
			CreateCountTrigger(1, 1, 3, mapCommandModule, mapNone, 1, cmpGreaterEqual, "P4_Command");
			CreateCountTrigger(1, 1, 3, mapHabitatRing, mapNone, 1, cmpGreaterEqual, "P4_Habitat");
		// 3 player game
		case 3:
			CreateCountTrigger(1, 1, 2, mapEDWARDSatellite, mapNone, 1, cmpGreaterEqual, "P3_Edward");
			CreateCountTrigger(1, 1, 2, mapSkydock, mapNone, 1, cmpGreaterEqual, "P3_Skydock");
			CreateCountTrigger(1, 1, 2, mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "P3_IonDrive");
			CreateCountTrigger(1, 1, 2, mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "P3_FusionDrive");
			CreateCountTrigger(1, 1, 2, mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "P3_Fueling");
			CreateCountTrigger(1, 1, 2, mapCommandModule, mapNone, 1, cmpGreaterEqual, "P3_Command");
			CreateCountTrigger(1, 1, 2, mapHabitatRing, mapNone, 1, cmpGreaterEqual, "P3_Habitat");
		// 2 player game
		case 2:
			CreateCountTrigger(1, 1, 1, mapEDWARDSatellite, mapNone, 1, cmpGreaterEqual, "P2_Edward");
			CreateCountTrigger(1, 1, 1, mapSkydock, mapNone, 1, cmpGreaterEqual, "P2_Skydock");
			CreateCountTrigger(1, 1, 1, mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "P2_IonDrive");
			CreateCountTrigger(1, 1, 1, mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "P2_FusionDrive");
			CreateCountTrigger(1, 1, 1, mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "P2_Fueling");
			CreateCountTrigger(1, 1, 1, mapCommandModule, mapNone, 1, cmpGreaterEqual, "P2_Command");
			CreateCountTrigger(1, 1, 1, mapHabitatRing, mapNone, 1, cmpGreaterEqual, "P2_Habitat");
		// 1 player game
		case 1:
			CreateCountTrigger(1, 1, 0, mapEDWARDSatellite, mapNone, 1, cmpGreaterEqual, "P1_Edward");
			CreateCountTrigger(1, 1, 0, mapSkydock, mapNone, 1, cmpGreaterEqual, "P1_Skydock");
			CreateCountTrigger(1, 1, 0, mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "P1_IonDrive");
			CreateCountTrigger(1, 1, 0, mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "P1_FusionDrive");
			CreateCountTrigger(1, 1, 0, mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "P1_Fueling");
			CreateCountTrigger(1, 1, 0, mapCommandModule, mapNone, 1, cmpGreaterEqual, "P1_Command");
			CreateCountTrigger(1, 1, 0, mapHabitatRing, mapNone, 1, cmpGreaterEqual, "P1_Habitat");
			break;
		// Should be impossible.
		case 0:
			TethysGame::AddMessage(-1, -1, "Zero player game?!  Critical error in mission script!", -1, sndSavnt227);
			break;
		// For 5/6 player games (impossible).
		default:
			TethysGame::AddMessage(-1, -1, "You didn't do a good job adding support for more players!", -1, sndSavnt227);
			break;
	}

}

Export void OtherPlayersCheck()
{
	bool objMet[4] = {true,true,true,true};

	UnitEx Unit1;
	for (int i = 0; i < 4; i++)
	{
		if (!Player[i].IsHuman())
		{
			continue;
		}

		int ets = 0;
		PlayerVehicleEnum CheckAll(i);
		while (CheckAll.GetNext(Unit1))
		{
			if (Unit1.GetType() == mapEvacuationTransport)
			{
				ets++;
			}
		}

		int k = Player[i].Kids(),
			w = Player[i].Workers(),
			s = Player[i].Scientists();

		if (!Player[i].HasTechnology(6405) || !Player[i].HasTechnology(7206) ||
			!Player[i].HasTechnology(7102) || !Player[i].HasTechnology(8601) ||
			!(Player[i].HasTechnology(6115) || Player[i].HasTechnology(6107)) ||
			!Player[i].HasTechnology(8801) || !Player[i].HasTechnology(8901) ||
			!Player[i].HasTechnology(8951) || !Player[i].HasTechnology(10202) ||
			!Player[i].HasTechnology(10205) || !hasEdward[i] ||
			!hasSkydock[i] || !hasIonDrive[i] || !hasFusionDrive[i] ||
			!hasFueling[i] || !hasCommand[i] || !hasHabitat[i] ||
			(k+w+s) - (ets*25) > 0)
		{
			objMet[i] = false;
			break;
		}
	}

	if (objMet[0] && objMet[1] && objMet[2] && objMet[3])
	{
		OtherPlayers.Enable();
	}
}

// --------------------------------------------------------------------------------------------------------------------
// Hack since there doesn't seem to be any other reliable way to figure out which components a player has launched.

// P1
Export void P1_Edward()
{
	hasEdward[0] = true;
}

Export void P1_Skydock()
{
	hasSkydock[0] = true;
}

Export void P1_IonDrive()
{
	hasIonDrive[0] = true;
}

Export void P1_FusionDrive()
{
	hasFusionDrive[0] = true;
}

Export void P1_Fueling()
{
	hasFueling[0] = true;
}

Export void P1_Command()
{
	hasCommand[0] = true;
}

Export void P1_Habitat()
{
	hasHabitat[0] = true;
}

// P2
Export void P2_Edward()
{
	hasEdward[1] = true;
}

Export void P2_Skydock()
{
	hasSkydock[1] = true;
}

Export void P2_IonDrive()
{
	hasIonDrive[1] = true;
}

Export void P2_FusionDrive()
{
	hasFusionDrive[1] = true;
}

Export void P2_Fueling()
{
	hasFueling[1] = true;
}

Export void P2_Command()
{
	hasCommand[1] = true;
}

Export void P2_Habitat()
{
	hasHabitat[1] = true;
}

// P3
Export void P3_Edward()
{
	hasEdward[2] = true;
}

Export void P3_Skydock()
{
	hasSkydock[2] = true;
}

Export void P3_IonDrive()
{
	hasIonDrive[2] = true;
}

Export void P3_FusionDrive()
{
	hasFusionDrive[2] = true;
}

Export void P3_Fueling()
{
	hasFueling[2] = true;
}

Export void P3_Command()
{
	hasCommand[2] = true;
}

Export void P3_Habitat()
{
	hasHabitat[2] = true;
}

// P4
Export void P4_Edward()
{
	hasEdward[3] = true;
}

Export void P4_Skydock()
{
	hasSkydock[3] = true;
}

Export void P4_IonDrive()
{
	hasIonDrive[3] = true;
}

Export void P4_FusionDrive()
{
	hasFusionDrive[3] = true;
}

Export void P4_Fueling()
{
	hasFueling[3] = true;
}

Export void P4_Command()
{
	hasCommand[3] = true;
}

Export void P4_Habitat()
{
	hasHabitat[3] = true;
}

// --------------------------------------------------------------------------------------------------------------------