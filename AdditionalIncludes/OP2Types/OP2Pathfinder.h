#ifndef OP2PATHFINDER_H
#define OP2PATHFINDER_H

#pragma pack(push,1)

struct DestWaypoints
{
  union {
    int numWaypoints; // 00
    DestWaypoints* freeListNext;
  };
  int maxWaypointIndex; // 04
  int currentWaypointIndex; // 08

  int _unknown4; // 0c **
  int _unknown5; // 10 **

  struct Waypoint {
    unsigned int pixelX:15;
    unsigned int pixelY:14;
    unsigned :3;
  } waypoints[8]; // 14 - 30

  struct
  {
    unsigned int _1        :1; // **
    unsigned int _2        :1; // **
    unsigned int _3        :1; // **
    unsigned int _4        :1; // **
    unsigned int _5        :1; // **
    unsigned int _6        :1; // **
    unsigned int _7        :1; // **
    unsigned int _8        :1; // **
    unsigned int _9        :1; // **
    unsigned int _10      :1; // **
    unsigned int _11      :1; // **
    unsigned int _12      :1; // **
    unsigned int _13      :1; // **
    unsigned int _14      :1; // **
    unsigned int _15      :1; // **
    unsigned int _16      :1; // **
    unsigned int _17      :1; // **
    unsigned int _18      :1; // **
    unsigned int _19      :1; // **
    unsigned int _20      :1; // **
    unsigned int _21      :1; // **
    unsigned int _22      :1; // **
    unsigned int _23      :1; // **
    unsigned int _24      :1; // **
    unsigned int _25      :1; // **
    unsigned int _26      :1; // **
    unsigned int _27      :1; // **
    unsigned int _28      :1; // **
    unsigned int _29      :1; // **
    unsigned int _30      :1; // **
    unsigned int _31      :1; // **
    unsigned int _32      :1; // **
  } flags; // 34
  DestWaypoints* nextDestination; // 38 **
  int _unknown15; // 3c {0 = Move/Dock/DockEG/StandGround/CargoRoute/Patrol/Build, 3 = RemoveWall}
  int _unknown16; // 40 **
  short _unknown17; // 44, num pixels moved X? **
  short _unknown18; // 46, num pixels moved Y? **

  int startPixelX; // 48, of current waypoint
  int startPixelY; // 4c, of current waypoint
  int destTileX; // 50, of current waypoint
  int destTileY; // 54, of current waypoint

  int _unknown22; // 58, (_unknown22 >> 16) == num pixels to move X? **
  int _unknown23; // 5c, (_unknown23 >> 16) == num pixels to move Y? **
  int rotationSpeed; // 60
  int _unknown25; // 64, timer? **
  int _unknown26; // 68, timer? **
  int _unknown27; // 6c **
  int _unknown28; // 70 **

  int numPathfinderPoints; // 74
  int currentPathfinderPoint; // 78
  char direction[64]; // 7c - bb
            // The actual path information is stored in here. It stores the direction the unit must take along every step of its current path.
            // If there isn't enough room for the entire path (or due to significant obstructions as well when RCC is active) then it will
            // "fragment" it somehow; when it reaches the end of the current direction list it generates a new list for the next path fragment.

  int _unknown47; // bc **
  int _unknown48; // c0 **
  int _unknown49; // c4 **
  int _unknown50; // c8 **
  int _unknown51; // cc, set to arg 3 of Unit.Pathfind (1 if there are player-defined waypoints) ** enum{0,1,2,3}
  int distance; // d0, set to arg 4 of Unit.Pathfind (2 if there are player-defined waypoints) **

  char padding[0x200 - 0xD4];
};

struct FreeWaypointList {
  int unk;                         // 0x0 **
  DestWaypoints* baseAllocAddr;    // 0x4
  DestWaypoints* nextAllocAddr;    // 0x8
  DestWaypoints* freeWaypointHead; // 0xC
};

#pragma pack(pop)

#endif