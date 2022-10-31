#pragma once

// Setup functions
void SetupAI();

void EdenBase(int pNo);

void InitPlymouth();

MAP_RECT GetMiningRect(Unit mine, Unit smelter);
MAP_RECT GetMiningRect(LOCATION mine, LOCATION smelter);

struct PatrolGroup
{
	int curWaypoint = 0;
	int totalWaypoints = 0;
	bool goBack = false;
	MAP_RECT waitRects[4];
	MAP_RECT guardRecs[3];
	int numGuardRecs = 0;
	//Trigger callback;
	FightGroup fg;
};

struct EdenAiData
{
	MiningGroup mg[16];	/* 0, 1, 2    = Inner base common ore smelters
						   3, 4       = Inner base rare ore smelters
						   5, 6, 7    = Outer base common ore smelters (west)
						   8, 9, 10   = Outer base common ore smelters (east)
						   11, 12, 13 = Outer base rare ore smelters
						   14         = Reserved
						   15         = Magma well smelter
						   */
	FightGroup FinalDefense,
		InnerDefense_Lynx,
		InnerDefense_WestEntrance,
		InnerDefense_EastEntrance,
		SW_Lab,
		Mid_Lab,
		North_Lab,
		SE_Lab,
		Wall_EastEntrance,
		Wall_NorthEntrance,
		//PantherPatrol[2],
		//LynxPatrol[2],
		Offense_Staging[2],
		Offense_Active[2];
		//OuterPatrol[3]
	PatrolGroup PGs[7];
	

	BuildingGroup InnerBG,
		OuterBG,
		InnerEWs,
		OuterEWs,
		VF[4];

	UnitEx repairs[4];
	MAP_RECT repairIdle_Inner = { 28 + 31,114 - 1, 31 + 31,116 - 1 },
		repairIdle_Outer = { 37 + 31,71 - 1,41 + 31,74 - 1 };
};

struct PlymouthAiData
{
	FightGroup pfg[7];
	Unit targetList[20];	// Ordered list of targets for Plymouth to attack
};