#include "Animation.h"

PENJIN_ERRORS Animation::loadFrame(CRstring fileName){return image.loadImageNoKey(fileName);}

PENJIN_ERRORS Animation::loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){image.clear(); animationTimer.start(); return image.loadImageSheetNoKey(fileName, xTiles, yTiles);}
