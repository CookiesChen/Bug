#ifndef __SCENE_LOGIN_AND_REGISTER_H__
#define __SCENE_LOGIN_AND_REGISTER_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneLoginAndRegister final : public SceneBase
{
public:
    static Scene * createScene();

    virtual bool init();
    virtual void updateLayer() override;

    CREATE_FUNC(SceneLoginAndRegister);

private:
    LayerBase* layerLogin;
    Layer* layerRegister;
    Layer* layerBackground;
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
