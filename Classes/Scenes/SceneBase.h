#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <string>

#include "cocos2d.h"

#include "Tag.h"

using namespace cocos2d;
using namespace std;

class SceneBase : public Scene
{
public:
    virtual void dialog(const string& str) final;
    virtual bool getHaltState() final;
    virtual bool init() override;
    virtual void updateLayer(Tag tag) = 0;
    virtual void updateScene(Tag tag) = 0;

private:
    LayerBase* d;
};

#endif // __SCENE_BASE_H__
