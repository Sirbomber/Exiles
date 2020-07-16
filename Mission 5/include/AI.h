#pragma once

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <list>

// AI units are each assigned to a group, and each group is assigned to a map zone.
// Groups can be in "active" or "idle" mode.  When active, they are pursuing a detected player unit.  When idle, they are standing ground or patrolling the map.
// Player units can lose their "detected" status if they keep their lights off while they transition between zones (unless at least one unit in an active group is within 8 tiles of them).

// ----------------------------------------------------------------------------
// Class for describing map geography.
class MapZone
{
public:
	MapZone();
	~MapZone();

	void AddRectToZone(MAP_RECT _rect);
	bool CheckUnitInZone(Unit _unit);
	std::list<MAP_RECT> test_GetZones() { return zoneRects; }
private:
	std::list<MAP_RECT> zoneRects;
};

// ----------------------------------------------------------------------------
// Parent unit group class.  Used as a template for the other unit group types, which all have special behavior.
class UnitGroup
{
public:
	UnitGroup(int _pNo, MapZone _zone);
	~UnitGroup();

	virtual void GroupStatusUpdate() = 0;
	int GetNearestUnitDistance(UnitEx _unit);
	void AddUnitToGroup(UnitEx _unit);

	void CheckTargets();

	
protected:
	int aiNum;
	std::list<UnitEx> unitsList;
	MapZone groupZone;
	bool isActive = false;
	FightGroup internalGroup;
	UnitEx curTarget;
};

// ----------------------------------------------------------------------------
// Patrol and wait unit group class.  Units in these groups will move to an area, guard it for awhile, then move to another area to do the same.
class GuardWatchGroup : public UnitGroup
{
public:
	GuardWatchGroup(int _pNo, MapZone _zone, MAP_RECT _rect1, MAP_RECT _rect2, int _waitTime) : UnitGroup(_pNo, _zone)
	{
		guardRect[0] = _rect1;
		guardRect[1] = _rect2;
		ticksToWait = _waitTime;
		lastChangeTick = TethysGame::Tick();
		internalGroup.SetRect(_rect2);
	};

	void GroupStatusUpdate()
	{
		CheckTargets();

		if (!isActive && TethysGame::Tick() > (lastChangeTick + ticksToWait))
		{
			internalGroup.ClearGuarderdRects();
			if (usingAlternate)
			{
				internalGroup.SetRect(guardRect[0]);
			}
			else
			{
				internalGroup.SetRect(guardRect[1]);
			}
			usingAlternate = !usingAlternate;
			lastChangeTick = TethysGame::Tick();

		}
	};

private:
	MAP_RECT guardRect[2];
	int ticksToWait,
		lastChangeTick;
	bool usingAlternate = true;	// Start with them in "alternate" mode so when the mission starts they're moving around.
};

// ----------------------------------------------------------------------------
// Roaming patrol unit group class.  Units in these groups will constantly patrol between waypoints, never stopping to wait.
class PatrolGroup : public UnitGroup
{
public:
	PatrolGroup(int _pNo, MapZone _zone, LOCATION _waypoints[]) : UnitGroup(_pNo, _zone)
	{
		route.waypoints = _waypoints;
		internalGroup.SetPatrolMode(route);
	};

	void GroupStatusUpdate()
	{
		//
	};

private:
	PatrolRoute route;
};

// ----------------------------------------------------------------------------
// Guard an area unit group class.  These units will sit and wait at an area, never moving until they spot something to shoot at.
class CampGroup : public UnitGroup
{
	//
};

// ----------------------------------------------------------------------------
// Special logic for the ESG Panthers that are always firing at the ground to block a path.
class EsgSpecial : public UnitGroup
{
	//
};

// ----------------------------------------------------------------------------
namespace X5AI
{
	const int NUMZONES = 6;				// Total number of unique AI zones
	const int AI_DETECT_RANGE = 2;		// How close a stealthed unit has to be for the AI to detect it
	const int AI_CHASE_RANGE = 12;		// How close a detected unit has to be for a group to chase after it
	const int AI_GIVEUP_RANGE = 24;		// Detected units will be re-added to the stealthed list if at least this far away from an AI unit

	extern MapZone zones[NUMZONES];
	extern std::list<UnitGroup*> aiGroups;
	extern std::list<UnitEx> stealthedUnits;
	extern std::list<UnitEx> detectedUnits;
	extern std::list<UnitEx> aiUnits;

	void AddGroup(UnitGroup *newGroup);
	MapZone* GetUnitZone(UnitEx unit);

}

// ----------------------------------------------------------------------------
