#ifndef __PLAYER_MODEL_H__
#define __PLAYER_MODEL_H__

#include <string>
#include <stdio.h>

using namespace std;

class ModelPlayer final
{
public:
    string Id;
    string roleId;
    string team;
    string userId;
    string userName;

    float x;
    float y;
    int dir;

    int hp;
    int sp;
    int moving;
};

#endif
