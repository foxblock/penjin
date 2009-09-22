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
