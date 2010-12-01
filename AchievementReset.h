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
#ifndef ACHIEVEMENTRESET_H
#define ACHIEVEMENTRESET_H

///------------------------------
/// Reset Achievement class
/// by foxblock 10/12/09
///
/// Like AchievementCount - only one increasing event, but multiple events
/// which reset the count or decrease it
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementReset : public Achievement
{
    public:
        AchievementReset();

        virtual void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
};

#endif // ACHIEVEMENTRESET_H


