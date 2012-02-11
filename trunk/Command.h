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
#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
using namespace std;
#include "Variable.h"
#include "PenjinTypes.h"

class Command
{
public:
	Command()
	{
		commandType = -1;
		params.clear();
	}
	Command(ushort type)
	{
		commandType = type;
		params.clear();
	}
	~Command(){};

	int getCommand(string name)
	{
	/*	if (name == "MAP")
			return MAP;
		else if (name == "CAM")
			return MOVE_CAM;
		else if (name == "STOP_CAM")
			return STOP_CAM;
		else if (name == "SHIP_POS")
			return SHIP_POS;
		else if (name == "PLAYER")
			return MOVE_SHIP;
		else if (name == "STOP_PLAYER")
			return STOP_SHIP;
		else if (name == "LOAD_VIDEO" )
			return LOAD_VID;
		else if (name == "LOAD_SOUND")
			return LOAD_SOUND;
		else if (name == "LOAD_MUSIC")
			return LOAD_MUSIC;
		else if (name == "SOUND_PROPS")
			return SET_SOUND_PROPS;
		else if (name == "MUSIC_PROPS")
			return SET_MUSIC_PROPS;
		else if (name == "VIDEO_PROPS")
			return SET_VID_PROPS;
		else if (name == "PLAY_VIDEO")
			return PLAY_VID;
		else if (name == "PLAY_MUSIC")
			return PLAY_MUSIC;
		else if (name == "PLAY_SOUND")
			return PLAY_SOUND;
		else if (name == "STOP_VIDEO")
			return STOP_VID;
		else if (name == "STOP_MUSIC")
			return STOP_MUSIC;
		else if (name == "STOP_SOUND")
			return STOP_SOUND;
		else if (name == "DELAY")
			return DELAY;
		else if (name == "START_COMBINE")
			return START_COMBINE;
		else if (name == "END_COMBINE")
			return END_COMBINE;
		else if (name == "SKIP")
			return SKIP;
		else if (name == "END_INIT")
			return END_INIT;
		else if (name == "END_SCRIPT")
			return END_SCRIPT;
		else
			return PARSE_ERROR;
*/
return -1;
	}
	int commandType;
    vector <Variable> params;//	Stores the params of the file
private:


};
#endif	//	COMMAND_H
