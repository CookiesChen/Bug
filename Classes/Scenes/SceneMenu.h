#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "LayerBase.h"
#include "SceneBase.h"
#include "ModelRoom.h"

class SceneMenu final : public SceneBase
{
public:
    static Scene* createScene();

    virtual bool init() override;
    virtual void updateLayer(Tag tag) override;
    virtual void updateScene(Tag tag) override;

    void addCardLayer(ModelRoom r, int index);

    void updateUserInfo();

    CREATE_FUNC(SceneMenu);
private:
    vector<LayerBase*> cards;
    LayerBase * layerMenu;
    LayerBase * layerJoinRoom;
    LayerBase * layerNewRoom;
    LayerBase * layerNewUser;
    LayerBase * layerLogin;
};

#endif //__SCENE_MENU_H__
