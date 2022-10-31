#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types.h>

#include "Bases.h"
#include "AI.h"

// Used below to randomize bases
#define numof(array) (sizeof(array)/sizeof(array[0]))
#define autosize(array) numof(array), array

extern int numEden;
extern int numPlym;

// --------------------------------------------------------------------------------------------------------------------

void SetupInitRes(int pNo)
{
	Player[pNo].MarkResearchComplete(9000);   // Mission 7 tech enabler

	switch (Player[pNo].Difficulty())
	{
	case 0:
		Player[pNo].SetKids(14);
		Player[pNo].SetWorkers(34);
		Player[pNo].SetScientists(15);
		Player[pNo].SetOre(4000);
		Player[pNo].SetRareOre(2000);
		break;
	case 1:
		Player[pNo].SetKids(12);
		Player[pNo].SetWorkers(32);
		Player[pNo].SetScientists(15);
		Player[pNo].SetOre(3500);
		Player[pNo].SetRareOre(1500);
		break;
	case 2:
		Player[pNo].SetKids(10);
		Player[pNo].SetWorkers(30);
		Player[pNo].SetScientists(13);
		Player[pNo].SetOre(3000);
		Player[pNo].SetRareOre(1000);
		break;
	}
	Player[pNo].SetFoodStored(3100);
}

// --------------------------------------------------------------------------------------------------------------------

void DoRandomBases()
{
	// Randomized Base code.
    int i[4] = { 0, 1, 2, 3 };
	//int i[4] = { 0, 0, 0, 0 };
	RandomizeList(autosize(i));
    
    if (Player[i[0]].IsHuman() )
    {
		SetupBase1(i[0]);
    }

	if (Player[i[1]].IsHuman() )
    {
		SetupBase2(i[1]);
    }

    if (Player[i[2]].IsHuman() )
    {
		SetupBase3(i[2]);
    }

    if (Player[i[3]].IsHuman() )
    {
		SetupBase4(i[3]);
    }

}   // end DoRandomBases

void SetupBase1(int pNo)
{
	UnitEx Unit1, lastMine, lastSmelter;
	map_id mWeapon = mapRPG;

	Player[pNo].CenterViewOn(99 + 31, 4 - 1);
	SetupInitRes(pNo);

	// Setup mining beacons.  Position of rare ore beacon changes if player is Plymouth.
	if (Player[pNo].IsEden())
	{
		mWeapon = mapRailGun;
		TethysGame::CreateBeacon(mapMiningBeacon, 148, 5, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(148, 5), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateBeacon(mapMiningBeacon, 140, 5, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(140, 5), pNo, mapNone, 0);
	}

	// Setup rare ore smelter and automatically issue ore hauling orders to trucks
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(144, 2), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(145, 4), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(142, 4), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now handle common ore.
	TethysGame::CreateBeacon(mapMiningBeacon, 131, 14, 0, 0, 0);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(131, 14), pNo, mapNone, 0);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(127, 11), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(127, 13), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(128, 14), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(132, 11), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(131, 13), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(132, 13), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now do the rest of the base
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(130, 3), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(119, 3), pNo, mapNone, 0);
	SetStructureFactoryCargo(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(124, 3), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapSolarPowerArray, LOCATION(105, 4), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(111, 2), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(134, 3), pNo, mapNone, 0);

	// Units
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(135, 4), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(125, 7), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(119, 7), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(129, 6), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(89+31, 11-1), pNo, mWeapon, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(90 + 31, 12 - 1), pNo, mWeapon, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(91 + 31, 13 - 1), pNo, mWeapon, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(91 + 31, 11 - 1), pNo, mapEMP, 3);
	Unit1.DoSetLights(1);
	
	// Tubes
	CreateTubeOrWallLine(83 + 31, 3 - 1, 85 + 31, 3 - 1, mapTube);
	CreateTubeOrWallLine(96 + 31, 4 - 1, 97 + 31, 4 - 1, mapTube);
	CreateTubeOrWallLine(99 + 31, 6 - 1, 99 + 31, 10 - 1, mapTube);
	CreateTubeOrWallLine(105 + 31, 3 - 1, 110 + 31, 3 - 1, mapTube);
	TethysGame::CreateWallOrTube(105 + 31, 4 - 1, -1, mapTube);

}

void SetupBase2(int pNo)
{
	UnitEx Unit1, lastMine, lastSmelter;
	map_id mWeapon = mapRPG;

	Player[pNo].CenterViewOn(120 + 31, 22 - 1);
	SetupInitRes(pNo);

	// Setup mining beacons.  Position of rare ore beacon changes if player is Plymouth.
	if (Player[pNo].IsEden())
	{
		mWeapon = mapRailGun;
		TethysGame::CreateBeacon(mapMiningBeacon, 136, 23, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(136, 23), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateBeacon(mapMiningBeacon, 128, 23, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(128, 23), pNo, mapNone, 0);
	}

	// Setup rare ore smelter and automatically issue ore hauling orders to trucks
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(132, 20), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(133, 22), pNo, mapNone, 5);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(130, 22), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now handle common ore.
	TethysGame::CreateBeacon(mapMiningBeacon, 156, 15, 0, 0, 0);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(156, 15), pNo, mapNone, 0);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(152, 12), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(156, 13), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(155, 13), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(152, 16), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(156, 17), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(154, 17), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now do the rest of the base
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(151, 21), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(144, 16), pNo, mapNone, 0);
	SetStructureFactoryCargo(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(144, 20), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapSolarPowerArray, LOCATION(157, 6), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(144, 13), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(153, 9), pNo, mapNone, 0);

	// Units
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(159, 7), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(140, 16), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(147, 18), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(141, 19), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(94 + 31, 20 - 1), pNo, mWeapon, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(94 + 31, 21 - 1), pNo, mWeapon, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(94 + 31, 22 - 1), pNo, mWeapon, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(96 + 31, 21 - 1), pNo, mapEMP, 4);
	Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(104 + 31, 21 - 1, 110 + 31, 21 - 1, mapTube);
	CreateTubeOrWallLine(116 + 31, 14 - 1, 118 + 31, 14 - 1, mapTube);
	CreateTubeOrWallLine(116 + 31, 22 - 1, 118 + 31, 22 - 1, mapTube);
	TethysGame::CreateWallOrTube(116 + 31, 21 - 1, -1, mapTube);
}

void SetupBase3(int pNo)
{
	UnitEx Unit1, lastMine, lastSmelter;
	map_id mWeapon = mapRPG;

	Player[pNo].CenterViewOn(117 + 31, 37 - 1);
	SetupInitRes(pNo);

	// Setup mining beacons.  Position of rare ore beacon changes if player is Plymouth.
	if (Player[pNo].IsEden())
	{
		mWeapon = mapRailGun;
		TethysGame::CreateBeacon(mapMiningBeacon, 142, 39, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(142, 39), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateBeacon(mapMiningBeacon, 134, 39, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(134, 39), pNo, mapNone, 0);
	}

	// Setup rare ore smelter and automatically issue ore hauling orders to trucks
	TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(138, 36), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(136, 38), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(139, 38), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now handle common ore.
	TethysGame::CreateBeacon(mapMiningBeacon, 152, 30, 0, 0, 0);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(152, 30), pNo, mapNone, 0);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(148, 27), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(150, 29), pNo, mapNone, 7);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(150, 30), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(153, 27), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(154, 29), pNo, mapNone, 6);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(154, 30), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now do the rest of the base
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(148, 36), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(138, 31), pNo, mapNone, 0);
	SetStructureFactoryCargo(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(143, 31), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapSolarPowerArray, LOCATION(153, 38), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(143, 28), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(139, 28), pNo, mapNone, 0);

	// Units
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(136, 34), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(144, 34), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(150, 37), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(139, 34), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(97 + 31, 33 - 1), pNo, mWeapon, 6);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(98 + 31, 33 - 1), pNo, mWeapon, 6);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(99 + 31, 33 - 1), pNo, mWeapon, 6);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(98 + 31, 35 - 1), pNo, mapEMP, 6);
	Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(117 + 31, 31 - 1, 117 + 31, 35 - 1, mapTube);
	CreateTubeOrWallLine(110 + 31, 37 - 1, 115 + 31, 37 - 1, mapTube);
	TethysGame::CreateWallOrTube(107 + 31, 35 - 1, -1, mapTube);
	TethysGame::CreateWallOrTube(110 + 31, 29 - 1, -1, mapTube);
}

void SetupBase4(int pNo)
{
	UnitEx Unit1, lastMine, lastSmelter;
	map_id mWeapon = mapRPG;

	Player[pNo].CenterViewOn(121 + 31, 49 - 1);
	SetupInitRes(pNo);

	// Setup mining beacons.  Position of rare ore beacon changes if player is Plymouth.
	// For this base, the position of the rare ore smelter has to change, too.
	if (Player[pNo].IsEden())
	{
		mWeapon = mapRailGun;
		TethysGame::CreateBeacon(mapMiningBeacon, 156, 67, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(156, 67), pNo, mapNone, 0);
		TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(152, 64), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateBeacon(mapMiningBeacon, 149, 67, 1, 0, 0);
		TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(149, 67), pNo, mapNone, 0);
		TethysGame::CreateUnit(lastSmelter, mapRareOreSmelter, LOCATION(153, 64), pNo, mapNone, 0);
	}

	// Automatically issue ore hauling orders to trucks
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(150, 66), pNo, mapNone, 1);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(153, 66), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	// Now handle common ore.
	TethysGame::CreateBeacon(mapMiningBeacon, 150, 58, 0, 0, 0);
	TethysGame::CreateUnit(lastMine, mapCommonOreMine, LOCATION(150, 58), pNo, mapNone, 0);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(146, 55), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(149, 56), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(150, 56), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);

	TethysGame::CreateUnit(lastSmelter, mapCommonOreSmelter, LOCATION(146, 59), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(149, 60), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(150, 60), pNo, mapNone, 2);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(lastMine, lastSmelter);


	// Now do the rest of the base
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(152, 48), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(141, 47), pNo, mapNone, 0);
	SetStructureFactoryCargo(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(146, 47), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapSolarPowerArray, LOCATION(140, 53), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(156, 48), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(153, 45), pNo, mapNone, 0);

	// Units
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(148, 49), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(141, 50), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(152, 51), pNo, mapNone, 3);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(154, 55), pNo, mapNone, 4);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(123 + 31, 75 - 1), pNo, mWeapon, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(124 + 31, 75 - 1), pNo, mWeapon, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(125 + 31, 75 - 1), pNo, mWeapon, 2);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(124 + 31, 73 - 1), pNo, mapEMP, 2);
	Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(118 + 31, 48 - 1, 119 + 31, 48 - 1, mapTube);
	CreateTubeOrWallLine(115 + 31, 51 - 1, 115 + 31, 54 - 1, mapTube);
	CreateTubeOrWallLine(118 + 31, 56 - 1, 122 + 31, 56 - 1, mapTube);
	CreateTubeOrWallLine(122 + 31, 57 - 1, 122 + 31, 63 - 1, mapTube);
}

// --------------------------------------------------------------------------------------------------------------------

void SetStructureFactoryCargo(Unit SF)
{
	switch (Player[SF.OwnerID()].Difficulty())
	{
	case 0:
		SF.SetFactoryCargo(0, mapVehicleFactory, mapNone);
		SF.SetFactoryCargo(1, mapStandardLab, mapNone);
		SF.SetFactoryCargo(2, mapNursery, mapNone);
		SF.SetFactoryCargo(3, mapUniversity, mapNone);
		SF.SetFactoryCargo(4, mapGORF, mapNone);
		break;
	case 1:
		SF.SetFactoryCargo(0, mapStandardLab, mapNone);
		SF.SetFactoryCargo(1, mapNursery, mapNone);
		SF.SetFactoryCargo(2, mapUniversity, mapNone);
		SF.SetFactoryCargo(3, mapGORF, mapNone);
		break;
	case 2:
		SF.SetFactoryCargo(0, mapNursery, mapNone);
		SF.SetFactoryCargo(1, mapUniversity, mapNone);
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------