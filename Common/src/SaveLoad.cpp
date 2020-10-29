#include <Outpost2DLL.h>
#include <HFL.h>

#include "SaveLoad.h"


/*
To-do: save code
void WriteSaveGame(char *saveName)
{
	//
}
*/

/*
To-do: load code
void ReadSaveGame(char *saveName)
{
	//
}
*/

// If no savegame, assume the player researched everything possible in the previous mission
// and give everything.
void SetMissionTechLevel(int mission, int player)
{
	// Player[player].MarkResearchComplete();
	switch (mission)
	{
		case 7:
			// Automatically give Mission 6's research topics.
			Player[player].MarkResearchComplete(8000);		// Mission 6 enabler tech
			Player[player].MarkResearchComplete(8201);		// Dual-Turret Weapons Systems
			Player[player].MarkResearchComplete(10204);		// Solar Power
			Player[player].MarkResearchComplete(10206);		// Sensor Package
			Player[player].MarkResearchComplete(10208);		// Stasis Systems

			// Also give the starship components and satellites the player should have.
			ExtPlayer[player].SetSatelliteCount(mapSolarSatellite, 2);
			ExtPlayer[player].SetSatelliteCount(mapSensorPackage, 1);
			ExtPlayer[player].SetSatelliteCount(mapStasisSystems, 1);
		case 6:
			// Mission 5 is a unit mission; no research to give.
		case 5:
			// Automatically give Mission 4's research topics.
			Player[player].MarkResearchComplete(6000);		// Mission 4 enabler tech
			Player[player].MarkResearchComplete(8001);		// Ion Drive Module enabler tech
			Player[player].MarkResearchComplete(8002);		// Fusion Drive Module enabler tech
			Player[player].MarkResearchComplete(8003);		// Fueling Systems enabler tech
			Player[player].MarkResearchComplete(8004);		// Command Module enabler tech
			Player[player].MarkResearchComplete(8005);		// Habitat Ring enabler tech
			Player[player].MarkResearchComplete(6405);		// Space Program
			Player[player].MarkResearchComplete(8601);		// Skydock
			Player[player].MarkResearchComplete(8801);		// Ion Drive Module
			Player[player].MarkResearchComplete(8901);		// Fusion Drive Module
			Player[player].MarkResearchComplete(8951);		// Fueling Systems
			Player[player].MarkResearchComplete(10202);		// Command Module
			Player[player].MarkResearchComplete(10205);		// Habitat Ring
			Player[player].MarkResearchComplete(7102);		// Explosive Charges
			Player[player].MarkResearchComplete(7201);		// Rare Ore Extraction
			Player[player].MarkResearchComplete(7202);		// Hot-Cracking Column Efficiency
			Player[player].MarkResearchComplete(7206);		// Scout-class Drive Train Refit
			Player[player].MarkResearchComplete(8306);		// Enhanced Defensive Fortifications
			if (Player[player].IsEden())
			{
				Player[player].MarkResearchComplete(6115);	// Geothermal Power
				Player[player].MarkResearchComplete(7213);	// Advanced Robotic Manipulator Arm (E)
				Player[player].MarkResearchComplete(7403);	// Increased Capacitance Circuitry
				Player[player].MarkResearchComplete(8104);	// Expanded Housing
			}
			else
			{
				Player[player].MarkResearchComplete(6107);	// Magnetohydrodynamics
				Player[player].MarkResearchComplete(7214);	// Advanced Robotic Manipulator Arm (P)
				Player[player].MarkResearchComplete(8105);	// Disaster-Resistant Housing
				Player[player].MarkResearchComplete(7104);	// Arachnid Weaponry
			}

			// Also give the starship components the player should have
			ExtPlayer[player].SetSatelliteCount(mapEDWARDSatellite, 1);
			ExtPlayer[player].SetSatelliteCount(mapSkydock, 1);
			ExtPlayer[player].SetSatelliteCount(mapIonDriveModule, 1);
			ExtPlayer[player].SetSatelliteCount(mapFusionDriveModule, 1);
			ExtPlayer[player].SetSatelliteCount(mapFuelingSystems, 1);
			ExtPlayer[player].SetSatelliteCount(mapCommandModule, 1);
			ExtPlayer[player].SetSatelliteCount(mapHabitatRing, 1);
		case 4:
			// Automatically give Mission 3's research topics.
			Player[player].MarkResearchComplete(5000);		// Mission 3 enabler tech
			Player[player].MarkResearchComplete(5051);		// Robot-Assist Mechanic (E)
			Player[player].MarkResearchComplete(5052);		// Robot-Assist Mechanic (P)
			Player[player].MarkResearchComplete(5110);		// Rare Ore Processing
			Player[player].MarkResearchComplete(5111);		// Independent Turret Power Systems
			Player[player].MarkResearchComplete(5201);		// Advanced Combat Chassis
			Player[player].MarkResearchComplete(5203);		// Electromagnetic Pulsing (E)
			Player[player].MarkResearchComplete(5507);		// Electromagnetic Pulsing (P)
			Player[player].MarkResearchComplete(5302);		// Meteorology
			Player[player].MarkResearchComplete(5305);		// DIRT Procedural Review
			Player[player].MarkResearchComplete(5306);		// Recycler Postprocessing
			Player[player].MarkResearchComplete(5307);		// Automated Diagnostic Examinations
			Player[player].MarkResearchComplete(5317);		// Reinforced Vehicle Construction
			Player[player].MarkResearchComplete(5318);		// Robotic Image Processing
			if (Player[player].IsEden())
			{
				Player[player].MarkResearchComplete(5309);	// Hypnopaedia (E)
				Player[player].MarkResearchComplete(5506);	// Directional Magnetic Fields
				Player[player].MarkResearchComplete(5101);	// Consumerism
			}
			else
			{
				Player[player].MarkResearchComplete(5116);	// Legged Robots
				Player[player].MarkResearchComplete(5202);	// Dissipating Adhesives
				Player[player].MarkResearchComplete(5310);	// Hypnopaedia (P)
				Player[player].MarkResearchComplete(5601);	// Heat Dissipation Systems (P)
				Player[player].MarkResearchComplete(5602);	// Rocket Propulsion
			}
		case 3:
			// Mission 2 is a unit mission; no research to give.
		case 2:
			// Automatically give Mission 1's research topics
			Player[player].MarkResearchComplete(3000);		// Mission 1 enabler tech
			Player[player].MarkResearchComplete(3301);		// Emergency Response Systems
			Player[player].MarkResearchComplete(3302);		// Metals Reclamation
			Player[player].MarkResearchComplete(3303);		// Health Maintenance
			Player[player].MarkResearchComplete(3401);		// Cybernetic Teleoperation
			Player[player].MarkResearchComplete(3402);		// High-Temperature Superconductivity
			Player[player].MarkResearchComplete(3403);		// Hydroponic Growing Media
			Player[player].MarkResearchComplete(3405);		// Metallogeny
			Player[player].MarkResearchComplete(3406);		// Environmental Psychology
			Player[player].MarkResearchComplete(3407);		// Large-Scale Optical Resonators
			Player[player].MarkResearchComplete(3408);		// Focused Microwave Projection
			Player[player].MarkResearchComplete(3851);		// Mobile Weapons Platform
			Player[player].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant
			Player[player].MarkResearchComplete(3201);		// Seismology
			Player[player].MarkResearchComplete(3202);		// Vulcanology
		case 1:
			// This is the first mission.  There is no previous mission to have done any research during.
		default:
			break;
	}
}