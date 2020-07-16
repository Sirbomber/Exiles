#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "functions.h"

int aiNum;
Unit CC, SF1, SF2, Smelter1, Smelter2, Mine, VF1, VF2, VF3, ALab, /*MedCenter, ARes,*/ ET, Tok1, Tok2, Garage;
Trigger NoScouts,
		NoETs,
        ScannedCC,
		//ScannedAdvRes,
		//ScannedMedCenter,
		ScannedLab,
		DestroyedLab,
		DestroyedCC,
		//DestroyedMC,
		//DestroyedAR,
		DestroyedTok1,
		DestroyedTok2,
		AttackedNW,
		MoveSE,
		MovePatrol,
		AttackedSE,
		Trap;

bool FlagSE,
     FlagPatrol,
     Hostile;

FightGroup NW, SW, SE1, SE2, Lab, Etc, I1, I2, Patrol1, Patrol2, Temp, Plymz;
MiningGroup C1, C2;
BuildingGroup S1, S2, V1, V2, V3;

void DoGameSetup()
{
	// Permanent darkness on this one.
    TethysGame::SetDaylightEverywhere(0);
	TethysGame::SetDaylightMoves(0);
	GameMap::SetInitialLightLevel(-32);

	// Next, we'll setup the in-game music
	SongIds X02Songs[] = { songEP51, songEP52, songEP41, songEden11 };
	TethysGame::SetMusicPlayList(4, 0, X02Songs);

	DestroyedTok1 = CreateTimeTrigger(1, 0, 10, "Tok1_Destroyed");
	DestroyedTok2 = CreateTimeTrigger(1, 0, 10, "Tok2_Destroyed");
	Hostile = false;
}

void SetupVictory()
{
	Trigger trig;

	// Victory conditions
	//trig = CreateSpecialTarget(1, 0, ARes, mapScout, "Scanned_ARes");
	//CreateVictoryCondition(1, 0, trig, "Plant spies at the Advanced Residence.");

	//trig = CreateSpecialTarget(1, 0, MedCenter, mapScout, "Scanned_MedCenter");
	//CreateVictoryCondition(1, 0, trig, "Plant spies at the Medical Center.");

	NoScouts = CreateCountTrigger(1, 0, -1, mapScout, mapAny, 0, cmpEqual, "None");
	CreateFailureCondition(1, 0, NoScouts, "");

	NoETs = CreateCountTrigger(1, 0, -1, mapEvacuationTransport, mapAny, 0, cmpEqual, "None");
	CreateFailureCondition(1, 0, NoETs, "");

	trig = CreateSpecialTarget(1, 0, CC, mapScout, "Scanned_CC");
	CreateVictoryCondition(1, 0, trig, "Plant spies at the Command Center.");

	ScannedLab = CreateSpecialTarget(1, 1, ALab, mapEvacuationTransport, "GotScientists");
	//CreateVictoryCondition(1, 0, ScannedLab, "Retrieve our captive scientists from the Advanced Lab.");
	trig = CreateEscapeTrigger(1, 0, -1, 1+31, 53-1, 17, 10, 1, mapEvacuationTransport, mapInterColonyShuttle, 1, "None");
	CreateVictoryCondition(1, 0, trig, "Return the captive scientists to the convoy starting location.");

	// Failure conditions
	DestroyedLab = CreateTimeTrigger(1, 0, 10, "CheckAdvLab1");
	DestroyedCC = CreateTimeTrigger(1, 0, 10, "CheckCC");
	//DestroyedMC = CreateTimeTrigger(1, 0, 10, "CheckMC");
	//DestroyedAR = CreateTimeTrigger(1, 0, 10, "CheckAR");

}

void SetupMiscObjects()
{
	Unit Unit1;
	TethysGame::PlaceMarker(Unit1, 12+31, 59-1, Circle);
}

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
	Unit Unit1;
	map_id weapon = mapMicrowave;
	if (Player[pNo].IsEden())
	{
		weapon = mapLaser;
	}

	Player[pNo].CenterViewOn(6+31, 55-1);

	// Give the player some free upgrades based on difficulty level.
	// These will not transfer to the next level.
	switch (Player[pNo].Difficulty())
	{
		case 0:
			Player[pNo].MarkResearchComplete(4002);		// Weapon damage upgrade
		case 1:
			Player[pNo].MarkResearchComplete(4001);		// Lynx speed upgrade
		case 2:
			Player[pNo].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant (just in case you didn't already get it)
			break;
	}

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(4+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(5+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(10+31, 54-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(2+31, 55-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3+31, 57-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(3+31, 53-1), pNo, mapNone, 0);
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

	Player[pNo].CenterViewOn(14+31, 57-1);

	// Give the player some free upgrades based on difficulty level.
	// These will not transfer to the next level.
	switch (Player[pNo].Difficulty())
	{
		case 0:
			Player[pNo].MarkResearchComplete(4002);		// Weapon damage upgrade
		case 1:
			Player[pNo].MarkResearchComplete(4001);		// Lynx speed upgrade
		case 2:
			Player[pNo].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant (just in case you didn't already get it)
			break;
	}

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 57-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 59-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15+31, 58-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(17+31, 57-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(11+31, 56-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(11+31, 58-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(10+31, 57-1), pNo, mapNone, 0);
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

	Player[pNo].CenterViewOn(7+31, 61-1);

	// Give the player some free upgrades based on difficulty level.
	// These will not transfer to the next level.
	switch (Player[pNo].Difficulty())
	{
		case 0:
			Player[pNo].MarkResearchComplete(4002);		// Weapon damage upgrade
		case 1:
			Player[pNo].MarkResearchComplete(4001);		// Lynx speed upgrade
		case 2:
			Player[pNo].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant (just in case you didn't already get it)
			break;
	}

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 59-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 60-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8+31, 61-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(9+31, 62-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 62-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 62-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 61-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3+31, 60-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3+31, 61-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(3+31, 62-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(2+31, 59-1), pNo, mapNone, 0);
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

	Player[pNo].CenterViewOn(18+31, 56-1);

	// Give the player some free upgrades based on difficulty level.
	// These will not transfer to the next level.
	switch (Player[pNo].Difficulty())
	{
		case 0:
			Player[pNo].MarkResearchComplete(4002);		// Weapon damage upgrade
		case 1:
			Player[pNo].MarkResearchComplete(4001);		// Lynx speed upgrade
		case 2:
			Player[pNo].MarkResearchComplete(3901);		// Advanced Vehicle Power Plant (just in case you didn't already get it)
			break;
	}

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(24+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(22+31, 57-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20+31, 55-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20+31, 56-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(20+31, 57-1), pNo, weapon, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(24+31, 58-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(22+31, 59-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapScout, LOCATION(20+31, 59-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapEvacuationTransport, LOCATION(18+31, 58-1), pNo, mapNone, 0);
		Unit1.DoSetLights(1);
}

void SetupBaseAI(int pAI)
{
	aiNum = pAI;
	SetupGroups(pAI);

	// Upgrades
	//Player[pAI].SetTechLevel(3);
	Player[pAI].MarkResearchComplete(8304);
	Player[pAI].SetOre(21000);
	Player[pAI].SetRareOre(2000);

	Unit Unit1;
	TethysGame::CreateBeacon(mapMiningBeacon, 109+31, 46-1, 0, 0, -1);

	// Structures
	TethysGame::CreateUnit(CC, mapCommandCenter, LOCATION(88+31, 25-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(ALab, mapAdvancedLab, LOCATION(99+31, 6-1), pAI, mapNone, 0);

	TethysGame::CreateUnit(SF1, mapStructureFactory, LOCATION(91+31, 33-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(SF2, mapStructureFactory, LOCATION(68+31, 14-1), pAI, mapNone, 0);

	TethysGame::CreateUnit(Mine, mapCommonOreMine, LOCATION(109+31, 46-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Smelter1, mapCommonOreSmelter, LOCATION(108+31, 40-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Smelter2, mapCommonOreSmelter, LOCATION(99+31, 43-1), pAI, mapNone, 0);

	TethysGame::CreateUnit(VF1, mapVehicleFactory, LOCATION(107+31, 16-1), pAI, mapNone, 0);
		V1.TakeUnit(VF1);
	TethysGame::CreateUnit(VF2, mapVehicleFactory, LOCATION(107+31, 22-1), pAI, mapNone, 0);
		V2.TakeUnit(VF2);
	TethysGame::CreateUnit(VF3, mapVehicleFactory, LOCATION(67+31, 26-1), pAI, mapNone, 0);
		V3.TakeUnit(VF3);

	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(98+31, 29-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapRobotCommand, LOCATION(98+31, 21-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(89+31, 19-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(84+31, 15-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(/*MedCenter,*/Unit1, mapMedicalCenter, LOCATION(107+31, 30-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(78+31, 22-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(76+31, 27-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(/*ARes,*/Unit1, mapAdvancedResidence, LOCATION(77+31, 17-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(65+31, 20-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(61+31, 9-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(102+31, 34-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGORF, LOCATION(79+31, 32-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapDIRT, LOCATION(102+31, 39-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonStorage, LOCATION(112+31, 19-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapRareStorage, LOCATION(102+31, 16-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(84+31, 39-1), pAI, mapNone, 0);

	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(123+31, 5-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(118+31, 3-1), pAI, mapNone, 0);
	//TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(61+31, 3-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(81+31, 7-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Tok1, mapTokamak, LOCATION(16+31, 9-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Tok2, mapTokamak, LOCATION(86+31, 51-1), pAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGeothermalPlant, LOCATION(125+31, 44-1), pAI, mapNone, 0);


	// Guard Posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(101+31, 10-1), pAI, mapEMP, 0);
		Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(97+31, 10-1), pAI, mapRailGun, 0);
		Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(100+31, 3-1), pAI, mapEMP, 0);
		Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(95+31, 9-1), pAI, mapEMP, 0);
		Lab.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(96+31, 6-1), pAI, mapRailGun, 0);
		Lab.TakeUnit(Unit1);

		TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(57+31, 6-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(50+31, 13-1), pAI, mapLaser, 0);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(46+31, 17-1), pAI, mapLaser, 0);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(44+31, 19-1), pAI, mapLaser, 0);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(39+31, 22-1), pAI, mapLaser, 0);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(45+31, 49-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(47+31, 52-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(105+31, 52-1), pAI, mapLaser, 0);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(115+31, 54-1), pAI, mapLaser, 0);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(113+31, 52-1), pAI, mapLaser, 0);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(111+31, 40-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(100+31, 40-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(95+31, 29-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(85+31, 25-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(92+31, 23-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(105+31, 27-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(110+31, 22-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(105+31, 19-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(86+31, 18-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(66+31, 17-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(65+31, 11-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(63+31, 26-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(67+31, 29-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(74+31, 31-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(84+31, 41-1), pAI, mapLaser, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(98+31, 18-1), pAI, mapLaser, 0);	

	// Units
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(110+31, 42-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(111+31, 42-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(112+31, 42-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(102+31, 45-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(102+31, 46-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(102+31, 47-1), pAI, mapNone, 0);
		Unit1.DoSetLights(1);
		C2.TakeUnit(Unit1);
	
	//TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(93+31, 36-1), pAI, mapNone, 0);
	//	Unit1.DoSetLights(1);
	//TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(94+31, 35-1), pAI, mapNone, 0);
	//	Unit1.DoSetLights(1);
	//TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(95+31, 35-1), pAI, mapNone, 0);
	//	Unit1.DoSetLights(1);
	//TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(73+31, 15-1), pAI, mapNone, 0);
	//	Unit1.DoSetLights(1);
	//TethysGame::CreateUnit(Unit1, mapConVec, LOCATION(72+31, 17-1), pAI, mapNone, 0);
	//	Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53+31, 15-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52+31, 16-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49+31, 20-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50+31, 20-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		NW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(104+31, 50-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105+31, 49-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(106+31, 50-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		SE1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(49+31, 49-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		SW.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(50+31, 51-1), pAI, mapLaser, 0);
		Unit1.DoSetLights(1);
		SW.TakeUnit(Unit1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(57+31, 21-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58+31, 21-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(59+31, 21-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(60+31, 21-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58+31, 22-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I1.TakeUnit(Unit1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(85+31, 22-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(90+31, 23-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(91+31, 27-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(90+31, 21-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(88+31, 28-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(93+31, 26-1), pAI, mapLaser,0);
		Unit1.DoSetLights(1);
		I2.TakeUnit(Unit1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(103+31, 7-1), pAI, mapRailGun, 0);
		Lab.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(105+31, 8-1), pAI, mapRailGun, 0);
		Lab.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(104+31, 5-1), pAI, mapEMP, 0);
		Lab.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(106+31, 6-1), pAI, mapEMP, 0);
		Lab.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(107+31, 9-1), pAI, mapRailGun, 0);
		Lab.TakeUnit(Unit1);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(97+31, 31-1), pAI, mapLaser, 2);
		Patrol1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(99+31, 32-1), pAI, mapLaser, 2);
		Patrol1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(96+31, 35-1), pAI, mapLaser, 2);
		Patrol1.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(101+31, 36-1), pAI, mapLaser, 2);
		Patrol1.TakeUnit(Unit1);

	// Tubes
	TethysGame::CreateWallOrTube(97+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 10-1, 0, mapTube);
	TethysGame::CreateWallOrTube(100+31, 10-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 11-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 12-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 13-1, 0, mapTube);
	TethysGame::CreateWallOrTube(91+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(92+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(93+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(95+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(96+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(97+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 23-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(100+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(101+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(103+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(104+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 18-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(100+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(101+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(103+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(104+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(86+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 21-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 23-1, 0, mapTube);
	TethysGame::CreateWallOrTube(92+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(93+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(95+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(96+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(97+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(101+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(103+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(104+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(105+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 28-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(78+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(78+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(78+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(78+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(79+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(80+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(81+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(82+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(83+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(85+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(86+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 27-1, 0, mapTube);
	TethysGame::CreateWallOrTube(81+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(82+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(83+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(85+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(86+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(83+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(82+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(81+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(80+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(77+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(68+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(68+31, 18-1, 0, mapTube);
	TethysGame::CreateWallOrTube(68+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(68+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(69+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(70+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(71+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(72+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(73+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(74+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(75+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(71+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(72+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(73+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(74+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(75+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 14-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 15-1, 0, mapTube);
	TethysGame::CreateWallOrTube(64+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(65+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(66+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(67+31, 9-1, 0, mapTube);
	TethysGame::CreateWallOrTube(67+31, 10-1, 0, mapTube);
	TethysGame::CreateWallOrTube(67+31, 11-1, 0, mapTube);
	TethysGame::CreateWallOrTube(67+31, 12-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 28-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 30-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 31-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(95+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(96+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(97+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(100+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(98+31, 31-1, 0, mapTube);
	TethysGame::CreateWallOrTube(105+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(106+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 33-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 29-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 30-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 31-1, 0, mapTube);
	TethysGame::CreateWallOrTube(77+31, 31-1, 0, mapTube);
	TethysGame::CreateWallOrTube(82+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(83+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(85+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(86+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 32-1, 0, mapTube);
	TethysGame::CreateWallOrTube(79+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(80+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(81+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(82+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(83+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(85+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(86+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 34-1, 0, mapTube);
	TethysGame::CreateWallOrTube(65+31, 22-1, 0, mapTube);
	TethysGame::CreateWallOrTube(65+31, 23-1, 0, mapTube);
	TethysGame::CreateWallOrTube(65+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(70+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(71+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(72+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(73+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(74+31, 26-1, 0, mapTube);
	TethysGame::CreateWallOrTube(110+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(111+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(112+31, 16-1, 0, mapTube);
	TethysGame::CreateWallOrTube(112+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 20-1, 0, mapTube);
	TethysGame::CreateWallOrTube(108+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(109+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(110+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(111+31, 19-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 36-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 37-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 35-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 36-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 37-1, 0, mapTube);
	TethysGame::CreateWallOrTube(107+31, 38-1, 0, mapTube);
	TethysGame::CreateWallOrTube(105+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 41-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 42-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 43-1, 0, mapTube);
	TethysGame::CreateWallOrTube(91+31, 36-1, 0, mapTube);
	TethysGame::CreateWallOrTube(91+31, 37-1, 0, mapTube);
	TethysGame::CreateWallOrTube(91+31, 38-1, 0, mapTube);
	TethysGame::CreateWallOrTube(91+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(92+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(93+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 40-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 41-1, 0, mapTube);
	TethysGame::CreateWallOrTube(94+31, 42-1, 0, mapTube);
	TethysGame::CreateWallOrTube(95+31, 42-1, 0, mapTube);
	TethysGame::CreateWallOrTube(96+31, 42-1, 0, mapTube);
	TethysGame::CreateWallOrTube(90+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(89+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(88+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(87+31, 39-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 35-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 36-1, 0, mapTube);
	TethysGame::CreateWallOrTube(84+31, 37-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 17-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 1-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 2-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 3-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 4-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 5-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 6-1, 0, mapTube);
	TethysGame::CreateWallOrTube(62+31, 7-1, 0, mapTube);
	TethysGame::CreateWallOrTube(99+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(100+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(101+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(102+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(103+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(104+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(105+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(106+31, 25-1, 0, mapTube);
	TethysGame::CreateWallOrTube(68+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(69+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(70+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(71+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(72+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(73+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(74+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(75+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(76+31, 24-1, 0, mapTube);
	TethysGame::CreateWallOrTube(77+31, 24-1, 0, mapTube);

	// Walls
	TethysGame::CreateWallOrTube(101+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(100+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(98+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(97+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(96+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(96+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(95+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(94+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 9-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 8-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(93+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(89+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(90+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(91+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(92+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(43+31, 48-1, 0, mapWall);
	TethysGame::CreateWallOrTube(43+31, 49-1, 0, mapWall);
	TethysGame::CreateWallOrTube(45+31, 52-1, 0, mapWall);
	TethysGame::CreateWallOrTube(45+31, 51-1, 0, mapWall);
	TethysGame::CreateWallOrTube(118+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(117+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(116+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(115+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(114+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(113+31, 56-1, 0, mapWall);
	TethysGame::CreateWallOrTube(113+31, 55-1, 0, mapWall);
	TethysGame::CreateWallOrTube(113+31, 54-1, 0, mapWall);
	TethysGame::CreateWallOrTube(100+31, 52-1, 0, mapWall);
	TethysGame::CreateWallOrTube(101+31, 52-1, 0, mapWall);
	TethysGame::CreateWallOrTube(102+31, 52-1, 0, mapWall);
	TethysGame::CreateWallOrTube(102+31, 53-1, 0, mapWall);
	TethysGame::CreateWallOrTube(103+31, 53-1, 0, mapWall);
	TethysGame::CreateWallOrTube(103+31, 54-1, 0, mapWall);
	TethysGame::CreateWallOrTube(104+31, 54-1, 0, mapWall);
	TethysGame::CreateWallOrTube(105+31, 54-1, 0, mapWall);
	TethysGame::CreateWallOrTube(106+31, 54-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 1-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 2-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 3-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 4-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 8-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 7-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 9-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 10-1, 0, mapWall);
	TethysGame::CreateWallOrTube(51+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(114+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(115+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(116+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(117+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(118+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(119+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(120+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(117+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(122+31, 7-1, 0, mapWall);
	TethysGame::CreateWallOrTube(122+31, 8-1, 0, mapWall);
	TethysGame::CreateWallOrTube(85+31, 9-1, 0, mapWall);
	TethysGame::CreateWallOrTube(85+31, 8-1, 0, mapWall);
	TethysGame::CreateWallOrTube(85+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(84+31, 6-1, 0, mapWall);
	TethysGame::CreateWallOrTube(84+31, 5-1, 0, mapWall);
	/*
	TethysGame::CreateWallOrTube(64+31, 4-1, 0, mapWall);
	TethysGame::CreateWallOrTube(63+31, 4-1, 0, mapWall);
	TethysGame::CreateWallOrTube(63+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(62+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(61+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(60+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(59+31, 5-1, 0, mapWall);
	TethysGame::CreateWallOrTube(58+31, 4-1, 0, mapWall);
	TethysGame::CreateWallOrTube(58+31, 3-1, 0, mapWall);
	TethysGame::CreateWallOrTube(58+31, 2-1, 0, mapWall);
	TethysGame::CreateWallOrTube(58+31, 1-1, 0, mapWall);
	*/
	TethysGame::CreateWallOrTube(37+31, 23-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 22-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 21-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 20-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 19-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 18-1, 0, mapWall);
	TethysGame::CreateWallOrTube(37+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(38+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(39+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(40+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(41+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(42+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(43+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(44+31, 17-1, 0, mapWall);
	TethysGame::CreateWallOrTube(44+31, 16-1, 0, mapWall);
	TethysGame::CreateWallOrTube(44+31, 15-1, 0, mapWall);
	TethysGame::CreateWallOrTube(50+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(49+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(48+31, 11-1, 0, mapWall);
	TethysGame::CreateWallOrTube(48+31, 12-1, 0, mapWall);
	TethysGame::CreateWallOrTube(48+31, 13-1, 0, mapWall);

	// Finalize groups
	C1.Setup(Mine, Smelter1, MAP_RECT(103+31, 40-1, 110+31, 47-1));
	C2.Setup(Mine, Smelter2, MAP_RECT(99+31, 43-1, 110+31, 47-1));
}
// *********************
//  Trigger responses
// *********************

SCRIPT_API void GotScientists()
{
	GetSpecialTargetData(ScannedLab, ET);
	ET.SetCargo(mapInterColonyShuttle, mapNone);

	TethysGame::AddMessage(-1, -1, "Scientists have been retrieved.", -1, sndBeep8);
	DestroyedLab.Destroy();
	NoETs.Disable();

	Trigger trig;

	// Create new objective to destroy the advanced lab.
	trig = CreateCountTrigger(1, 0, aiNum, mapAdvancedLab, mapNone, 0, cmpEqual, "None");
	CreateVictoryCondition(1, 0, trig, "Destroy the Advanced Lab.");
	TethysGame::AddMessage(-1, -1, "Eden is now aware of your presence, commanders.  Destroy that lab and get our people out of there!", -1, sndSavant30);

	// Add a check - if the ET holding the scientists is destroyed, it's game over.
	trig = CreateTimeTrigger(1, 0, 10, "CheckET");

	// Set all Eden forces to hostile.
	GoHostile();

	// Transfer any disabled GPs back to the AI and disable the destroyed Tokamak checks.
	if (Tok1.IsLive())
	{
		DestroyedTok1.Destroy();
	}

	if (Tok2.IsLive())
	{
		DestroyedTok2.Destroy();
	}

	Unit Unit1;
	map_id weapon;
	PlayerBuildingEnum GPs(aiNum+1, mapGuardPost);
	while (GPs.GetNext(Unit1))
	{
		Unit1.DoTransfer(aiNum);
	}

	// Create player reinforcements.
	for (int i = 0; i < aiNum; i++)
	{
		if (Player[i].IsEden())
		{
			weapon = mapLaser;
		}
		else
		{
			weapon = mapMicrowave;
		}

		switch (Player[i].Difficulty())
		{
			default:
			case 0:
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(6+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
			case 1:
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(5+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(4+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
			case 2:
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(3+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
				TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(1+31, 63-1-i), i, weapon, 0);
					Unit1.DoSetLights(1);
				break;
		}
	}

	TethysGame::AddMessage(6*32, 60*32, "Reinforcements ready.", -1, sndSavnt205);

	// Setup a surprise.
	Trap = CreateTimeTrigger(1, 0, 10, "SurpriseAttack");

	// Make the third VF start pumping out lynx.
	V3.RecordVehReinforceGroup(Etc, 10000);

	// Clear the lab's special target data.
	ALab.ClearSpecialTarget();
}

SCRIPT_API void Scanned_CC()
{
	CC.ClearSpecialTarget();
	NoScouts.Disable();
	//TethysGame::AddMessage(-1, -1, "Spies have infiltrated Eden via the Commander Center.", -1, sndBeep8);
	TethysGame::AddMessage(-1, -1, "Our spies have successfully infiltrated Eden.", -1, sndBeep8);
}

SCRIPT_API void SurpriseAttack()
{
	int x = ET.Location().x,
		y = ET.Location().y;

	if (x >= 34+31 && x <= 44+31 && y >= 1-1 && y <= 23-1)
	{
	
		Unit Unit1;
		for (int x = 53; x < 61; x++)
		{
			TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 1-1), aiNum, mapLaser, 2);
				Unit1.DoSetLights(1);
				Etc.TakeUnit(Unit1);
		}
		//Etc.SetTargetUnit(ET);
		//Etc.DoAttackUnit();
		Etc.DoAttackEnemy();

		Trap.Destroy();
	}

}

// *********************
//  AI setup and actions
// *********************

void SetupGroups (int pAI)
{
	NW = CreateFightGroup(pAI);
	NW.SetRect(MAP_RECT(48+31,14-1, 53+31, 21-1));
	NW.AddGuardedRect(MAP_RECT(47+31,15-1, 55+31, 20-1));
	NW.AddGuardedRect(MAP_RECT(38+31,18-1, 46+31, 24-1));

	SW = CreateFightGroup(pAI);
	SW.SetRect(MAP_RECT(50+31, 49-1, 52+31, 51-1));

	SE1 = CreateFightGroup(pAI);
	SE1.SetRect(MAP_RECT(101+31, 46-1, 104+31, 49-1));
	SE2 = CreateFightGroup(pAI);
	SE2.SetRect(MAP_RECT(114+31, 50-1, 117+31, 53-1));
	MoveSE = CreateTimeTrigger(1, 0, 600, 1100, "SE_Relocate");
	FlagSE = false;

	Lab = CreateFightGroup(pAI);
	Lab.SetRect(MAP_RECT(102+31, 5-1, 107+31, 9-1));
	Lab.AddGuardedRect(MAP_RECT(92+31, 4-1, 104+31, 11-1));

	I1 = CreateFightGroup(pAI);
	I1.SetRect(MAP_RECT(57+31, 20-1, 61+31, 22-1));

	I2 = CreateFightGroup(pAI);
	I2.SetRect(MAP_RECT(84+31, 21-1, 94+31, 28-1));

	Patrol1 = CreateFightGroup(pAI);
	Patrol1.SetRect(MAP_RECT(90+31, 41-1, 93+31, 46-1));
	Patrol2 = CreateFightGroup(pAI);
	Patrol2.SetRect(MAP_RECT(70+31, 16-1, 75+31, 22-1));
	MovePatrol = CreateTimeTrigger(1, 0, 1200, 1600, "Patrol_Relocate");
	FlagPatrol = false;

	Etc = CreateFightGroup(pAI);
	Etc.SetRect(MAP_RECT(128+31, 17-1, 129+31, 25-1));
	Etc.SetTargCount(mapLynx, mapLaser, 22);
	CreateTimeTrigger(1, 0, 10, "PoofLynx");

	C1 = CreateMiningGroup(pAI);
	C1.SetTargCount(mapCargoTruck, mapAny, 3);
	C2 = CreateMiningGroup(pAI);
	C2.SetTargCount(mapCargoTruck, mapAny, 3);

	S1 = CreateBuildingGroup(pAI);
	S2 = CreateBuildingGroup(pAI);
	V1 = CreateBuildingGroup(pAI);
	V1.RecordVehReinforceGroup(Etc, 9999);
	V2 = CreateBuildingGroup(pAI);
	V2.RecordVehReinforceGroup(Etc, 2000);
	V3 = CreateBuildingGroup(pAI);

	// If at least one player is playing on hard, strictly enforce the stealth mechanic.
	for (int i = 0; i < pAI; i++)
	{
		if (Player[i].Difficulty() == 2)
		{
			AttackedNW = CreateTimeTrigger(1, 0, 10, "CheckAttacked");
			break;
		}
	}
}

SCRIPT_API void CheckAttacked()
{
	if (NW.HasBeenAttacked() ||
		SW.HasBeenAttacked() ||
		SE1.HasBeenAttacked() ||
		SE2.HasBeenAttacked() ||
		I1.HasBeenAttacked() ||
		I2.HasBeenAttacked() ||
		Patrol1.HasBeenAttacked() ||
		Patrol2.HasBeenAttacked() ||
		Etc.HasBeenAttacked() )
	{
		GoHostile();
	}
}

void GoHostile()
{
	if (!Hostile)
	{
		NW.DoAttackEnemy();
		SW.DoAttackEnemy();
		SE1.DoAttackEnemy();
		SE2.DoAttackEnemy();
		Etc.DoAttackEnemy();
		I1.DoAttackEnemy();
		I2.DoAttackEnemy();
		//Lab.DoAttackEnemy();

		MoveSE.Destroy();
		if (AttackedNW.IsInitialized())
		{
			AttackedNW.Destroy();
		}
		Hostile = true;
	}
}

SCRIPT_API void PoofLynx()
{
	UnitEx Unit1;
	InRectEnumerator AtEdge(MAP_RECT(128+31, 17-1, 129+31, 25-1));
	while (AtEdge.GetNext(Unit1))
	{
		if (Unit1.OwnerID() == aiNum)
		{
			Unit1.DoPoof();
		}
	}
}

SCRIPT_API void SE_Relocate()
{
	if (FlagSE)
	{
		//SE.SetRect(MAP_RECT(101+31, 46-1, 103+31, 49-1));
		SE1.TakeAllUnits(SE2);
	}
	else
	{
		//SE.SetRect(MAP_RECT(114+31, 50-1, 117+31, 53-1));
		SE2.TakeAllUnits(SE1);
	}
	FlagSE = !FlagSE;
}

SCRIPT_API void Patrol_Relocate()
{
	if (FlagPatrol)
	{
		Patrol1.TakeAllUnits(Patrol2);
	}
	else
	{
		Patrol2.TakeAllUnits(Patrol1);
	}
	FlagPatrol = !FlagPatrol;
}

// *********************
//  Death checks
// *********************

SCRIPT_API void CheckET()
{
	if (!ET.IsLive())
	{
		CreateFailureCondition(1, 0, DestroyedCC, ".");
	}
}

SCRIPT_API void CheckAdvLab1()
{
	if (!ALab.IsLive())
	{
		CreateFailureCondition(1, 0, DestroyedLab, ".");
	}
}

SCRIPT_API void CheckCC()
{
	if (!CC.IsLive() || !SF1.IsLive() || !SF2.IsLive() ||
		!VF1.IsLive() || !VF2.IsLive() || !VF3.IsLive() ||
		!Smelter1.IsLive() || !Smelter2.IsLive())
	{
		CreateFailureCondition(1, 0, DestroyedCC, ".");
	}
}

/*
SCRIPT_API void LabDestroyed()
{
	TethysGame::SetDaylightMoves(1);
	GameMap::SetVirusUL(LOCATION(99+31, 6-1), 1100);
	GameMap::SetVirusUL(LOCATION(100+31, 6-1), 1100);
	GameMap::SetVirusUL(LOCATION(99+31, 5-1), 1100);
	TethysGame::SetMicrobeSpreadSpeed(1100);
	TethysGameEx::ResetCheatedGame();
}
*/

SCRIPT_API void Tok1_Destroyed()
{
	if (!Tok1.IsLive())
	{
		Unit GP;
		InRectEnumerator TopLeftGPs(MAP_RECT(35+31, 5-1, 81+31, 32-1));
		while (TopLeftGPs.GetNext(GP))
		{
			if (GP.GetType() == mapGuardPost && GP.GetWeapon() == mapLaser)
			{
				GP.DoTransfer(aiNum+1);
			}
		}
		DestroyedTok1.Destroy();
		Temp = CreateFightGroup(aiNum);
		Temp.TakeAllUnits(I1);
		I1.Destroy();
		I1 = CreateFightGroup(aiNum);
		I1.SetRect(MAP_RECT(12+31, 3-1, 21+31, 18-1));
		I1.TakeAllUnits(Temp);
		Temp.Destroy();
	}
}

SCRIPT_API void Tok2_Destroyed()
{
	if (!Tok2.IsLive())
	{
		Unit GP;
		InRectEnumerator OtherGPs(MAP_RECT(84+31, 15-1, 119+31, 59-1));
		while (OtherGPs.GetNext(GP))
		{
			if (GP.GetType() == mapGuardPost && GP.GetWeapon() == mapLaser
				&& GP.Location().x != 85+31)
			{
				GP.DoTransfer(aiNum+1);
			}
		}
		DestroyedTok2.Destroy();
		Temp = CreateFightGroup(aiNum);
		Temp.TakeAllUnits(I2);
		I2.Destroy();
		I2 = CreateFightGroup(aiNum);
		I2.SetRect(MAP_RECT(81+31, 47-1, 88+31, 53-1));
		I2.TakeAllUnits(Temp);
		Temp.Destroy();
	}
}