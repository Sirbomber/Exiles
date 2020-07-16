#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

#include "AI.h"

// AI data
extern int numAI;

// ----------------------------------------------------------------------------
// MapZone member functions

MapZone::MapZone()
{
	//
}

MapZone::~MapZone()
{
	//
}

void MapZone::AddRectToZone(MAP_RECT _rect)
{
	zoneRects.push_back(_rect);
}

bool MapZone::CheckUnitInZone(Unit _unit)
{
	for (std::list<MAP_RECT>::iterator i = zoneRects.begin(); i != zoneRects.end(); i++)
	{
		if (i->Check(_unit.Location()))
		{
			return true;
		}
	}
	return false;
}

// ----------------------------------------------------------------------------
// UnitGroup member functions

UnitGroup::UnitGroup(int _pNo, MapZone _zone)
{
	aiNum = _pNo;
	groupZone = _zone;
	internalGroup = CreateFightGroup(_pNo);
}

UnitGroup::~UnitGroup()
{
	if (internalGroup.IsInitialized())
	{
		internalGroup.Destroy();
	}
}

int UnitGroup::GetNearestUnitDistance(UnitEx _unit)
{
	//
	return 0;
}

void UnitGroup::AddUnitToGroup(UnitEx _unit)
{
	unitsList.push_back(_unit);
	internalGroup.TakeUnit(_unit);
}

void UnitGroup::CheckTargets()
{
	// For each unit in the group, check if there are any undetected units within detection range.
	// If any are found, add them to the detected units list.

	// If this group is currently active, for each unit in the group, check if there are still detected targets within the "give up" range.
	// If so, have the group go after whichever potential target is closest (giving the current target a -3 modifier to distance, to make it harder to exploit the AI).
	// Otherwise, inactivate this group so that units resume regular patrolling behavior.

	// If this group is not currently active, check if there are any detected targets within chase range of any unit in the group.
	// If so, set that unit as the target and go active (cancel previous patrolling behavior and chase that unit).
}
//
namespace X5AI
{
	MapZone zones[NUMZONES];
	std::list<UnitGroup*> aiGroups;
	std::list<UnitEx> stealthedUnits;
	std::list<UnitEx> detectedUnits;
	std::list<UnitEx> aiUnits;

	void AddGroup(UnitGroup *newGroup)
	{
		aiGroups.push_back(newGroup);
	}

	MapZone* GetUnitZone(UnitEx unit)
	{
		for (int i = 0; i < NUMZONES; i++)
		{
			if (zones[i].CheckUnitInZone(unit))
			{
				return &zones[i];
			}
		}
		return nullptr;
	}

}