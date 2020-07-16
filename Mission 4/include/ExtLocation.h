#ifndef EXTLOCATION_H
#define EXTLOCATION_H


// Undefine this if either of your map's dimensions are (somehow) not powers of two
#define EXTLOCATION_MAPSIZE_IS_PWR_OF_2


#ifdef EXTLOCATION_MAPSIZE_IS_PWR_OF_2
#define WrappedCoord(coord, mask) mask & coord
#else
#define WrappedCoord(coord, mask) coord % (mask + 1)
#endif

#include <Outpost2DLL.h>

// Extensions of the LOCATION struct
struct LocationEx : LOCATION
{
public:
	LocationEx(int tileX, int tileY);
	LocationEx(LOCATION location);
	LocationEx();
	LOCATION ToPixels();
	LOCATION FromPixels();
	LOCATION Wrapped();
	void Wrap();
	LOCATION WrappedXY();
	void WrapXY();
	LOCATION MapOffsetted();
	void MapOffset();
	LOCATION Clipped();
	LOCATION Added(const LOCATION &vector);
	LOCATION Normalized();
};


// This derivative of LocationEx (which is derived from LOCATION) automatically adds the map tile offsets to the x and y values when instantiated
struct MapLocation : LocationEx
{
public:
	MapLocation(int tileX, int tileY);
	MapLocation(LOCATION location);
	MapLocation();
};


// Splits LOCATION into two arguments of x, y; use for function calls that take int x, int y instead of LOCATION
#define SplitLoc(location) location.x, location.y
// Splits MAP_RECT into four arguments of x1, y1, x2, y2; use for function calls that take int x1, int y1, int x2, int y2 instead of MAP_RECT
#define SplitRect(rect) rect.x1, rect.y1, rect.x2, rect.y2

#endif