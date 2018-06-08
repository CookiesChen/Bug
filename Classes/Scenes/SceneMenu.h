#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneMenu final : public SceneBase
{
public:
    static Scene* createScene();

    virtual bool init() override;
    virtual void updateLayer() override;
    virtual void updateScene() override;

    CREATE_FUNC(SceneMenu);
};

#endif //__SCENE_MENU_H__
