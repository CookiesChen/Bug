#ifndef __SCENE_LOGIN_AND_REGISTER_H__
#define __SCENE_LOGIN_AND_REGISTER_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneLoginAndRegister final : public SceneBase
{
public:
    static SceneBase * createScene();

    virtual bool init() override;
    virtual void updateLayer() override;
    virtual void updateScene() override;

    void getNewVersion();

    CREATE_FUNC(SceneLoginAndRegister);

private:
    LayerBase* layerLogin;
    LayerBase* layerRegister;
    LayerBase* layerBackground;
    Label* labelVersion;
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
