//----------------------
// template functions implementation
//----------------------

// Collision testing agains any Penjin object which supports position and size (CollisionRegion and Sprite for example)
// objVel is the velocity the object is moving at, stepSize is the maximum height the object can overcome when moving one pixel horizontally
// It returns a vector by which objVel has to be corrected to conform to the height map (so you should add it to the velocity)
template <class T, class K>
Vector2df HeightMap2D::hitTest(const T* const object, const K& objVel, CRuint stepSize) const
{
    Vector2df proPos = object->getPosition() + objVel;
    proPos.y += object->getHeight();

    Vector2df correction(0,0);
    int length = object->getWidth()-1;
    int corrArray[length];

    for (int I = 0; I < object->getWidth(); ++I)
    {
        corrArray[I] = max(correction.y, proPos.y - position.y - getTotalHeight() + getHeight(proPos.x + I - position.x));
    }

    // determining the index of the greatest value in the array (I)
    int max = length - 1;
    for (int I = length - 2; I >= 0; --I)
    {
        if (corrArray[I] > corrArray[max])
        {
            max = I;
        }
    }

    int I = max;
    if (objVel.x != 0)
    {
        if (corrArray[max] > (stepSize + objVel.y))
        {
            if (objVel.x > 0)
            {
                --I;
                while (I >= 0 && corrArray[I] > (stepSize + objVel.y))
                    --I;
                // if loop ran out of bounds, just apply y-correction
                if (I < 0)
                    I = max;
                else
                    correction.x = (object->getWidth() - I - 2) * -1;
            }
            else
            {
                ++I;
                while (I < object->getWidth() && corrArray[I] > (stepSize + objVel.y))
                    ++I;
                if (I > length)
                    I = max;
                else
                    correction.x = max + 1;
            }
        }
    }
    correction.y = corrArray[I] * -1;

    return correction;
}

// Using external positioning (on top of the internal position in object)
template <class T, class K, class L>
Vector2df HeightMap2D::hitTest(const T* const object, const K* const objPos, const L& objVel, CRuint stepSize) const
{
    // implementation missing because I am a lazy fuck
}
