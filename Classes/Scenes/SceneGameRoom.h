#pragma once

#include "LayerBase.h"
#include "SceneBase.h"
#include "cocos2d.h"

class SceneGameRoom final : public SceneBase
{
public:
    static SceneBase * createScene();

    virtual bool init() override;
    virtual void updateLayer() override;
    virtual void updateScene() override;

    void addKeyboardListener();
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
    void GetState();

    CREATE_FUNC(SceneGameRoom);

private:
    Label *msgLabel;
    int id;
};

