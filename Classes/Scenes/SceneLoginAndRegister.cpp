#include "SimpleAudioEngine.h"

#include "LayerLogin.h"
#include "LayerLoginAndRegisterBackground.h"
#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"
#include "SceneMenu.h"

SceneBase* SceneLoginAndRegister::createScene()
{
    return SceneLoginAndRegister::create();
}

bool SceneLoginAndRegister::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 预加载图片资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LogInScene.plist");

    // 添加层
    layerLogin = LayerLogin::createLayer();
    layerRegister = LayerRegister::createLayer();
    layerBackground = LayerLoginAndRegisterBackground::createLayer();

    layerRegister->setVisible(false);

    this->addChild(layerLogin, 10, "Login");
    this->addChild(layerRegister, 10, "Register");
    this->addChild(layerBackground, 9, "Background");

    return true;
}

void SceneLoginAndRegister::updateLayer()
{
    if (layerLogin->getActive())
    {
        ((LayerLoginAndRegisterBackground*) layerBackground)->transition();
        layerLogin->setActive(false);
        layerLogin->setVisible(false);
        layerRegister->setVisible(true);
        layerRegister->setActive(true);
    }
    else if (layerRegister->getActive())
    {
        ((LayerLoginAndRegisterBackground*) layerBackground)->transition();
        layerRegister->setActive(false);
        layerRegister->setVisible(false);
        layerLogin->setVisible(true);
        layerLogin->setActive(true);
    }
}

void SceneLoginAndRegister::updateScene()
{
    if (layerLogin->getActive())
    {
        Director::getInstance()->replaceScene(SceneMenu::createScene());
    }
}
