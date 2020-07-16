#ifndef OP2SCSTUB_H
#define OP2SCSTUB_H

#pragma pack(push,1)

class StreamIO;

struct OP2ScStubCreator
{
  // Doesn't look right at all
  OP2ScStubCreator* parentScStubCreator; // 00
  void *scStubArray; // 04
  int sizeOfScStub; // 08
  void* Create(void* thisPtr); // 0c
  char* (__thiscall *GetSizeOfThisScStubTypeOrNextScStubType)(void* thisPtr); // 10
  void *unknownLinkedListHead; // 14 **
  int _18; // 18
  int _1C; // 1c
};


class OP2FunctionReference
{
public:
  struct OP2FunctionReferenceVtbl
  {
    // Member functions
    int (__thiscall *_00)(OP2FunctionReference *classPtr); // 00 **
    int (__thiscall *_04)(OP2FunctionReference *classPtr); // 04 **
    int (__thiscall *_08)(OP2FunctionReference *classPtr); // 08 **
    void (__thiscall *Enable)(OP2FunctionReference *classPtr); // 0c
    void (__thiscall *Disable)(OP2FunctionReference *classPtr); // 10
    int (__thiscall *_14)(OP2FunctionReference *classPtr); // 14 **
    int (__thiscall *_18)(OP2FunctionReference *classPtr); // 18 **
    void (__thiscall *Destroy)(OP2FunctionReference *classPtr); // 1c
  } *vtbl; // 00

public:
  // Member variables
  int _04; // 04 **
  int _08; // 08 **
  int _0c; // 0c **
  int _10; // 10 **
  int _14; // 14 **
  int _18; // 18 **
  char* triggerName; // 20
  void* triggerFunctionPtr; // 24
  int _28; // 28 **
  int _2c; // 2c **
  int _30; // 30 **
};


class OP2Trigger
{
public:
  struct OP2TriggerVtbl
  {
    // Member functions
    void (__thiscall *Destructor)(OP2Trigger *classPtr, bool doDelSelf); // 00
    OP2ScStubCreator* (__thiscall *GetScStubCreator)(OP2Trigger *classPtr); // 04
    void (__thiscall *Init)(OP2Trigger *classPtr); // 08
    void (__thiscall *Enable)(OP2Trigger *classPtr); // 0c
    void (__thiscall *Disable)(OP2Trigger *classPtr); // 10
    void (__thiscall *Save)(OP2Trigger *classPtr, StreamIO *savedGameFile); // 14
    void (__thiscall *Load)(OP2Trigger *classPtr, StreamIO *savedGameFile); // 18
    void (__thiscall *RaiseEvent)(OP2Trigger *classPtr); // 1c
    int (__thiscall *_20)(OP2Trigger *classPtr); // 20 **
    void (__thiscall *HasFired)(OP2Trigger *classPtr); // 24, pure virtual for base Trigger class
    OP2FunctionReference* (__thiscall *GetCallbackFunctionReference)(OP2Trigger *classPtr); // 28
  } *vtbl; // 00

public:
  // Member variables
  int ID; // 04
  int bEnabled; // 08
  void *exportClass1; // 0c
  void *exportClass2; // 10
  OP2Trigger *prev; // 14
  OP2Trigger *next; // 18
  int boolNoRepeat; // 1c
  int boolVectorHasFired; // 20, player bit vector
  OP2FunctionReference* callback; // 24
  int _28; // 28 **
  int _2c; // 2c **
  union
  {
    struct BuildingCount
    {
      int refValue; // 30
      int playerNum; // 34
      compare_mode compareMode; // 38
    } buildingCount;
    struct Operational
    {
      map_id buildingType; // 30
      int refValue; // 34
      int playerNum; // 38
      compare_mode compareMode; // 3c
    } operational;
    struct Point
    {
      int refValue; // 30
      int playerNum; // 34
      int playerBitMask; // 38
    } point;
    struct Research
    {
      int techId; // 30
    } research;
    struct SpecialTarget
    {
      int targetUnitIndex; // 30
      int sourceUnitIndex; // 34
      map_id sourceUnitType; // 38
      int boolHasFired; // 3c
    } specialTarget;
    struct Time
    {
      int time; // 30
      int timeLeft; // 34
    } time;
    struct VictoryCondition
    {
      char* missionObjective; // 30
      int victoryConditionScStubIndex; // 34
    } victoryCondition;
  };
};

#pragma pack(pop)

#endif