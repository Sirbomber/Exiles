#pragma once

#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>
#include <OP2Types\OP2Units.h>

#include <list>
#include <vector>

// AI units are each assigned to a group, and each group is assigned to a map zone.
// Groups can be in "active" or "idle" mode.  When active, they are pursuing a detected player unit.  When idle, they are standing ground or patrolling the map.
// Player units can lose their "detected" status if they keep their lights off while they transition between zones (unless at least one unit in an active group is within detection range).

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
	void CheckTargets();

	bool UnitIsInGroup(UnitEx _unit);
	void AddUnitToGroup(UnitEx _unit);
	bool GroupIsEmpty() { return unitsList.empty(); }
	
	int GetUnitToUnitDistance(LOCATION l1, LOCATION l2);
	void RecalculateGroupMidpoint();

	void CheckBlight();

protected:
	void RemoveDeadUnitsFromGroup();

	int aiNum;
	std::list<UnitEx> unitsList;
	MapZone groupZone;
	FightGroup internalGroup;

	bool isActive,			// Set if this group is chasing a target.  Will suspend regular patrol actions until the target is destroyed or escapes.
		leavingMap;			// Set if the Blight gets too close to this group.  Will end regular patrol actions and cause the group to head to the bottom right corner of the map.
	
	UnitEx curTarget;		// Vehicle we're currently pursuing.  So long as a detected vehicle is still alive and <7 tiles away, reset the lastOrdersTick.  If another detected unit is < (distance of curTarget +2) tiles away, that unit becomes the new target.  Distance is calculated by averaging the distance of all units in the group to the target/candidate vehicles.
	int lastOrdersTick;		// Set to -1 and resume original behavior if this ever exceeds 8000 ticks (8 marks).
	
	LOCATION avgLocation;	// The midpoint between all units in the group.
	int lastRecalcTick;		// avgLocation doesn't need to be recalculated every 4 ticks.  Keep track of when we last did that.

};

// ----------------------------------------------------------------------------
// Patrol and wait unit group class.  Units in these groups will move to an area, guard it for awhile, then move to another area to do the same.
class GuardWatchGroup : public UnitGroup
{
public:
	GuardWatchGroup(int _pNo, MapZone _zone, std::initializer_list<MAP_RECT> _rects, int _waitTime, int _startAt = 1, bool _reverseAtEnd = false) : UnitGroup(_pNo, _zone)
	//GuardWatchGroup(int _pNo, MapZone _zone, MAP_RECT _rect1, MAP_RECT _rect2, int _waitTime) : UnitGroup(_pNo, _zone)
	{
		//guardRect[0] = _rect1;
		//guardRect[1] = _rect2;
		guardRects = _rects;
		ticksToWait = _waitTime;
		lastChangeTick = TethysGame::Tick();
		//internalGroup.SetRect(_rect2);
		internalGroup.SetRect(guardRects[_startAt]);
		curWpt = _startAt;
		reverseCourse = _reverseAtEnd;

		// Sanity/safety checks
		if (_startAt >= guardRects.size())
		{
			TethysGame::AddMessage(-1, -1, "Error in GuardWatchGroup: startAt out of bounds!", -1, sndDirt);
			curWpt = 0;
		}
		if (guardRects.size() == 1)
		{
			TethysGame::AddMessage(-1, -1, "Error in GuardWatchGroup: only 1 rect defined!", -1, sndDirt);
			guardRects[1] = guardRects[0];
		}
		else if (guardRects.size() == 0)
		{
			TethysGame::AddMessage(-1, -1, "Error in GuardWatchGroup: no rects defined!", -1, sndDirt);
			guardRects[0] = MAP_RECT(1 + 31, 1 - 1, 3 + 31, 3 - 1);
			guardRects[1] = guardRects[0];
		}
	};

	void GroupStatusUpdate();

private:
	//MAP_RECT guardRect[2];
	std::vector<MAP_RECT> guardRects;
	int ticksToWait,
		lastChangeTick;
	//bool usingAlternate = true;	// Start with them in "alternate" mode (but spawn them in their "regular" area) so when the mission starts they're moving around.
	int curWpt;
	bool reverseCourse,				// Normally, when reaching the end of its patrol route, the group will return to the first waypoint in the list.  If this is set, it will reverse course, going back to each waypoint until it reaches the first one again.
		reversing;                  // Set if group is currently going backwards
};

// ----------------------------------------------------------------------------
// Roaming patrol unit group class.  Units in these groups will constantly patrol between waypoints, never stopping to wait.
class PatrolGroup : public UnitGroup
{
public:
	PatrolGroup(int _pNo, MapZone _zone, LOCATION **_waypoints) : UnitGroup(_pNo, _zone)
	{
		//route.waypoints = _waypoints;
		patrolWpts = new LOCATION[8];
		for (int i = 0; i < 8; i++)
		{
			patrolWpts[i].x = (*_waypoints)[i].x;
			patrolWpts[i].y = (*_waypoints)[i].y;
			
			if ((*_waypoints)[i].x == -1)
			{
				break;
			}
		}
		route.waypoints = patrolWpts;
		internalGroup.SetPatrolMode(route);
	}
	~PatrolGroup()
	{
		delete patrolWpts;
	}

	void GroupStatusUpdate();

private:
	PatrolRoute route;
	LOCATION *patrolWpts;
};

// ----------------------------------------------------------------------------
// Guard an area unit group class.  These units will sit and wait at an area, never moving until they spot something to shoot at.
class CampGroup : public UnitGroup
{
public:
	CampGroup(int _pNo, MapZone _zone, MAP_RECT _idleArea) : UnitGroup(_pNo, _zone)
	{
		idleRect = _idleArea;
		internalGroup.SetRect(_idleArea);
	}

	void GroupStatusUpdate();

private:
	MAP_RECT idleRect;
};

// ----------------------------------------------------------------------------
// Special logic for the ESG Panthers that are always firing at the ground to block a path.
class EsgSpecial : public UnitGroup
{
public:
	EsgSpecial(int _pNo, MapZone _zone, MAP_RECT _idleArea, LOCATION _fireAt) : UnitGroup(_pNo, _zone)
	{
		idleRect = _idleArea;
		internalGroup.SetRect(_idleArea);
		esgLoc = _fireAt;
	}

	void GroupStatusUpdate();

private:
	MAP_RECT idleRect;
	LOCATION esgLoc;
};

// ----------------------------------------------------------------------------
namespace X5AI
{
	const int NUMZONES = 9;				// Total number of unique AI zones
	const int AI_DETECT_RANGE = 5;		// How close a stealthed unit has to be for the AI to detect it
	const int AI_CHASE_RANGE = 12;		// How close a detected unit has to be for a group to chase after it
	const int AI_GIVEUP_RANGE = 18;		// Detected units will be re-added to the stealthed list if at least this far away from an AI unit
	const int AI_BLIGHT_RANGE = 48;		// How close the Blight has to be before unit groups try to escape.

	extern int numAI;
	extern MapZone zones[NUMZONES];
	extern std::list<UnitGroup*> aiGroups;
	extern std::list<UnitEx> stealthedUnits;
	extern std::list<UnitEx> detectedUnits;

	void AddGroup(UnitGroup *newGroup);
	MapZone* GetUnitZone(UnitEx unit);

	void DetectPlayerUnits();
	void ForgetPlayerUnits();
	int AiUnitWithinRange(LOCATION _l, int _r);			// Returns a unit ID (or 0 if no unit found)
	bool InfectedTileWithinRange(LOCATION _l, int _r);	// Note that this only checks tiles to the left, since that's where the Blight comes from.

	void GroupManagement();
}

// ----------------------------------------------------------------------------
