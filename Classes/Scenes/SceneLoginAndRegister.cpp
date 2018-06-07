#include "LayerLogin.h"
#include "LayerLoginAndRegisterBackground.h"
#include "LayerMessageDialog.h"
#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"
#include "SimpleAudioEngine.h"

Scene* SceneLoginAndRegister::createScene()
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
    if (layerLogin->getActive() == false)
    {
        auto rotate1 = RotateTo::create(0.5f, 180.0f);
        auto rotate2 = RotateTo::create(0.5f, -180.0f);
        auto rotate3 = RotateTo::create(0.5f, 180.0f);

        layerBackground->getChildByName("compass_1")->runAction(rotate1);
        layerBackground->getChildByName("compass_2")->runAction(rotate2);
        layerBackground->getChildByName("compass_3")->runAction(rotate3);

        layerRegister->setVisible(true);
        // layerRegister->setActive(true);
    }
}
