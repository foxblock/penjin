/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
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
