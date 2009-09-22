#ifndef STARFIELD_H
#define STARFIELD_H

#include "Emitter.h"
#include <vector>
using namespace std;
/*
A StarField effect using particles

TODO finish this class :P
*/

class StarField
{
    public:
        StarField();
        ~StarField();

    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #else
        void render();
    #endif
        void update();

        void setNumLayers(CRuint layers){emit.resize(layers);}    /// set the number of particle layers
        void setLayerMaxParticles(CRuint layer, CRuint max){emit.at(layer).setMax(max);}
        void setLayerMaxParticles(CRuint max){emit.back().setMax(max);}
        void setMaxParticles(CRuint max);

        void setLayerColour(CRuint layer, const Colour& col){emit.at(layer).setColour(col);}    /// Set layers Colour
        void setLayerColour(const Colour& col){emit.back().setColour(col);}                     /// Set last layer's Colour
        void setColour(const Colour& col);                                                      /// Set all layer's Colour

        void setLayerBounds(CRuint layer,const SDL_Rect& bounds){emit.at(layer).setBoundaries(bounds);} /// Set Layer's boundaries
        void setLayerBounds(const SDL_Rect& bounds){emit.back().setBoundaries(bounds);}                 /// Set last Layer's boundaries
        void setBounds(const SDL_Rect& bounds);                                                         /// Set all layer's boundaries


    private:
        vector <Emitter> emit;
};

#endif // STARFIELD_H
