#include "HeightMap2D.h"

// TODO: Proper documentation and stuff

HeightMap2D::HeightMap2D()
{
    imMode = imMedian;
    chunkSize = 1;
    position = Vector2df(0,0);
}

HeightMap2D::~HeightMap2D()
{
    clear();
}

// Clear the whole data
void HeightMap2D::clear()
{
    clearImages();
    map.clear();
}

// Only delete images, keeps the actual height map data intact, so it can still be used
// Use this when you have to preserve memory (note that re-analysation is no longer possible then)
void HeightMap2D::clearImages()
{
    vector<pair<Sprite*,Colour> >::iterator I;
    for (I = images.begin(); I < images.end(); ++I)
        delete I->first;
    images.clear();
}

// Add an image to the collision landscape (aka HeightMap)
void HeightMap2D::loadImage(CRstring imageFile, const Colour& noCollisionColour)
{
    Sprite* temp = new Sprite;
    temp->loadSprite(imageFile);
    temp->disableTransparentColour();
    if (not images.empty())
    {
        // align all images so the bottom border is at the same height (they form a landscape)
        temp->setY(images.back().first->getHeight() + images.back().first->getY() - temp->getHeight());

        vector<pair<Sprite*,Colour> >::const_iterator I;
        for (I = images.begin(); I < images.end(); ++I)
            temp->setX(temp->getX() + I->first->getWidth());
    }
    images.push_back(make_pair(temp,noCollisionColour));
}

// Generate height data from the loaded images
void HeightMap2D::generateHeightMap(CRuint newChunkSize, const InterpolationMode& newMode)
{
    chunkSize = newChunkSize;
    imMode = newMode;
    map.clear();

    vector<int> cache;
    bool finished = false;
    vector<pair<Sprite*,Colour> >::const_iterator current = images.begin();
    int yPos = 0; // from the bottom
    int xPos = 0;

    while (not finished)
    {
        if (xPos >= current->first->getWidth())
        {
            ++current;
            if (current >= images.end())
            {
                finished = true;
                continue;
            }
            xPos = 0;
        }
        if (cache.size() >= chunkSize)
        {
            flushCache(cache);
        }

        if (current->first->getPixel(xPos,current->first->getHeight() - yPos - 1) != current->second)
        {
            while ((yPos < current->first->getHeight()) && (current->first->getPixel(xPos,current->first->getHeight() - yPos - 1) != current->second))
                ++yPos;
        }
        else
        {
            while ((yPos >= 0) && (current->first->getPixel(xPos,current->first->getHeight() - yPos - 1) == current->second))
                --yPos;
            ++yPos;
        }
        ++xPos;
        cache.push_back(yPos);
    }
    if (not cache.empty())
    {
        flushCache(cache);
    }
    #ifdef _DEBUG
    cout << "HeightMap2D: Analysis complete, " << map.size() << " chunks of size " << chunkSize << " have been created." << endl;
    #endif
}

// Get the height for posX based off the left border of the map
// posX in pixels and relative to HeightMap position (so 0 refers to the first column of pixels in the first image regardless of position offset)
int HeightMap2D::getHeight(CRint posX) const
{
    int pos = posX / chunkSize;
    if (pos >= map.size())
        return -1;
    return map[pos];
}

// Get the total width of all images (so all individual widths added up)
int HeightMap2D::getTotalWidth() const
{
    int result = 0;
    vector<pair<Sprite*,Colour> >::const_iterator I;
    for (I = images.begin(); I < images.end(); ++I)
        result += I->first->getWidth();
    return result;
}

// Get the total height, which just is the height of the first image as this is used for all references
int HeightMap2D::getTotalHeight() const
{
    if (images.empty())
        return -1;
    return images.front().first->getHeight();
}

// Debug: render the collision images to the screen
void HeightMap2D::render()
{
    vector<pair<Sprite*,Colour> >::iterator I;
    for (I = images.begin(); I < images.end(); ++I)
    {
        Sprite* temp = I->first;
        temp->setPosition(temp->getPosition() + position);
        temp->render();
        temp->setPosition(temp->getPosition() - position);
    }
}

// Private: add a vector of integers, forming one chunk, to the map
void HeightMap2D::flushCache(vector<int>& cache)
{
    int value = 0;
    switch (imMode)
    {
    case imMedian:
    {
        while (not cache.empty())
        {
            value += cache.back();
            cache.pop_back();
        }
        value /= chunkSize;
        break;
    }
    case imHighest:
    {
        while (not cache.empty())
        {
            value = max(value,cache.back());
            cache.pop_back();
        }
        break;
    }
    case imLowest:
    {
        value = INT_MAX;
        while (not cache.empty())
        {
            value = min(value,cache.back());
            cache.pop_back();
        }
        break;
    }
    } // switch
    map.push_back(value);
    cache.clear();
}
