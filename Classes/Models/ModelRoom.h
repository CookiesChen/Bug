#ifndef __ROOM_MODEL_H__
#define __ROOM_MODEL_H__

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct {
    string userId;
    int gameId;
    string roleId;
    bool isReady;
    int team;
    string userName;
    string avatar;
    int gender;
} playerInfo;

class ModelRoom final
{
public:
    int roomId;
    string ownId;
    bool isOwn;
    int port;
    string title;
    string gameMap;
    int maxPalyer;
    string mode;
    bool isRandom;
    bool isPublic;
    bool playing;
    vector<playerInfo> players;
};

#endif
