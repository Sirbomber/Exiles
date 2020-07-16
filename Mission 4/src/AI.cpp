#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <hfl.h>
#include "AI.h"

// AI data
extern int numAI;

FightGroup DefLynx,
		   DefPnth,
		   GenericAttackers,
		   ActiveAttackers,
		   DefIon,
		   DefFusion,
		   DefFuel,
		   DefCommand,
		   PatrolTeam,
		   FusionTrap,
		   CommandTrap,
		   FuelingDecoy,
		   FuelingTrap,
		   CanyonLynx,
		   RandomPanthers,
		   PlateauGroup,
		   AiDft;

bool panic = false;

void SetupAI()
{
	// AI setup/tech bonus
	Player[numAI].GoPlymouth();
	Player[numAI].SetTechLevel(5);
	Player[numAI].MarkResearchComplete(5111);	// Independent Turret Power Systems
	Player[numAI].MarkResearchComplete(7206);	// Scout-Class Drive Train Refit
	Player[numAI].MarkResearchComplete(5601);	// Heat Dissipation Systems (P)
	Player[numAI].MarkResearchComplete(8309);	// Reinforced Panther Construction
	Player[numAI].MarkResearchComplete(8302);	// Efficiency Engineering (P)


	// Setup global fight groups
	DefLynx = CreateFightGroup(numAI);
	DefPnth = CreateFightGroup(numAI);
	GenericAttackers = CreateFightGroup(numAI);
	ActiveAttackers = CreateFightGroup(numAI);
	DefIon = CreateFightGroup(numAI);
	DefFusion = CreateFightGroup(numAI);
	DefFuel = CreateFightGroup(numAI);
	DefCommand = CreateFightGroup(numAI);
	PatrolTeam = CreateFightGroup(numAI);
	FusionTrap = CreateFightGroup(numAI);
	CommandTrap = CreateFightGroup(numAI);
	FuelingDecoy = CreateFightGroup(numAI);
	FuelingTrap = CreateFightGroup(numAI);
	CanyonLynx = CreateFightGroup(numAI);
	RandomPanthers = CreateFightGroup(numAI);
	PlateauGroup = CreateFightGroup(numAI);
	AiDft = CreateFightGroup(numAI);
	AiDft.SetRect(MAP_RECT(1+31, 126-1, 4+31, 128-1));
	Player[numAI].SetDefaultGroup(AiDft);
	CreateTimeTrigger(1, 0, 50, "PoofCapturedTrucks");
	CreateTimeTrigger(1, 0, 7800, 9200, "DoRandomAttack");

	// Setup main AI base
	SetupAiBase();
	Player[numAI].SetOre(8000);
	Player[numAI].SetRareOre(6000);

	// Setup AI units throughout the map
	SetupDefenders_IonDrive();
	SetupDefenders_FusionDrive();
	SetupDefenders_FuelingSystems();
	SetupDefenders_CommandModule();
	SetupGroup_HighPlateau();
	SetupGroup_RandomCanyonLynx();
	SetupGroup_RandomPanthers();
	SetupGroup_Patrol();
	SetupGroup_FusionDriveTrap();
	Setup_RandomGuardPosts();

}

void SetupAiBase()
{
	Unit Unit1;

	// AI unit groups (and required unit handles)
	UnitEx cS, cM, rS, rM;
	MiningGroup Common = CreateMiningGroup(numAI),
		        Rare = CreateMiningGroup(numAI);
	BuildingGroup VF[2];
	VF[0] = CreateBuildingGroup(numAI);
	VF[1] = CreateBuildingGroup(numAI);

	// Mining beacons
	TethysGame::CreateBeacon(mapMiningBeacon, 34+31, 107-1, 0, 0, -1);
	TethysGame::CreateBeacon(mapMiningBeacon,  5+31, 123-1, 1, 1, -1);

	// Structures
	TethysGame::CreateUnit(Unit1, mapCommandCenter, LOCATION(9+31, 111-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAdvancedLab, LOCATION(3+31, 111-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(cS, mapCommonOreSmelter, LOCATION(22+31, 108-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(cM, mapCommonOreMine, LOCATION(34+31, 107-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapAgridome, LOCATION(23+31, 114-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapReinforcedResidence, LOCATION(19+31, 114-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(rS, mapRareOreSmelter, LOCATION(11+31, 116-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(rM, mapCommonOreMine, LOCATION(5+31, 123-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMHDGenerator, LOCATION(18+31, 121-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapMHDGenerator, LOCATION(14+31, 124-1), numAI, mapNone, 0);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(15+31, 104-1), numAI, mapNone, 0);
		VF[0].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapVehicleFactory, LOCATION(10+31, 103-1), numAI, mapNone, 0);
		VF[1].TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapRobotCommand, LOCATION(24+31, 117-1), numAI, mapNone, 0);

	// Vehicles
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(27+31, 107-1), numAI, mapNone, 0);
		Common.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(29+31, 108-1), numAI, mapNone, 0);
		Common.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(31+31, 107-1), numAI, mapNone, 0);
		Common.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(32+31, 108-1), numAI, mapNone, 0);
		Common.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(26+31, 109-1), numAI, mapNone, 0);
		Common.TakeUnit(Unit1);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(5+31, 121-1), numAI, mapNone, 0);
		Rare.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(6+31, 120-1), numAI, mapNone, 0);
		Rare.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapCargoTruck, LOCATION(9+31, 119-1), numAI, mapNone, 0);
		Rare.TakeUnit(Unit1);
		Unit1.DoSetLights(1);

	// Record mining group info
	Common.Setup(cM, cS, MAP_RECT(22+31, 105-1, 36+31, 110-1) );
	Common.SetTargCount(mapCargoTruck, mapNone, 5);
	Rare.Setup(rM, rS, MAP_RECT(4+31, 116-1, 13+31, 124-1) );
	Rare.SetTargCount(mapCargoTruck, mapNone, 3);
	VF[0].RecordVehReinforceGroup(Common, 7000);
	VF[0].RecordVehReinforceGroup(Rare, 6000);

	// Record defender group info
	DefPnth.SetTargCount(mapPanther, mapMicrowave, 8);
    DefPnth.SetTargCount(mapPanther, mapEMP, 6);
	DefPnth.SetTargCount(mapPanther, mapRPG, 12);
	DefPnth.SetTargCount(mapPanther, mapESG, 4);
    DefPnth.SetRect(MAP_RECT(17+31, 99-1, 25+31, 106-1));
    DefPnth.AddGuardedRect(MAP_RECT( 1+31,  91-1, 30+31, 111-1));
    DefPnth.AddGuardedRect(MAP_RECT(31+31,  95-1, 40+31, 107-1));
	DefPnth.AddGuardedRect(MAP_RECT(31+31, 108-1, 38+31, 110-1));
	DefPnth.AddGuardedRect(MAP_RECT( 1+31, 112-1, 29+31, 117-1));
	DefPnth.AddGuardedRect(MAP_RECT( 1+31, 118-1, 24+31, 123-1));
    VF[0].RecordVehReinforceGroup(DefPnth, 5000);

    DefLynx.SetTargCount(mapLynx, mapEMP, 12);
	DefLynx.SetTargCount(mapLynx, mapRPG, 14);
	DefLynx.SetTargCount(mapLynx, mapStickyfoam, 6);
    DefLynx.SetRect(MAP_RECT(1+31, 98-1, 16+31, 101-1));
    DefLynx.AddGuardedRect(MAP_RECT( 1+31,  91-1, 30+31, 111-1));
    DefLynx.AddGuardedRect(MAP_RECT(31+31,  95-1, 40+31, 107-1));
	DefLynx.AddGuardedRect(MAP_RECT(31+31, 108-1, 38+31, 110-1));
	DefLynx.AddGuardedRect(MAP_RECT( 1+31, 112-1, 29+31, 117-1));
	DefLynx.AddGuardedRect(MAP_RECT( 1+31, 118-1, 24+31, 123-1));
    VF[1].RecordVehReinforceGroup(DefLynx, 6000);

	GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 7);
	GenericAttackers.SetTargCount(mapLynx, mapEMP, 3);
    GenericAttackers.SetRect(MAP_RECT(9+31, 93-1, 17+31, 97-1));
    VF[1].RecordVehReinforceGroup(GenericAttackers, 7000);

	// Guard Posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(39+31, 85-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(41+31, 80-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(20+31, 96-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(22+31, 96-1), numAI, mapRPG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(24+31, 96-1), numAI, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(6+31, 96-1), numAI, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(4+31, 96-1), numAI, mapRPG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(2+31, 96-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(50+31, 58-1), numAI, mapStickyfoam, 0);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(23+31, 103-1), numAI, mapMicrowave, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(21+31, 102-1), numAI, mapMicrowave, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(4+31, 100-1), numAI, mapRPG, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(5+31, 101-1), numAI, mapRPG, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(4+31, 103-1), numAI, mapRPG, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(5+31, 104-1), numAI, mapRPG, 0);
		DefPnth.TakeUnit(Unit1);
		Unit1.DoSetLights(1);

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(10+31, 107-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(11+31, 108-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(13+31, 109-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(16+31, 109-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(17+31, 110-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(15+31, 110-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(12+31, 110-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(8+31, 108-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(7+31, 108-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(5+31, 108-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(3+31, 108-1), numAI, mapRPG, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2+31, 104-1), numAI, mapStickyfoam, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2+31, 105-1), numAI, mapStickyfoam, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2+31, 106-1), numAI, mapStickyfoam, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(2+31, 107-1), numAI, mapStickyfoam, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(21+31, 104-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(19+31, 105-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(23+31, 105-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(25+31, 106-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(16+31, 107-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(17+31, 108-1), numAI, mapEMP, 0);
		DefLynx.TakeUnit(Unit1);
		Unit1.DoSetLights(1);

	// Tubes
	TethysGame::CreateWallOrTube(6+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(7+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(9+31, 113-1, 0, mapTube);
	TethysGame::CreateWallOrTube(9+31, 114-1, 0, mapTube);
	TethysGame::CreateWallOrTube(12+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(13+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(14+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(15+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(16+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(17+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(18+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(19+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(20+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(21+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(22+31, 111-1, 0, mapTube);
	TethysGame::CreateWallOrTube(22+31, 112-1, 0, mapTube);
	TethysGame::CreateWallOrTube(15+31, 107-1, 0, mapTube);
	TethysGame::CreateWallOrTube(15+31, 108-1, 0, mapTube);
	TethysGame::CreateWallOrTube(15+31, 109-1, 0, mapTube);
	TethysGame::CreateWallOrTube(15+31, 110-1, 0, mapTube);

	// Walls
	TethysGame::CreateWallOrTube(25+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(24+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(23+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(22+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(21+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(20+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(19+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(18+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(18+31, 95-1, 0, mapWall);
	TethysGame::CreateWallOrTube(18+31, 96-1, 0, mapWall);
	TethysGame::CreateWallOrTube(1+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(2+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(3+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(4+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(5+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(6+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(7+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(8+31, 94-1, 0, mapWall);
	TethysGame::CreateWallOrTube(8+31, 95-1, 0, mapWall);
	TethysGame::CreateWallOrTube(8+31, 96-1, 0, mapWall);
}

void SetupDefenders_IonDrive()
{
	Unit Unit1;
	DefIon.SetRect(MAP_RECT(167+31, 51-1, 188+31, 66-1));
	DefIon.AddGuardedRect(MAP_RECT(167+31, 51-1, 188+31, 66-1));

	// Guard Posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(183+31, 52-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(180+31, 51-1), numAI, mapRPG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(169+31, 69-1), numAI, mapMicrowave, 0);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(174+31, 56-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(177+31, 55-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(179+31, 57-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(178+31, 58-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(174+31, 58-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(175+31, 59-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefIon.TakeUnit(Unit1);
}

void SetupDefenders_FusionDrive()
{
	Unit Unit1;

	DefFusion.SetRect(MAP_RECT(105+31, 14-1, 115+31, 19-1));
	DefFusion.AddGuardedRect(MAP_RECT(92+31, 1-1, 109+31, 10-1));
	DefFusion.AddGuardedRect(MAP_RECT(99+31, 16-1, 121+31, 22-1));

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(106+31, 14-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		DefFusion.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(107+31, 16-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		DefFusion.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(109+31, 17-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFusion.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(111+31, 16-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFusion.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(109+31, 15-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFusion.TakeUnit(Unit1);
}

void SetupDefenders_FuelingSystems()
{
	Unit Unit1;

	DefFuel.SetRect(MAP_RECT(111+31, 109-1, 123+31, 127-1));
	DefFuel.AddGuardedRect(MAP_RECT(106+31, 106-1, 125+31, 119-1));

	if (numAI > 3)
	{
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(113 + 31, 111 - 1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(114 + 31, 113 - 1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	}
	else if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(113 + 31, 111 - 1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(114 + 31, 113 - 1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	}
	else
	{
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(113 + 31, 111 - 1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(114 + 31, 113 - 1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	}
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(115+31, 110-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(116+31, 111-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(116+31, 114-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(117+31, 113-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(117+31, 110-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(118+31, 111-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(119 + 31, 113 - 1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(118 + 31, 114 - 1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		DefFuel.TakeUnit(Unit1);
	}
}

void SetupDefenders_CommandModule()
{
	Unit Unit1;

	DefCommand.SetRect(MAP_RECT(50+31, 28-1, 59+31, 34-1));
	DefCommand.AddGuardedRect(MAP_RECT(47+31, 26-1, 64+31, 37-1));

	// Guard Posts
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(51+31, 26-1), numAI, mapESG, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(58+31, 26-1), numAI, mapRPG, 0);

	// Tanks
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(56+31, 30-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58+31, 32-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(57+31, 29-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(59+31, 30-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(53+31, 30-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(55+31, 32-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(52+31, 32-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(58+31, 34-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		DefCommand.TakeUnit(Unit1);
}

void SetupGroup_HighPlateau()
{
	Unit Unit1;

	PlateauGroup.SetRect(MAP_RECT(76+31, 81-1, 84+31, 88-1));

	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(78+31, 87-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(80+31, 86-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(81+31, 87-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(83+31, 86-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(78+31, 86-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(80+31, 85-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(82+31, 85-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(77+31, 85-1), numAI, mapESG, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(76+31, 84-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(78+31, 82-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(80+31, 83-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(82+31, 84-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PlateauGroup.TakeUnit(Unit1);
}

void SetupGroup_RandomCanyonLynx()
{
	Unit Unit1;

	CanyonLynx.SetRect(MAP_RECT(162+31, 31-1, 168+31, 35-1));

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(163+31, 32-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		CanyonLynx.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(165+31, 34-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		CanyonLynx.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(164+31, 31-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		CanyonLynx.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(165+31, 32-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		CanyonLynx.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(167+31, 33-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		CanyonLynx.TakeUnit(Unit1);

	PatrolRoute Route2;
	LOCATION Points2[] =
	{
		LOCATION(170+31, 26-1),
		LOCATION(163+31, 34-1),
		LOCATION(142+31, 35-1),
		LOCATION(-1,-1)
	};

	Route2.waypoints = Points2;
	CanyonLynx.SetPatrolMode(Route2);

}

void SetupGroup_RandomPanthers()
{
	Unit Unit1;

	RandomPanthers.SetRect(MAP_RECT(191+31, 121-1, 199+31, 127-1));

	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(195+31, 122-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(197+31, 123-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(195+31, 124-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(196+31, 125-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(193+31, 123-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(194+31, 125-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		RandomPanthers.TakeUnit(Unit1);
}

void SetupGroup_Patrol()
{
	Unit Unit1;

	PatrolTeam.SetRect(MAP_RECT(143+31, 109-1, 153+31, 116-1));

	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(146+31, 111-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(147+31, 113-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(149+31, 115-1), numAI, mapEMP, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(148+31, 112-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(150+31, 114-1), numAI, mapStickyfoam, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(149+31, 110-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(150+31, 111-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(144+31, 112-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(146+31, 114-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(152+31, 113-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapPanther, LOCATION(147+31, 110-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		PatrolTeam.TakeUnit(Unit1);

	PatrolRoute Route1;
	LOCATION Points1[] =
	{
		LOCATION(153+31, 124-1),
		LOCATION(147+31,  99-1),
		LOCATION(136+31,  85-1),
		LOCATION(136+31,  52-1),
		LOCATION(143+31,  32-1),
		LOCATION(-1,-1)
	};

	Route1.waypoints = Points1;
	PatrolTeam.SetPatrolMode(Route1);

}

void SetupGroup_FusionDriveTrap()
{
	Unit Unit1;

	FusionTrap.SetRect(MAP_RECT(120+31, 34-1, 127+31, 39-1));

	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(123+31, 35-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(124+31, 36-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125+31, 37-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(126+31, 36-1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	if (numAI > 2)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(125 + 31, 35 - 1), numAI, mapRPG, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(121 + 31, 36 - 1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	}
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(122+31, 37-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(120+31, 38-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(121+31, 38-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(123+31, 38-1), numAI, mapMicrowave, 0);
		Unit1.DoSetLights(1);
		FusionTrap.TakeUnit(Unit1);
}

void Setup_RandomGuardPosts()
{
	Unit Unit1;

	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(159+31, 12-1), numAI, mapMicrowave, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(134+31, 19-1), numAI, mapMicrowave, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(192+31, 86-1), numAI, mapStickyfoam, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(137+31, 102-1), numAI, mapEMP, 0);
	TethysGame::CreateUnit(Unit1, mapGuardPost, LOCATION(140+31, 103-1), numAI, mapRPG, 0);
}

void TriggerFusionDriveTrap(UnitEx wTruck)
{
	FusionTrap.SetTargetUnit(wTruck);
	FusionTrap.DoAttackUnit();
	FusionTrap.DoAttackEnemy();
}

void TriggerFuelingTrap_Decoy(UnitEx wTruck)
{
	Unit Unit1;
	int numToSpawn;
	switch (numAI)
	{
	case 4:
		numToSpawn = 9;
		break;
	case 3:
		numToSpawn = 7;
		break;
	case 2:
		numToSpawn = 5;
		break;
	default:
		numToSpawn = 4;
		break;
	}
	for (int x = 77; x < (77+numToSpawn); x++)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 126-1), numAI, mapRPG, 6);
			Unit1.DoSetLights(1);
			FuelingDecoy.TakeUnit(Unit1);
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapEMP, 6);
			Unit1.DoSetLights(1);
			FuelingDecoy.TakeUnit(Unit1);
	}

	FuelingDecoy.SetTargetUnit(wTruck);
	FuelingDecoy.DoAttackUnit();
	FuelingDecoy.DoAttackEnemy();

	CreateTimeTrigger(1, 1, 600, 700, "TriggerFuelingTrap_ActualTrap");
}

Export void TriggerFuelingTrap_ActualTrap()
{
	Unit Unit1;
	for (int x = 156; x < 161; x++)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 127-1), numAI, mapEMP, 4);
			Unit1.DoSetLights(1);
			FuelingTrap.TakeUnit(Unit1);
	}
	for (int x = 162; x < 166; x++)
	{
		TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(x+31, 127-1), numAI, mapNone, 4);
			Unit1.DoSetLights(1);
			FuelingTrap.TakeUnit(Unit1);
	}
	FuelingTrap.SetAttackType(mapCargoTruck);
	FuelingTrap.DoAttackEnemy();
}

void TriggerCommandTrap(UnitEx wTruck)
{
	Unit Unit1;
	for (int x = 38; x < 49; x++)
	{
		TethysGame::CreateUnit(Unit1, mapLynx, LOCATION(x+31, 2-1), numAI, mapEMP, 2);
			Unit1.DoSetLights(1);
			CommandTrap.TakeUnit(Unit1);
	}
	TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(41+31, 1-1), numAI, mapNone, 2);
			Unit1.DoSetLights(1);
			CommandTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(42+31, 1-1), numAI, mapNone, 2);
			Unit1.DoSetLights(1);
			CommandTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(43+31, 1-1), numAI, mapNone, 2);
			Unit1.DoSetLights(1);
			CommandTrap.TakeUnit(Unit1);
	TethysGame::CreateUnit(Unit1, mapSpider, LOCATION(44+31, 1-1), numAI, mapNone, 2);
			Unit1.DoSetLights(1);
			CommandTrap.TakeUnit(Unit1);

	CommandTrap.SetTargetUnit(wTruck);
	CommandTrap.DoAttackUnit();
	CommandTrap.DoAttackEnemy();
}

void TriggerHabitatTrap(UnitEx wTruck)
{
	PlateauGroup.SetTargetUnit(wTruck);
	PlateauGroup.DoAttackUnit();
	PlateauGroup.DoAttackEnemy();
}

void TriggerPanic()
{
	if (!panic)
	{
		// Send all unoccupied AI attack groups after the players
		DefLynx.DoAttackEnemy();
		DefPnth.DoAttackEnemy();
		RandomPanthers.DoAttackEnemy();
		panic = true;
	}
}

Export void PoofCapturedTrucks()
{
	UnitEx Unit1;
	InRectEnumerator AtEdge(MAP_RECT(1+31, 126-1, 4+31, 128-1));
	while (AtEdge.GetNext(Unit1))
	{
		if (Unit1.OwnerID() == numAI)
		{
			Unit1.DoPoof();
		}
	}
}

Export void DoRandomAttack()
{
	// Send attackers
	ActiveAttackers.SetAttackType(mapCommandCenter);
	ActiveAttackers.TakeAllUnits(GenericAttackers);
	ActiveAttackers.DoAttackEnemy();

	// Pick a random unit composition for the next wave.
	GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 0);
	GenericAttackers.SetTargCount(mapLynx, mapEMP, 0);
	GenericAttackers.SetTargCount(mapLynx, mapESG, 0);
	GenericAttackers.SetTargCount(mapLynx, mapRPG, 0);
	GenericAttackers.SetTargCount(mapLynx, mapStickyfoam, 0);
	GenericAttackers.SetTargCount(mapPanther, mapMicrowave, 0);
	GenericAttackers.SetTargCount(mapPanther, mapEMP, 0);
	GenericAttackers.SetTargCount(mapPanther, mapESG, 0);
	GenericAttackers.SetTargCount(mapPanther, mapRPG, 0);
	GenericAttackers.SetTargCount(mapPanther, mapStickyfoam, 0);

	switch (TethysGame::GetRand(4))
	{
		// Microwave/EMP Lynx push
		case 0:
			switch (numAI)
			{
			case 4:
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 14);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 8);
				break;
			case 3:
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 11);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 7);
				break;
			case 2:
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 10);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 5);
				break;
			default:
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 8);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 4);
				break;
			}
			break;
		
		// RPG/EMP/Microwave Lynx push
		case 1:
			switch (numAI)
			{
			case 4:
				GenericAttackers.SetTargCount(mapLynx, mapRPG, 10);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 8);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 10);
				break;
			case 3:
				GenericAttackers.SetTargCount(mapLynx, mapRPG, 8);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 7);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 8);
				break;
			default:
				GenericAttackers.SetTargCount(mapLynx, mapRPG, 6);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 6);
				GenericAttackers.SetTargCount(mapLynx, mapEMP, 6);
				break;
			}
			break;
		
		// Heavy assault with Panthers
		case 2:
			switch (numAI)
			{
			case 4:
				GenericAttackers.SetTargCount(mapPanther, mapRPG, 9);
				GenericAttackers.SetTargCount(mapPanther, mapMicrowave, 4);
				GenericAttackers.SetTargCount(mapPanther, mapEMP, 7);
				GenericAttackers.SetTargCount(mapPanther, mapESG, 5);
				break;
			case 3:
				GenericAttackers.SetTargCount(mapPanther, mapRPG, 7);
				GenericAttackers.SetTargCount(mapPanther, mapMicrowave, 4);
				GenericAttackers.SetTargCount(mapPanther, mapEMP, 6);
				GenericAttackers.SetTargCount(mapPanther, mapESG, 4);
				break;
			default:
				GenericAttackers.SetTargCount(mapPanther, mapRPG, 6);
				GenericAttackers.SetTargCount(mapPanther, mapMicrowave, 3);
				GenericAttackers.SetTargCount(mapPanther, mapEMP, 5);
				GenericAttackers.SetTargCount(mapPanther, mapESG, 4);
				break;
			}
			break;

		// Splash damage
		case 3:
			switch (numAI)
			{
			case 4:
				GenericAttackers.SetTargCount(mapLynx, mapStickyfoam, 10);
				GenericAttackers.SetTargCount(mapLynx, mapESG, 8);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 4);
				break;
			case 3:
				GenericAttackers.SetTargCount(mapLynx, mapStickyfoam, 8);
				GenericAttackers.SetTargCount(mapLynx, mapESG, 6);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 4);
				break;
			default:
				GenericAttackers.SetTargCount(mapLynx, mapStickyfoam, 7);
				GenericAttackers.SetTargCount(mapLynx, mapESG, 4);
				GenericAttackers.SetTargCount(mapLynx, mapMicrowave, 3);
				break;
			}
			break;
	}
}