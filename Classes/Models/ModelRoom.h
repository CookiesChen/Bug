#ifndef __MODEL_ROOM_H__
#define __MODEL_ROOM_H__

#include <string>

using namespace std;

class ModelRoom final
{
public:
    int Id;
    string OwnId;
    int Port;
    string Title;
    bool IsRandom;
    string GameMap;
    int MaxPlayer;
    string Mode;
    string Password;
    bool Playing;
    // todo Players
};

#endif // __MODEL_ROOM_H__
