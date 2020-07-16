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
	Unit Unit1;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(6 + 31, 55 - 1);
	SetupInitRes(pNo);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(4 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(5 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(10 + 31, 54 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(2 + 31, 55 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 57 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(3 + 31, 53 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

}

void SetupBase2(int pNo)
{
	Unit Unit1;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(14 + 31, 57 - 1);
	SetupInitRes(pNo);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 57 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 58 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13 + 31, 59 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15 + 31, 58 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(17 + 31, 57 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(11 + 31, 56 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(11 + 31, 58 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(10 + 31, 57 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}

void SetupBase3(int pNo)
{
	Unit Unit1;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(7 + 31, 61 - 1);
	SetupInitRes(pNo);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 59 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 60 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8 + 31, 61 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(9 + 31, 62 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7 + 31, 62 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 62 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6 + 31, 61 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 60 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 61 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3 + 31, 62 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(2 + 31, 59 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}

void SetupBase4(int pNo)
{
	Unit Unit1;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(18 + 31, 56 - 1);
	SetupInitRes(pNo);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(24 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22 + 31, 57 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20 + 31, 55 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20 + 31, 56 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20 + 31, 57 - 1), pNo, weapon, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(24 + 31, 58 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(22 + 31, 59 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(20 + 31, 59 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(18 + 31, 58 - 1), pNo, mapNone, 0);
	Unit1.DoSetLights(1);
}
