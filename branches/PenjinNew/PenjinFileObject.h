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
*/#ifndef PENJINFILEOBJECT_H
#define PENJINFILEOBJECT_H

#include "PenjinObject.h"
#include <string>
using std::string;
#include "PenjinErrors.h"

class PenjinFileObject : public PenjinObject
{
    public:
        /** Default constructor */
        PenjinFileObject();
        /** Default destructor */
        virtual ~PenjinFileObject();

        virtual PenjinErrors::PENJIN_ERRORS load(const string& fileName)=0;
        virtual PenjinErrors::PENJIN_ERRORS save(const string& fileName)=0;

    protected:
        string fileName;    //we keep a copy of the the filename if needed.
    private:
};

#endif // PENJINFILEOBJECT_H
