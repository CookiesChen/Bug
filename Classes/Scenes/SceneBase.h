#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "cocos2d.h"

#include "Tag.h"

using namespace cocos2d;

class SceneBase : public Scene
{
public:
    virtual void updateLayer(Tag tag) = 0;
    virtual void updateScene(Tag tag) = 0;
    int targetLayer;
};

#endif // __SCENE_BASE_H__
