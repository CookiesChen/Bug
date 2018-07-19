#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneMenu final : public SceneBase
{
public:
    static Scene* createScene();

    virtual bool init() override;
    virtual void updateLayer(Tag tag) override;
    virtual void updateScene(Tag tag) override;

    CREATE_FUNC(SceneMenu);
private:

    LayerBase * layerMenu;
    LayerBase * layerJoinRoom;
    LayerBase * layerNewRoom;
};

#endif //__SCENE_MENU_H__
