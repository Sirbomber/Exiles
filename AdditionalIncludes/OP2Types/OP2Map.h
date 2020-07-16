#ifndef OP2MAP_H
#define OP2MAP_H

#include <Outpost2DLL.h>

struct OP2Unit;

#pragma pack(push,1)

struct OP2Map
{
  int unknown; // **
  unsigned int pixelWidthMask;
  int pixelWidth;
  unsigned int tileXMask;
  int tileWidth;
  int logTileWidth; // base 2 log
  int tileHeight;
  MAP_RECT clipRect;
  int numTiles;
  int numTileSets;
  int logTileHeight; // base 2 log
  int paddingOffsetTileX;
  int numUnits;
  int lastUsedUnitIndex;
  int nextFreeUnitSlotIndex;
  int firstFreeUnitSlotIndex;
  void* freeUnitList;
  OP2Unit* unitArray;
  OP2Unit* unitLinkedListHead; // **
  OP2Unit* unitArrayEnd; // **
  int lightLevel; // char?
};

#ifndef _HFLTYPES_H_
struct MapTile
{
  unsigned int cellType        :5;   // Cell type of this tile
  unsigned int tileIndex       :11;  // Mapping index (tile graphics to use)
  unsigned int unitIndex       :11;  // Index of unit on this tile
  unsigned int lava            :1;   // true if lava is on the tile
  unsigned int lavaPossible    :1;   // true if lava can flow on the tile
  unsigned int expand          :1;   // true if lava / microbe is expanding to this tile
  unsigned int microbe         :1;   // true if microbe is on the tile
  unsigned int wallOrBuilding  :1;   // true if a wall or building is on the tile
};
#endif

struct OP2MapCell
{
  char* name;
  int trackSpeed[5]; // 0: legged,  1: wheeled,  2: miner/geocon,  3: tracked,  4: hover
  int boolLavaUnknown; // **
  int blightSpeed;
  int unknown; // **
};

#pragma pack(pop)

#endif