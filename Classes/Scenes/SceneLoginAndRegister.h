#ifndef __SCENE_LOGIN_AND_REGISTER_H__
#define __SCENE_LOGIN_AND_REGISTER_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneLoginAndRegister final : public SceneBase
{
public:
    static SceneBase * createScene();

    virtual bool init() override;
    virtual void updateLayer(Tag tag) override;
    virtual void updateScene(Tag tag) override;

    void getNewVersion();

    CREATE_FUNC(SceneLoginAndRegister);

private:
    void website(Ref* pSender);

    Label * labelVersion;
    LayerBase* layerBackground;
    LayerBase* layerEmail;
    LayerBase* layerLogin;
    LayerBase* layerRegister;
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
