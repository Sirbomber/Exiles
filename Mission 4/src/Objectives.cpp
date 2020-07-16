#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "Objectives.h"
#include "AI.h"

extern int numAI;

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

Export void NewObj_SpaceStuff()
{
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);

	// Research Skydock
	trig = CreateResearchTrigger(1, 1, 8601, TethysGame::LocalPlayer(), "NewObj_LaunchSkydock");
	CreateVictoryCondition(1, 0, trig, "Completely research the Skydock.");

	// Launch EDWARD
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapEDWARDSatellite, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place an EDWARD Satellite in orbit.");
}

Export void NewObj_LaunchSkydock()
{
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);

	// Launch Skydock
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapSkydock, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Skydock in orbit.");
}

void SetupWreckCheck()
{
	for (int i = 0; i < 5; i++)
	{
		wreckageStatus[i] = 0;
	}

	CreateTimeTrigger(1, 0, 10, "WreckCheck");
}

Export void WreckCheck()
{
	UnitEx wTruck;

	// ---------------------------------------------------------------------------
	// Ion Drive Module
	if (wreckageStatus[0] == 0)
	{
		// Check if the wreckage has been bulldozed or built over
		if (GameMap::GetCellType(LOCATION(176+31, 57-1)) != cellMediumPassible2)
		{
			wreckageStatus[0] = 3;
		}

		// Otherwise, check if there's a truck carrying this wreckage.
		LocationEnumerator findTruck(LOCATION(176+31, 57-1));
		while (findTruck.GetNext(wTruck))
		{
			if (wTruck.GetType() == mapCargoTruck &&
				wTruck.GetCargoType() == truckGarbage &&
				wTruck.GetCargoAmount() == 8001)
			{
				wreckageTrucks[0] = wTruck;
				wreckageStatus[0] = 1;
			}
		}
	}

	else if (wreckageStatus[0] == 1)
	{
		if (Player[wreckageTrucks[0].OwnerID()].HasTechnology(8001))
		{
			wreckageStatus[0] = 2;
		}

		else
		{
			if (wreckageTrucks[0].GetCargoType() != truckGarbage ||
				!wreckageTrucks[0].IsLive() ||
				(wreckageTrucks[0].OwnerID() == numAI && noEden))
			{
				wreckageStatus[0] = 3;
			}
		}
	}

	// ---------------------------------------------------------------------------
	// Fusion Drive Module
	if (wreckageStatus[1] == 0)
	{
		// Check if the wreckage has been bulldozed or built over
		if (GameMap::GetCellType(LOCATION(100+31, 5-1)) != cellMediumPassible2)
		{
			wreckageStatus[1] = 3;
		}

		// Otherwise, check if there's a truck carrying this wreckage.
		LocationEnumerator findTruck(LOCATION(100+31, 5-1));
		while (findTruck.GetNext(wTruck))
		{
			if (wTruck.GetType() == mapCargoTruck &&
				wTruck.GetCargoType() == truckGarbage &&
				wTruck.GetCargoAmount() == 8002)
			{
				wreckageTrucks[1] = wTruck;
				wreckageStatus[1] = 1;

				// Trigger AI response
				TriggerFusionDriveTrap(wTruck);
			}
		}
	}

	else if (wreckageStatus[1] == 1)
	{
		if (Player[wreckageTrucks[1].OwnerID()].HasTechnology(8002))
		{
			wreckageStatus[1] = 2;
		}

		else
		{
			if (wreckageTrucks[1].GetCargoType() != truckGarbage ||
				!wreckageTrucks[1].IsLive() ||
				(wreckageTrucks[1].OwnerID() == numAI && noEden))
			{
				wreckageStatus[1] = 3;
			}
		}
	}

	// ---------------------------------------------------------------------------
	// Fueling Systems
	if (wreckageStatus[2] == 0)
	{
		// Check if the wreckage has been bulldozed or built over
		if (GameMap::GetCellType(LOCATION(116+31, 112-1)) != cellFastPassible1)
		{
			wreckageStatus[2] = 3;
		}

		// Otherwise, check if there's a truck carrying this wreckage.
		LocationEnumerator findTruck(LOCATION(116+31, 112-1));
		while (findTruck.GetNext(wTruck))
		{
			if (wTruck.GetType() == mapCargoTruck &&
				wTruck.GetCargoType() == truckGarbage &&
				wTruck.GetCargoAmount() == 8003)
			{
				wreckageTrucks[2] = wTruck;
				wreckageStatus[2] = 1;

				// Trigger AI response
				TriggerFuelingTrap_Decoy(wTruck);
			}
		}
	}

	else if (wreckageStatus[2] == 1)
	{
		if (Player[wreckageTrucks[2].OwnerID()].HasTechnology(8003))
		{
			wreckageStatus[2] = 2;
		}

		else
		{
			if (wreckageTrucks[2].GetCargoType() != truckGarbage ||
				!wreckageTrucks[2].IsLive() ||
				(wreckageTrucks[2].OwnerID() == numAI && noEden))
			{
				wreckageStatus[2] = 3;
			}
		}
	}

	// ---------------------------------------------------------------------------
	// Command Module
	if (wreckageStatus[3] == 0)
	{
		// Check if the wreckage has been bulldozed or built over
		if (GameMap::GetCellType(LOCATION(61+31, 29-1)) != cellFastPassible2)
		{
			wreckageStatus[3] = 3;
		}

		// Otherwise, check if there's a truck carrying this wreckage.
		LocationEnumerator findTruck(LOCATION(61+31, 29-1));
		while (findTruck.GetNext(wTruck))
		{
			if (wTruck.GetType() == mapCargoTruck &&
				wTruck.GetCargoType() == truckGarbage &&
				wTruck.GetCargoAmount() == 8004)
			{
				wreckageTrucks[3] = wTruck;
				wreckageStatus[3] = 1;

				// Trigger AI response
				TriggerCommandTrap(wTruck);
			}
		}
	}

	else if (wreckageStatus[3] == 1)
	{
		if (Player[wreckageTrucks[3].OwnerID()].HasTechnology(8004))
		{
			wreckageStatus[3] = 2;
		}

		else
		{
			if (wreckageTrucks[3].GetCargoType() != truckGarbage ||
				!wreckageTrucks[3].IsLive() ||
				(wreckageTrucks[3].OwnerID() == numAI && noEden))
			{
				wreckageStatus[3] = 3;
			}
		}
	}

	// ---------------------------------------------------------------------------
	// Habitat Ring
	if (wreckageStatus[4] == 0)
	{
		// Check if the wreckage has been bulldozed or built over
		if (GameMap::GetCellType(LOCATION(50+31, 112-1)) != cellFastPassible2)
		{
			wreckageStatus[4] = 3;
		}

		// Otherwise, check if there's a truck carrying this wreckage.
		LocationEnumerator findTruck(LOCATION(50+31, 112-1));
		while (findTruck.GetNext(wTruck))
		{
			if (wTruck.GetType() == mapCargoTruck &&
				wTruck.GetCargoType() == truckGarbage &&
				wTruck.GetCargoAmount() == 8005)
			{
				wreckageTrucks[4] = wTruck;
				wreckageStatus[4] = 1;

				// Trigger AI response
				TriggerHabitatTrap(wTruck);
			}
		}
	}

	else if (wreckageStatus[4] == 1)
	{
		if (Player[wreckageTrucks[4].OwnerID()].HasTechnology(8005))
		{
			wreckageStatus[4] = 2;
		}

		else
		{
			if (wreckageTrucks[4].GetCargoType() != truckGarbage ||
				!wreckageTrucks[4].IsLive() ||
				(wreckageTrucks[4].OwnerID() == numAI && noEden))
			{
				wreckageStatus[4] = 3;
			}
		}
	}

	// If all wreckages collected, trigger AI panic mode
	if (wreckageStatus[0] != 0 &&
		wreckageStatus[1] != 0 &&
		wreckageStatus[2] != 0 &&
		wreckageStatus[3] != 0 &&
		wreckageStatus[4] != 0)
	{
		TriggerPanic();
	}
}

// The triggers set up by this function also disable the "fail on wreckage not in cargo truck" checks
void SetupTechShare()
{
	CreateResearchTrigger(1, 1, 8001, -1, "EnableIonDrive");
	CreateResearchTrigger(1, 1, 8002, -1, "EnableFusionDrive");
	CreateResearchTrigger(1, 1, 8003, -1, "EnableFuelingSystems");
	CreateResearchTrigger(1, 1, 8004, -1, "EnableCommandModule");
	CreateResearchTrigger(1, 1, 8005, -1, "EnableHabitatRing");
}

Export void EnableIonDrive()
{
	// Share the enabler tech with all players.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(8001);
	}

	// Add new objective to research the new component
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateResearchTrigger(1, 1, 8801, TethysGame::LocalPlayer(), "NewObj_LaunchIonDrive");
	CreateVictoryCondition(1, 0, trig, "Completely research the Ion Drive Module.");
}

Export void EnableFusionDrive()
{
	// Share the enabler tech with all players.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(8002);
	}

	// Add new objective to research the new component
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateResearchTrigger(1, 1, 8901, TethysGame::LocalPlayer(), "NewObj_LaunchFusionDrive");
	CreateVictoryCondition(1, 0, trig, "Completely research the Fusion Drive Module.");
}

Export void EnableFuelingSystems()
{
	// Share the enabler tech with all players.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(8003);
	}

	// Add new objective to research the new component
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateResearchTrigger(1, 1, 8951, TethysGame::LocalPlayer(), "NewObj_LaunchFuelingSystems");
	CreateVictoryCondition(1, 0, trig, "Completely research the Fueling Systems.");
}

Export void EnableCommandModule()
{
	// Share the enabler tech with all players.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(8004);
	}

	// Add new objective to research the new component
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateResearchTrigger(1, 1, 10202, TethysGame::LocalPlayer(), "NewObj_LaunchCommandModule");
	CreateVictoryCondition(1, 0, trig, "Completely research the Command Module.");
}

Export void EnableHabitatRing()
{
	// Share the enabler tech with all players.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(8005);
	}

	// Add new objective to research the new component
	Trigger trig;
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateResearchTrigger(1, 1, 10205, TethysGame::LocalPlayer(), "NewObj_LaunchHabitatRing");
	CreateVictoryCondition(1, 0, trig, "Completely research the Habitat Ring.");
}

Export void NewObj_LaunchIonDrive()
{
	Trigger trig;

	// Launch Ion Drive
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapIonDriveModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Ion Drive Module in orbit.");
}

Export void NewObj_LaunchFusionDrive()
{
	Trigger trig;

	// Launch Fusion Drive
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapFusionDriveModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Fusion Drive Module in orbit.");
}

Export void NewObj_LaunchFuelingSystems()
{
	Trigger trig;

	// Launch Fueling Systems
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapFuelingSystems, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Fueling Systems in orbit.");
}

Export void NewObj_LaunchCommandModule()
{
	Trigger trig;

	// Launch Command Module
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapCommandModule, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Command Module in orbit.");
}

Export void NewObj_LaunchHabitatRing()
{
	Trigger trig;

	// Launch Habitat Ring
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	trig = CreateCountTrigger(1, 1, TethysGame::LocalPlayer(), mapHabitatRing, mapNone, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Place the Habitat Ring in orbit.");
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