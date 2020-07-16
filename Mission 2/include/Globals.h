#pragma once

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

// Global stuff used by the AI and objectives.
extern int numAI;
	
extern Unit CC, SF1, SF2, Smelter1, Smelter2, Mine, VF1, VF2, VF3, ALab, Tok1, Tok2, Garage;
//extern FightGroup NW, SW, SE1, SE2, Lab, Etc, I1, I2, Patrol1, Patrol2, Temp, Plymz;
//extern MiningGroup C1, C2;
//extern BuildingGroup S1, S2, V1, V2, V3;

extern Unit LoadedEvacTrans;

	// AI group control flags
//extern bool Hostile,
	//	 FlagSE,
		// FlagPatrol;

	// Triggers that update mission progress.
extern Trigger mp_ScannedCC,
		mp_ScientistsRescued,
		mp_LabDestroyed,
		mp_Tok1Destroyed,
		mp_Tok2Destroyed,
		mp_DefendersFiredAt;	// Only used on hard difficulty.  Triggers a "realistic" response.

	// Failure checks
extern Trigger fc_NoScouts,
		fc_NoEvacTrans,
		fc_LoadedEvacTransDestroyed,
		fc_VitalBuildingDestroyed,
		fc_BlewUpLabEarly;

