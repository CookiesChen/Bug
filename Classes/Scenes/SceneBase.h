#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "cocos2d.h"

USING_NS_CC;

class SceneBase : public Scene
{
public:
    virtual void updateLayer() = 0;
    virtual void updateScene() = 0;
};

#endif // __SCENE_BASE_H__
