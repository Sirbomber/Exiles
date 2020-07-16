#include <Outpost2DLL.h>
#include <hfl.h>
#include "OP2Types\OP2Map.h"
#include "ExtLocation.h"

LocationEx::LocationEx(int tileX, int tileY)
{
	this->x = tileX;
	this->y = tileY;
}

LocationEx::LocationEx(LOCATION location)
{
	this->x = location.x;
	this->y = location.y;
}

LocationEx::LocationEx()
{
	this->x = 0;
	this->y = 0;
}


LOCATION LocationEx::ToPixels()
{
	if (!isInited)
		return LOCATION(this->x, this->y);

	int tilePixelWidth = ((OP2Map*)mapObj)->pixelWidth / ((OP2Map*)mapObj)->tileWidth;
	return LOCATION((this->x * tilePixelWidth) + (tilePixelWidth / 2), (this->y * tilePixelWidth) + (tilePixelWidth / 2));
}


LOCATION LocationEx::FromPixels()
{
	if (!isInited)
		return LOCATION(this->x, this->y);

	int tilePixelWidth = ((OP2Map*)mapObj)->pixelWidth / ((OP2Map*)mapObj)->tileWidth;
	return LOCATION((this->x - (tilePixelWidth / 2)) / tilePixelWidth, (this->y - (tilePixelWidth / 2)) / tilePixelWidth);
}


LOCATION LocationEx::Wrapped()
{
	LocationEx ret = LocationEx(this->x, this->y);
	ret.Wrap();
	return ret;
}


void LocationEx::Wrap()
{
	if (!isInited)
		return;
	this->x = WrappedCoord(this->x, ((OP2Map*)mapObj)->tileXMask);
}


LOCATION LocationEx::WrappedXY()
{
	LocationEx ret = LocationEx(this->x, this->y);
	ret.WrapXY();
	return ret;
}


void LocationEx::WrapXY()
{
	if (!isInited)
		return;
	this->x = WrappedCoord(this->x, ((OP2Map*)mapObj)->tileXMask);
	this->y = WrappedCoord(this->y, (((OP2Map*)mapObj)->tileHeight - 1));
}


LOCATION LocationEx::MapOffsetted()
{
	LocationEx ret = LocationEx(this->x, this->y);
	ret.MapOffset();
	return ret;
}


void LocationEx::MapOffset()
{
	if (!isInited)
		return;

	this->x += ((OP2Map*)mapObj)->paddingOffsetTileX - 1;
	this->y += -1;
}


LOCATION LocationEx::Clipped()
{
	LOCATION ret = LOCATION(this->x, this->y);
	ret.Clip();
	return ret;
}


LOCATION LocationEx::Added(const LOCATION &vector)
{
	LOCATION ret = LOCATION(this->x, this->y);
	ret.Add(vector);
	return ret;
}


LOCATION LocationEx::Normalized()
{
	LOCATION ret = LOCATION(this->x, this->y);
	ret.Norm();
	return ret;
}



MapLocation::MapLocation(int tileX, int tileY)
{
	this->x = tileX;
	this->y = tileY;
	this->MapOffset();
}

MapLocation::MapLocation(LOCATION location)
{
	this->x = location.x;
	this->y = location.y;
	this->MapOffset();
}

MapLocation::MapLocation()
{
	this->x = 0;
	this->y = 0;
	this->MapOffset();
}