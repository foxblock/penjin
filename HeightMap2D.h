#ifndef HEIGHTMAP2D_H
#define HEIGHTMAP2D_H

#include "PenjinTypes.h"
#include "Sprite.h"
#include "Vector2df.h"
#include "Vector2di.h"
#include "Colour.h"
#include <vector>

enum InterpolationMode
{
    imMedian=0,
    imHighest,
    imLowest
};

class HeightMap2D
{
public:
    HeightMap2D();
    ~HeightMap2D();

    void clear();
    void clearImages();

    void loadImage(CRstring imageFile, const Colour& noCollisionColour);
    void addChunks(const vector<int>& chunks);

    uint getChunkSize() const {return chunkSize;};
    InterpolationMode getInterpolationMode() const {return imMode;};

    void generateHeightMap(CRuint newChunkSize, const InterpolationMode& newMode);

    int getHeight(CRint posX) const;

    int chunkCount() const {return map.size();};

    template <class T, class K>
    Vector2df hitTest(const T* const object, const K& objVel, CRuint stepSize) const;
    template <class T, class K, class L>
    Vector2df hitTest(const T* const object, const K* const objPos, const L& objVel, CRuint stepSize) const;

    Vector2df position;

    int getTotalWidth() const;
    int getTotalHeight() const;

    void render();
private:
    void flushCache(vector<int>& cache);

    vector<pair<Sprite*,Colour> > images;
    vector<int> map;
    InterpolationMode imMode;
    uint chunkSize;
};

#include "HeightMap2D.inl"

#endif
