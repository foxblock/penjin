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

        template <class T>
        void setPosition(const T& p){position.x = p.x;position.y=p.y;position.z=p.z;}
        void setColour(const Colour& c){colour = c;}
        void setAlpha(CRfloat a){colour.alpha = a;}

        void render();

    private:
        void refresh(); //  recalc vertices if something changed
        uint Hsegs;
        uint Vsegs;
        float radius;
        vector<float> verts;
        Colour colour;
        Vector3df position;
};

#endif // SPHERE_H
