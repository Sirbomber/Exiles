#ifndef OP2BLIGHTLAVAMGR_H
#define OP2BLIGHTLAVAMGR_H

#include <Outpost2DLL.h>

#pragma pack(push,1)

class OP2SpreadMgrBase
{
public:
  struct OP2SpreadMgrBaseVtbl
  {
    // Member functions
    // ...
  } *vtbl; // 00

public:
  // Member variables
  // ...
};


class OP2BlightMgr
{
public:
  struct OP2BlightMgrVtbl
  {
    // Member functions
    void (__thiscall *SpreadTo)(OP2BlightMgr *classPtr, LOCATION where); // 00
    void (__thiscall *LoadVirMask)(OP2BlightMgr *classPtr); // 04
    void (__thiscall *SetBlight)(OP2BlightMgr *classPtr, LOCATION where); // 08
    int (__thiscall *_0C)(OP2BlightMgr *classPtr, LOCATION where); // 0c **
    void (__thiscall *InfectAreaNear)(OP2BlightMgr *classPtr, LOCATION where); // 10
    int (__thiscall *_14)(OP2BlightMgr *classPtr, LOCATION where); // 14 **
    void (__thiscall *Save)(OP2BlightMgr *classPtr, void *savedGameFile); // 18
    void (__thiscall *Load)(OP2BlightMgr *classPtr, void *savedGameFile); // 1c
    void (__thiscall *ShowMinimapCoverage)(OP2BlightMgr *classPtr); // 1c, the game always calls this function in a non-virtual way
    void (__thiscall *SetSpreadSpeed)(OP2BlightMgr *classPtr, int spreadSpeed); // 20
  } *vtbl; // 00

public:
  // Member variables
  int currentPosition; // 04
  int _08; // 08 **, gets set to 0 when SetSpreadSpeed is called, gets XOR 1'd by SpreadTo
  int _0C; // 0c **
  int spreadSpeed; // 10
  void *virMaskBuffer; // 14
};


class OP2LavaMgr
{
public:
  struct OP2LavaMgrVtbl
  {
    // Member functions
    // ...
  } *vtbl; // 00

public:
  // Member variables
  // ...
};

#pragma pack(pop)

#endif