#ifndef OP2GRAPHICS_H
#define OP2GRAPHICS_H

#pragma pack(push,1)

struct OP2Bitmap {
  int width;           // 0x0
  int height;          // 0x4
  int pitch;           // 0x8
  int bitDepth;        // 0xC
  int imageBufferSize; // 0x10 [((pitch * bitDepth) / 8) * height]
  char* imageBuffer;   // 0x14 char[imageBufferSize]*
  void* palette;       // 0x18
  int flags;           // 0x1C **
};

#define MAX_LIGHT_LEVELS 32

struct OP2BmpManager : public OP2Bitmap {
  int numLightLevels;  // 0x20
  int unk1;            // 0x24
  int drawMethod;      // 0x28
  void* lightLevelPal; // 0x2C short[256 * numLightLevels]*
  char mappedPlayerColorIndex[MAX_LIGHT_LEVELS]; // 0x30
  int unk2;            // 0x50
  void* lightLevelPals[MAX_LIGHT_LEVELS]; // 0x54 - 0xD0, objects are 48 bytes each
  int unk3[2];         // 0xD4 - 0xD8
};

struct OP2Tileset : public OP2BmpManager {
  int numTiles;        // 0xDC
  int numTilesRequest; // 0xE0
  int unk3[2];         // 0xE4 - 0xE8
  int tileHeight;      // 0xEC
  int tilesetHeight;   // 0xF0
  int bytesPerTile;    // 0xF4
  char* pixelData;     // 0xF8 char[numTiles * bytesPerTile]*, not imageBufferSize
                       //      duplicate of imageBuffer ptr, used for drawing tiles
};

struct OP2Prt : public OP2BmpManager {
  void*  hFile;        // 0xDC
  void*  hMapping;     // 0xE0
  char*  bmpFileData;  // 0xE4
  int    fileSize;     // 0xE8
  char*  pixelData;    // 0xEC (duplicate of imageBuffer)
  int    unknown[3];   // 0xF0-0xF8
};

struct OP2Rect
{
  int left;
  int top;
  int right;
  int bottom;
};


struct OP2FrameComponentInfo
{
  short pixelXOffset;
  short pixelYOffset;
  short imageInfoIndex;
};


struct OP2FrameOptionalInfo
{
  char offsetX;
  char offsetY;
  char unknown[2]; // **
};


struct OP2FrameInfo
{
  struct
  {
    short left;
    short top;
    short right;
    short bottom;
  } rect;
  short numFrameComponents;
  OP2FrameComponentInfo *frameComponentInfo;
};


struct OP2Graphics
{
  char* unk_palData; // **
  int unk_palSize; // **
  struct ImageInfo
  {
    int scanlineByteWidth;
    int dataOffset;
    int height;
    int width;
    short typeFlags;
    short paletteIndex;
  } imageInfo[5608];
  int numImages;
  struct AnimationInfo
  {
    int unknown; // **
    OP2Rect selectionBox;
    int pixelXDisplacement;
    int pixelYDisplacement;
    int unknown2; // **
    int numFrames;
    OP2FrameInfo **frameInfo;
    short frameOptionalInfoStartIndex;
  } animationInfo[2176];
  int numAnimations;
  void* bmpManager;
  OP2FrameInfo** frameInfo;
  OP2FrameComponentInfo** frameComponentInfo;
  OP2FrameOptionalInfo** frameOptionalInfo;
};

union Rgb555 {
  struct {
    unsigned short  b : 5;
    unsigned short  g : 5;
    unsigned short  r : 5;
    unsigned short  a : 1;
  };

  unsigned short  u16All;
};

struct BitmapCopyInfo {
    void*  pSrc;
    void*  pDst;
    int    unknown[2];
    int    srcWidth;
    int    srcHeight;
    int    srcPitch;
    int    dstPitch;
    int    drawMethod;
    void*  pDarkPal16;
};

#pragma pack(pop)

#endif