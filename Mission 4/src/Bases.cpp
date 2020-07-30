#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "Bases.h"

// Used below to randomize bases
#define numof(array) (sizeof(array)/sizeof(array[0]))
#define autosize(array) numof(array), array

extern int numAI;

void DoRandomBases()
{
	// Randomized Base code.
    int i[4] = { 0, 1, 2, 3 };

    RandomizeList(autosize(i) );

    // Create bases - check to make sure owner is active first!
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
	UnitEx Unit1, Mine[2], Smelter[2];
	map_id eWeapon = mapMicrowave,
		   mWeapon = mapRPG;
	if (Player[pNo].IsEden())
	{
		eWeapon = mapLaser;
		mWeapon = mapRailGun;
	}

	Player[pNo].CenterViewOn(236+31, 59-1);
	SetupInitRes(pNo);

	// Mining beacons.  If less than 3 players, everyone gets 3 bar yields.  Otherwise, 2 bars.
	int yield = 0;
	if (numAI > 2)
	{
		yield = 1;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 251+31, 61-1, 0, yield, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 238+31, 84-1, 1, yield, 1);
	TethysGame::CreateBeacon(mapFumarole, 251+31, 78-1, -1, -1, -1);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(236+31, 59-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(247+31, 58-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(251+31, 61-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(237+31, 65-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(241+31, 65-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(229+31, 59-1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
		case 0:
			Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
			Unit1.SetFactoryCargo(1, mapVehicleFactory, mapNone);
			Unit1.SetFactoryCargo(2, mapRobotCommand, mapNone);
			Unit1.SetFactoryCargo(3, mapMedicalCenter, mapNone);
			Unit1.SetFactoryCargo(4, mapResidence, mapNone);
			break;
		case 1:
			Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
			Unit1.SetFactoryCargo(1, mapRobotCommand, mapNone);
			Unit1.SetFactoryCargo(2, mapMedicalCenter, mapNone);
			break;
		case 2:
			Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
			break;
	}
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(245+31, 50-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(252+31, 52-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(237+31, 68-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(241+31, 68-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(240+31, 54-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(237+31, 54-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(229+31, 65-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(247+31, 55-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(229+31, 56-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(237+31, 74-1), pNo, mapNone, 0);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(234+31, 81-1), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(242+31, 81-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(238+31, 84-1), pNo, mapNone, 0);

	// Units
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(248+31, 60-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(249+31, 60-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(237+31, 84-1), pNo, mapNone, 4);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(230+31, 60-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(230+31, 61-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(235+31, 82-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	else
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(227+31, 60-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(227+31, 61-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(240+31, 82-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(238+31, 71-1), pNo, mapNone, 4);
		Unit1.DoSetLights(1);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(229+31, 81-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(227+31, 79-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(226+31, 77-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(221+31, 53-1), pNo, mapEMP, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(224+31, 52-1), pNo, mapEMP, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(220+31, 51-1), pNo, mWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(223+31, 50-1), pNo, mWeapon, 0);
		Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(229+31, 62-1, 229+31, 63-1, mapTube);
	CreateTubeOrWallLine(232+31, 59-1, 234+31, 59-1, mapTube);
	CreateTubeOrWallLine(236+31, 61-1, 236+31, 63-1, mapTube);
	CreateTubeOrWallLine(232+31, 65-1, 235+31, 65-1, mapTube);
	CreateTubeOrWallLine(237+31, 56-1, 237+31, 57-1, mapTube);
	CreateTubeOrWallLine(239+31, 59-1, 244+31, 59-1, mapTube);
	CreateTubeOrWallLine(237+31, 70-1, 237+31, 72-1, mapTube);
	if (Player[pNo].IsEden())
	{
		CreateTubeOrWallLine(237+31, 77-1, 235+31, 79-1, mapTube);
	}
	else
	{
		CreateTubeOrWallLine(240+31, 74-1, 240+31, 79-1, mapTube);
	}
	
}

void SetupBase2(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[2];
	map_id eWeapon = mapMicrowave,
		   mWeapon = mapRPG;
	if (Player[pNo].IsEden())
	{
		eWeapon = mapLaser;
		mWeapon = mapRailGun;
	}

	Player[pNo].CenterViewOn(244+31, 93-1);
	SetupInitRes(pNo);

	// Mining beacons.  If less than 3 players, everyone gets 3 bar yields.  Otherwise, 2 bars.
	int yield = 0;
	if (numAI > 2)
	{
		yield = 1;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 252+31, 103-1, 0, yield, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 243+31, 113-1, 1, yield, 1);
	TethysGame::CreateBeacon(mapFumarole, 246+31, 123-1, -1, -1, -1);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(244+31, 93-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(251+31, 93-1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapVehicleFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(3, mapMedicalCenter, mapNone);
		Unit1.SetFactoryCargo(4, mapResidence, mapNone);
		break;
	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(2, mapMedicalCenter, mapNone);
		break;
	case 2:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		break;
	}
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(248+31, 100-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(252+31, 103-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(246+31, 88-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(250+31, 88-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(239+31, 93-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(239+31, 90-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(244+31, 101-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(241+31, 101-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(232+31, 93-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(232+31, 90-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(237+31, 101-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(254+31, 111-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(253+31, 82-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(232+31, 105-1), pNo, mapNone, 0);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(239+31, 110-1), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(247+31, 110-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(243+31, 113-1), pNo, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(249+31, 102-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(250+31, 102-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(242+31, 113-1), pNo, mapNone, 4);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(252+31, 94-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(252+31, 95-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(240+31, 111-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	else
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(249+31, 94-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(249+31, 95-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(245+31, 111-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(250+31, 106-1), pNo, mapNone, 2);
		Unit1.DoSetLights(1);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(228+31, 98-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(226+31, 96-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(230+31, 99-1), pNo, eWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(224+31, 89-1), pNo, mapEMP, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(227+31, 87-1), pNo, mapEMP, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(222+31, 87-1), pNo, mWeapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(224+31, 85-1), pNo, mWeapon, 0);
		Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(248+31, 103-1, 248+31, 106-1, mapTube);
	CreateTubeOrWallLine(254+31, 107-1, 254+31, 109-1, mapTube);
	CreateTubeOrWallLine(248+31, 107-1, 253+31, 107-1, mapTube);
	if (Player[pNo].IsEden())
	{
		CreateTubeOrWallLine(240+31, 108-1, 247+31, 107-1, mapTube);
	}
	else
	{
		TethysGame::CreateWallOrTube(248+31, 108-1, 0, mapTube);
	}
	CreateTubeOrWallLine(250+31,  90-1, 250+31,  91-1, mapTube);
	CreateTubeOrWallLine(247+31,  93-1, 248+31,  93-1, mapTube);
	CreateTubeOrWallLine(241+31,  93-1, 242+31,  93-1, mapTube);
	CreateTubeOrWallLine(235+31,  93-1, 237+31,  93-1, mapTube);
	CreateTubeOrWallLine(244+31,  95-1, 244+31,  99-1, mapTube);
	CreateTubeOrWallLine(251+31,  96-1, 251+31, 100-1, mapTube);
	TethysGame::CreateWallOrTube(239+31, 68-1, 0, mapTube);
}

void SetupBase3(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[2];
	map_id eWeapon = mapMicrowave,
		   mWeapon = mapRPG;
	if (Player[pNo].IsEden())
	{
		eWeapon = mapLaser;
		mWeapon = mapRailGun;
	}

	Player[pNo].CenterViewOn(247+31, 22-1);
	SetupInitRes(pNo);


	// Mining beacons.  If less than 3 players, everyone gets 3 bar yields.  Otherwise, 2 bars.
	int yield = 0;
	if (numAI > 2)
	{
		yield = 1;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 250+31, 7-1, 0, yield, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 236+31, 12-1, 1, yield, 1);
	TethysGame::CreateBeacon(mapFumarole, 226+31, 18-1, -1, -1, -1);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(247+31, 22-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(246+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(250+31, 7-1), pNo, mapNone, 0);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(232+31, 9-1), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(240+31, 9-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(236+31, 12-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(246+31, 15-1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapVehicleFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(3, mapMedicalCenter, mapNone);
		Unit1.SetFactoryCargo(4, mapResidence, mapNone);
		break;
	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(2, mapMedicalCenter, mapNone);
		break;
	case 2:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		break;
	}
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(229+31, 3-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(225+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(250+31, 16-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(240+31, 22-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(240+31, 19-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(251+31, 22-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(254+31, 22-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(235+31, 26-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(244+31, 27-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(254+31, 11-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(248+31, 27-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(251+31, 27-1), pNo, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(247+31, 6-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(248+31, 6-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(235+31, 12-1), pNo, mapNone, 4);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(233+31, 10-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(247+31, 16-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(247+31, 17-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
	}
	else
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(238+31, 10-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(244+31, 16-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(244+31, 17-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
	}
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(241+31, 27-1), pNo, mapNone, 6);
		Unit1.DoSetLights(1);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(225+31, 21-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(226+31, 23-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(228+31, 22-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(228+31, 25-1), pNo, mWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(230+31, 27-1), pNo, mWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(238+31, 28-1), pNo, mapEMP, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(240+31, 29-1), pNo, mapEMP, 4);
		Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(238+31, 26-1, 242+31, 26-1, mapTube);
	CreateTubeOrWallLine(240+31, 25-1, 240+31, 24-1, mapTube);
	CreateTubeOrWallLine(247+31, 24-1, 247+31, 25-1, mapTube);
	CreateTubeOrWallLine(251+31, 24-1, 251+31, 25-1, mapTube);
	CreateTubeOrWallLine(243+31, 22-1, 245+31, 22-1, mapTube);
	CreateTubeOrWallLine(246+31, 18-1, 246+31, 20-1, mapTube);
	CreateTubeOrWallLine(253+31, 16-1, 254+31, 16-1, mapTube);
	CreateTubeOrWallLine(246+31,  7-1, 246+31, 13-1, mapTube);
	CreateTubeOrWallLine(243+31,  9-1, 245+31,  9-1, mapTube);
	CreateTubeOrWallLine(254+31, 14-1, 254+31, 15-1, mapTube);
	if (Player[pNo].IsEden())
	{
		CreateTubeOrWallLine(235+31, 9-1, 242+31, 9-1, mapTube);
	}

}

void SetupBase4(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[2];
	map_id eWeapon = mapMicrowave,
		   mWeapon = mapRPG;
	if (Player[pNo].IsEden())
	{
		eWeapon = mapLaser;
		mWeapon = mapRailGun;
	}

	Player[pNo].CenterViewOn(234+31, 34-1);
	SetupInitRes(pNo);


	// Mining beacons.  If less than 3 players, everyone gets 3 bar yields.  Otherwise, 2 bars.
	int yield = 0;
	if (numAI > 2)
	{
		yield = 1;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 246+31, 36-1, 0, yield, 1);
	TethysGame::CreateBeacon(mapMiningBeacon, 220+31, 40-1, 1, yield, 1);
	TethysGame::CreateBeacon(mapFumarole, 243+31, 41-1, -1, -1, -1);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(234+31, 34-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(242+31, 33-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(246+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(253+31, 38-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(252+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(234+31, 45-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(234+31, 37-1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapVehicleFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(3, mapMedicalCenter, mapNone);
		Unit1.SetFactoryCargo(4, mapResidence, mapNone);
		break;
	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapRobotCommand, mapNone);
		Unit1.SetFactoryCargo(2, mapMedicalCenter, mapNone);
		break;
	case 2:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		break;
	}
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(225+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(221+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(221+31, 29-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(225+31, 29-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(238+31, 38-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(218+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(218+31, 29-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(211+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(211+31, 29-1), pNo, mapNone, 0);

	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(216+31, 37-1), pNo, mapNone, 0);
	}
	else
	{
		TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(224+31, 37-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(220+31, 40-1), pNo, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(243+31, 35-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(244+31, 35-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(219+31, 40-1), pNo, mapNone, 4);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	if (Player[pNo].IsEden())
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(235+31, 38-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(235+31, 39-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(217+31, 38-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	else
	{
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(232+31, 38-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(232+31, 39-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(222+31, 38-1), pNo, mapNone, 4);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	}
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(214+31, 31-1), pNo, mapNone, 2);
		Unit1.DoSetLights(1);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(209+31, 37-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(206+31, 39-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(208+31, 40-1), pNo, eWeapon, 4);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(209+31, 18-1), pNo, mapEMP, 6);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(212+31, 17-1), pNo, mapEMP, 6);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(209+31, 15-1), pNo, mWeapon, 5);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(212+31, 14-1), pNo, mWeapon, 5);
		Unit1.DoSetLights(1);

	// Tubes
	CreateTubeOrWallLine(214+31, 32-1, 216+31, 32-1, mapTube);
	CreateTubeOrWallLine(237+31, 34-1, 239+31, 34-1, mapTube);
	CreateTubeOrWallLine(234+31, 40-1, 234+31, 43-1, mapTube);
	if (Player[pNo].IsEden())
	{
		CreateTubeOrWallLine(225+31, 34-1, 225+31, 36-1, mapTube);
		CreateTubeOrWallLine(219+31, 37-1, 231+31, 37-1, mapTube);
	}
	else
	{
		CreateTubeOrWallLine(225+31, 34-1, 225+31, 35-1, mapTube);
		CreateTubeOrWallLine(227+31, 37-1, 231+31, 37-1, mapTube);
	}

}

void SetupInitRes(int pNo)
{
	Player[pNo].MarkResearchComplete(6000);   // Mission 4 tech enabler

	switch (Player[pNo].Difficulty() )
	{
		case 0:
			Player[pNo].SetKids(28);
			Player[pNo].SetWorkers(34);
            Player[pNo].SetScientists(20);
            Player[pNo].SetFoodStored(1600);
			Player[pNo].SetOre(5000);
			Player[pNo].SetRareOre(3000);
            break;

        case 1:
			Player[pNo].SetKids(26);
			Player[pNo].SetWorkers(31);
            Player[pNo].SetScientists(20);
            Player[pNo].SetFoodStored(1300);
			Player[pNo].SetOre(4000);
			Player[pNo].SetRareOre(2000);
            break;

        case 2:
			Player[pNo].SetKids(24);
			Player[pNo].SetWorkers(29);
            Player[pNo].SetScientists(18);
            Player[pNo].SetFoodStored(1000);
			Player[pNo].SetOre(3000);
			Player[pNo].SetRareOre(1000);
            break;
	}
}
