#ifndef OP2GAME_H
#define OP2GAME_H

#pragma pack(push,1)

class OP2Game
{
public:
  // Member variables
  int unlimitedRes; // 00
  int produceAll; // 04
  int enableMoraleLog; // 08
  int boolDamage4x; // 0c
  int fastUnits; // 10
  int fastProduction; // 14
  short unknown; // 18
  short unitRoutes; // 1a
  int _1C; // 1c **
  int _20; // 20 **
  int _24; // 24 **
  int _28; // 28 **
  int _2C; // 2c **
  int _30; // 30 **
  int _34; // 34 **
  int disableRCC; // 38
  int forceRCC; // 3c
  int _40; // 40 **
  int _44; // 44 **
  int _48; // 48 **
  int boolDaylightEverywhere; // 4c
  int gameSpeedx4; // 50
  int _54; // 54 **
  int _58; // 58 **
  int _5C; // 5c **
  int _60; // 60 **
  int _64; // 64 **
  int numPlayers; // 68
  int numHumanPlayers; // 6c
  int _70; // 70 **
  int _74; // 74 **
  int _78; // 78 **
  int _7C; // 7c **
  int _80; // 80 **
  int tick; // 84
  int tickOfLastSetGameOpt; // 88
  int _8C; // 8c **
  int localPlayer; // 90
  int chatDestPlayerBitmask; // 94
  int startFadeOutTick; // 98
  int gameTermReasons; // 9c
  int skipProgressSave; // a0
  struct GameStartInfo
  {
    struct StartupFlags
    {
      unsigned int diastersOn      :1; // a4
      unsigned int dayAndNightOn    :1;
      unsigned int moraleOn      :1;
      unsigned int isCampaign      :1;
      unsigned int isMultiplayer    :1;
      unsigned int cheatsOn      :1;
      unsigned int maxPlayers      :3;
      unsigned            :8; // **
      unsigned int initialVehicles  :4;
      unsigned            :11; // **
    } startupFlags;
    int gameVersion;
    int unk1; // **
    struct GameFlags
    {
      unsigned int numPlayers      :3;
      unsigned            :29; // **
    } gameFlags;
    char scriptName[32];
    struct PlayerFlags
    {
      unsigned            :1; // **
      unsigned int isHost        :1;
      unsigned int isEden        :1;
      unsigned int difficulty      :2;
      unsigned int colorNum      :3;
      unsigned            :24; // **
    } playerFlags[6];
    int playerNetId[6];
    char playerName[13 * 6];
    int gameSpeed;
    int randomNumberSeed; // b2
    short unk2; // b6 **
    int unk2_[2]; // b8 **
    // bc **
    int unk3[6]; // c0 **
    // c4 **
    // c8 **
    // cc **
    // d0 **
    // d4 **
    int hostPlayerNetId; // d8
    int unk4[35]; // dc - 164 **
    short unk5; // 168 **
    int missionType; // 16a
    struct LocalPlayerStartInfo
    {
      int food; // 16e
      int commonOre;
      int rareOre;
      int workers;
      int scientists;
      int kids;
      struct
      {
        unsigned int rlv        :4;
        unsigned int solarSat      :4;
        unsigned            :1; // **
        unsigned int edwardSat      :4;
        unsigned            :19; // **
      } satellites;
    } localPlayerStartInfo;
    char localPlayerNum;
    int tick;
    struct MoraleState
    {
      int moraleLevel;
      int eventMoraleModifier;
      int unk1; // **
      int morale;
      int unk2; // **
      int residenceDemand;
      int foodSupply;
      int disabledBldgRatio;
      int recForumDemandPercent;
      int unk3; // **
      int medCenterDemandPercent;
      int boolNurseryOperational;
      int boolUniversityOperational;
      int numDisasterWarningSystems;
      int dirtAvgDamagePrevention;
      int unoccupiedColonistPercent;
      int scientistsAsWorkersPercent;
      int boolGorfOperational;
    } moraleState;
    struct ResearchState
    {
      int numTechs;
      short techLevel;
      char techNum[256];
      char playerBitmask[256];
    } researchState;
  } gameStartInfo;
};

#pragma pack(pop)

enum class GameTermReasons : int {
  MissionAccomplished = 3,
  MissionFailed       = 4,
  VictoryIsSweet      = 7,
  YouHaveBeenDefeated = 8,
  AutoDemo            = 10
};

#endif