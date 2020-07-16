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

	// Zone 0 patrol #2 - patroling canyon width near bottom of map
	//LOCATION t[] = { LOCATION(40 + 31,28 - 1),LOCATION(46 + 31,31 - 1),LOCATION(-1,-1) };
	//PatrolGroup *z0_Group3 = new PatrolGroup(pNo, X5AI::zones[0], t);
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

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(77 + 31, 55 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(78 + 31, 57 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(81 + 31, 57 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(79 + 31, 59 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);

	

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63 + 31, 2 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(67 + 31, 4 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(64 + 31, 6 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 8 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(35 + 31, 42 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(37 + 31, 43 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(35 + 31, 44 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(84 + 31, 49 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(86 + 31, 50 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(88 + 31, 50 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(86 + 31, 48 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(88 + 31, 49 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(91 + 31, 49 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(90 + 31, 51 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(87 + 31, 52 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(101 + 31, 34 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 32 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104 + 31, 33 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 36 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104 + 31, 35 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(103 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105 + 31, 32 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(107 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105 + 31, 34 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(106 + 31, 36 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 9 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(100 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 12 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(126 + 31, 4 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128 + 31, 6 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125 + 31, 5 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(126 + 31, 7 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(123 + 31, 19 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(125 + 31, 20 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(126 + 31, 22 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(123 + 31, 21 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(127 + 31, 20 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(143 + 31, 34 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(145 + 31, 36 - 1), pNo, mapStickyfoam, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(144 + 31, 35 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(145 + 31, 33 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(146 + 31, 34 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(172 + 31, 20 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(173 + 31, 23 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(176 + 31, 21 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(171 + 31, 22 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(174 + 31, 20 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(175 + 31, 23 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(172 + 31, 9 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(172 + 31, 11 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(200 + 31, 9 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(201 + 31, 10 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(204 + 31, 9 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(204 + 31, 11 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(202 + 31, 8 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(206 + 31, 10 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(199 + 31, 7 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(202 + 31, 9 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(205 + 31, 10 - 1), pNo, mapESG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(203 + 31, 10 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(205 + 31, 12 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(200 + 31, 8 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(162 + 31, 52 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(160 + 31, 50 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(158 + 31, 48 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(158 + 31, 51 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(160 + 31, 52 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(159 + 31, 49 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(157 + 31, 50 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(161 + 31, 53 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(150 + 31, 4 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(151 + 31, 2 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(153 + 31, 2 - 1), pNo, mapMicrowave, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(151 + 31, 5 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(153 + 31, 5 - 1), pNo, mapRPG, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(152 + 31, 4 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);

	// Reference points
	// Zone 0
	/*
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(1 + 31, 1 - 1), 3, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(60 + 31, 63 - 1), 3, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)13, LOCATION(55 + 31, 50 - 1), 3, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)13, LOCATION(73 + 31, 63 - 1), 3, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)15, LOCATION(74 + 31, 53 - 1), 3, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)15, LOCATION(85 + 31, 63 - 1), 3, mapNone, 0);

	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(46 + 31, 31 - 1), 3, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(36 + 31, 43 - 1), 3, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(12 + 31, 53 - 1), 3, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(79 + 31, 57 - 1), 3, mapLaser, 0);
	*/

	// Zone 1
	/*
	TethysGame::CreateUnit(Unit1, (map_id)11, LOCATION(40 + 31, 1 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)11, LOCATION(87 + 31, 8 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(40 + 31, 9 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(76 + 31, 20 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(49 + 31, 21 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(86 + 31, 35 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)15, LOCATION(81 + 31, 50 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)15, LOCATION(54 + 31, 33 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)10, LOCATION(76 + 31, 36 - 1), 4, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)10, LOCATION(102 + 31, 52 - 1), 4, mapNone, 0);

	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(64 + 31, 4 - 1), 4, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(50 + 31, 9 - 1), 4, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(87 + 31, 49 - 1), 4, mapLaser, 0);
	*/

	// Zone 2
	/*
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(97 + 31, 21 - 1), 5, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(76 + 31, 7 - 1), 5, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(89 + 31, 1 - 1), 5, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(142 + 31, 27 - 1), 5, mapNone, 0);

	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(124 + 31, 21 - 1), 5, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(126 + 31, 5 - 1), 5, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(101 + 31, 10 - 1), 5, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(104 + 31, 34 - 1), 5, mapLaser, 0);
	*/
	
	// Zone 3
	/*
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(124 + 31, 24 - 1), 0, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)1, LOCATION(256 + 31, 63 - 1), 0, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(149 + 31, 1 - 1), 0, mapNone, 0);
	TethysGame::CreateUnit(Unit1, (map_id)2, LOCATION(236 + 31, 54 - 1), 0, mapNone, 0);

	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(173 + 31, 21 - 1), 0, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(145 + 31, 34 - 1), 0, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(152 + 31, 3 - 1), 0, mapLaser, 0);
	*/
}
/*
Reference
if (TethysGame::NoPlayers() > 0)
{
	
	
	
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(172 + 31, 10 - 1), 0, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(203 + 31, 9 - 1), 0, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, (map_id)7, LOCATION(159 + 31, 51 - 1), 0, mapLaser, 0);
}
if (TethysGame::NoPlayers() > 1)
{
	
}
if (TethysGame::NoPlayers() > 2)
{
	
}
if (TethysGame::NoPlayers() > 3)
{
	
}
if (TethysGame::NoPlayers() > 4)
{
	
}
if (TethysGame::NoPlayers() > 5)
{
	
}
if (TethysGame::NoPlayers() > 6)
{
	
}
*/