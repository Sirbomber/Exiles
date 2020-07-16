#ifndef OP2RESEARCH_H
#define OP2RESEARCH_H

// Shamelessly pulled from ForcedExports, modified to have nesting

#pragma pack(push,1)

struct GameStartInfo;
class StreamIO;

class OP2Research
{
public:
  // Member functions
  int GetTechNum(int techID);
  bool HasTech(int playerNum, int techNum);
  bool CanResearchTech(int playerNum, int techNum);
  void MarkResearchComplete(int playerNum, int techNum);
  void SetTechLevel(int playerNum, int techID);
  void GiveClosureOfTech(int playerNum, int techNum);
  void GiveTechUpgrades(int playerNum, int techNum);
  void LoadAndProcessTechFile(const char* fileName, int maxTechLevel);
  void LoadTechFile(const char* fileName, int maxTechID);
  bool SaveStartState(GameStartInfo* gameStartInfo);
  bool LoadStartState(GameStartInfo* gameStartInfo);
  bool Save(StreamIO* savedGameFile);
  bool Load(StreamIO* savedGameFile);
  void GiveInitialTechs();
  int Checksum();

public:
  // Member variables
  int numTechs;
  struct TechInfo
  {
    int techID;
    enum TechCategory
    {
      tcFree,            // 0 = Free technologies (and unavailable technologies)
      tcBasic,          // 1 = Basic labratory sciences
      tcDefenses,          // 2 = Defenses (GP upgrade, walls, and efficiency engineering)
      tcPower,          // 3 = Power
      tcVehicles,          // 4 = Vehicles (which ones can be built, speed upgrades, armor upgrades)
      tcFood,            // 5 = Food
      tcMetals,          // 6 = Metals gathering
      tcWeapons,          // 7 = Weapons
      tcSpace,          // 8 = Space (spaceport, observatory, launch vehicle, skydock)
      tcPopulationHappiness,    // 9 = Population (happiness)
      tcDisaster,          // 10 = Disaster warning (and defense)
      tcPopulationGrowth,      // 11 = Population (health, growth)
      tcSpaceshipModule,      // 12 = Spaceship module
    } category;
    int techLevel;
    int plyCost;
    int edenCost;
    int maxScis;
    int lab;
    int playerHasTech;
    int numUpgrades;
    int numRequiredTechs;
    char *techName;
    char *description;
    char *teaser;
    char *improveDesc;
    int *requiredTechNum;
    struct TechUpgradeInfo
    {
      struct UpgradeType
      {
        int type;          // Type of upgrade  [0 = Unit_Prop, 1 = Player_Prop, 2 = Function_Result]
        char *upgradeType;      // Pointer to a string that follows the "UNIT_PROP" tag in the sheets
        int offsetToProp;      // Offset of property in the upgraded structure (byte offset added to base of where data starts for current player)
                      // or function address for type = 2 (Function_Result)
      } *type;          // Pointer to struct describing the type of upgrade (Production_Capacity, Move_Speed, Sight_Range, etc.)
      map_id unitType;      // Type of unit this upgrade applies to
      int newValue;        // New value of property being upgraded
    } **upgrades;        // TechUpgradeInfo*[]*
    int numDepTech;
    int *depTechNum;
    int pad1, pad2;
  } **techInfos;        // TechInfo*[]*
  int maxTechID;        // 12999  [maxTechLevel * 1000 + 999]
};

#pragma pack(pop)

#endif