#ifndef OP2PLAYER_H
#define OP2PLAYER_H

#pragma pack(push,1)

struct OP2Unit;

// todo: added a whole bunch of members, test if they are in the correct positions
// 0x56EF1C
struct OP2Player
{
  int playerId; // 00
  unsigned int playerBitmask; // 04
  struct {
    unsigned int rlv :4;
    unsigned int solarSat :4;
    unsigned int edwardSat :4;
    unsigned  :20; // **
  } satellites; // 08
  int difficulty; // 0c
  int foodStored; // 10
  int unk0; // 14 **
  int maxCommonOre; // 18
  int maxRareOre; // 1c
  int commonOre; // 20
  int rareOre; // 24
  int isHuman; // 28
  int isEden; // 2c
  int colorNumber; // 30
  int moraleLevel; // 34
  int moraleEventModifier; // 38
  int unk1; // 3c **
  int morale; // 40
  int unk2; // 44 **
  int residenceDemandPercent; // 48
  int foodSupply; // 4c
  int disabledBldgRatio; // 50
  int recForumDemandPercent; // 54
  int unk3; // 58 **
  int medCenterDemandPercent; // 5c
  int boolNurseryOperational; // 60
  int boolUniversityOperational; // 64
  int numDisasterWarningSystems; // 68
  int dirtAvgDamagePrevention; // 6c
  int unoccupiedColonistPercent; // 70
  int scientistsAsWorkersPercent; // 74
  int boolGorfOperational; // 78
  int unk4; // 7c **
  int workerGrowthRemainder; // 80
  int kidGrowthRemainder; // 84
  int kidDeathRemainder; // 88
  int scientistDeathRemainder; // 8c
  int workerDeathRemainder; // 90
  int workers; // 94
  int scientists; // 98
  int kids; // 9c
  int boolRecalcValues; // a0
  int numAvailableWorkers; // a4
  int numAvailableScientists; // a8
  int amountPowerGenerated; // ac
  int inactivePowerCapacity; // b0
  int amountPowerUse; // b4
  int amountPowerAvailable; // b8
  // ------------ after here it's very wrong ------------
  int numBuildings; // bc
  int numStructuresDisabledPower; // c0
  int numScientistsRequired; // c4
  int numScientistsAsWorkers; // c8
  int numScientistsAssignedToResearch; // cc
  int totalFoodProduction; // d0
  int totalFoodConsumption; // d4
  int totalResidenceCapacity; // d8
  int numActiveCommandCenters; // dc
  int numActiveNurseries; // e0
  int numActiveUniversities; // e4
  int numActiveMeteorDefenses; // e8
  int numPowerGenerationFacilities; // ec
  int numActivePowerGenerationFacilities; // f0
  int numDisabledPowerGenerationFacilities; // f4
  int numIdledPowerGenerationFacilities; // f8
  int numAgridomes; // fc
  int numActiveAgridomes; // 100
  int numDisabledAgridomes;
  int numIdledAgridomes;
  int numCommonOreSmelters;
  int numActiveCommonOreSmelters;
  int numDisabledCommonOreSmelters;
  int numIdledCommonOreSmelters;
  int numCommonOreStorageTanks;
  int numActiveCommonOreStorageTanks;
  int numDisabledCommonOreStorageTanks;
  int numIdledCommonOreStorageTanks;
  int numRareOreStorageTanks;
  int numActiveRareOreStorageTanks;
  int numDisabledRareOreStorageTanks;
  int numIdledRareOreStorageTanks;
  int numRareOreSmelters;
  int numActiveRareOreSmelters;
  int numDisabledRareOreSmelters;
  int numIdledRareOreSmelters;
  int numCommonOreMines;
  int numHighYieldCommonOreMines;
  int numMediumYieldCommonOreMines;
  int numLowYieldCommonOreMines;
  int numRareOreMines;
  int numHighYieldRareOreMines;
  int numMediumYieldRareOreMines;
  int numLowYieldRareOreMines;
  int numRobotCommandCenters;
  int numActiveRobotCommandCenters;
  int numDisabledRobotCommandCenters;
  int numIdledRobotCommandCenters;
  int boolRobotCommandCenterOperational;
  //int unk5[5];
  int numBuildingsBuilt; // supposed to be at 1bc
  int numUnitsCreated;
  int unk6[191];
  int playerNetID;
  int CommandPacket0_messageType;
  int CommandPacket0_dataLength;
  int CommandPacket0_timeStamp;
  int CommandPacket0_unknown;
  int unk7[465]; // 460?
  OP2Unit *buildingList;
  OP2Unit *vehicleList;
  OP2Unit *unk8;
  int padding_temp_until_struct_is_fixed[15];
};

struct OP2Player_HFL
{
  int playerId; // 00
  unsigned int playerBitmask; // 04
  struct {
    unsigned int rlv :4;
    unsigned int solarSat :4;
    unsigned int edwardSat :4;
    unsigned  :20;
  } satellites; // 08
  int difficulty; // 0c
  int foodStored; // 10
  int unk0; // 14 **
  int maxCommonOre; // 18
  int maxRareOre; // 1c
  int commonOre; // 20
  int rareOre; // 24
  int isHuman; // 28
  int isEden; // 2c
  int colorNumber; // 30
  int moraleLevel; // 34
  int unk1[5]; // 38 **
  // 3c **
  // 40 **
  // 44 **
  // 48 **
  int foodSupply; // 4c
  int unk2[17]; // 50 **
  // 54 **
  // 58 **
  // 5c **
  // 60 ** [5]
  // 64 **
  // 68 **
  // 6c **
  // 70 **
  // 74 ** [10]
  // 78 **
  // 7c **
  // 80 **
  // 84 **
  // 88 ** [15]
  // 8c **
  // 90 ** [17]
  int workers; // 94
  int scientists; // 98
  int kids; // 9c
  int boolRecalcValues; // a0
  int unk3[70]; // a4 **
  // a8 **
  // ac **
  // b0 **
  // b4 ** [5]
  // b8 **
  // bc **
  // c0 **
  // c4 **
  // c8 ** [10]
  // cc **
  // d0 **
  // d4 **
  // d8 **
  // dc ** [15]
  // e0 **
  // e4 **
  // e8 **
  // ec **
  // f0 ** [20]
  // f4 **
  // f8 **
  // fc **
  // 100 **
  // 104 ** [25]
  // 108 **
  // 10c **
  // 110 **
  // 114 **
  // 118 ** [30]
  // 11c **
  // 120 **
  // 124 **
  // 128 **
  // 12c ** [35]
  // 130 **
  // 134 **
  // 138 **
  // 13c **
  // 140 ** [40]
  // 144 **
  // 148 **
  // 14c **
  // 150 **
  // 154 ** [45]
  // 158 **
  // 15c **
  // 160 **
  // 164 **
  // 168 ** [50]
  // 16c **
  // 170 **
  // 174 **
  // 178 **
  // 17c ** [55]
  // 180 **
  // 184 **
  // 188 **
  // 18c **
  // 190 ** [60]
  // 194 **
  // 198 **
  // 19c **
  // 1a0 **
  // 1a4 ** [65]
  // 1a8 **
  // 1ac **
  // 1b0 **
  // 1b4 **
  // 1b8 ** [70]
  int numBuildingsBuilt; // 1bc
  int unk4[662]; // 1c0 - c14 **
  OP2Unit *buildingList; // c18
  OP2Unit *vehicleList; // c1c
  OP2Unit *unk5; // c18 **
};

#pragma pack(pop)

#endif