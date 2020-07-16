#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"

Trigger OtherPlayers;

void SetupVictory()
{
	Trigger trig;

	// "All other players"
	CreateTimeTrigger(1, 0, 10, "OtherPlayersCheck");
	OtherPlayers = CreateTimeTrigger(0, 0, 1, "None");
	CreateVictoryCondition(1, 0, OtherPlayers, "All players must complete their objectives.");

	// Tokamak
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapConVec, mapTokamak, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have a Tokamak kit in a ConVec.");

	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapConVec, mapAgridome, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have an Agridome kit in a ConVec.");

	// Common Ore Smelter
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapConVec, mapCommonOreSmelter, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have a Common Ore Smelter kit in a ConVec.");

	// Structure Factory
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapConVec, mapStructureFactory, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have a Structure Factory kit in a ConVec.");

	// Command Center
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapConVec, mapCommandCenter, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have a Command Center kit in a ConVec.");

	// Food in trucks
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapCargoTruck, (map_id)truckFood, 3, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 3000 units of food in Cargo Trucks.");

	// Common metal in trucks
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapCargoTruck, (map_id)truckCommonMetal, 5, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 5000 units of Metals in Cargo Trucks.");

	// Robo-Surveyor
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapRoboSurveyor, mapAny, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 1 or more Robo-Surveyors.");

	// Robo-Miner
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapRoboMiner, mapAny, 1, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 1 or more Robo-Miners.");

	// Scouts
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapScout, mapAny, 3, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 3 or more Scouts.");

	// Lynx
	trig = CreateCountTrigger(1, 0, TethysGame::LocalPlayer(), mapLynx, mapAny, 7, cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have 7 or more Lynx.");

	// Evac Transports
	trig = CreateEvacTrigger(1, 0, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Have enough Evacuation Transports for your population.");

	// Research Cybernetic Teleoperation
	trig = CreateResearchTrigger(1, 0, 3401, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Cybernetic Teleoperation.");

	// Research Health Maintenance
	trig = CreateResearchTrigger(1, 0, 3303, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Health Maintenance.");

	// Research Emergency Response Systems
	trig = CreateResearchTrigger(1, 0, 3301, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Emergency Response Systems.");

	// Research Mobile Weapons Platform
	trig = CreateResearchTrigger(1, 0, 3851, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Mobile Weapons Platform.");

	// Population -- Scientists
	trig = CreateResourceTrigger(1, 0, resScientists, 16, TethysGame::LocalPlayer(), cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have at least 16 scientists alive.");

	// Population -- Workers
	trig = CreateResourceTrigger(1, 0, resWorkers, 22, TethysGame::LocalPlayer(), cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have at least 22 workers alive.");

	// Population -- Children
	trig = CreateResourceTrigger(1, 0, resKids, 28, TethysGame::LocalPlayer(), cmpGreaterEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Have at least 28 children alive.");
}

void SetupFailure()
{
	Trigger trig[4], group;
	int i;

	// Defeat (at least one player has no operational CCs)
	for (i = 0; i < 4; i++)
	{
		if (i < numAI)
		{
			trig[i] = CreateOperationalTrigger(1, 0, i, mapCommandCenter, 0, cmpEqual, "None");
		}
		else
		{
			// Some impossible condition (tech 5701 is for lava walls, which are never made available)
			trig[i] = CreateResearchTrigger(0, 1, 5701, i, "None");
		}
	}
	group = CreateSetTrigger(1, 0, numAI, numAI, "None", trig[0], trig[1], trig[2], trig[3]);
	CreateFailureCondition(1, 0, group, "All players have lost their CCs");
}

Export void OtherPlayersCheck()
{
	bool objMet[4] = { true,true,true,true };

	UnitEx Unit1;
	for (int i = 0; i < numAI; i++)
	{
		if (!Player[i].IsHuman())
		{
			continue;
		}

		bool agri = false,
			tok = false,
			cc = false,
			sf = false,
			cos = false,
			miner = false,
			surveyor = false;
		int ets = 0, scouts = 0, lynx = 0, metal = 0, food = 0;

		PlayerVehicleEnum CheckAll(i);
		while (CheckAll.GetNext(Unit1))
		{
			map_id cargo = Unit1.GetCargo();
			if (Unit1.GetType() == mapConVec)
			{
				if (cargo == mapCommandCenter)
				{
					cc = true;
				}
				else if (cargo == mapStructureFactory)
				{
					sf = true;
				}
				else if (cargo == mapCommonOreSmelter)
				{
					cos = true;
				}
				else if (cargo == mapTokamak)
				{
					tok = true;
				}
				else if (cargo == mapAgridome)
				{
					agri = true;
				}
				else
				{
					//continue;
				}
			}

			else if (Unit1.GetType() == mapCargoTruck)
			{
				if (Unit1.GetCargoType() == truckCommonMetal)
				{
					metal++;
				}
				else if (Unit1.GetCargoType() == truckFood)
				{
					food++;
				}
				else
				{
					//continue;
				}
			}

			else if (Unit1.GetType() == mapRoboSurveyor)
			{
				surveyor = true;
			}

			else if (Unit1.GetType() == mapRoboMiner)
			{
				miner = true;
			}

			else if (Unit1.GetType() == mapScout)
			{
				scouts++;
			}

			else if (Unit1.GetType() == mapLynx)
			{
				lynx++;
			}

			else if (Unit1.GetType() == mapEvacuationTransport)
			{
				ets++;
			}

			else
			{
				//continue;
			}
		}

		int k = Player[i].Kids(),
			w = Player[i].Workers(),
			s = Player[i].Scientists();
		if (!agri || !tok || !cc || !sf || !cos || !miner || !surveyor ||
			scouts < 3 || lynx < 7 || metal < 5 || food < 3 ||
			k < 28 || w < 22 || s < 16 ||
			!Player[i].HasTechnology(3851) || !Player[i].HasTechnology(3301) ||
			!Player[i].HasTechnology(3303) || !Player[i].HasTechnology(3401) ||
			(k + w + s) - (ets * 25) > 0)
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