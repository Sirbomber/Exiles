#include <Outpost2DLL.h>
#include <OP2Helper.h>
#include <HFL.h>

#include "AI.h"

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

	isActive = false;
	leavingMap = false;
	curTarget.unitID = 0;
	lastOrdersTick = -1;
	avgLocation = LOCATION(-1, -1);
	lastRecalcTick = 100;
}

UnitGroup::~UnitGroup()
{
	if (internalGroup.IsInitialized())
	{
		internalGroup.Destroy();
	}
}

bool UnitGroup::UnitIsInGroup(UnitEx _unit)
{
	if (!_unit.IsLive() || !_unit.OwnerID() == X5AI::numAI)
	{
		return false;
	}
	else
	{
		std::list<UnitEx>::iterator i = unitsList.begin();
		while (i != unitsList.end())
		{
			if (i->unitID == _unit.unitID)
			{
				return true;
			}
			i++;
		}
	}
	return false;
}

void UnitGroup::AddUnitToGroup(UnitEx _unit)
{
	unitsList.push_back(_unit);
	internalGroup.TakeUnit(_unit);
}

void UnitGroup::RecalculateGroupMidpoint()
{
	// Only do this (roughly) every mark
	if (TethysGame::Tick() > (lastRecalcTick + 100))
	{
		// Calculate average position
		int x = 0, y = 0, total = 0;
		std::list<UnitEx>::iterator i = unitsList.begin();
		while (i != unitsList.end())
		{
			if (i->IsLive())
			{
				x += i->Location().x;
				y += i->Location().y;
				total++;
			}
			i++;
		}
		if (total > 0)
		{
			avgLocation = LOCATION(x / total, y / total);
		}

		// Update the recalc timer
		lastRecalcTick = TethysGame::Tick();
	}
}

void UnitGroup::RemoveDeadUnitsFromGroup()
{
	std::list<UnitEx>::iterator i = unitsList.begin();
	while (i != unitsList.end())
	{
		// Unit is dead; remove it from the list.
		if (!i->IsLive())
		{
			unitsList.erase(i++);
		}
		else
		{
			i++;
		}
	}
}

void UnitGroup::CheckTargets()
{
	// Sanity check
	if (avgLocation.x == -1)
	{
		return;
	}

	// Find the nearest (already detected) player unit (in this group's AI zone)
	UnitEx closestUnit;
	closestUnit.unitID = 0;
	int dist = 99999, temp;
	for (std::list<UnitEx>::iterator i = X5AI::detectedUnits.begin(); i != X5AI::detectedUnits.end(); i++)
	{
		if (i->IsLive() && groupZone.CheckUnitInZone(*i))
		{
			if (temp = GetUnitToUnitDistance(avgLocation, i->Location()) < dist)
			{
				dist = temp;
				closestUnit.unitID = i->unitID;
			}
		}
	}

	// If group is active:
	//  If the found closest unit is outside of give up range, or we've taken too long tracking them, revert to inactive mode and resume patrolling behavior.
	//  If the closest unit is the same as the current target unit, refresh the lastOrdersTick if it's still within chasing range.
	//  If the closest unit is less than (distance from current target + 2) tiles away, switch to chasing that unit (so long as it's within chase range).
	if (isActive)
	{
		if (dist > X5AI::AI_GIVEUP_RANGE || lastOrdersTick > 8000 || closestUnit.unitID == 0)
		{
			isActive = false;
			curTarget.unitID = 0;
			lastOrdersTick = -1;
		}

		else if (curTarget.unitID != 0 && closestUnit.unitID == curTarget.unitID)
		{
			if (dist <= X5AI::AI_CHASE_RANGE)
			{
				lastOrdersTick = TethysGame::Tick();
			}
		}

		else if (dist < GetUnitToUnitDistance(avgLocation, curTarget.Location()) + 2 && dist <= X5AI::AI_CHASE_RANGE)
		{
			curTarget.unitID = closestUnit.unitID;
			lastOrdersTick = TethysGame::Tick();
		}
	}

	// Group is not active.  Check if there's a unit it should chase and, if so, cease patrolling operations and pursue it!
	else
	{
		if (dist <= X5AI::AI_CHASE_RANGE && closestUnit.unitID != 0)
		{
			isActive = true;
			curTarget.unitID = closestUnit.unitID;
			lastOrdersTick = TethysGame::Tick();
		}
	}
}

int UnitGroup::GetUnitToUnitDistance(LOCATION l1, LOCATION l2)
{
	// Manhattan/taxicab distance
	return abs(l1.x - l2.x) + abs(l1.y - l2.y);
}

void UnitGroup::CheckBlight()
{
	// Blight isn't even a threat until roughly mark 180, so do nothing until then.
	if (TethysGame::Tick() < 18000 || leavingMap)
	{
		return;
	}

	if (X5AI::InfectedTileWithinRange(avgLocation, X5AI::AI_BLIGHT_RANGE))
	{
		leavingMap = true;
		internalGroup.ClearGuarderdRects();
		internalGroup.ClearPatrolMode();
		internalGroup.SetRect(MAP_RECT(256 + 31, 63 - 1, 257 + 31, 64 - 1));
	}
}

// ----------------------------------------------------------------------------

void GuardWatchGroup::GroupStatusUpdate()
{
	RemoveDeadUnitsFromGroup();
	RecalculateGroupMidpoint();
	bool wasActive = isActive;
	CheckTargets();
	CheckBlight();

	if (!isActive)
	{
		if (wasActive)
		{
			if (leavingMap)
			{
				internalGroup.SetRect(MAP_RECT(256 + 31, 63 - 1, 257 + 31, 64 - 1));
			}
			else
			{
				if (usingAlternate)
				{
					internalGroup.SetRect(guardRect[0]);
				}
				else
				{
					internalGroup.SetRect(guardRect[1]);
				}
			}
		}

		else if (TethysGame::Tick() > (lastChangeTick + ticksToWait) && !leavingMap)
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
	}
	else/* if (isActive && !wasActive)*/
	{
		if (curTarget.unitID != 0)	// Should be impossible, but a waste of a check is better than crashing
		{
			if (!wasActive)
			{
				internalGroup.ClearGuarderdRects();
			}
			for (std::list<UnitEx>::iterator i = unitsList.begin(); i != unitsList.end(); i++)
			{
				if (i->IsLive())
				{
					i->Unit::DoAttack(curTarget);
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

void PatrolGroup::GroupStatusUpdate()
{
	RemoveDeadUnitsFromGroup();
	RecalculateGroupMidpoint();
	bool wasActive = isActive;
	CheckTargets();
	CheckBlight();

	if (!isActive)
	{
		if (wasActive)
		{
			if (leavingMap)
			{
				internalGroup.SetRect(MAP_RECT(256 + 31, 63 - 1, 257 + 31, 64 - 1));
			}
			else
			{
				internalGroup.SetPatrolMode(route);
			}
		}
	}
	else
	{
		if (curTarget.unitID != 0)
		{
			if (!wasActive)
			{
				internalGroup.ClearPatrolMode();
			}

			for (std::list<UnitEx>::iterator i = unitsList.begin(); i != unitsList.end(); i++)
			{
				if (i->IsLive())
				{
					i->Unit::DoAttack(curTarget);
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

void CampGroup::GroupStatusUpdate()
{
	RemoveDeadUnitsFromGroup();
	RecalculateGroupMidpoint();
	bool wasActive = isActive;
	CheckTargets();
	CheckBlight();

	if (!isActive)
	{
		if (wasActive)
		{
			if (leavingMap)
			{
				internalGroup.SetRect(MAP_RECT(256 + 31, 63 - 1, 257 + 31, 64 - 1));
			}
			else
			{
				internalGroup.SetRect(idleRect);
			}
		}
	}
	else
	{
		if (curTarget.unitID != 0)
		{
			if (!wasActive)
			{
				internalGroup.ClearGuarderdRects();
			}

			for (std::list<UnitEx>::iterator i = unitsList.begin(); i != unitsList.end(); i++)
			{
				if (i->IsLive())
				{
					i->Unit::DoAttack(curTarget);
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

void EsgSpecial::GroupStatusUpdate()
{
	RemoveDeadUnitsFromGroup();
	RecalculateGroupMidpoint();
	bool wasActive = isActive;
	CheckTargets();
	CheckBlight();

	if (!isActive)
	{
		if (wasActive)
		{
			if (leavingMap)
			{
				internalGroup.SetRect(MAP_RECT(256 + 31, 63 - 1, 257 + 31, 64 - 1));
			}
			else
			{
				internalGroup.SetRect(idleRect);
			}
		}

		if (!leavingMap)
		{
			for (std::list<UnitEx>::iterator i = unitsList.begin(); i != unitsList.end(); i++)
			{
				if (idleRect.Check(i->Location()))
				{
					i->DoAttack(esgLoc);
				}
			}
		}
	}
	else
	{
		if (curTarget.unitID != 0)
		{
			if (!wasActive)
			{
				internalGroup.ClearGuarderdRects();
			}

			for (std::list<UnitEx>::iterator i = unitsList.begin(); i != unitsList.end(); i++)
			{
				if (i->IsLive())
				{
					i->Unit::DoAttack(curTarget);
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

namespace X5AI
{
	extern int numAI = -1;
	MapZone zones[NUMZONES];
	std::list<UnitGroup*> aiGroups;
	std::list<UnitEx> stealthedUnits;
	std::list<UnitEx> detectedUnits;
	std::list<UnitEx> aiUnits;
}

void X5AI::AddGroup(UnitGroup *newGroup)
{
	aiGroups.push_back(newGroup);
}

MapZone* X5AI::GetUnitZone(UnitEx unit)
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

void X5AI::DetectPlayerUnits()
{
	// Check all currently stealthed player units and see if they're within detection range of an AI unit or have their lights on
	std::list<UnitEx>::iterator i = stealthedUnits.begin();
	while (i != stealthedUnits.end())
	{
		// Unit is dead; remove it from the list.
		if (!i->IsLive())
		{
			stealthedUnits.erase(i++);
		}

		else
		{
			// Lights are on or an AI unit spotted the unit, move it to the detected units list
			if (i->GetLights() || AiUnitWithinRange(i->Location(), AI_DETECT_RANGE)) //&& i->GetType() != mapTiger /* debug */)
			{
				detectedUnits.push_back(*i);
				stealthedUnits.erase(i++);
			}

			else
			{
				i++;
			}
		}

	}
}

void X5AI::ForgetPlayerUnits()
{
	// Check all currently detected player units and see if they've moved out of range of all AI units and have their lights off
	std::list<UnitEx>::iterator i = detectedUnits.begin();
	while (i != detectedUnits.end())
	{
		// Unit is dead; remove it from the list.
		if (!i->IsLive())
		{
			detectedUnits.erase(i++);
		}

		else
		{
			Unit found;
			// Lights are off and no AI units in range, remove from detected units list and add it back to the stealthed units list.
			if (!i->GetLights() && !AiUnitWithinRange(i->Location(), AI_GIVEUP_RANGE))
			{
				stealthedUnits.push_back(*i);
				detectedUnits.erase(i++);
			}

			else
			{
				i++;
			}
		}
	}
}

void X5AI::GroupManagement()
{
	// Iterate over each group
	std::list<UnitGroup*>::iterator aigIt = X5AI::aiGroups.begin();
	while (aigIt != X5AI::aiGroups.end())
	{
		if ((*aigIt)->GroupIsEmpty())
		{
			delete *aigIt;
			X5AI::aiGroups.erase(aigIt++);
		}
		else
		{
			(*aigIt)->GroupStatusUpdate();
			aigIt++;
		}
	}
}

int X5AI::AiUnitWithinRange(LOCATION _l, int _r)
{
	// Check if there are any AI units within range of this unit.
	Unit next;
	for (int y = _l.y - _r;
		y <= _l.y + _r;
		y++)
	{
		for (int x = _l.x - (_r - abs(y - _l.y));
			x <= _l.x + (_r - abs(y - _l.y));
			x++)
		{
			if (x < 0 || y < 0 || x > 256 + 31 || y > 63 || (_l.x == x && _l.y == y))
			{
				continue;
			}

			next.unitID = 0;
			next.unitID = GameMapEx::GetTileEx(LOCATION(x,y)).unitIndex;
			if (next.unitID != 0 && next.OwnerID() == X5AI::numAI)
			{
				return next.unitID;
			}
		}
	}

	return 0;
}

bool X5AI::InfectedTileWithinRange(LOCATION _l, int _r)
{
	// Check if there are any infected tiles within range of this unit.
	for (int y = _l.y - _r;
		y <= _l.y + _r;
		y++)
	{
		for (int x = _l.x - (_r - abs(y - _l.y));
			x <= _l.x;
			x++)
		{
			if (x < 0 || y < 0 || x > 256 + 31 || y > 63 || (_l.x == x && _l.y == y))
			{
				continue;
			}

			if (GameMapEx::GetTileEx(LOCATION(x, y)).microbe)
			{
				return true;
			}
		}
	}

	return false;
}
