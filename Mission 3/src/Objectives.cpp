#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "Objectives.h"

extern int numAI;

Trigger OtherPlayers,
        Survive;


void SetupFailure(int pAI)
{
	Trigger trig[4], group;
	int i;

	// Defeat (at least one player has no operational CCs)
	for (i = 0; i < 4; i++)
	{
		if (i < pAI)
		{
			trig[i] = CreateOperationalTrigger(1, 0, i, mapCommandCenter, 0, cmpEqual, "None");
		}
		else
		{
			trig[i] = CreateResearchTrigger(0, 1, 5000, i, "None");
		}
	}
	group = CreateSetTrigger(1, 0, pAI, pAI, "None", trig[0], trig[1], trig[2], trig[3]);
	CreateFailureCondition(1, 0, group, "If everyone loses his/her CC, it's game over");
}

void SetupVictory(int pAI)
{
	Trigger trig;

	// "All other players"
	CreateTimeTrigger(1, 0, 10, "OtherPlayersCheck");
	OtherPlayers = CreateTimeTrigger(0, 0, 1, "None");
	CreateVictoryCondition(1, 0, OtherPlayers, "All players must complete their objectives.");

	// Rail Gun (E) or RPG (P)
	if (Player[TethysGame::LocalPlayer()].IsEden())
	{
		// Research Directional Magnetic Fields
		trig = CreateResearchTrigger(1, 0, 5506, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Completely research Directional Magnetic Fields.");
	}
	else
	{
		// Research Rocket Propulsion
		trig = CreateResearchTrigger(1, 0, 5602, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Completely research Rocket Propulsion.");
	}

	// Research Advanced Combat Chassis
	trig = CreateResearchTrigger(1, 0, 5201, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Advanced Combat Chassis.");

	// Independent Turret Power Systems
	trig = CreateResearchTrigger(1, 0, 5111, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Independent Turret Power Systems .");

	// Research Electromagnetic Pulsing
	trig = CreateResearchTrigger(1, 0, 5508, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Electromagnetic Pulsing.");

	// Research Meteorology
	trig = CreateResearchTrigger(1, 0, 5302, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Meteorology.");

	// "Survive AI attacks"
	trig = CreateTimeTrigger(1, 1, 100, "None");
	Survive = CreateVehicleCountTrigger(1, 0, numAI, 0, cmpEqual, "None");
	CreateVictoryCondition(1, 0, CreateSetTrigger(1, 0, 2, 2, "None", trig, Survive), "Survive until reinforcements can arrive.");
}

void OtherPlayersCheck()
{
	bool objMet[4] = {true,true,true,true};

	UnitEx Unit1;
	for (int i = 0; i < 4; i++)
	{
		if (!Player[i].IsHuman())
		{
			continue;
		}

		if (!Player[i].HasTechnology(5508) || !Player[i].HasTechnology(5111) ||
			!Player[i].HasTechnology(5201) || !Player[i].HasTechnology(5302) ||
			!(Player[i].HasTechnology(5602) || Player[i].HasTechnology(5506)))
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

void EnableNoEnemyUnitsCheck()
{
	Survive.Enable();
}