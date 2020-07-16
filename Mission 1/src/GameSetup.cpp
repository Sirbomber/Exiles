#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>

#include "GameSetup.h"

DisasterCreator DC;

void DoGameSetup()
{
	// For mission 1, morale will always be forced at good.
	TethysGame::ForceMoraleGood(-1);

	// Force the day/night cycle.
	TethysGame::SetDaylightEverywhere(0);
	GameMap::SetInitialLightLevel(17);
	TethysGame::SetDaylightMoves(1);

	// Setup DisasterCreator
	SetupDisasters();

	// Next, we'll setup the in-game music
	SongIds X01Songs[] = { songStatic01, songEden21, songStatic05, songPlymth11, songEden21, songEden22 };
	TethysGame::SetMusicPlayList(6, 2, X01Songs);

	// Determine AI player number.
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		if (!Player[i].IsHuman() && numAI < 0)
		{
			numAI = i;
		}
	}

	// Automatically ally all human players with one another.
	for (int i = 0; i < numAI; i++)
	{
		for (int j = 0; j < numAI; j++)
		{
			if (i != j)
				Player[i].AllyWith(j);
		}
	}

	// Setup AI and attack waves
	SetupAI();
	CreateTimeTrigger(1, 1, 1900, "Scout");
	CreateTimeTrigger(1, 1, 4400, "Attack1");
	CreateTimeTrigger(1, 1, 8600, "Attack2");
	CreateTimeTrigger(1, 1, 13060, "Attack3");
	CreateTimeTrigger(1, 1, 17300, "Attack4");
	CreateTimeTrigger(1, 1, 21010, "Attack5");
}

void SetupInitRes(int pNo)
{
	Player[pNo].SetTechLevel(2);
	Player[pNo].MarkResearchComplete(3000);

	switch (Player[pNo].Difficulty())
	{
	case 0:
		Player[pNo].SetKids(25);
		Player[pNo].SetWorkers(21);
		Player[pNo].SetScientists(14);
		Player[pNo].SetFoodStored(1800);
		Player[pNo].SetOre(2000);
		Player[pNo].MarkResearchComplete(3401);   // Cybernetic Teleoperation
		Player[pNo].MarkResearchComplete(3407);   // Large-Scale Optical Resonators
		Player[pNo].MarkResearchComplete(3408);   // Focused Microwave Projection
		break;

	case 1:
		Player[pNo].SetKids(23);
		Player[pNo].SetWorkers(19);
		Player[pNo].SetScientists(13);
		Player[pNo].SetFoodStored(1100);
		Player[pNo].SetOre(1200);
		Player[pNo].MarkResearchComplete(3407);   // Large-Scale Optical Resonators
		Player[pNo].MarkResearchComplete(3408);   // Focused Microwave Projection
		break;

	case 2:
		Player[pNo].SetKids(22);
		Player[pNo].SetWorkers(18);
		Player[pNo].SetScientists(12);
		Player[pNo].SetFoodStored(700);
		Player[pNo].SetOre(800);
		Player[pNo].MarkResearchComplete(3407);   // Large-Scale Optical Resonators
		Player[pNo].MarkResearchComplete(3408);   // Focused Microwave Projection
		break;
	}
}

void SetupDisasters()
{
	DC.SetMapSize(64, 128);
	DC.SetMinimumWait(2800);
	DC.SetIgnoreChance(0);
	DC.EnableDisaster(disQuake);
	DC.SetDisasterTypeWeight(disQuake, 80);
	DC.SetDisasterTypeWeight(disNone, 20);
	DC.SetDisasterPowerWeight(pwrLow, 100);
	DC.AddDisasterZone(disQuake, MAP_RECT(4+31, 2-1, 60+31, 116-1));
	DC.SetDisasterTargetWeight(trgZone, 100);

	DC.DefineVolcano(LOCATION(12 + 31, 10 - 1), 1, 19000, volSouthEast, spdFast);
	DC.DefineVolcano(LOCATION(9 + 31, 12 - 1), 1, 49000, volSouth, spdFast);
	DC.SetLavaTiles();

	CreateTimeTrigger(1, 1, 1, "DisasterCreator_Callback");		// Called at mission start to initialize volcano graphics
	DC.SetCallbackTrigger("DisasterCreator_Callback", 200);
}

Export void DisasterCreator_Callback()
{
	DC.RollRandom();
	DC.CheckVolcanoes();
}