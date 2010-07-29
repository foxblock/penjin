#ifndef SPHERE_H
#define SPHERE_H
#include "PenjinTypes.h"
#include "Colour.h"
#include <vector>

class Sphere
{
    public:
        Sphere();
        ~Sphere();

        void setRadius(CRfloat r);
        void setSegmentsH(CRuint s);
        void setSegmentsV(CRuint s);

        void render();

    private:
        void refresh(); //  recalc vertices if something changed
        uint Hsegs;
        uint Vsegs;
        float radius;
        vector<float> verts;
        Colour colour;
};

#endif // SPHERE_H
