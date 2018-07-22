#ifndef __PLAYER_MODEL_H__
#define __PLAYER_MODEL_H__

#include <string>

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ModelPlayer final
{
public:
    ModelPlayer() : hp(100), sp(100) {}

    Sprite* sprite;

    int Id;
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
