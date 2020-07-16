#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"

int numAI = -1;

void SetupAI()
{
	Player[numAI].GoPlymouth();
}

FightGroup FG;

Export void Scout()
{
	// 46, 1
	FG = CreateFightGroup(numAI);
	PatrolRoute Route1;
	LOCATION Points1[] =
	{
		LOCATION(49 + 31, 48 - 1),
		LOCATION(25 + 31, 66 - 1),
		LOCATION(55 + 31, 73 - 1),
		LOCATION(35 + 31, 88 - 1),
		LOCATION(-1,-1)
	};
	Route1.waypoints = Points1;

	Unit Unit1;
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(46 + 31, 1 - 1), numAI, mapNone, 2);
	Unit1.DoSetLights(1);

	FG.TakeUnit(Unit1);
	FG.SetPatrolMode(Route1);

}

Export void Attack1()
{
	Unit Unit1;
	FG.ClearPatrolMode();
	FG.GetFirstOfType(Unit1, clsAll);
	if (Unit1.IsLive())
	{
		FG.RemoveUnit(Unit1);
		Unit1.DoMove(LOCATION(64 + 31, 18 - 1));
	}

	CreatePointTrigger(1, 1, numAI, 64 + 31, 18 - 1, "RemoveScout");

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	FG.DoAttackEnemy();
}

Export void Attack2()
{
	Unit Unit1;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	FG.DoAttackEnemy();
}

Export void Attack3()
{
	Unit Unit1;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(55 + 31, 1 - 1), numAI, mapStickyfoam, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	FG.DoAttackEnemy();
}

Export void Attack4()
{
	Unit Unit1;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(55 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);

	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(57 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	if (numAI > 3)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(59 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	FG.DoAttackEnemy();
}

Export void Attack5()
{
	Unit Unit1;
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(46 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(47 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(48 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(51 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(54 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(55 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56 + 31, 1 - 1), numAI, mapStickyfoam, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(57 + 31, 1 - 1), numAI, mapMicrowave, 2);
	Unit1.DoSetLights(1);
	FG.TakeUnit(Unit1);

	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(59 + 31, 1 - 1), numAI, mapStickyfoam, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60 + 31, 1 - 1), numAI, mapStickyfoam, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	if (numAI > 3)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(61 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(62 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(63 + 31, 1 - 1), numAI, mapMicrowave, 2);
		Unit1.DoSetLights(1);
		FG.TakeUnit(Unit1);
	}

	FG.DoAttackEnemy();
}

Export void RemoveScout()
{
	UnitEx Unit1;
	Unit1.unitID = GameMapEx::GetTileEx(LOCATION(64 + 31, 18 - 1)).unitIndex;
	Unit1.DoPoof();
}