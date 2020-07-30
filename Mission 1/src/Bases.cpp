#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"

#define numof(array) (sizeof(array)/sizeof(array[0]))
#define autosize(array) numof(array), array

void DoRandomBases()
{
	// Randomized Base code.
	int i[4] = { 0, 1, 2, 3 };

	RandomizeList(autosize(i));

	// Create bases - check to make sure owner is active first!
	if (Player[i[0]].IsHuman())
	{
		SetupBase1(i[0]);
	}

	if (Player[i[1]].IsHuman())
	{
		SetupBase2(i[1]);
	}

	if (Player[i[2]].IsHuman())
	{
		SetupBase3(i[2]);
	}

	if (Player[i[3]].IsHuman())
	{
		SetupBase4(i[3]);
	}

}   // end DoRandomBases

void SetupBase1(int pNo)
{
	UnitEx Unit1, Mine, Smelter;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(49 + 31, 47 - 1);
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
	TethysGame::CreateBeacon(mapMiningBeacon, 58 + 31, 56 - 1, 0, yield, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(49 + 31, 47 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(49 + 31, 50 - 1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommandCenter, mapNone);
		Unit1.SetFactoryCargo(1, mapStructureFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapCommonOreSmelter, mapNone);
		break;

	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapAgridome, mapNone);
		break;

	case 2:
		Unit1.SetFactoryCargo(0, mapAgridome, mapNone);
		Unit1.SetFactoryCargo(1, mapGuardPost, weapon);
		break;
	}
	TethysGame::CreateUnit(Smelter, mapCommonOreSmelter, LOCATION(54 + 31, 50 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(53 + 31, 47 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(57 + 31, 47 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine, mapCommonOreMine, LOCATION(58 + 31, 56 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(58 + 31, 51 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(61 + 31, 59 - 1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(53 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(54 + 31, 53 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(55 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(56 + 31, 53 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(57 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);

	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(49 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(48 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(47 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(46 + 31, 52 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(46 + 31, 51 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(62 + 31, 50 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(61 + 31, 48 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(60 + 31, 49 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 46 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(45 + 31, 47 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(44 + 31, 48 - 1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	}

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(48 + 31, 48 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(49 + 31, 48 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}

void SetupBase2(int pNo)
{
	UnitEx Unit1, Mine, Smelter;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(25 + 31, 65 - 1);
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
	TethysGame::CreateBeacon(mapMiningBeacon, 31 + 31, 73 - 1, 0, yield, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(25 + 31, 65 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(21 + 31, 65 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(25 + 31, 62 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(29 + 31, 62 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter, mapCommonOreSmelter, LOCATION(27 + 31, 68 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(22 + 31, 68 - 1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommandCenter, mapNone);
		Unit1.SetFactoryCargo(1, mapStructureFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapCommonOreSmelter, mapNone);
		break;

	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapAgridome, mapNone);
		break;

	case 2:
		Unit1.SetFactoryCargo(0, mapAgridome, mapNone);
		Unit1.SetFactoryCargo(1, mapGuardPost, weapon);
		break;
	}
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(13 + 31, 69 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine, mapCommonOreMine, LOCATION(31 + 31, 73 - 1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(26 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(27 + 31, 71 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(28 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(29 + 31, 71 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(30 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);

	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(23 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(22 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(21 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(20 + 31, 70 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(24 + 31, 69 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(17 + 31, 66 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(18 + 31, 67 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(16 + 31, 68 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(31 + 31, 64 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(32 + 31, 65 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(33 + 31, 66 - 1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	}

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(27 + 31, 64 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(27 + 31, 65 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}

void SetupBase3(int pNo)
{
	UnitEx Unit1, Mine, Smelter;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(55 + 31, 72 - 1);
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
	TethysGame::CreateBeacon(mapMiningBeacon, 60 + 31, 80 - 1, 0, yield, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(55 + 31, 72 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(51 + 31, 72 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(48 + 31, 72 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(51 + 31, 75 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(60 + 31, 65 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Smelter, mapCommonOreSmelter, LOCATION(56 + 31, 76 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(47 + 31, 75 - 1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommandCenter, mapNone);
		Unit1.SetFactoryCargo(1, mapStructureFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapCommonOreSmelter, mapNone);
		break;

	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapAgridome, mapNone);
		break;

	case 2:
		Unit1.SetFactoryCargo(0, mapAgridome, mapNone);
		Unit1.SetFactoryCargo(1, mapGuardPost, weapon);
		break;
	}
	TethysGame::CreateUnit(Mine, mapCommonOreMine, LOCATION(60 + 31, 80 - 1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(60 + 31, 77 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(59 + 31, 78 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(58 + 31, 79 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(58 + 31, 80 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(58 + 31, 81 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);

	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(49 + 31, 76 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(48 + 31, 77 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(47 + 31, 77 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(48 + 31, 78 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(47 + 31, 78 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(50 + 31, 80 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(52 + 31, 79 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(52 + 31, 77 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(59 + 31, 69 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60 + 31, 70 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61 + 31, 71 - 1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	}

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(57 + 31, 72 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(56 + 31, 73 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}

void SetupBase4(int pNo)
{
	UnitEx Unit1, Mine, Smelter;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(35 + 31, 87 - 1);
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
	TethysGame::CreateBeacon(mapMiningBeacon, 48 + 31, 83 - 1, 0, yield, -1);

	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(35 + 31, 87 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(39 + 31, 87 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(32 + 31, 87 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(28 + 31, 87 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(31 + 31, 83 - 1), pNo, mapNone, 0);
	switch (Player[pNo].Difficulty())
	{
	case 0:
		Unit1.SetFactoryCargo(0, mapCommandCenter, mapNone);
		Unit1.SetFactoryCargo(1, mapStructureFactory, mapNone);
		Unit1.SetFactoryCargo(2, mapCommonOreSmelter, mapNone);
		break;

	case 1:
		Unit1.SetFactoryCargo(0, mapCommonOreSmelter, mapNone);
		Unit1.SetFactoryCargo(1, mapAgridome, mapNone);
		break;

	case 2:
		Unit1.SetFactoryCargo(0, mapAgridome, mapNone);
		Unit1.SetFactoryCargo(1, mapGuardPost, weapon);
		break;
	}
	TethysGame::CreateUnit(Smelter, mapCommonOreSmelter, LOCATION(39 + 31, 83 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(47 + 31, 90 - 1), pNo, mapNone, 0);
	TethysGame::CreateUnit(Mine, mapCommonOreMine, LOCATION(48 + 31, 83 - 1), pNo, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(42 + 31, 84 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(43 + 31, 83 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(44 + 31, 84 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(43 + 31, 85 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(46 + 31, 84 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	Unit1.DoCargoRoute(Mine, Smelter);

	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(34 + 31, 82 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(34 + 31, 83 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(34 + 31, 84 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(30 + 31, 85 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(29 + 31, 85 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(34 + 31, 88 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(36 + 31, 88 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEarthworker, LOCATION(26 + 31, 90 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboMiner, LOCATION(40 + 31, 90 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapRoboSurveyor, LOCATION(42 + 31, 89 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(25 + 31, 83 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(27 + 31, 82 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	if (Player[pNo].Difficulty() == 0)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(29 + 31, 81 - 1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	}
}
