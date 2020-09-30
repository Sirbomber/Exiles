#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

#include "Bases.h"
#include "AI.h"

// Friendly AI base
void SetupFriendlyBase(int pNo)
{
	UnitEx Unit1;
	Player[pNo].GoPlymouth();
	Player[pNo].GoAI();
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(9 + 31, 9 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(4 + 31, 3 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(20 + 31, 4 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(20 + 31, 7 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(20 + 31, 10 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(20 + 31, 13 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(4 + 31, 13 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(4 + 31, 16 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(11 + 31, 18 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(15 + 31, 18 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(13 + 31, 4 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonStorage, LOCATION(6 + 31, 9 - 1), pNo, mapNone, 0);

	TethysGame::CreateWallOrTube(12 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(13 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(13 + 31, 8 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(13 + 31, 7 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(13 + 31, 6 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(14 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(16 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(17 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(18 + 31, 9 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(9 + 31, 11 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(9 + 31, 12 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(9 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(8 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(7 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 4 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(16 + 31, 4 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(17 + 31, 4 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(18 + 31, 4 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(7 + 31, 16 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(7 + 31, 17 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(8 + 31, 17 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(9 + 31, 17 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(10 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(11 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(12 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(13 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(14 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(17 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(16 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(18 + 31, 13 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 10 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 11 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(15 + 31, 12 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(12 + 31, 14 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(12 + 31, 15 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(12 + 31, 16 - 1, 0, mapTube);

}

void SetupHostilePatrols(int pNo)
{
	Player[pNo].GoPlymouth();

	UnitEx Unit1;

	// Zone 0 patrol #1 - bottom left corner
	GuardWatchGroup *z0_Group1 = new GuardWatchGroup(pNo, X5AI::zones[0], MAP_RECT(10 + 31, 52 - 1, 14 + 31, 55 - 1), MAP_RECT(25 + 31, 49 - 1, 29 + 31, 51 - 1), 930);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(12 + 31, 52 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 53 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(11 + 31, 54 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z0_Group1);

	// Zone 0 stationary #1 - blocking canyon entrance
	CampGroup *z0_Group2 = new CampGroup(pNo, X5AI::zones[0], MAP_RECT(34 + 31, 42 - 1, 38 + 31, 45 - 1));
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(35 + 31, 42 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(37 + 31, 43 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(35 + 31, 44 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group2->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z0_Group2);

	// Zone 0 patrol #2 - patroling canyon width near bottom of map
	GuardWatchGroup *z0_Group3 = new GuardWatchGroup(pNo, X5AI::zones[0], MAP_RECT(45 + 31, 31 - 1, 48 + 31, 34 - 1), MAP_RECT(39 + 31, 26 - 1, 42 + 31, 29 - 1), 709);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 30 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 32 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 31 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	z0_Group3->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z0_Group3);

	// Zone 0 stationary #2 - these guys don't guard anything important and exist just to help chase down any detected units.
	CampGroup *z0_Group4 = new CampGroup(pNo, X5AI::zones[0], MAP_RECT(76 + 31, 54 - 1, 82 + 31, 60 - 1));
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(77 + 31, 55 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z0_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(78 + 31, 57 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z0_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(81 + 31, 57 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z0_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(79 + 31, 59 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group4->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z0_Group4);

	// Zone 0 patrol #3 - An extra patrol along the north of the first canyon area
	LOCATION *temp = new LOCATION[8];
	temp[0] = LOCATION(50 + 31, 9 - 1);
	temp[1] = LOCATION(31 + 31, 8 - 1);
	temp[2] = LOCATION(-1, -1);
	PatrolGroup *z0_Group5 = new PatrolGroup(pNo, X5AI::zones[0], &temp);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 8 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z0_Group5->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z0_Group5);

	// Zone 1 patrol #1 - these guys patrol north to south along the top of the cliff
	GuardWatchGroup *z1_Group1 = new GuardWatchGroup(pNo, X5AI::zones[1], MAP_RECT(60 + 31, 2 - 1, 67 + 31, 8 - 1), MAP_RECT(57 + 31, 26 - 1, 64 + 31, 30 - 1), 770);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63 + 31, 2 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z1_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(67 + 31, 4 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z1_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z1_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(64 + 31, 6 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z1_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z1_Group1);

	// Zone 2 guard group #1 - Sacrifice a scout to get past this stationary guard group
	CampGroup *z2_Group1 = new CampGroup(pNo, X5AI::zones[2], MAP_RECT(83 + 31, 48 - 1, 93 + 31, 53 - 1));
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(84 + 31, 49 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(86 + 31, 50 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(88 + 31, 50 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(86 + 31, 48 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(88 + 31, 49 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(91 + 31, 49 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(90 + 31, 51 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(87 + 31, 52 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z2_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z2_Group1);

	// Zone 3 patrol #1 - Big Lynx patrol in the canyon leading north (after the group that needs a decoy to get past)
	GuardWatchGroup *z3_Group1 = new GuardWatchGroup(pNo, X5AI::zones[3], MAP_RECT(109 + 31, 37 - 1, 113 + 31, 42 - 1), MAP_RECT(88 + 31, 20 - 1, 92 + 31, 24 - 1), 720);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(101 + 31, 34 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 32 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104 + 31, 33 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 36 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104 + 31, 35 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(103 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105 + 31, 32 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(107 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105 + 31, 34 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(106 + 31, 36 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z3_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z3_Group1);

	// Zone 3 patrol #2 - Small Lynx patrol at the end of the canyon leading north
	temp[0] = LOCATION(91 + 31, 8 - 1);
	temp[1] = LOCATION(102 + 31, 11 - 1);
	temp[2] = LOCATION(-1, -1);
	PatrolGroup *z3_Group2 = new PatrolGroup(pNo, X5AI::zones[3], &temp);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 9 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(100 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 12 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z3_Group2->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z3_Group2);

	// Zone 4 patrol #1 - Lynx patrol near the unused Blight spawn
	GuardWatchGroup *z4_Group1 = new GuardWatchGroup(pNo, X5AI::zones[4], MAP_RECT(126 + 31, 5 - 1, 129 + 31, 8 - 1), MAP_RECT(106 + 31, 2 - 1, 109 + 31, 5 - 1), 820);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(126 + 31, 4 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z4_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128 + 31, 6 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z4_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125 + 31, 5 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z4_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(126 + 31, 7 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z4_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z4_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z4_Group1);

	// Zone 4 patrol #2 - First panther group
	GuardWatchGroup *z4_Group2 = new GuardWatchGroup(pNo, X5AI::zones[4], MAP_RECT(123 + 31, 19 - 1, 127 + 31, 23 - 1), MAP_RECT(134 + 31, 28 - 1, 137 + 31, 31 - 1), 666);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(123 + 31, 19 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z4_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(125 + 31, 20 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z4_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(126 + 31, 22 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z4_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(123 + 31, 21 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z4_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(127 + 31, 20 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z4_Group2->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z4_Group2);

	// Zone 5 patrol #1 - Lynx patrol guarding the "end zone"
	temp[0] = LOCATION(122 + 31, 36 - 1);
	temp[1] = LOCATION(125 + 31, 50 - 1);
	temp[2] = LOCATION(149 + 31, 50 - 1);
	temp[3] = LOCATION(148 + 31, 35 - 1);
	temp[4] = LOCATION(-1, -1);
	PatrolGroup *z5_Group1 = new PatrolGroup(pNo, X5AI::zones[5], &temp);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(143 + 31, 34 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	z5_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(145 + 31, 36 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	z5_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(144 + 31, 35 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(145 + 31, 33 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(146 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group1);

	// Zone 5 patrol #2 - "Sister" patrol to the above group (same patrol route but hits waypoints at different times)
	temp[0] = LOCATION(149 + 31, 50 - 1);
	temp[1] = LOCATION(148 + 31, 35 - 1);
	temp[2] = LOCATION(122 + 31, 36 - 1);
	temp[3] = LOCATION(125 + 31, 50 - 1);
	temp[4] = LOCATION(-1, -1);
	PatrolGroup *z5_Group2 = new PatrolGroup(pNo, X5AI::zones[5], &temp);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(127 + 31, 50 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125 + 31, 49 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	z5_Group2->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125 + 31, 52 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group2->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group2);

	// Zone 5 patrol #3 - Lynx south of the ESG guards
	GuardWatchGroup *z5_Group3 = new GuardWatchGroup(pNo, X5AI::zones[5], MAP_RECT(170 + 31, 20 - 1, 176 + 31, 24 - 1), MAP_RECT(147 + 31, 17 - 1, 152 + 31, 19 - 1), 780);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(172 + 31, 20 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(173 + 31, 23 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(176 + 31, 21 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(171 + 31, 22 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(174 + 31, 20 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(175 + 31, 23 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group3->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group3);

	// Zone 5 patrol #4 - Lynx patrol west of the ESG guards
	GuardWatchGroup *z5_Group4 = new GuardWatchGroup(pNo, X5AI::zones[5], MAP_RECT(155 + 31, 5 - 1, 159 + 31, 7 - 1), MAP_RECT(153 + 31, 33 - 1, 160 + 31, 36 - 1), 980);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(150 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(151 + 31, 2 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(153 + 31, 2 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(151 + 31, 5 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(153 + 31, 5 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(152 + 31, 4 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group4->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group4);

	// Zone 5 camp group #1 - Panthers guarding the northern path leading to the evac zone
	CampGroup *z5_Group5 = new CampGroup(pNo, X5AI::zones[5], MAP_RECT(198 + 31, 6 - 1, 206 + 31, 13 - 1));
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(200 + 31, 9 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(201 + 31, 10 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(204 + 31, 9 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(204 + 31, 11 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(202 + 31, 8 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(206 + 31, 10 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(199 + 31, 7 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(202 + 31, 9 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(205 + 31, 10 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(203 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(205 + 31, 12 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(200 + 31, 8 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group5->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group5);

	// Zone 5 camp group #2 - Panthers guarding the southern cliffside leading to the evac zone (they actually patrol, but so slowly they might as well be camping)
	GuardWatchGroup *z5_Group6 = new GuardWatchGroup(pNo, X5AI::zones[5], MAP_RECT(168 + 31, 49 - 1, 172 + 31, 54 - 1), MAP_RECT(155 + 31, 49 - 1, 159 + 31, 55 - 1), 1666);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(162 + 31, 52 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(160 + 31, 50 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(158 + 31, 48 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(158 + 31, 51 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(160 + 31, 52 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(159 + 31, 49 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(157 + 31, 50 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(161 + 31, 53 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	z5_Group6->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z5_Group6);

	// ESG guards
	EsgSpecial *z6_Group1 = new EsgSpecial(pNo, X5AI::zones[6], MAP_RECT(170 + 31, 8 - 1, 173 + 31, 12 - 1), LOCATION(169 + 31, 11 - 1));
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(172 + 31, 9 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	z6_Group1->AddUnitToGroup(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(172 + 31, 11 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	z6_Group1->AddUnitToGroup(Unit1);
	X5AI::aiGroups.push_back(z6_Group1);

	delete temp;
}
