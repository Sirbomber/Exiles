#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "AI.h"

// AI data
extern int numEden;
extern int numPlym;

void SetupAI()
{
	// AI setup/tech bonus
	Player[numEden].GoEden();
	Player[numEden].SetTechLevel(9);
	Player[numPlym].GoPlymouth();
	Player[numPlym].SetTechLevel(9);
	

	// Setup initial AI base (which just gets destroyed)
	SetupAiBase();

}

void SetupAiBase()
{
	// Randomized Base code.
	int i[4] = { 0, 1, 2, 3 };
	RandomizeList(autosize(i));

	SetupAiBase1();
	SetupAiBase2();
	SetupAiBase3();

	// Randomly create bases based on # of human players.  These bases will be given out randomly once the capture phase of the mission is over.
	/*
	if (Player[i[0]].IsHuman())
	{
		SetupAiBase1();
	}

	if (Player[i[1]].IsHuman())
	{
		SetupAiBase2();
	}

	if (Player[i[2]].IsHuman())
	{
		SetupAiBase3(i[2]);
	}

	if (Player[i[3]].IsHuman())
	{
		SetupAiBase4(i[3]);
	}
	*/
	
}

void SetupAiBase1()
{
	UnitEx Unit1;

	// Beacons
	TethysGame::CreateBeacon(mapMiningBeacon, 44 + 31, 42 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 30 + 31, 67 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 35 + 31, 31 - 1, 1, 1, 0);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(44 + 31, 57 - 1), numEden, mapNone, 0);
	Trigger trig = CreateSpecialTarget(1, 1, Unit1, mapEvacuationTransport, "CapturedCC");
	CreateVictoryCondition(1, 1, trig, "Infiltrate the Command Center at (44, 57).");
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(38 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(47 + 31, 50 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(43 + 31, 50 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapRareStorage, LOCATION(34 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(32 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(32 + 31, 56 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(37 + 31, 47 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(40 + 31, 39 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(44 + 31, 42 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(45 + 31, 62 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(29 + 31, 43 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(45 + 31, 65 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(48 + 31, 65 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(37 + 31, 61 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(37 + 31, 65 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(37 + 31, 69 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(26 + 31, 64 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(30 + 31, 67 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(25 + 31, 37 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(22 + 31, 53 - 1), numEden, mapNone, 0);
	
	// Tubes
	CreateTubeOrWallLine(47 + 31, 53 - 1, 47 + 31, 57 - 1, mapTube);
	CreateTubeOrWallLine(44 + 31, 59 - 1, 44 + 31, 60 - 1, mapTube);
	CreateTubeOrWallLine(40 + 31, 61 - 1, 43 + 31, 61 - 1, mapTube);
	CreateTubeOrWallLine(29 + 31, 64 - 1, 35 + 31, 64 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 51 - 1, 39 + 31, 50 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 51 - 1, 39 + 31, 50 - 1, mapTube);
	CreateTubeOrWallLine(40 + 31, 50 - 1, 41 + 31, 50 - 1, mapTube);
	CreateTubeOrWallLine(40 + 31, 49 - 1, 40 + 31, 42 - 1, mapTube);
	CreateTubeOrWallLine(32 + 31, 43 - 1, 39 + 31, 43 - 1, mapTube);
	CreateTubeOrWallLine(32 + 31, 37 - 1, 32 + 31, 42 - 1, mapTube);
	TethysGame::CreateWallOrTube(37 + 31, 63 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(37 + 31, 67 - 1, 0, mapTube);
}

void SetupAiBase2()
{
	UnitEx Unit1;

	// Beacons
	TethysGame::CreateBeacon(mapMiningBeacon, 87 + 31, 46 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 92 + 31, 61 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 83 + 31, 76 - 1, 1, 1, 0);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(77 + 31, 59 - 1), numEden, mapNone, 0);
	Trigger trig = CreateSpecialTarget(1, 1, Unit1, mapEvacuationTransport, "CapturedCC");
	CreateVictoryCondition(1, 1, trig, "Infiltrate the Command Center at (77, 59).");
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(70 + 31, 58 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(60 + 31, 51 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(65 + 31, 62 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapRareStorage, LOCATION(63 + 31, 52 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(62 + 31, 62 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(78 + 31, 67 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(72 + 31, 47 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(83 + 31, 43 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(87 + 31, 46 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(81 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(61 + 31, 44 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(81 + 31, 64 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(78 + 31, 64 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(71 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(70 + 31, 62 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(76 + 31, 53 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(88 + 31, 58 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(92 + 31, 61 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(57 + 31, 39 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(90 + 31, 52 - 1), numEden, mapNone, 0);

	// Tubes
	CreateTubeOrWallLine(61 + 31, 47 - 1, 61 + 31, 50 - 1, mapTube);
	CreateTubeOrWallLine(65 + 31, 52 - 1, 69 + 31, 52 - 1, mapTube);
	CreateTubeOrWallLine(72 + 31, 49 - 1, 72 + 31, 51 - 1, mapTube);
	CreateTubeOrWallLine(83 + 31, 46 - 1, 83 + 31, 50 - 1, mapTube);
	CreateTubeOrWallLine(82 + 31, 50 - 1, 82 + 31, 51 - 1, mapTube);
	CreateTubeOrWallLine(80 + 31, 59 - 1, 85 + 31, 59 - 1, mapTube);
	CreateTubeOrWallLine(73 + 31, 58 - 1, 75 + 31, 58 - 1, mapTube);
	CreateTubeOrWallLine(77 + 31, 61 - 1, 77 + 31, 62 - 1, mapTube);
	CreateTubeOrWallLine(67 + 31, 62 - 1, 68 + 31, 62 - 1, mapTube);
	CreateTubeOrWallLine(76 + 31, 55 - 1, 77 + 31, 57 - 1, mapTube);
	TethysGame::CreateWallOrTube(74 + 31, 53 - 1, 0, mapTube);
	TethysGame::CreateWallOrTube(79 + 31, 53 - 1, 0, mapTube);
}

void SetupAiBase3()
{
	UnitEx Unit1;

	// Beacons
	TethysGame::CreateBeacon(mapMiningBeacon, 51 + 31, 94 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 28 + 31, 84 - 1, 0, 1, 0);
	TethysGame::CreateBeacon(mapMiningBeacon, 69 + 31, 81 - 1, 1, 1, 0);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(43 + 31, 85 - 1), numEden, mapNone, 0);
	Trigger trig = CreateSpecialTarget(1, 1, Unit1, mapEvacuationTransport, "CapturedCC");
	CreateVictoryCondition(1, 1, trig, "Infiltrate the Command Center at (43, 85).");
	TethysGame::CreateUnit(Unit1, mapStructureFactory, LOCATION(39 + 31, 76 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(59 + 31, 91 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(46 + 31, 102 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapRareStorage, LOCATION(37 + 31, 84 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapResidence, LOCATION(52 + 31, 102 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMedicalCenter, LOCATION(49 + 31, 102 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapGarage, LOCATION(47 + 31, 80 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(47 + 31, 91 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(51 + 31, 94 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapStandardLab, LOCATION(66 + 31, 92 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(36 + 31, 91 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapUniversity, LOCATION(70 + 31, 92 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapNursery, LOCATION(70 + 31, 89 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(50 + 31, 85 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(55 + 31, 85 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(66 + 31, 89 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreSmelter, LOCATION(24 + 31, 81 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapCommonOreMine, LOCATION(28 + 31, 84 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(51 + 31, 74 - 1), numEden, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapTokamak, LOCATION(66 + 31, 98 - 1), numEden, mapNone, 0);

	// Tubes
	CreateTubeOrWallLine(46 + 31, 85 - 1, 48 + 31, 85 - 1, mapTube);
	CreateTubeOrWallLine(46 + 31, 86 - 1, 46 + 31, 89 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 84 - 1, 41 + 31, 84 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 79 - 1, 39 + 31, 83 - 1, mapTube);
	CreateTubeOrWallLine(27 + 31, 81 - 1, 38 + 31, 81 - 1, mapTube);
	CreateTubeOrWallLine(39 + 31, 91 - 1, 44 + 31, 91 - 1, mapTube);
	CreateTubeOrWallLine(50 + 31, 91 - 1, 56 + 31, 91 - 1, mapTube);
	CreateTubeOrWallLine(62 + 31, 91 - 1, 64 + 31, 91 - 1, mapTube);
	CreateTubeOrWallLine(47 + 31, 94 - 1, 47 + 31, 98 - 1, mapTube);
	CreateTubeOrWallLine(47 + 31, 82 - 1, 47 + 31, 84 - 1, mapTube);
	CreateTubeOrWallLine(48 + 31, 98 - 1, 48 + 31, 100 - 1, mapTube);
	TethysGame::CreateWallOrTube(53 + 31, 85 - 1, 0, mapTube);
}
