#ifndef __PLAYER_MODEL_H__
#define __PLAYER_MODEL_H__

#include <string>

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ModelPlayer final
{
public:
    Sprite* sprite;

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
