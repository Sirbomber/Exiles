#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "AI.h"

// AI data
extern int numAI;
FightGroup FG[5];
UnitEx HackScout;
int finalAttackTick = 20319;
bool cheated = false;

void SetupAI()
{
	// Set AI to Eden
	Player[numAI].GoEden();

	// Give AI some technology
	Player[numAI].MarkResearchComplete(5111);	// Independent Turret Power Systems
	Player[numAI].MarkResearchComplete(7206);	// Scout-Class Drive Train Refit

	// Setup attack groups
	FG[0] = CreateFightGroup(numAI);
	FG[1] = CreateFightGroup(numAI);
	FG[2] = CreateFightGroup(numAI);
	FG[3] = CreateFightGroup(numAI);
	FG[4] = CreateFightGroup(numAI);

	// Setup attack waves
	CreateTimeTrigger(1, 1,  1500, "SpawnAttack1");
	CreateTimeTrigger(1, 1,  5100, "SpawnAttack2");
	CreateTimeTrigger(1, 1,  9300, "SpawnAttack3");
	CreateTimeTrigger(1, 1, 10715, "SpawnAttack4");
	CreateTimeTrigger(1, 1, 13032, "SpawnAttack5");
	CreateTimeTrigger(1, 1, 16866, "SpawnAttack6");
	CreateTimeTrigger(1, 1, finalAttackTick, "SpawnAttackF");

	// Stealth groups - turn lights on if attacked
	CreateTimeTrigger(1, 0, 25, "CheckLights");

	// This stops the "no enemy units left" trigger from going off early.
	TethysGame::CreateUnit(HackScout, mapScout, LOCATION(60+31, 127-1), numAI, mapNone, 6);
	HackScout.SetInvisible(1);
	CreateTimeTrigger(1, 0, 50, "AntiCheat");
}

Export void SpawnAttack1()
{
	// Attack strength:
	// 10 Laser Lynx, east (8 if <3 players)
	// 8-10 units total

	// Probing attack from the east
    Unit Unit1;
	int stopAt = 71;
	if (numAI < 3)
	{
		stopAt = 69;
	}
    for (int y = 60; y < stopAt; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128+31, y-1), numAI, mapLaser, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

}

Export void SpawnAttack2()
{
	// Attack strength:
	// 1-2 players:
	//  11 Laser Lynx, southeast (+1/2 for players on normal/hard)
	//  11-15 units total
	// 3 players:
	//  14 Laser Lynx, southeast (+1/2 for players on normal/hard)
	//  14 - 20 units total
	// 4 players:
	//  16 Laser Lynx, southeast (+1/2 for players on normal/hard)
	//  16 - 24 units total

	// Laser Lynx rush
    Unit Unit1;
	int stopAt = 113;
	switch (numAI)
	{
		case 4:
			stopAt += 2;
			stopAt += Player[3].Difficulty();
		case 3:
			stopAt += 3;
			stopAt += Player[2].Difficulty();
		case 2:
			stopAt += Player[1].Difficulty();
		default:
			stopAt += Player[0].Difficulty();
			break;
	}
    for (int x = 102; x < stopAt; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 5);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

}

Export void SpawnAttack3()
{
	// Attack strength:
	// 1-2 players:
	//  4 Laser Lynx, northeast
	//  6 Rail Gun Lynx, northeast (+1/2 for players on normal/hard)
	//  9 Laser Lynx, southwest
	//  19-23 units total
	// 3 players:
	//  5 Laser Lynx, northeast
	//  7 Rail Gun Lynx, northeast (+1/2 for players on normal/hard)
	//  10 Laser Lynx, southwest
	//  22 - 28 units total
	// 4 players:
	//  6 Laser Lynx, northeast
	//  8 Rail Gun Lynx, northeast (+1/2 for players on normal/hard)
	//  10 Laser Lynx, southwest (+1 for players on hard)
	//  24 - 36 units total

	// ** to do: update attack strength to match values above
	// Laser Lynx flanking attack from the northeast and south
    Unit Unit1;
    for (int x = 112; x < 119; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 3-1), numAI, mapLaser, 3);
            Unit1.DoSetLights(1);
            FG[1].TakeUnit(Unit1);
    }

	for (int x = 118; x < 126; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 1-1), numAI, mapLaser, 3);
            Unit1.DoSetLights(1);
            FG[1].TakeUnit(Unit1);
    }

    FG[1].SetAttackType(mapCommandCenter);
    FG[1].DoAttackEnemy();

	for (int x = 11; x < 18; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 6);
            Unit1.DoSetLights(1);
            FG[2].TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 126-1), numAI, mapLaser, 6);
            Unit1.DoSetLights(1);
            FG[2].TakeUnit(Unit1);
    }
    FG[2].SetAttackType(mapCommandCenter);
    FG[2].DoAttackEnemy();

}

Export void SpawnAttack4()
{
	// Attack strength:
	// 11 Rail Gun Lynx, southeast
	// 11 units total

	// Rail Gun follow-up to previous attack
    Unit Unit1;
    for (int y = 105; y < 116; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128+31, y-1), numAI, mapRailGun, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

}


Export void SpawnAttack5()
{
	// Attack strength:
	// 19 Laser Lynx + 11 Rail Gun Lynx, southeast
	// 3 Starflare Lynx, northeast
	// 3 Starflare Lynx, southwest
	// 36 units total

	// Distraction
    Unit Unit1;
    for (int y = 105; y < 116; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128+31, y-1), numAI, mapRailGun, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

	for (int x = 105; x < 124; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 5);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

	FG[1].SetLights(false);
	FG[2].SetLights(false);

	// Starflare squad
	for (int x = 1; x < 4; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapStarflare, 6);
            FG[1].TakeUnit(Unit1);
    }

	FG[1].SetAttackType(mapCommandCenter);
    FG[1].DoAttackEnemy();

	for (int x = 121; x < 124; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 1-1), numAI, mapStarflare, 3);
            FG[2].TakeUnit(Unit1);
    }

	FG[2].SetAttackType(mapCommandCenter);
    FG[2].DoAttackEnemy();

}

Export void SpawnAttack6()
{
	// Attack strength:
	// 22 Laser Lynx + 10 Rail Gun Lynx, east
	// 32 units total

	// Eastern spawn
    Unit Unit1;
    for (int y = 61; y < 71; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128+31, y-1), numAI, mapRailGun, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

	for (int y = 63; y < 76; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125+31, y-1), numAI, mapLaser, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

	for (int y = 61; y < 72; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(119+31, y-1), numAI, mapLaser, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

	// Northeastern spawn
	FG[3].SetLights(false);
    for (int x = 112; x < 119; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 3-1), numAI, mapLaser, 3);
            Unit1.DoSetLights(1);
            FG[3].TakeUnit(Unit1);
    }

	for (int x = 118; x < 126; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 1-1), numAI, mapRailGun, 3);
            Unit1.DoSetLights(1);
            FG[3].TakeUnit(Unit1);
    }

    FG[3].SetAttackType(mapCommandCenter);
    FG[3].DoAttackEnemy();

	// Southwestern spawn
	FG[4].SetLights(false);
	for (int x = 11; x < 20; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 6);
            Unit1.DoSetLights(1);
            FG[4].TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 126-1), numAI, mapRailGun, 6);
            Unit1.DoSetLights(1);
            FG[4].TakeUnit(Unit1);
    }
    FG[4].SetAttackType(mapCommandCenter);
    FG[4].DoAttackEnemy();
}

Export void SpawnAttackF()
{
	// Repeat performance of everything we've seen so far.
	// But the players get reinforcements to mop it up, so it should be okay.
	FG[1].SetLights(true);
	FG[2].SetLights(true);

	// Southeast spawn
	Unit Unit1;
    for (int y = 105; y < 116; y++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(128+31, y-1), numAI, mapRailGun, 4);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

	for (int x = 105; x < 124; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 5);
            Unit1.DoSetLights(1);
            FG[0].TakeUnit(Unit1);
    }

    FG[0].SetAttackType(mapCommandCenter);
    FG[0].DoAttackEnemy();

	// Northeastern spawn
    for (int x = 112; x < 119; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 3-1), numAI, mapLaser, 3);
            Unit1.DoSetLights(1);
            FG[1].TakeUnit(Unit1);
    }

	for (int x = 118; x < 126; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 1-1), numAI, mapRailGun, 3);
            Unit1.DoSetLights(1);
            FG[1].TakeUnit(Unit1);
    }

    FG[1].SetAttackType(mapCommandCenter);
    FG[1].DoAttackEnemy();

	// Southwestern spawn
	for (int x = 11; x < 20; x++)
    {
        TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapLaser, 6);
            Unit1.DoSetLights(1);
            FG[2].TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 126-1), numAI, mapRailGun, 6);
            Unit1.DoSetLights(1);
            FG[2].TakeUnit(Unit1);
    }
    FG[2].SetAttackType(mapCommandCenter);
    FG[2].DoAttackEnemy();

	HackScout.DoPoof();
	CreateTimeTrigger(1, 1, 10, "EnableNoEnemyUnitsCheck");
	CreateTimeTrigger(1, 1, 320, "ReinforcePlayers");
}

Export void ReinforcePlayers()
{
	// Create a massive wave of reinforcements for the players
	CreateTimeTrigger(1, 0, 25, "ReinforceWave");
	TethysGame::AddMessage(1, 1, "Reinforcements ready.", -1, 162);
}

int numReinforcements = 120;
int rPlayer = 0;

Export void ReinforceWave()
{
	if (numReinforcements == 0)
	{
		return;
	}

	Unit Unit1;
	for (int x = 0; x < numAI; x++)
	{
		map_id weapon;
		if (Player[rPlayer].IsEden())
		{
			weapon = mapLaser;
		}
		else
		{
			weapon = mapMicrowave;
		}

		if (Player[rPlayer].IsHuman())
		{
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1+31+x, 1-1), rPlayer, weapon, 1);
				Unit1.DoSetLights(1);
				Unit1.DoMove(LOCATION(39+31, 56-1));
				rPlayer++;
				if (rPlayer >= numAI)
				{
					rPlayer = 0;
				}
				numReinforcements--;
		}
	}
}

Export void CheckLights()
{
	if (FG[1].HasBeenAttacked())
	{
		FG[1].SetLights(true);
	}

	if (FG[2].HasBeenAttacked())
	{
		FG[2].SetLights(true);
	}

	if (FG[3].HasBeenAttacked())
	{
		FG[3].SetLights(true);
	}

	if (FG[4].HasBeenAttacked())
	{
		FG[4].SetLights(true);
	}
}

Export void AntiCheat()
{
	if (cheated)
	{
		return;
	}

	if (TethysGame::Tick() < (finalAttackTick - 100))
	{
		if (!HackScout.IsLive())
		{
			cheated = true;
		}
		else
		{
			HackScout.SetDamage(-999);
		}
	}

	if (cheated)
	{
		GameMap::SetVirusUL(LOCATION(29+31, 29-1), 1);
		TethysGame::SetMicrobeSpreadSpeed(2000);
		TethysGame::AddMessage(-1, -1, "SOMEONE'S A CHEATER!", -1, sndSavnt227);
	}

}
