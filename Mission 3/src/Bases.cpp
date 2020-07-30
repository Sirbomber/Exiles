#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "Bases.h"

// Used below to randomize bases
#define numof(array) (sizeof(array)/sizeof(array[0]))
#define autosize(array) numof(array), array

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
	UnitEx Unit1, Mine[2], Smelter[3];
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(33+31, 7-1);
	SetupInitRes(pNo);

	int yield;
	if (Player[pNo].Difficulty() == 2)
	{
		yield = 1;
	}
	else
	{
		yield = 0;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 50+31, 6-1, 0, yield, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 31+31, 16-1, 1, 1, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(33+31, 7-1), pNo, mapNone, 0);
    TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(9+31, 3-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(14+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(39+31, 10-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(21+31, 10-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(29+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(29+31, 7-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(33+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(37+31, 7-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(37+31, 4-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(45+31, 3-1), pNo, mapNone, 0);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Smelter[2], mapCommonOreSmelter, LOCATION(45+31, 7-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(50+31, 6-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(31+31, 16-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(31+31, 13-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(23+31, 4-1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(47+31, 5-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(48+31, 6-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(47+31, 7-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(48+31, 8-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
	}
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(30+31, 10-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapDIRT, mapNone);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(31+31, 11-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(32+31, 10-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(33+31, 11-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(39+31, 3-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(29+31, 17-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(30+31, 17-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54+31, 4-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54+31, 5-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54+31, 6-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54+31, 7-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	if (Player[pNo].Difficulty() < 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56+31, 6-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56+31, 7-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56+31, 8-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56+31, 9-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}


	CreateTubeOrWallLine(29+31,  9-1, 29+31, 11-1, mapTube);
	CreateTubeOrWallLine(24+31, 10-1, 28+31, 10-1, mapTube);
	CreateTubeOrWallLine(39+31,  4-1, 42+31,  4-1, mapTube);
	CreateTubeOrWallLine(23+31,  7-1, 22+31,  8-1, mapTube);
	CreateTubeOrWallLine(26+31,  4-1, 27+31,  4-1, mapTube);
}

void SetupBase2(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[3];
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(40+31, 26-1);
	SetupInitRes(pNo);

	int yield;
	if (Player[pNo].Difficulty() == 2)
	{
		yield = 1;
	}
	else
	{
		yield = 0;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 55+31, 27-1, 0, yield, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 37+31, 34-1, 1, 1, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(40+31, 26-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(26+31, 17-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(25+31, 21-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(29+31, 26-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(40+31, 23-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(40+31, 20-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(40+31, 17-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(33+31, 21-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(48+31, 19-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(50+31, 24-1), pNo, mapNone, 0);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Smelter[2], mapCommonOreSmelter, LOCATION(50+31, 28-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(37+31, 31-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(44+31, 26-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(44+31, 23-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(55+31, 27-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(37+31, 34-1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(53+31, 24-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(54+31, 25-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(52+31, 29-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(53+31, 30-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
	}
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(33+31, 34-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(34+31, 35-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(36+31, 20-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(34+31, 25-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapDIRT, mapNone);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(36+31, 25-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(35+31, 27-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(37+31, 27-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(44+31, 31-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(45+31, 31-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46+31, 31-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47+31, 31-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	if (Player[pNo].Difficulty() < 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(45+31, 33-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46+31, 33-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47+31, 33-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48+31, 33-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}

	CreateTubeOrWallLine(32+31, 26-1, 38+31, 26-1, mapTube);
	CreateTubeOrWallLine(46+31, 23-1, 47+31, 23-1, mapTube);
	TethysGame::CreateWallOrTube(48+31, 22-1, 0, mapTube);
	CreateTubeOrWallLine(36+31, 21-1, 38+31, 22-1, mapTube);
	CreateTubeOrWallLine(43+31, 17-1, 43+31, 20-1, mapTube);
	CreateTubeOrWallLine(44+31, 19-1, 45+31, 19-1, mapTube);
	CreateTubeOrWallLine(33+31, 24-1, 33+31, 25-1, mapTube);
	CreateTubeOrWallLine(40+31, 28-1, 40+31, 31-1, mapTube);
}

void SetupBase3(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[3];
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(23+31, 36-1);
	SetupInitRes(pNo);

	int yield;
	if (Player[pNo].Difficulty() == 2)
	{
		yield = 1;
	}
	else
	{
		yield = 0;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 28+31, 44-1, 0, yield, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 12+31, 44-1, 1, 1, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(23+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(4+31, 25-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(6+31, 29-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(4+31, 35-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(11+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(15+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(19+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(19+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(14+31, 32-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(23+31, 33-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(27+31, 36-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(23+31, 41-1), pNo, mapNone, 0);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Smelter[2], mapCommonOreSmelter, LOCATION(23+31, 45-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(12+31, 41-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(28+31, 44-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(12+31, 44-1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(26+31, 40-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(27+31, 41-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(26+31, 46-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(27+31, 47-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
	}
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(16+31, 43-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(15+31, 44-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(22+31, 38-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(25+31, 38-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapDIRT, mapNone);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(26+31, 38-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(16+31, 39-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(17+31, 39-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(26+31, 30-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(27+31, 30-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(28+31, 30-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(29+31, 30-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	if (Player[pNo].Difficulty() < 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(25+31, 32-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(26+31, 32-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(27+31, 32-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(28+31, 32-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}

	CreateTubeOrWallLine(23+31, 38-1, 23+31, 39-1, mapTube);
	CreateTubeOrWallLine(11+31, 38-1, 11+31, 39-1, mapTube);
	CreateTubeOrWallLine(15+31, 41-1, 20+31, 41-1, mapTube);
	CreateTubeOrWallLine( 7+31, 35-1,  9+31, 35-1, mapTube);
}

void SetupBase4(int pNo)
{
	UnitEx Unit1, Mine[2], Smelter[3];
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(16+31, 52-1);
	SetupInitRes(pNo);

	int yield;
	if (Player[pNo].Difficulty() == 2)
	{
		yield = 1;
	}
	else
	{
		yield = 0;
	}
	TethysGame::CreateBeacon(mapMiningBeacon, 37+31, 54-1, 0, yield, -1);
	TethysGame::CreateBeacon(mapMiningBeacon, 23+31, 58-1, 1, 1, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(16+31, 52-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(5+31, 57-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(11+31, 59-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(4+31, 50-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(12+31, 49-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(12+31, 52-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(16+31, 55-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(13+31, 55-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(10+31, 55-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(24+31, 51-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[0], mapCommonOreSmelter, LOCATION(32+31, 51-1), pNo, mapNone, 0);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Smelter[2], mapCommonOreSmelter, LOCATION(32+31, 55-1), pNo, mapNone, 0);
	}
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(17+31, 48-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter[1], mapRareOreSmelter, LOCATION(23+31, 55-1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[0], mapCommonOreMine, LOCATION(37 + 31, 54 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine[1], mapCommonOreMine, LOCATION(23+31, 58-1), pNo, mapNone, 0);
	

	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(8+31, 49-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(35+31, 50-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(36+31, 50-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[0], Smelter[0]);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(36+31, 57-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
		TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(35+31, 57-1), pNo, mapNone, 0);
			Unit1.DoSetLights(1);
			Unit1.DoCargoRoute(Mine[0], Smelter[2]);
	}
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(19+31, 57-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(20+31, 58-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.DoCargoRoute(Mine[1], Smelter[1]);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(26+31, 49-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapDIRT, mapNone);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(27+31, 50-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(27+31, 53-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(27+31, 54-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
		Unit1.SetCargo(mapGuardPost, weapon);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(39+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(40+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(41+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(42+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	if (Player[pNo].Difficulty() < 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(41+31, 60-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(42+31, 60-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(43+31, 60-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(44+31, 60-1), pNo, weapon, 0);
			Unit1.DoSetLights(1);
	}

	CreateTubeOrWallLine( 7+31, 50-1, 10+31, 51-1, mapTube);
	CreateTubeOrWallLine(19+31, 52-1, 21+31, 52-1, mapTube);
	CreateTubeOrWallLine(19+31, 55-1, 20+31, 55-1, mapTube);
	CreateTubeOrWallLine(27+31, 51-1, 29+31, 51-1, mapTube);
}

void SetupInitRes(int pNo)
{
	Player[pNo].MarkResearchComplete(3000);   // Mission 1 tech enabler
	Player[pNo].MarkResearchComplete(5000);   // Mission 3 tech enabler
	Player[pNo].MarkResearchComplete(5110);   // Rare Ore Processing

	switch (Player[pNo].Difficulty() )
	{
		case 0:
			Player[pNo].SetWorkers(35);
            Player[pNo].SetScientists(20);
            Player[pNo].SetFoodStored(1200);
			Player[pNo].SetOre(3000);
			Player[pNo].SetRareOre(1000);
            break;

        case 1:
			Player[pNo].SetWorkers(28);
            Player[pNo].SetScientists(18);
            Player[pNo].SetFoodStored(1000);
			Player[pNo].SetOre(2400);
			Player[pNo].SetRareOre(700);
            break;

        case 2:
			Player[pNo].SetWorkers(24);
            Player[pNo].SetScientists(15);
            Player[pNo].SetFoodStored(800);
			Player[pNo].SetOre(1800);
			Player[pNo].SetRareOre(400);
            break;
	}
}
