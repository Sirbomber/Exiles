#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include <stdio.h>
#include "Objectives.h"
#include "AI.h"

// AI "research" objective data
int edenResearchProgress = 0;		// Current progress towards research
int maxResearchPoints = 9600;		// Total cost of the research project
int pointsPerLab = 8;				// How many points per update each lab contributes to the research project
int numLabsAlive = 0;				// This will get set to its actual value after setting up the AI base.
int numCCsAlive = 0;
UnitEx edenLabs[6], edenCCs[2];
bool doneWithCCs = false, doneWithLabs = false;

// 8 points per lab
// 6 labs = 48 points per update = 200 updates to complete = 350 marks
// 5 labs = 40 points per update = 240 updates to complete = 420 marks
// 4 labs = 32 points per update = 300 updates to complete = 525 marks
// 3 labs = 24 points per update = 400 updates to complete = 700 marks
// 2 labs = 20 points per update = 480 updates to complete = 840 marks (lab output is boosted slightly with only 2 labs left)
// 1 lab  = 16 points per update = 600 updates to complete = 1,050 marks (lab output is doubled with only 1 lab left)
// 1 update every 1.75 marks

Trigger OtherPlayers,
		LabObj,
		CommandCenterObj,
		ResearchObj,
		vc_ResearchObj,
		StructureCheck;

// To do:
// Triggers for scanning labs both before and after research completes
//  If scanned before: show research progress
//  If scanned after: trigger next phase of mission
// Update other player check
// Detect when a lab gets destroyed and adjust numLabsAlive and pointsPerLab appropriately (+4 if only 1 lab left)

void PassUnitIdsToObjectives(Unit toAdd)
{
	if (toAdd.GetType() == mapAdvancedLab)
	{
		edenLabs[numLabsAlive].unitID = toAdd.unitID;
		CreateSpecialTarget(1, 0, edenLabs[numLabsAlive], mapScout, "ScanLab");
		numLabsAlive++;
	}
	else if (toAdd.GetType() == mapCommandCenter)
	{
		edenCCs[numCCsAlive].unitID = toAdd.unitID;
		numCCsAlive++;
	}
}

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
			trig[i] = CreateResearchTrigger(0, 1, 5555, i, "None");
		}
	}
	group = CreateSetTrigger(1, 0, pAI, pAI, "None", trig[0], trig[1], trig[2], trig[3]);
	CreateFailureCondition(1, 0, group, "If everyone loses his/her CC, it's game over");

	StructureCheck = CreateTimeTrigger(1, 0, 4, "CheckMissionCriticalStructuresDestroyed");
}

void SetupVictory(int pAI)
{
	Trigger trig;

	// "All other players"
	CreateTimeTrigger(1, 0, 10, "OtherPlayersCheck");
	OtherPlayers = CreateTimeTrigger(0, 0, 1, "None");
	CreateVictoryCondition(1, 0, OtherPlayers, "All players must complete their objectives.");

	// Dummy objective used for "at least one CC must survive"
	CommandCenterObj = CreateTimeTrigger(0, 1, 4, "MarkDoneWithCCs");
	CreateVictoryCondition(1, 0, CommandCenterObj, "At least one of Eden's Command Centers must remain operational until research data has been completed.");

	// Dummy objective used for "at least one lab must survive"
	LabObj = CreateTimeTrigger(0, 1, 4, "MarkDoneWithLabs");
	CreateVictoryCondition(1, 0, LabObj, "At least one of Eden's Advanced Labs must survive until research data has been extracted.");

	// Objective to check if Eden is done researching
	ResearchObj = CreateTimeTrigger(1, 0, 175, "UpdateEdenResearch");
	vc_ResearchObj = CreateVictoryCondition(0, 0, CommandCenterObj, "Defend Eden's Advanced Labs until their counteragent research is complete.");
}

Export void MarkDoneWithCCs()
{
	doneWithCCs = true;
}

Export void MarkDoneWithLabs()
{
	doneWithLabs = true;
}

Export void OtherPlayersCheck()	// *** TO DO!!! ***
{
	// to do for mission 7
	bool objMet[4] = {true,true,true,true};

	UnitEx Unit1;
	for (int i = 0; i < 4; i++)
	{
		if (!Player[i].IsHuman())
		{
			continue;
		}
		
		int ets = 0,
			lynx = 0,
			panthers = 0,
			tigers = 0;
		PlayerVehicleEnum CheckAll(i);
		while (CheckAll.GetNext(Unit1))
		{
			if (Unit1.GetType() == mapEvacuationTransport)
			{
				ets++;
			}
			else if (Unit1.GetType() == mapLynx)
			{
				lynx++;
			}
			else if (Unit1.GetType() == mapPanther)
			{
				panthers++;
			}
			else if (Unit1.GetType() == mapTiger)
			{
				tigers++;
			}
		}

		int k = Player[i].Kids(),
			w = Player[i].Workers(),
			s = Player[i].Scientists();
		
		if (!Player[i].HasTechnology(8201) || !Player[i].HasTechnology(10204) ||
			lynx < 20 || panthers < 16 || tigers < 12 ||
			ExtPlayer[i].GetSatelliteCount(mapSolarSatellite) < 2 ||
			ExtPlayer[i].GetSatelliteCount(mapStasisSystems) < 1 ||
			ExtPlayer[i].GetSatelliteCount(mapSensorPackage) < 1 /*||
			(k+w+s) - (ets*25) > 0*/)
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

Export void UpdateEdenResearch()
{
	edenResearchProgress += (pointsPerLab * numLabsAlive);
	if (edenResearchProgress >= maxResearchPoints)
	{
		// Mark the associated victory condition as complete
		vc_ResearchObj.Enable();
		CommandCenterObj.Enable();
		ResearchObj.Disable();

		// Add the next step to the objectives list
		Trigger trig;
		trig = CreateResearchTrigger(1, 0, 9001, TethysGame::LocalPlayer(), "None");
		CreateVictoryCondition(1, 0, trig, "Use a Scout to secure Eden's research data.");
		TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);
	}
}

void NewObj_ResearchMicrobeWalls()
{
	Trigger trig;
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		Player[i].MarkResearchComplete(9001);
	}
	trig = CreateResearchTrigger(1, 0, 8401, TethysGame::LocalPlayer(), "None");
	CreateVictoryCondition(1, 0, trig, "Completely research Blight-Resistant Isotopes.");
	TethysGame::AddMessage(-1, -1, "New objective.", -1, sndSavant30);

	// Eden's labs are no longer relevant.  Clear the related objectives and failure conditions.
	LabObj.Enable();
}

Export void CheckMissionCriticalStructuresDestroyed()
{
	bool anyCCs = false;
	int labsTemp = 0;

	// Check CCs
	if (doneWithCCs)
	{
		anyCCs = true;
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			if (edenCCs[i].IsLive() && edenCCs[i].GetType() == mapCommandCenter /* && check not disabled*/)
			{
				anyCCs = true;
				break;
			}
		}
	}

	// Check labs
	if (doneWithLabs)
	{
		labsTemp = 1;
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (edenLabs[i].IsLive() && edenLabs[i].GetType() == mapAdvancedLab)
			{
				labsTemp++;
			}
		}
		// Update the alive labs count and bump up the research rate if the players are struggling
		numLabsAlive = labsTemp;
		switch (numLabsAlive)
		{
		case 2:
			pointsPerLab = 20;
			break;
		case 1:
			pointsPerLab = 16;
			break;
		}
	}

	// If either of these checks failed, end the mission
	if (!anyCCs || labsTemp == 0)
	{
		CreateFailureCondition(1, 0, StructureCheck, "All mission critical structures destroyed");
	}
}

Export void ScanLab()
{
	char buffer[50];
	// Labs still researching the counteragent
	if (edenResearchProgress < maxResearchPoints)
	{
		snprintf(buffer, 50, "Microbe Counteragent Research: %i / %i", edenResearchProgress, maxResearchPoints);
		TethysGame::AddMessage(-1, -1, buffer, -1, sndSavnt201);
	}
	// Research completed but not yet stolen
	else
	{
		TethysGame::AddMessage(-1, -1, "Research data procured!", -1, sndSavnt201);
		NewObj_ResearchMicrobeWalls();
		for (int i = 0; i < 6; i++)
		{
			if (edenLabs[i].IsLive())
			{
				edenLabs[i].ClearSpecialTarget();
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------
