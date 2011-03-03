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
*/#ifndef COLOUROBJECT_H
#define COLOUROBJECT_H

#include "RenderObject.h"
#include "Colour.h"

using Penjin::RenderObject;
using Penjin::Colour;

namespace Penjin
{
    class ColourObject : public RenderObject
    {
        public:
            /** Default constructor */
            ColourObject();
            /** Default destructor */
            virtual ~ColourObject();

            /**< Setter Methods */
            void setAlpha(CRuchar alpha);           /**< Sets the alpha component of the ColourObject */
            void setColour(const Colour& colour);   /**< Sets all Colour components of the ColourObject */

            /**< Getter Methods */
            uchar getAlpha();       /**< Returns the alpha component of the ColourObject */
            Colour getColour();     /**< Returns the alpha component of the ColourObject */

        protected:
            Colour* colour;

    };
}
#endif // COLOUROBJECT_H
