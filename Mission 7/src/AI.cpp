#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types.h>
#include <Outpost2App.h>

#include "AI.h"
#include "Objectives.h"

// AI data
extern int numEden;
extern int numPlym;

EdenAiData E;

void SetupAI()
{
	// AI setup/tech bonus
	Player[numEden].GoEden();
	Player[numEden].SetTechLevel(11);	// It's Eden's big research center, give them a tech edge
	Player[numPlym].GoPlymouth();
	Player[numPlym].SetTechLevel(10);
	
	EdenBase(numEden);
	
	InitPlymouth();

}

void EdenBase(int pNo)
{
	UnitEx Unit1, lastSmelter, lastMine;

	Player[pNo].CenterViewOn(33 + 31, 120 - 1);
	Player[pNo].SetOre(27000);
	Player[pNo].SetRareOre(14000);
	Player[pNo].SetFoodStored(39000);
	CreateTimeTrigger(1, 0, 1230, "UpdatePatrolPositions");

	// Common ore mines
	TethysGame::CreateBeacon(mapMiningBeacon, 51, 72, 0, 0, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 120, 99, 0, 0, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 80, 118, 0, 0, 0);

	// Rare ore mines
	TethysGame::CreateBeacon(mapMiningBeacon, 105, 77, 1, 0, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 103, 110, 1, 0, 0);

	// Fumaroles
	TethysGame::CreateBeacon(mapFumarole, 78, 75, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 71, 96, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 84, 102, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 55, 125, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 7 + 31, 75 - 1, -1, -1, -1);
	TethysGame::CreateBeacon(mapFumarole, 52 + 31, 50 - 1, -1, -1, -1);

	// Magma vents
	TethysGame::CreateBeacon(mapMagmaVent, 69, 48, -1, -1, -1);

	// Advanced Labs
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(78, 60), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(69, 86), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(102, 94), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(34, 96), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(78, 104), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(97, 123), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);

	// Inner base structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(64, 119), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(62, 107), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(92, 117), pNo, mapNone, 0);
	E.VF[0] = CreateBuildingGroup(pNo);
	E.VF[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(56, 109), pNo, mapNone, 0);
	E.VF[1] = CreateBuildingGroup(pNo);
	E.VF[1].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapRobotCommand, LOCATION(66, 123), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(44, 112), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(50, 117), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(57, 118), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(87, 106), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(65, 101), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(55, 125), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(84, 102), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(71, 96), pNo, mapNone, 0);

	// Inner base common ore mining
	E.mg[0] = CreateMiningGroup(pNo);
	E.mg[1] = CreateMiningGroup(pNo);
	E.mg[2] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(80, 118), pNo, mapNone, 0);
	// Bottom left smelter
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(75, 118), pNo, mapNone, 0);
	E.mg[0].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(76, 120), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	E.mg[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(77, 120), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	E.mg[0].TakeUnit(Unit1);
	// Top right smelter
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(80, 114), pNo, mapNone, 0);
	E.mg[1].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(82, 116), pNo, mapNone, 4);
	E.mg[1].TakeUnit(Unit1);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(81, 116), pNo, mapNone, 4);
	E.mg[1].TakeUnit(Unit1);
	Unit1.DoSetLights(1);
	// Top left smelter
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(75, 114), pNo, mapNone, 0);
	E.mg[2].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(77, 115), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[2].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(77, 116), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	E.mg[2].TakeUnit(Unit1);
	E.mg[0].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[0].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.mg[2].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[1].SetTargCount(mapCargoTruck, mapNone, 2);
	E.VF[1].RecordVehReinforceGroup(E.mg[0], 10);
	E.VF[1].RecordVehReinforceGroup(E.mg[1], 15);
	E.VF[1].RecordVehReinforceGroup(E.mg[2], 15);
	E.VF[1].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Inner base rare ore mining
	E.mg[3] = CreateMiningGroup(pNo);
	E.mg[4] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(103, 110), pNo, mapNone, 0);
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(98, 106), pNo, mapNone, 0);
	E.mg[3].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(100, 107), pNo, mapNone, 5);
	Unit1.DoSetLights(1);
	E.mg[3].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(100, 108), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	E.mg[3].TakeUnit(Unit1);
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(98, 110), pNo, mapNone, 0);
	E.mg[4].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(99, 112), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[4].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(100, 112), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	E.mg[4].TakeUnit(Unit1);
	E.mg[3].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[3].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.mg[4].SetTargCount(mapCargoTruck, mapNone, 2);
	E.VF[0].RecordVehReinforceGroup(E.mg[3], 10);
	E.VF[0].RecordVehReinforceGroup(E.mg[4], 15);
	E.VF[0].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Inner base construction and repair
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(64, 109), pNo, mapNone, 1);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(65, 110), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(64, 110), pNo, mapNone, 3);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(55, 113), pNo, mapTube, 0);
	Unit1.DoSetLights(1);

	// Inner base - eastern wall defenders
	E.InnerDefense_EastEntrance = CreateFightGroup(pNo);
	E.InnerDefense_EastEntrance.SetRect(MAP_RECT(58 + 31, 87 - 1, 63 + 31, 95 - 1));
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(91, 88), pNo, mapAcidCloud, 2);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(90, 88), pNo, mapAcidCloud, 4);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(92, 88), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(90, 89), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(91, 89), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(92, 89), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(92, 90), pNo, mapEMP, 1);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(91, 90), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(91, 92), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(91, 93), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.InnerDefense_EastEntrance.TakeUnit(Unit1);
	E.InnerDefense_EastEntrance.SetTargCount(mapTiger, mapAcidCloud, 2);
	E.InnerDefense_EastEntrance.SetTargCount(mapTiger, mapEMP, 3);
	E.InnerDefense_EastEntrance.SetTargCount(mapTiger, mapRailGun, 5);
	E.VF[1].RecordVehReinforceGroup(E.InnerDefense_EastEntrance, 3);

	// Inner base - western entrance defenders
	E.InnerDefense_WestEntrance = CreateFightGroup(pNo);
	E.InnerDefense_WestEntrance.SetRect(MAP_RECT(15 + 31, 98 - 1, 23 + 31, 101 - 1));
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(52, 99), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(51, 99), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(48, 100), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(49, 100), pNo, mapAcidCloud, 4);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(50, 101), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(52, 101), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(49, 101), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(49, 102), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(53, 103), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(52, 103), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(52, 104), pNo, mapEMP, 2);
	Unit1.DoSetLights(1);
	E.InnerDefense_WestEntrance.TakeUnit(Unit1);
	E.InnerDefense_WestEntrance.SetTargCount(mapTiger, mapAcidCloud, 1);
	E.InnerDefense_WestEntrance.SetTargCount(mapTiger, mapEMP, 5);
	E.InnerDefense_WestEntrance.SetTargCount(mapTiger, mapRailGun, 5);
	E.VF[0].RecordVehReinforceGroup(E.InnerDefense_WestEntrance, 3);

	// Inner base - final defenders (to do: add more)
	E.FinalDefense = CreateFightGroup(pNo);
	E.FinalDefense.SetRect(MAP_RECT(34 + 31, 113 - 1, 41 + 31, 120 - 1));
	E.FinalDefense.AddGuardedRect(MAP_RECT(6 + 31, 99 - 1, 67 + 31, 127 - 1));
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(67, 114), pNo, mapRailGun, 4);
	Unit1.DoSetLights(1);
	E.FinalDefense.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(69, 115), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.FinalDefense.TakeUnit(Unit1);
	E.FinalDefense.SetTargCount(mapTiger, mapRailGun, 8);
	E.FinalDefense.SetTargCount(mapTiger, mapEMP, 6);
	E.FinalDefense.SetTargCount(mapTiger, mapAcidCloud, 3);
	E.FinalDefense.SetTargCount(mapLynx, mapRailGun, 9);
	E.FinalDefense.SetTargCount(mapLynx, mapEMP, 4);
	E.VF[0].RecordVehReinforceGroup(E.FinalDefense, 1);
	
	// Inner base guard posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(48, 97), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(93, 86), pNo, mapAcidCloud, 0);

	// Inner base tubes
	CreateTubeOrWallLine(34 + 31, 104 - 1, 34 + 31, 108 - 1, mapTube);
	CreateTubeOrWallLine(35 + 31, 108 - 1, 38 + 31, 108 - 1, mapTube);
	CreateTubeOrWallLine(38 + 31, 109 - 1, 38 + 31, 113 - 1, mapTube);
	CreateTubeOrWallLine(16 + 31, 113 - 1, 37 + 31, 113 - 1, mapTube);
	CreateTubeOrWallLine(33 + 31, 114 - 1, 33 + 31, 118 - 1, mapTube);
	CreateTubeOrWallLine(33 + 31, 122 - 1, 33 + 31, 123 - 1, mapTube);
	CreateTubeOrWallLine(36 + 31, 120 - 1, 41 + 31, 120 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 121 - 1, 39 + 31, 127 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 110 - 1, 56 + 31, 110 - 1, mapTube);
	CreateTubeOrWallLine(31 + 31, 111 - 1, 31 + 31, 112 - 1, mapTube);
	CreateTubeOrWallLine(25 + 31, 114 - 1, 25 + 31, 117 - 1, mapTube);
	CreateTubeOrWallLine(22 + 31, 118 - 1, 24 + 31, 118 - 1, mapTube);
	CreateTubeOrWallLine(19 + 31,  80 - 1, 19 + 31, 116 - 1, mapTube);
	CreateTubeOrWallLine(37 + 31, 124 - 1, 64 + 31, 124 - 1, mapTube);
	CreateTubeOrWallLine(61 + 31, 121 - 1, 61 + 31, 123 - 1, mapTube);
	CreateTubeOrWallLine(44 + 31, 111 - 1, 44 + 31, 113 - 1, mapTube);
	CreateTubeOrWallLine(47 + 31, 108 - 1, 47 + 31, 109 - 1, mapTube);
	CreateTubeOrWallLine(50 + 31, 105 - 1, 55 + 31, 105 - 1, mapTube);
	CreateTubeOrWallLine(56 + 31, 109 - 1, 56 + 31, 111 - 1, mapTube);
	CreateTubeOrWallLine(57 + 31, 111 - 1, 60 + 31, 111 - 1, mapTube);
	CreateTubeOrWallLine(59 + 31, 112 - 1, 59 + 31, 116 - 1, mapTube);
	CreateTubeOrWallLine(60 + 31, 103 - 1, 60 + 31, 111 - 1, mapTube);
	CreateTubeOrWallLine(59 + 31, 107 - 1, 64 + 31, 107 - 1, mapTube);
	CreateTubeOrWallLine(61 + 31,  89 - 1, 61 + 31, 103 - 1, mapTube);
	CreateTubeOrWallLine(62 + 31,  89 - 1, 64 + 31,  89 - 1, mapTube);
	CreateTubeOrWallLine(64 + 31,  76 - 1, 64 + 31,  88 - 1, mapTube);
	CreateTubeOrWallLine(28 + 31, 109 - 1, 28 + 31, 110 - 1, mapTube);
	CreateTubeOrWallLine(29 + 31, 119 - 1, 31 + 31, 119 - 1, mapTube);

	// Inner base walls
	CreateTubeOrWallLine(61 + 31, 85 - 1, 63 + 31, 85 - 1, mapWall);
	CreateTubeOrWallLine(65 + 31, 85 - 1, 67 + 31, 85 - 1, mapWall);
	TethysGame::CreateWallOrTube(67 + 31, 86 - 1, -1, mapWall);
	CreateTubeOrWallLine(16 + 31, 96 - 1, 18 + 31, 96 - 1, mapWall);
	CreateTubeOrWallLine(20 + 31, 96 - 1, 22 + 31, 96 - 1, mapWall);
	TethysGame::CreateWallOrTube(22 + 31, 97 - 1, -1, mapWall);
	
	// Outer base structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(66, 77), pNo, mapNone, 0);
	PassUnitIdsToObjectives(Unit1);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(74, 68), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(59, 63), pNo, mapNone, 0);
	E.VF[2] = CreateBuildingGroup(pNo);
	E.VF[2].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(90, 72), pNo, mapNone, 0);
	E.VF[3] = CreateBuildingGroup(pNo);
	E.VF[3].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapRobotCommand, LOCATION(109, 102), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(78, 75), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(7 + 31, 75 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(52 + 31, 50 - 1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(111, 77), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(43, 87), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(75, 80), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(52, 60), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(84, 66), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(56, 85), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(64, 69), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(61, 72), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(91, 68), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(101, 84), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGORF, LOCATION(45, 79), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(82, 78), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(106, 87), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(98, 68), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedResidence, LOCATION(58, 77), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedResidence, LOCATION(91, 79), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapObservatory, LOCATION(91, 49), pNo, mapNone, 0);

	// Outer base magma well operation
	Doze(MAP_RECT(36 + 31, 50 - 1, 39 + 31, 60 - 1));
	E.mg[15] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(69, 48), pNo, mapNone, 0);
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(67, 57), pNo, mapNone, 0);
	E.mg[15].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(68, 50), pNo, mapNone, 5);
	Unit1.DoSetLights(1);
	E.mg[15].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(70, 51), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	E.mg[15].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(69, 53), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	E.mg[15].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(70, 55), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[15].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(70, 57), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[15].TakeUnit(Unit1);

	E.mg[15].SetTargCount(mapCargoTruck, mapNone, 5);
	E.mg[15].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.VF[2].RecordVehReinforceGroup(E.mg[15], 12);
	E.VF[2].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Outer base western common ore mine
	E.mg[5] = CreateMiningGroup(pNo);
	E.mg[6] = CreateMiningGroup(pNo);
	E.mg[7] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(51, 72), pNo, mapNone, 0);
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(47, 68), pNo, mapNone, 0);
	E.mg[5].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(53, 70), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	E.mg[5].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(54, 70), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	E.mg[5].TakeUnit(Unit1);
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(52, 68), pNo, mapNone, 0);
	E.mg[6].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(49, 70), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	E.mg[6].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(48, 70), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	E.mg[6].TakeUnit(Unit1);
	E.mg[7].Setup(lastMine.Location(), LOCATION(16 + 31, 73 - 1), mapCommonOreMine, mapCommonOreSmelter, GetMiningRect(lastMine.Location(), LOCATION(16 + 31, 73 - 1)));
	//E.mg[7].SetTargCount(mapCargoTruck, mapAny, 2);
	//E.mg[7].SetTargCount(mapCommonOreMine, mapAny, 1);
	E.mg[5].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[5].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.mg[6].SetTargCount(mapCargoTruck, mapNone, 2);
	//E.mg[7].SetTargCount(mapCargoTruck, mapNone, 2);
	E.VF[2].RecordVehReinforceGroup(E.mg[5], 10);
	E.VF[2].RecordVehReinforceGroup(E.mg[6], 15);
	//E.VF[2].RecordVehReinforceGroup(E.mg[7], 15);
	E.VF[2].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Outer base eastern common ore mine
	E.mg[8] = CreateMiningGroup(pNo);
	E.mg[9] = CreateMiningGroup(pNo);
	E.mg[10] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(120, 99), pNo, mapNone, 0);
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(115, 95), pNo, mapNone, 0);
	E.mg[8].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(117, 96), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[8].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(117, 97), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	E.mg[8].TakeUnit(Unit1);
	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(115, 99), pNo, mapNone, 0);
	E.mg[9].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(117, 100), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	E.mg[9].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(116, 100), pNo, mapNone, 5);
	Unit1.DoSetLights(1);
	E.mg[9].TakeUnit(Unit1);

	E.mg[8].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[8].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.mg[9].SetTargCount(mapCargoTruck, mapNone, 2);
	E.VF[3].RecordVehReinforceGroup(E.mg[8], 12);
	E.VF[3].RecordVehReinforceGroup(E.mg[9], 16);
	E.VF[3].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Outer base rare ore mine
	E.mg[11] = CreateMiningGroup(pNo);
	E.mg[12] = CreateMiningGroup(pNo);
	E.mg[13] = CreateMiningGroup(pNo);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(105, 77), pNo, mapNone, 0);
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(100, 73), pNo, mapNone, 0);
	E.mg[11].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(100, 75), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	E.mg[11].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(101, 75), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	E.mg[11].TakeUnit(Unit1);

	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(105, 73), pNo, mapNone, 0);
	E.mg[12].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(106, 75), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[12].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(107, 75), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[12].TakeUnit(Unit1);

	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(100, 77), pNo, mapNone, 0);
	E.mg[13].Setup(lastMine, lastSmelter, GetMiningRect(lastMine, lastSmelter));
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(102, 78), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[13].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(103, 78), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	E.mg[13].TakeUnit(Unit1);

	E.mg[11].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[11].SetTargCount(mapCommonOreMine, mapNone, 1);
	E.mg[12].SetTargCount(mapCargoTruck, mapNone, 2);
	E.mg[13].SetTargCount(mapCargoTruck, mapNone, 2);
	E.VF[3].RecordVehReinforceGroup(E.mg[11], 10);
	E.VF[3].RecordVehReinforceGroup(E.mg[12], 12);
	E.VF[3].RecordVehReinforceGroup(E.mg[13], 12);
	E.VF[3].RecordBuilding(lastMine.Location(), lastMine.GetType(), lastMine.GetCargo());

	// Outer base non-combat vehicles
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(78, 69), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(75, 71), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(64, 64), pNo, mapTube, 5);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(80, 71), pNo, mapTube, 5);
	Unit1.DoSetLights(1);
	
	// Lynx Patrol #1
	E.PGs[0].fg = CreateFightGroup(pNo);
	E.PGs[0].curWaypoint = 0;
	E.PGs[0].totalWaypoints = 4;
	E.PGs[0].goBack = true;
	E.PGs[0].numGuardRecs = 3;
	E.PGs[0].waitRects[0] = MAP_RECT(11 + 31, 73 - 1, 17 + 31, 77 - 1);
	E.PGs[0].waitRects[1] = MAP_RECT(28 + 31, 54 - 1, 33 + 31, 58 - 1);
	E.PGs[0].waitRects[2] = MAP_RECT(52 + 31, 53 - 1, 56 + 31, 57 - 1);
	E.PGs[0].waitRects[3] = MAP_RECT(74 + 31, 80 - 1, 78 + 31, 85 - 1);
	E.PGs[0].guardRecs[0] = MAP_RECT(1 + 31, 47 - 1, 69 + 31, 127 - 1);
	E.PGs[0].guardRecs[1] = MAP_RECT(70 + 31, 59 - 1, 78 + 31, 112 - 1);
	E.PGs[0].guardRecs[2] = MAP_RECT(79 + 31, 64 - 1, 97 + 31, 109 - 1);
	E.PGs[0].fg.SetRect(E.PGs[0].waitRects[0]);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(62, 54), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63, 54), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61, 54), pNo, mapRailGun, 7);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(62, 55), pNo, mapEMP, 7);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63, 55), pNo, mapEMP, 7);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61, 55), pNo, mapEMP, 6);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60, 55), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(62, 56), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63, 56), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60, 56), pNo, mapEMP, 6);
	Unit1.DoSetLights(1);
	E.PGs[0].fg.TakeUnit(Unit1);
	E.PGs[0].fg.SetTargCount(mapLynx, mapRailGun, 6);
	E.PGs[0].fg.SetTargCount(mapLynx, mapEMP, 4);
	E.VF[2].RecordVehReinforceGroup(E.PGs[0].fg, 9);

	// Lynx Patrol #2
	E.PGs[1].fg = CreateFightGroup(pNo);
	E.PGs[1].curWaypoint = 2;
	E.PGs[1].totalWaypoints = 3;
	E.PGs[1].goBack = false;
	E.PGs[1].numGuardRecs = 3;
	E.PGs[1].waitRects[0] = MAP_RECT(28 + 31, 54 - 1, 32 + 31, 57 - 1);
	E.PGs[1].waitRects[1] = MAP_RECT(60 + 31, 57 - 1, 65 + 31, 62 - 1);
	E.PGs[1].waitRects[2] = MAP_RECT(39 + 31, 73 - 1, 43 + 31, 77 - 1);
	E.PGs[1].guardRecs[0] = MAP_RECT(1 + 31, 47 - 1, 69 + 31, 127 - 1);
	E.PGs[1].guardRecs[1] = MAP_RECT(70 + 31, 59 - 1, 78 + 31, 112 - 1);
	E.PGs[1].guardRecs[2] = MAP_RECT(79 + 31, 64 - 1, 97 + 31, 109 - 1);
	E.PGs[1].fg.SetRect(E.PGs[1].waitRects[2]);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(95, 57), pNo, mapEMP, 7);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(93, 57), pNo, mapRailGun, 7);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(94, 57), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(95, 58), pNo, mapEMP, 7);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(93, 58), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(92, 59), pNo, mapRailGun, 4);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(96, 59), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(95, 59), pNo, mapEMP, 6);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(94, 59), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(92, 60), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.PGs[1].fg.TakeUnit(Unit1);
	E.PGs[1].fg.SetTargCount(mapLynx, mapRailGun, 6);
	E.PGs[1].fg.SetTargCount(mapLynx, mapEMP, 4);
	E.VF[3].RecordVehReinforceGroup(E.PGs[1].fg, 9);

	// Panther Patrol #1
	E.PGs[2].fg = CreateFightGroup(pNo);
	E.PGs[2].curWaypoint = 0;
	E.PGs[2].totalWaypoints = 2;
	E.PGs[2].goBack = false;
	E.PGs[2].numGuardRecs = 3;
	E.PGs[2].waitRects[0] = MAP_RECT(12 + 31, 52 - 1, 17 + 31, 56 - 1);
	E.PGs[2].waitRects[1] = MAP_RECT(40 + 31, 52 - 1, 43 + 31, 55 - 1);
	E.PGs[2].guardRecs[0] = MAP_RECT(1 + 31, 47 - 1, 69 + 31, 127 - 1);
	E.PGs[2].guardRecs[1] = MAP_RECT(70 + 31, 59 - 1, 78 + 31, 112 - 1);
	E.PGs[2].guardRecs[2] = MAP_RECT(79 + 31, 64 - 1, 97 + 31, 109 - 1);
	E.PGs[2].fg.SetRect(E.PGs[2].waitRects[0]);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(47, 51), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(46, 51), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(45, 51), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(47, 52), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(45, 52), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(48, 53), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(45, 53), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(46, 53), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(47, 53), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(46, 55), pNo, mapEMP, 2);
	Unit1.DoSetLights(1);
	E.PGs[2].fg.TakeUnit(Unit1);
	E.PGs[2].fg.SetTargCount(mapPanther, mapRailGun, 6);
	E.PGs[2].fg.SetTargCount(mapPanther, mapEMP, 4);
	E.VF[2].RecordVehReinforceGroup(E.PGs[2].fg, 9);

	// Panther Patrol #2
	E.PGs[3].fg = CreateFightGroup(pNo);
	E.PGs[3].curWaypoint = 0;
	E.PGs[3].totalWaypoints = 3;
	E.PGs[3].goBack = true;
	E.PGs[3].numGuardRecs = 3;
	E.PGs[3].waitRects[0] = MAP_RECT(12 + 31, 52 - 1, 17 + 31, 56 - 1);
	E.PGs[3].waitRects[1] = MAP_RECT(84 + 31, 75 - 1, 89 + 31, 79 - 1);
	E.PGs[3].waitRects[2] = MAP_RECT(88 + 31, 102 - 1, 91 + 31, 105 - 1);
	E.PGs[3].guardRecs[0] = MAP_RECT(1 + 31, 47 - 1, 69 + 31, 127 - 1);
	E.PGs[3].guardRecs[1] = MAP_RECT(70 + 31, 59 - 1, 78 + 31, 112 - 1);
	E.PGs[3].guardRecs[2] = MAP_RECT(79 + 31, 64 - 1, 97 + 31, 109 - 1);
	E.PGs[3].fg.SetRect(E.PGs[3].waitRects[0]);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(117, 74), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(116, 75), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(116, 76), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(118, 76), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(117, 76), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(116, 77), pNo, mapEMP, 6);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(119, 77), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(117, 77), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(118, 77), pNo, mapRailGun, 6);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(117, 78), pNo, mapRailGun, 2);
	Unit1.DoSetLights(1);
	E.PGs[3].fg.TakeUnit(Unit1);
	E.PGs[3].fg.SetTargCount(mapPanther, mapRailGun, 8);
	E.PGs[3].fg.SetTargCount(mapPanther, mapEMP, 2);
	E.VF[3].RecordVehReinforceGroup(E.PGs[3].fg, 9);

	// Tigers - Northern Entrance
	E.Wall_NorthEntrance = CreateFightGroup(pNo);
	E.Wall_NorthEntrance.SetRect(MAP_RECT(17 + 31, 51 - 1, 21 + 31, 54 - 1));
	E.Wall_NorthEntrance.AddGuardedRect(MAP_RECT(17 + 31, 44 - 1, 22 + 31, 55 - 1));
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(51, 50), pNo, mapEMP, 4);
	Unit1.DoSetLights(1);
	E.Wall_NorthEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(51, 51), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.Wall_NorthEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(50, 51), pNo, mapRailGun, 5);
	Unit1.DoSetLights(1);
	E.Wall_NorthEntrance.TakeUnit(Unit1);
	E.Wall_NorthEntrance.SetTargCount(mapTiger, mapRailGun, 4);
	E.Wall_NorthEntrance.SetTargCount(mapTiger, mapEMP, 3);
	E.VF[2].RecordVehReinforceGroup(E.Wall_NorthEntrance, 8);

	// Tigers - Eastern Entrance
	E.Wall_EastEntrance = CreateFightGroup(pNo);
	E.Wall_EastEntrance.SetRect(MAP_RECT(85 + 31, 83 - 1, 90 + 31, 88 - 1));
	E.Wall_EastEntrance.AddGuardedRect(MAP_RECT(88 + 31, 83 - 1, 101 + 31, 87 - 1));
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(119, 84), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.Wall_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(118, 84), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.Wall_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(120, 84), pNo, mapEMP, 7);
	Unit1.DoSetLights(1);
	E.Wall_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(118, 85), pNo, mapEMP, 1);
	Unit1.DoSetLights(1);
	E.Wall_EastEntrance.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(119, 85), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.Wall_EastEntrance.TakeUnit(Unit1);
	E.Wall_EastEntrance.SetTargCount(mapTiger, mapRailGun, 3);
	E.Wall_EastEntrance.SetTargCount(mapTiger, mapEMP, 2);
	E.VF[3].RecordVehReinforceGroup(E.Wall_EastEntrance, 8);

	// Southeastern Lab Defenders
	E.SE_Lab = CreateFightGroup(pNo);
	E.SE_Lab.SetRect(MAP_RECT(70 + 31, 87 - 1, 74 + 31, 91 - 1));
	E.SE_Lab.AddGuardedRect(MAP_RECT(61 + 31, 80 - 1, 73 + 31, 87- 1));
	E.SE_Lab.AddGuardedRect(MAP_RECT(66 + 31, 88 - 1, 80 + 31, 93 - 1));
	E.SE_Lab.AddGuardedRect(MAP_RECT(63 + 31, 94 - 1, 81 + 31, 98 - 1));
	E.SE_Lab.AddGuardedRect(MAP_RECT(73 + 31, 99 - 1, 84 + 31, 105 - 1));
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(104, 87), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.SE_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(103, 87), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.SE_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(105, 88), pNo, mapRailGun, 1);
	Unit1.DoSetLights(1);
	E.SE_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(104, 88), pNo, mapRailGun, 2);
	Unit1.DoSetLights(1);
	E.SE_Lab.TakeUnit(Unit1);
	E.SE_Lab.SetTargCount(mapPanther, mapRailGun, 3);
	E.SE_Lab.SetTargCount(mapPanther, mapEMP, 1);
	E.VF[3].RecordVehReinforceGroup(E.SE_Lab, 7);

	// Western Lab Defenders
	E.SW_Lab = CreateFightGroup(pNo);
	E.SW_Lab.SetRect(MAP_RECT(3 + 31, 90 - 1, 9 + 31, 93 - 1));
	E.SW_Lab.AddGuardedRect(MAP_RECT(1 + 31, 80 - 1, 7 + 31, 100 - 1));
	E.SW_Lab.AddGuardedRect(MAP_RECT(8 + 31, 84 - 1, 15 + 31, 96 - 1));
	E.SW_Lab.AddGuardedRect(MAP_RECT(16 + 31, 92 - 1, 24 + 31, 97 - 1));
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(35, 89), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.SW_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(37, 89), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.SW_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(38, 89), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.SW_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(38, 91), pNo, mapAcidCloud, 3);
	Unit1.DoSetLights(1);
	E.SW_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapTiger, LOCATION(39, 91), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.SW_Lab.TakeUnit(Unit1);
	E.SW_Lab.SetTargCount(mapPanther, mapRailGun, 2);
	E.SW_Lab.SetTargCount(mapTiger, mapRailGun, 1);
	E.SW_Lab.SetTargCount(mapTiger, mapEMP, 1);
	E.SW_Lab.SetTargCount(mapTiger, mapAcidCloud, 1);
	E.VF[2].RecordVehReinforceGroup(E.SW_Lab, 7);

	// Bottom middle Lab Defenders
	E.Mid_Lab = CreateFightGroup(pNo);
	E.Mid_Lab.SetRect(MAP_RECT(31 + 31, 82 - 1, 34 + 31, 87 - 1));
	E.Mid_Lab.AddGuardedRect(MAP_RECT(27 + 31, 81 - 1, 35 + 31, 89 - 1));
	E.Mid_Lab.AddGuardedRect(MAP_RECT(36 + 31, 79 - 1, 41 + 31, 90 - 1));
	E.Mid_Lab.AddGuardedRect(MAP_RECT(30 + 31, 73 - 1, 44 + 31, 88 - 1));
	E.Mid_Lab.AddGuardedRect(MAP_RECT(45 + 31, 76 - 1, 49 + 31, 83 - 1));
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(64, 82), pNo, mapEMP, 5);
	Unit1.DoSetLights(1);
	E.Mid_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(65, 83), pNo, mapRailGun, 3);
	Unit1.DoSetLights(1);
	E.Mid_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(64, 83), pNo, mapRailGun, 2);
	Unit1.DoSetLights(1);
	E.Mid_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(64, 84), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	E.Mid_Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(65, 84), pNo, mapRailGun, 2);
	Unit1.DoSetLights(1);
	E.Mid_Lab.TakeUnit(Unit1);
	E.Mid_Lab.SetTargCount(mapPanther, mapRailGun, 3);
	E.Mid_Lab.SetTargCount(mapPanther, mapEMP, 2);
	E.VF[2].RecordVehReinforceGroup(E.Mid_Lab, 7);

	// Northern Lab Defenders
	// to do

	// Outer patrol - north
	// rect1 = 4, 41 - 7, 45
	// rect2 = 29,42 - 31, 45
	E.PGs[4].fg = CreateFightGroup(pNo);
	E.PGs[4].waitRects[0] = MAP_RECT(4 + 31, 41 - 1, 7 + 31, 45 - 1);
	E.PGs[4].waitRects[1] = MAP_RECT(29 + 31, 42 - 1, 31 + 31, 45 - 1);
	E.PGs[4].totalWaypoints = 2;
	E.PGs[4].goBack = false;
	E.PGs[4].curWaypoint = 1;
	E.PGs[4].fg.SetRect(E.PGs[4].waitRects[1]);
	E.PGs[4].guardRecs[0] = MAP_RECT(1 + 31, 40 - 1, 42 + 31, 45 - 1);
	E.PGs[4].guardRecs[1] = MAP_RECT(16 + 31, 46 - 1, 23 + 31, 54 - 1);
	E.PGs[4].numGuardRecs = 2;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(9 + 31, 41 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(12 + 31, 42 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8 + 31, 43 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(10 + 31, 40 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 41 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8 + 31, 40 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.PGs[4].fg.TakeUnit(Unit1);
	E.PGs[4].fg.SetTargCount(mapLynx, mapRailGun, 4);
	E.PGs[4].fg.SetTargCount(mapLynx, mapEMP, 2);
	E.VF[2].RecordVehReinforceGroup(E.PGs[4].fg, 9);

	// Outer patrol - northeast
	// rect1 = 45, 38 - 49, 43
	// rect2 = 69,40 - 73, 44
	// rect3 = 81, 59 - 84, 63
	E.PGs[5].fg = CreateFightGroup(pNo);
	E.PGs[5].waitRects[0] = MAP_RECT(45 + 31, 38 - 1, 49 + 31, 43 - 1);
	E.PGs[5].waitRects[1] = MAP_RECT(70 + 31, 40 - 1, 73 + 31, 44 - 1);
	E.PGs[5].waitRects[2] = MAP_RECT(81 + 31, 59 - 1, 84 + 31, 63 - 1);
	E.PGs[5].totalWaypoints = 3;
	E.PGs[5].goBack = false;
	E.PGs[5].curWaypoint = 1;
	E.PGs[5].fg.SetRect(E.PGs[5].waitRects[1]);
	E.PGs[5].guardRecs[0] = MAP_RECT(42 + 31, 37 - 1, 74 + 31, 45 - 1);
	E.PGs[5].guardRecs[1] = MAP_RECT(69 + 31, 42 - 1, 82 + 31, 58 - 1);
	E.PGs[5].guardRecs[2] = MAP_RECT(78 + 31, 57 - 1, 94 + 31, 64 - 1);
	E.PGs[5].numGuardRecs = 3;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 39 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 38 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 40 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 41 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 41 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(45 + 31, 39 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52 + 31, 41 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[5].fg.TakeUnit(Unit1);
	E.PGs[5].fg.SetTargCount(mapLynx, mapRailGun, 7);
	E.VF[2].RecordVehReinforceGroup(E.PGs[5].fg, 9);

	// Outer patrol - south and west
	// rect1 = 81, 110 -  84, 113
	// rect2 = 98, 110 - 101, 113
	// rect3 = 98,  88 - 101, 93
	E.PGs[6].fg = CreateFightGroup(pNo);
	E.PGs[6].waitRects[0] = MAP_RECT(81 + 31, 110 - 1,  84 + 31, 113 - 1);
	E.PGs[6].waitRects[1] = MAP_RECT(98 + 31, 110 - 1, 101 + 31, 113 - 1);
	E.PGs[6].waitRects[2] = MAP_RECT(98 + 31,  88 - 1, 101 + 31,  93 - 1);
	E.PGs[6].totalWaypoints = 3;
	E.PGs[6].goBack = true;
	E.PGs[6].curWaypoint = 0;
	E.PGs[6].fg.SetRect(E.PGs[6].waitRects[0]);
	E.PGs[6].guardRecs[0] = MAP_RECT(80 + 31, 109 - 1, 103 + 31, 114 - 1);
	E.PGs[6].guardRecs[1] = MAP_RECT(97 + 31, 85 - 1, 108 + 31, 114 - 1);
	E.PGs[6].numGuardRecs = 2;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(100 + 31, 111 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(102 + 31, 112 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(99 + 31, 109 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(100 + 31, 112 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(100 + 31, 113 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(103 + 31, 110 - 1), pNo, mapRailGun, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(98 + 31, 110 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(98 + 31, 112 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104 + 31, 108 - 1), pNo, mapEMP, 0);
	Unit1.DoSetLights(1);
	E.PGs[6].fg.TakeUnit(Unit1);
	E.PGs[6].fg.SetTargCount(mapLynx, mapRailGun, 6);
	E.PGs[6].fg.SetTargCount(mapLynx, mapEMP, 3);
	E.VF[3].RecordVehReinforceGroup(E.PGs[6].fg, 9);

	// Outer base guard posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(77, 55), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(83, 58), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(60, 60), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(48, 63), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(70, 64), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(43, 67), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(94, 70), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(108, 73), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(64, 74), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(81, 74), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(53, 77), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(69, 80), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(106, 89), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(33, 91), pNo, mapRailGun, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(107, 96), pNo, mapRailGun, 0);

	// Outer base tubes
	CreateTubeOrWallLine( 4 + 31, 92 - 1, 18 + 31, 92 - 1, mapTube);
	CreateTubeOrWallLine( 4 + 31, 93 - 1,  4 + 31, 95 - 1, mapTube);
	CreateTubeOrWallLine(15 + 31, 88 - 1, 18 + 31, 88 - 1, mapTube);
	CreateTubeOrWallLine(17 + 31, 80 - 1, 18 + 31, 80 - 1, mapTube);
	CreateTubeOrWallLine(20 + 31, 83 - 1, 44 + 31, 83 - 1, mapTube);
	CreateTubeOrWallLine(25 + 31, 81 - 1, 25 + 31, 84 - 1, mapTube);
	CreateTubeOrWallLine(26 + 31, 81 - 1, 27 + 31, 81 - 1, mapTube);
	CreateTubeOrWallLine(38 + 31, 84 - 1, 38 + 31, 85 - 1, mapTube);
	CreateTubeOrWallLine(35 + 31, 80 - 1, 35 + 31, 82 - 1, mapTube);
	CreateTubeOrWallLine(30 + 31, 75 - 1, 30 + 31, 82 - 1, mapTube);
	CreateTubeOrWallLine(31 + 31, 78 - 1, 33 + 31, 78 - 1, mapTube);
	CreateTubeOrWallLine(28 + 31, 67 - 1, 28 + 31, 72 - 1, mapTube);
	CreateTubeOrWallLine(24 + 31, 69 - 1, 27 + 31, 69 - 1, mapTube);
	CreateTubeOrWallLine(21 + 31, 63 - 1, 21 + 31, 67 - 1, mapTube);
	CreateTubeOrWallLine(24 + 31, 61 - 1, 25 + 31, 61 - 1, mapTube);
	CreateTubeOrWallLine(25 + 31, 62 - 1, 25 + 31, 63 - 1, mapTube);
	CreateTubeOrWallLine(32 + 31, 73 - 1, 36 + 31, 73 - 1, mapTube);
	CreateTubeOrWallLine(35 + 31, 74 - 1, 35 + 31, 76 - 1, mapTube);
	CreateTubeOrWallLine(36 + 31, 61 - 1, 36 + 31, 73 - 1, mapTube);
	CreateTubeOrWallLine(31 + 31, 64 - 1, 35 + 31, 64 - 1, mapTube);
	CreateTubeOrWallLine(47 + 31, 81 - 1, 51 + 31, 81 - 1, mapTube);
	CreateTubeOrWallLine(35 + 31, 70 - 1, 40 + 31, 70 - 1, mapTube);
	CreateTubeOrWallLine(46 + 31, 69 - 1, 53 + 31, 69 - 1, mapTube);
	CreateTubeOrWallLine(47 + 31, 64 - 1, 47 + 31, 68 - 1, mapTube);
	CreateTubeOrWallLine(38 + 31, 78 - 1, 40 + 31, 78 - 1, mapTube);
	CreateTubeOrWallLine(40 + 31, 75 - 1, 40 + 31, 77 - 1, mapTube);
	CreateTubeOrWallLine(41 + 31, 75 - 1, 43 + 31, 75 - 1, mapTube);
	CreateTubeOrWallLine(43 + 31, 72 - 1, 43 + 31, 74 - 1, mapTube);
	CreateTubeOrWallLine(44 + 31, 73 - 1, 53 + 31, 73 - 1, mapTube);
	CreateTubeOrWallLine(53 + 31, 70 - 1, 53 + 31, 73 - 1, mapTube);
	CreateTubeOrWallLine(53 + 31, 70 - 1, 53 + 31, 72 - 1, mapTube);
	CreateTubeOrWallLine(52 + 31, 74 - 1, 52 + 31, 76 - 1, mapTube);
	CreateTubeOrWallLine(53 + 31, 76 - 1, 64 + 31, 76 - 1, mapTube);
	CreateTubeOrWallLine(54 + 31, 77 - 1, 54 + 31, 79 - 1, mapTube);
	CreateTubeOrWallLine(55 + 31, 79 - 1, 58 + 31, 79 - 1, mapTube);
	CreateTubeOrWallLine(59 + 31, 77 - 1, 59 + 31, 78 - 1, mapTube);
	CreateTubeOrWallLine(62 + 31, 69 - 1, 65 + 31, 69 - 1, mapTube);
	CreateTubeOrWallLine(57 + 31, 57 - 1, 57 + 31, 71 - 1, mapTube);
	CreateTubeOrWallLine(58 + 31, 57 - 1, 60 + 31, 57 - 1, mapTube);
	CreateTubeOrWallLine(60 + 31, 52 - 1, 60 + 31, 56 - 1, mapTube);
	CreateTubeOrWallLine(67 + 31, 71 - 1, 67 + 31, 72 - 1, mapTube);
	CreateTubeOrWallLine(65 + 31, 78 - 1, 68 + 31, 78 - 1, mapTube);
	CreateTubeOrWallLine(65 + 31, 81 - 1, 79 + 31, 81 - 1, mapTube);
	CreateTubeOrWallLine(80 + 31, 80 - 1, 80 + 31, 94 - 1, mapTube);
	CreateTubeOrWallLine(69 + 31, 82 - 1, 69 + 31, 83 - 1, mapTube);
	CreateTubeOrWallLine(78 + 31, 88 - 1, 79 + 31, 88 - 1, mapTube);
	CreateTubeOrWallLine(74 + 31, 95 - 1, 81 + 31, 95 - 1, mapTube);
	CreateTubeOrWallLine(78 + 31, 96 - 1, 78 + 31, 101 - 1, mapTube);
	TethysGame::CreateWallOrTube(33 + 31, 72 - 1, -1, mapTube);
	TethysGame::CreateWallOrTube(63 + 31, 80 - 1, -1, mapTube);
	TethysGame::CreateWallOrTube(56 + 31, 67 - 1, -1, mapTube);
	TethysGame::CreateWallOrTube(58 + 31, 68 - 1, -1, mapTube);
	TethysGame::CreateWallOrTube(60 + 31, 71 - 1, -1, mapTube);

	// Outer base walls
	CreateTubeOrWallLine( 1 + 31, 94 - 1,  3 + 31, 94 - 1, mapWall);
	CreateTubeOrWallLine( 5 + 31, 94 - 1,  6 + 31, 94 - 1, mapWall);
	CreateTubeOrWallLine(35 + 31, 84 - 1, 35 + 31, 89 - 1, mapWall);
	CreateTubeOrWallLine(41 + 31, 84 - 1, 41 + 31, 88 - 1, mapWall);
	CreateTubeOrWallLine(36 + 31, 84 - 1, 37 + 31, 84 - 1, mapWall);
	CreateTubeOrWallLine(39 + 31, 84 - 1, 40 + 31, 84 - 1, mapWall);
	CreateTubeOrWallLine(69 + 31, 92 - 1, 74 + 31, 92 - 1, mapWall);
	CreateTubeOrWallLine(74 + 31, 93 - 1, 74 + 31, 94 - 1, mapWall);
	CreateTubeOrWallLine(74 + 31, 96 - 1, 74 + 31, 100 - 1, mapWall);
	CreateTubeOrWallLine(44 + 31, 58 - 1, 50 + 31, 58 - 1, mapWall);
	CreateTubeOrWallLine(44 + 31, 59 - 1, 44 + 31, 64 - 1, mapWall);
	CreateTubeOrWallLine(50 + 31, 59 - 1, 50 + 31, 64 - 1, mapWall);
	CreateTubeOrWallLine(44 + 31, 64 - 1, 46 + 31, 64 - 1, mapWall);
	CreateTubeOrWallLine(48 + 31, 64 - 1, 49 + 31, 64 - 1, mapWall);
	TethysGame::CreateWallOrTube(6 + 31, 95 - 1, -1, mapWall);

	// Outer wall guard posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(85, 45), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(98, 45), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(73, 47), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(63, 47), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(34, 47), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(39, 47), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(45, 47), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(56, 47), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(45, 49), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(56, 49), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(107, 60), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(124, 79), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(126, 79), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(124, 89), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(126, 89), pNo, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(126, 97), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(119, 106), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(113, 106), pNo, mapAcidCloud, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(126, 106), pNo, mapAcidCloud, 0);

	// Outer wall
	CreateTubeOrWallLine( 1 + 31, 46 - 1, 16 + 31, 46 - 1, mapWall);
	CreateTubeOrWallLine(16 + 31, 47 - 1, 16 + 31, 49 - 1, mapWall);
	CreateTubeOrWallLine(23 + 31, 47 - 1, 23 + 31, 49 - 1, mapWall);
	CreateTubeOrWallLine(23 + 31, 46 - 1, 43 + 31, 46 - 1, mapWall);
	CreateTubeOrWallLine(43 + 31, 44 - 1, 43 + 31, 45 - 1, mapWall);
	CreateTubeOrWallLine(44 + 31, 44 - 1, 69 + 31, 44 - 1, mapWall);
	CreateTubeOrWallLine(69 + 31, 45 - 1, 69 + 31, 59 - 1, mapWall);
	CreateTubeOrWallLine(70 + 31, 59 - 1, 78 + 31, 59 - 1, mapWall);
	CreateTubeOrWallLine(78 + 31, 60 - 1, 78 + 31, 64 - 1, mapWall);
	CreateTubeOrWallLine(78 + 31, 64 - 1, 97 + 31, 64 - 1, mapWall);
	CreateTubeOrWallLine(97 + 31, 65 - 1, 97 + 31, 82 - 1, mapWall);
	CreateTubeOrWallLine(93 + 31, 82 - 1, 96 + 31, 82 - 1, mapWall);
	CreateTubeOrWallLine(93 + 31, 88 - 1, 96 + 31, 88 - 1, mapWall);
	CreateTubeOrWallLine(97 + 31, 88 - 1, 97 + 31, 109 - 1, mapWall);
	CreateTubeOrWallLine(81 + 31, 109 - 1, 96 + 31, 109 - 1, mapWall);

}

MAP_RECT GetMiningRect(Unit mine, Unit smelter)
{
	return GetMiningRect(mine.Location(), smelter.Location());
}

MAP_RECT GetMiningRect(LOCATION mine, LOCATION smelter)
{
	LOCATION topLeft,
		bottomRight;
	if (mine.x < smelter.x)
	{
		topLeft.x = mine.x;
		bottomRight.x = smelter.x;
	}
	else
	{
		topLeft.x = smelter.x;
		bottomRight.x = mine.x;
	}
	if (mine.y < smelter.y)
	{
		topLeft.y = mine.y;
		bottomRight.y = smelter.y;
	}
	else if (mine.y == smelter.y)
	{
		topLeft.y = smelter.y;
		bottomRight.y = mine.y + 1;
	}
	else
	{
		topLeft.y = smelter.y;
		bottomRight.y = mine.y;
	}
	return MAP_RECT{ topLeft, bottomRight };
}

Export void UpdatePatrolPositions()
{
	for (int i = 0; i < 7; i++)
	{
		if (E.PGs[i].fg.IsInitialized())
		{
			if (E.PGs[i].goBack)
			{
				if (E.PGs[i].curWaypoint <= 0)
				{
					E.PGs[i].goBack = false;
					E.PGs[i].curWaypoint = 1;
				}
				else
				{
					E.PGs[i].curWaypoint--;
				}
			}
			else
			{
				if (E.PGs[i].curWaypoint >= E.PGs[i].totalWaypoints - 1)
				{
					E.PGs[i].goBack = true;
					E.PGs[i].curWaypoint = E.PGs[i].totalWaypoints - 2;
				}
				else
				{
					E.PGs[i].curWaypoint++;
				}
			}
			if (E.PGs[i].curWaypoint < 0 || E.PGs[i].curWaypoint >= E.PGs[i].totalWaypoints)
			{
				TethysGame::AddMessage(-1, -1, "Patrol group tried to move to undefined location", -1, sndDirt);
			}
			else
			{
				E.PGs[i].fg.ClearGuarderdRects();
				E.PGs[i].fg.SetRect(E.PGs[i].waitRects[E.PGs[i].curWaypoint]);
				for (int j = 0; j < E.PGs[i].numGuardRecs; j++)
				{
					E.PGs[i].fg.AddGuardedRect(E.PGs[i].guardRecs[j]);
				}
			}
		}
	}
}
