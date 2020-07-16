#ifndef OP2UNITS_H
#define OP2UNITS_H

#include <Outpost2DLL.h>

#pragma pack(push,1)

struct OP2UnitInfo;
struct DestWaypoints;

// Note: OP2Unit and OP2UnitInfo are declared as structs instead of classes because they are declared as so in HFL
/*  Combining all the internal unit data structures into one general struct with the use of unions is fairly messy, but bypasses the need to typecast as
    would be the case if an inheritance hierarchy were set up. Also, the vtbl mimicing struct would be especially problematic with setting up inheritance.
    Sizeof(Unit), for any type of unit, always == 0x78 (120) in Outpost 2. */
struct OP2Unit
{
  struct OP2UnitVtbl
  {
    // Member functions (from all child classes too)
    OP2UnitInfo* (__thiscall *GetUnitTypeInfo)(OP2Unit *classPtr); // 00
    void (__thiscall *ProcessForGameCycle)(OP2Unit *classPtr); // 04
    int (__thiscall *ProcessTimers)(OP2Unit *classPtr); // 08
    bool (__thiscall *CheckSpontaneouslyExplode)(OP2Unit *classPtr); // 0c
    int (__thiscall *FireWeapon)(OP2Unit *classPtr); // 10
    void (__thiscall *GetTurretAnimationIndex)(OP2Unit *classPtr, OP2Unit *chassis, int rotation); // 14
    void (__thiscall *DrawUnit)(OP2Unit *classPtr, void *viewport); // 18
    void (__thiscall *LightUpVisibleRange)(OP2Unit *classPtr, void *viewport); // 1c
    void (__thiscall *MarkBackgroundRectToRedraw)(OP2Unit *classPtr, void *viewport); // 20
    int (__thiscall *IsUnitVisible)(OP2Unit *classPtr, void *viewport); // 24
    int (__thiscall *IsUnitVisibleY)(OP2Unit *classPtr, void *viewport); // 28
    int (__thiscall *EMPMissileUnknown)(OP2Unit *classPtr, void *viewport); // 2c
    int (__thiscall *GetSelectionBoxSize)(OP2Unit *classPtr, int *w, int *h); // 30
    int (__thiscall *GetSelectionBoxPos)(OP2Unit *classPtr, int *xOff, int *yOff); // 34
    int (__thiscall *MouseOver)(OP2Unit *classPtr, int xOff, int yOff); // 38
    int (__thiscall *GetRolloverText)(OP2Unit *classPtr, char *destBuffer, int bufferSize); // 3c
    int (__thiscall *GetSelectedUnitDisplayString)(OP2Unit *classPtr, char *destBuffer, int bufferSize); // 40
    int (__thiscall *IsMouseCursorOverSelection)(OP2Unit *classPtr, int pixelX, int pixelY); // 44
    int (__thiscall *unused)(OP2Unit *classPtr); // 48, never used, never overridden, returns (int)2
    OP2Unit* (__thiscall *Release)(OP2Unit *classPtr, int u1); // 4c
    void (__thiscall *DoEvent)(OP2Unit *classPtr); // 50, DoDockDamage (structures with docks), DoSelfDamage (Tokamak), DoImpact (meteor)
    void (__thiscall *OnSave)(OP2Unit *classPtr); // 54
    void (__thiscall *OnLoad)(OP2Unit *classPtr); // 58
    void (__thiscall *EMPed)(OP2Unit *classPtr, short empTime); // 5c
    void (__thiscall *Stickyfoamed)(OP2Unit *classPtr, int stickyfoamTime); // 60
    void (__thiscall *Move)(OP2Unit *classPtr); // 64
    int (__thiscall *TransferUnit)(OP2Unit *classPtr, int destPlayerIdx); // 68
    void (__thiscall *GetLocation)(OP2Unit *classPtr, int unused1, int unused2, int *tileX, int *tileY); // 6c
    int (__thiscall *_70)(OP2Unit *classPtr); // 70 **, base class function == return 0; overridden by base "air unit" class, SCAT inherits from base air unit class
    int (__thiscall *IsLive)(OP2Unit *classPtr); // 74
    // Base unit class vtbl ends here
    void (__thiscall *DrawAmbientGraphic)(OP2Unit *classPtr, void *viewport); // 78
    union
    {
      int (__thiscall *Pathfind)(OP2Unit *classPtr, int destTileX, int destTiley, int unk1, int unk2); // 7c, last two args have something to do with waypoints
      int (__thiscall *Warn)(OP2Unit *classPtr, int disasterWarn1StringIndex, int disasterWarn1SoundID, int disasterWarn2StringIndex, int disasterWarn2SoundID);
      void (__thiscall *Launch)(OP2Unit *classPtr); // 7c
    };
    union
    {
      int (__thiscall *GetChassisAnimationIndex)(OP2Unit *classPtr, int rotation); // 80
      void (__thiscall *EMPMissileLand)(OP2Unit *classPtr); // 80
      void (__thiscall *Explode)(OP2Unit *classPtr, OP2Unit *source); // 80
    };
    void (__thiscall *EMPMissileCreateBlast)(OP2Unit *classPtr); // 84
    int (__thiscall *_88)(OP2Unit *classPtr); // 88 **
    int (__thiscall *_8C)(OP2Unit *classPtr); // 8c **
    void (__thiscall *CanMoveToTile)(OP2Unit *classPtr, LOCATION location); // 90
    union
    {
      void (__thiscall *Unit_DoAmbientAnimation)(OP2Unit *classPtr); // 94
      void (__thiscall *SetWeaponSource)(OP2Unit *classPtr, int unitIndex); // 94
    };
    union
    {
      void (__thiscall *Unit_GetAnimationFrame)(OP2Unit *classPtr); // 98
      int (__thiscall *GetOreType)(OP2Unit *classPtr); // 98
    };
    union
    {
      void (__thiscall *Building_9C)(OP2Unit *classPtr, int, int); // 9c
      void (__thiscall *Survey)(OP2Unit *classPtr, int playerNum); // 9c
    };
    int (__thiscall *IsBeaconSurveyed)(OP2Unit *classPtr, int playerNum); // a0
    void (__thiscall *CreateBeacon)(OP2Unit *classPtr, int oreType, int barYield, int variant); // a4
    int (__thiscall *GetBarYield)(OP2Unit *classPtr); // a8
    int (__thiscall *BuildMine)(OP2Unit *classPtr, OP2Unit *mineUnit); // ac
    void (__thiscall *SetNumTruckLoads)(OP2Unit *classPtr, int numTruckLoads); // b0
    int (__thiscall *_B4)(OP2Unit *classPtr); // b4 **
    int (__thiscall *_B8)(OP2Unit *classPtr); // b8 **
    int (__thiscall *_BC)(OP2Unit *classPtr); // bc **
    int (__thiscall *_C0)(OP2Unit *classPtr); // c0 **
    void (__thiscall *Building_ProcessDeath)(OP2Unit *classPtr); // c4
    int (__thiscall *_C8)(OP2Unit *classPtr); // c8 **
    int (__thiscall *_CC)(OP2Unit *classPtr); // cc **
    int (__thiscall *_D0)(OP2Unit *classPtr); // d0 **
    int (__thiscall *_D4)(OP2Unit *classPtr); // d4 **
    int (__thiscall *_D8)(OP2Unit *classPtr); // d8 **
    int (__thiscall *_DC)(OP2Unit *classPtr); // dc **
    int (__thiscall *_E0)(OP2Unit *classPtr); // e0 **
    int (__thiscall *_E4)(OP2Unit *classPtr); // e4 **
    int (__thiscall *_E8)(OP2Unit *classPtr); // e8 **
    int (__thiscall *_EC)(OP2Unit *classPtr); // ec **
    int (__thiscall *_F0)(OP2Unit *classPtr); // f0 **
    int (__thiscall *_F4)(OP2Unit *classPtr); // f4 **
    int (__thiscall *_F8)(OP2Unit *classPtr); // f8 **
    int (__thiscall *_FC)(OP2Unit *classPtr); // fc **
    int (__fastcall *FinishProducingUnit)(OP2Unit *classPtr, int unused, int producedUnitId, int unknown); // 100
    // who cares after here
  } *vtbl; // 00

  // Member variables (from all child classes too)
  OP2Unit *next; // 04
  OP2Unit *prev; // 08
  OP2Unit *playerNext; // 0c
  int unitIndex; // 10
  int pixelX; // 14
  int pixelY; // 18
  char rotation; // 1c
  char ownerNum:4; // 1d
  char creatorNum:4;
  short damage; // 1E
  char boolBusy; // 20
  char command; // 21
  char action; // 22
  char executingAction; // 23
  union
  {
    short cargoOrWeapon; // 24
    struct
    {
      unsigned short cargoType:4; // 24
      unsigned short cargoAmount:12;
    };
    short tubeOrWallType;
    short researchTimer; // 24
    short disasterDuration;
    short earthquakeStrength;
  };
  short attackingUnitIndex; // 26
  int _28; // 28 **
  char unitTypeInstanceNum; // 2c
  char _2D; // 2d **
  short reloadTimer; // 2e
  int _30; // 30 **
  union
  {
    DestWaypoints *destWaypoints; // 34, stores information about the unit's current move order path, and waypoints
    int destPixelX; // 34
    struct
    {
      short destTileX; // 34
      short destTileY; // 36
    };
  };
  union
  {
    int unkWaypointData; // 38, ???
    void *dirtHelperPtr; // 38, points to an object that helps with calculating unit's DIRT damage prevention, maybe it also
                         //     has to do with command center connections, making it a general tube connection helper?
    int destPixelY; // 38
  };
  int actionTimer; // 3c
  int animAndFrameIndex; // 40
  unsigned int flags; // 44
  // Derived class member variables
  union
  {
    struct
    {
      int _48; // 48 **
      int _4C; // 4c **
      int _50; // 50 **
      int _54; // 54 **
      int truckloads; // 58, how many truckloads of ore (relating to yield peaking and declining)
      int yield; // 5c
      int variant; // 60
      char type; // 64
      short _65; // 65 **
      char surveyed; // 67, player bit vector
    } Beacon;
    struct
    {
      // ...
    } Weapon;
    struct
    {
      // ...
    } Structure;
    struct
    {
      int _48; // 48 **
      int _4C; // 4c **
      int _50; // 50 **
      short timerStickyfoam; // 54
      short timerEMP; // 56
      int _58; // 58 **
      int _5C; // 5c **
      int _60; // 60 **
      int _64; // 64 **
      int _68; // 68 **
      short _6C; // 6c **
      int _6E; // 6e **
      int _72; // 72 **
      union
      {
        short _76; // 76 **
        short timerInfection; // 76, BlightHook
      };
    } Vehicle;
    struct
    {
      int _48; // 48 **
      int directionChangeStartTick; // 58
      unsigned char directionOfMovement; // 5c, (0-0xFF, 0 = right, 0x40 = down, 0x80 = left, 0xC0 = up)
    } Vortex;
    struct
    {
      int _48; // 48 **
      int _4C; // 4c **
      int _50; // 50 **
      short timerStickyfoam; // 54
      short timerEMP; // 56
      int _58; // 58 **
      int _5C; // 5c **
      int _60; // 60 **
      int _64; // 64 **
      int _68; // 68 **
      short _6C; // 6c **
      int objectOnPad; // 6e
      int launchCargo; // 72
      short _76; // 76 **
    } Etc;
  };
};

// OP2Unit Flags field
#define UNIT_LIGHTSON                  0x1
#define UNIT_ISVEHICLE                 0x2
#define UNIT_ISBUILDING                0x4
// 0x8
#define UNIT_ISOFFENSIVE               0x10
#define UNIT_DOUBLEFIRERATE            0x20
#define UNIT_NOINSTANTDELETE           0x40 // non-vehicles only
#define UNIT_WEAPONCONNECTEDTOCC       0x80
#define UNIT_CANEXPLODE                0x100 // also has something to do with weapons, mining beacons
// 0x200
#define UNIT_CANBEDAMAGED              0x400
// 0x800
#define UNIT_ISEDEN                    0x1000
#define UNIT_DISASTERDETECTED          0x2000
#define UNIT_ENABLEDPOWER              UNIT_DISASTERDETECTED
#define UNIT_DISASTERNOFIRSTWARN       0x4000
#define UNIT_ENABLEDWORKERS            UNIT_DISASTERNOFIRSTWARN
#define UNIT_DISASTERNOSECONDWARN      0x8000
#define UNIT_ENABLEDSCIENTISTS         UNIT_DISASTERNOSECONDWARN
#define UNIT_DOAFTERSHOCK              0x10000
#define UNIT_ISDEAD                    0x20000
#define UNIT_ISSTICKYFOAMED            0x40000
#define UNIT_ISINFECTED                UNIT_ISSTICKYFOAMED
#define UNIT_ISEMPED                   0x80000
#define UNIT_ISESGED                   0x100000
// 0x200000
#define UNIT_PREVENTEXPLOSIONONDEATH   0x400000
#define UNIT_SETOPPFIREDUPON           0x800000
#define UNIT_ISUNDOCKING               0x1000000
#define UNIT_HASSPECIALTARGET          0x2000000
// 0x4000000
#define UNIT_FORCEFULLLIGHTVISIBILITY  0x8000000
#define UNIT_ISINVISIBLE               0x10000000
#define UNIT_HASSPECIALTARGET2         0x20000000 // do not auto target
#define UNIT_EX_INFECTEDVEHICLE         0x40000000
// 0x40000000, unused? (BlightHook: UNIT_EX_INFECTEDVEHICLE)
// 0x80000000, has something to do with tank units??

struct OP2UnitInfo
{
  struct OP2UnitInfoVtbl
  {
    // Member functions
    OP2Unit* (__thiscall *CreateUnit)(OP2UnitInfo *thisPtr, int pixelX, int pixelY, int unitIndex); // 00
    char* (__thiscall *GetCodeName)(OP2UnitInfo *thisPtrt); // 04
    bool (__thiscall *SaveData)(OP2UnitInfo *thisPtr, void *streamIO); // 08
    bool (__thiscall *LoadData)(OP2UnitInfo *thisPtr, void *streamIO); // 0c
    bool (__thiscall *Init)(OP2UnitInfo *thisPtr); // 10
    void (__thiscall *Process)(OP2UnitInfo *thisPtr); // 14
    OP2Unit* (__thiscall *FindTarget)(OP2UnitInfo *thisPtr); // 18
    void (__thiscall *GetGuardPostTurretAnimationIndex)(OP2UnitInfo *thisPtr, OP2Unit *unit, int rotation); // 1c
    void (__thiscall *GetTigerTurretAnimationIndex)(OP2UnitInfo *thisPtr, OP2Unit *unit, int rotation); // 20
    void (__thiscall *GetPantherTurretAnimationIndex)(OP2UnitInfo *thisPtr, OP2Unit *unit, int rotation); // 24
    void (__thiscall *GetLynxTurretAnimationIndex)(OP2UnitInfo *thisPtr, OP2Unit *unit, int rotation); // 28
    int (__thiscall *_2C)(OP2UnitInfo *thisPtr); // 2c **
  } *vtbl; // 00

  // Member variables
  int unitType; // 04
  struct PlayerData // 08, player specific data chunk (also at 4c, 90, d4, 118, 15c, 1a0)
  {
    int hitPoints; // 08
    int repairAmount; // 0c
    int armorClass; // 10
    int commonCost; // 14
    int rareCost; // 18
    int buildTime; // 1c
    int sightRange; // 20
    char numUnitsOfType; // 24
    char improved; // 25
    short unknown; // 26
    int unknown1; // 28, PLAYER_PROP Ore
    union
    {
      int powerRequired; // 2c
      int moveSpeed; // 2c
      int turretTurnRate; // 2c
    };
    union
    {
      int concussionDamage; // 30
      int workersRequired; // 30
      int turnRate; // 30
    };
    union
    {
      int penetrationDamage; // 34
      int scientistsRequired; // 34
      int productionRate; // 34
    };
    union
    {
      int reloadTime; // 38
      int storageCapacity; // 38
    };
    union
    {
      int productionCapacity; // 3c
      int weaponRange; // 3c
    };
    union
    {
      int numBays; // 40
      int cargoCapacity; // 40
    };
    int unknown2[2]; // 44 **
    // 48 **
  } playerData[7];
  int techId; // 1e4
  int trackType; // 1e8
  int unknown; // 1ec **
  int selectSoundId; // 1f0
  int ownerType; // 1f4
  char unitName[40]; // 1f8
  char produceName[40]; // 220
  union
  {
    short xSize; // 248
    short damageRadius; // 248
    short vehicleFlags; // 248
  };
  short ySize; // 24a
  union
  {
    int pixelsSkipped; // 24c
    int buildingFlags; // 24c
  };
  int edenAnimationIndex[10]; // 250
  int plyAnimationIndex[10]; // 278
  char resPriority; // 2a0
  char rareRubble; // 2a1
  char unknown3; // 2a2
  char normalRubble; // 2a3
  char edenDockLoc; // 2a4
  char plyDockLoc; // 2a5
  int unknown4[107]; // 2a6 - 454 **
};

// track types
#define TRACK_LEGGED  0
#define TRACK_WHEELED  1
#define TRACK_MINER    2
#define TRACK_TRACKED  3
#define TRACK_HOVER    4

// owner types
#define OWNER_PLYMOUTH  0x800
#define OWNER_EDEN    0x1000

#pragma pack(pop)

#endif
