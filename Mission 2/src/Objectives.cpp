#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"
#include "Globals.h"

// Triggers that update mission progress.
Trigger mp_ScannedCC,
		mp_ScientistsRescued,
		mp_LabDestroyed,
		mp_Tok1Destroyed,
		mp_Tok2Destroyed,
		mp_DefendersFiredAt;	// Only used on hard difficulty.  Triggers a "realistic" response.

// Failure checks
Trigger fc_NoScouts,
		fc_NoEvacTrans,
		fc_LoadedEvacTransDestroyed,
		fc_VitalBuildingDestroyed,
		fc_BlewUpLabEarly;

Unit LoadedEvacTrans;

void SetupVictory()
{
	Trigger trig;

	// Initial victory conditions - scan Eden CC, return loaded Evac Trans to start location
	mp_ScannedCC = CreateSpecialTarget(1, 0, CC, mapScout, "Scanned_CC");
	CreateVictoryCondition(1, 0, mp_ScannedCC, "Plant spies at the Command Center.");

	trig = CreateEscapeTrigger(1, 0, -1, 1 + 31, 53 - 1, 17, 10, 1, mapEvacuationTransport, mapInterColonyShuttle, 1, "None");
	CreateVictoryCondition(1, 0, trig, "Return the captive scientists to the convoy starting location.");

	// Not actually a victory condition, but needed to progress the mission
	mp_ScientistsRescued = CreateSpecialTarget(1, 1, ALab, mapEvacuationTransport, "GotScientists");
}

void SetupFailure()
{
	Trigger noScouts[4], noETs[4], group;
	int i;

	// At least one player-owned scout and Evac Transport must survive until certain points in the mission.
	for (i = 0; i < 4; i++)
	{
		if (i < numAI)
		{
			noScouts[i] = CreateCountTrigger(1, 0, i, mapScout, mapAny, 0, cmpEqual, "None");
			noETs[i] = CreateCountTrigger(1, 0, i, mapEvacuationTransport, mapAny, 0, cmpEqual, "None");
		}
		else
		{
			// Some impossible condition (tech 5701 is for lava walls, which are never made available)
			noScouts[i] = CreateResearchTrigger(0, 1, 5701, i, "None");
			noETs[i] = CreateResearchTrigger(0, 1, 5701, i, "None");
		}
	}
	fc_NoScouts = CreateSetTrigger(1, 0, numAI, numAI, "None", noScouts[0], noScouts[1], noScouts[2], noScouts[3]);
	CreateFailureCondition(1, 0, fc_NoScouts, "All player Scouts destroyed");

	fc_NoEvacTrans = CreateSetTrigger(1, 0, numAI, numAI, "None", noETs[0], noETs[1], noETs[2], noETs[3]);
	CreateFailureCondition(1, 0, fc_NoEvacTrans, "All player Evac Transports destroyed");

	fc_BlewUpLabEarly = CreateTimeTrigger(1, 0, 10, "CheckAdvLab1");
	//fc_BlewUpLabEarly = CreateCountTrigger(1, 0, numAI, mapAdvancedLab, mapNone, 0, cmpEqual, "None");
	//CreateFailureCondition(1, 0, fc_BlewUpLabEarly, "Lab destroyed before scientists rescued.");

	fc_VitalBuildingDestroyed = CreateTimeTrigger(1, 0, 10, "CheckCC");
}

Export void GotScientists()
{
	GetSpecialTargetData(mp_ScientistsRescued, LoadedEvacTrans);
	LoadedEvacTrans.SetCargo(mapInterColonyShuttle, mapNone);

	TethysGame::AddMessage(-1, -1, "Scientists have been retrieved.", -1, sndBeep8);
	fc_BlewUpLabEarly.Destroy();
	fc_NoEvacTrans.Disable();

	Trigger trig;

	// Create new objective to destroy the advanced lab.
	mp_LabDestroyed = CreateCountTrigger(1, 0, numAI, mapAdvancedLab, mapNone, 0, cmpEqual, "None");
	CreateVictoryCondition(1, 0, mp_LabDestroyed, "Destroy the Advanced Lab.");
	TethysGame::AddMessage(-1, -1, "Eden is now aware of your presence, commanders.  Destroy that lab and get out of there!", -1, sndSavant30);

	// Add a check - if the ET holding the scientists is destroyed, it's game over.
	fc_LoadedEvacTransDestroyed = CreateTimeTrigger(1, 0, 10, "CheckLoadedEvacTrans");

	// Set all Eden forces to hostile.
	GoHostile();

	// Transfer any disabled GPs back to the AI and disable the destroyed Tokamak checks.
	if (Tok1.IsLive())
	{
		mp_Tok1Destroyed.Destroy();
	}

	if (Tok2.IsLive())
	{
		mp_Tok2Destroyed.Destroy();
	}

	Unit Unit1;
	map_id weapon;
	PlayerBuildingEnum GPs(numAI + 1, mapGuardPost);
	while (GPs.GetNext(Unit1))
	{
		Unit1.DoTransfer(numAI);
	}

	// Create player reinforcements.
	for (int i = 0; i < numAI; i++)
	{
		if (Player[i].IsEden())
		{
			weapon = mapLaser;
		}
		else
		{
			weapon = mapMicrowave;
		}

		switch (Player[i].Difficulty())
		{
		default:
		case 0:
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
		case 1:
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(5 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(4 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
		case 2:
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(3 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1 + 31, 63 - 1 - i), i, weapon, 0);
			Unit1.DoSetLights(1);
			break;
		}
	}

	TethysGame::AddMessage(6 * 32, 60 * 32, "Reinforcements ready.", -1, sndSavnt205);

	// Change AI behavior
	EdenReact();

	// Clear the lab's special target data.
	ALab.ClearSpecialTarget();
}

Export void Scanned_CC()
{
	CC.ClearSpecialTarget();
	fc_NoScouts.Disable();
	TethysGame::AddMessage(-1, -1, "Our spies have successfully infiltrated Eden.", -1, sndBeep8);
}

Export void CheckLoadedEvacTrans()
{
	if (!LoadedEvacTrans.IsLive())
	{
		CreateFailureCondition(1, 0, fc_VitalBuildingDestroyed, ".");
	}
}

Export void CheckAdvLab1()
{
	if (!ALab.IsLive())
	{
		CreateFailureCondition(1, 0, fc_BlewUpLabEarly, ".");
	}
}

Export void CheckCC()
{
	if (!CC.IsLive() || !SF1.IsLive() || !SF2.IsLive() ||
		!VF1.IsLive() || !VF2.IsLive() || !VF3.IsLive() ||
		!Smelter1.IsLive() || !Smelter2.IsLive())
	{
		CreateFailureCondition(1, 0, fc_VitalBuildingDestroyed, ".");
	}
}
