#include "LayerLogin.h"
#include "LayerLoginAndRegisterBackground.h"
#include "LayerMessageDialog.h"
#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SceneLoginAndRegister::createScene()
{
    return SceneLoginAndRegister::create();
}

// on "init" you need to initialize your instance
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
    auto Login = LayerLogin::createLayer();
    auto Register = LayerRegister::createLayer();
    auto Background = LayerLoginAndRegisterBackground::createLayer();

    Register->setVisible(false);

    this->addChild(Login, 10, "Login");
    this->addChild(Register, 10, "Register");
    this->addChild(Background, 9, "Background");
    return true;
}
