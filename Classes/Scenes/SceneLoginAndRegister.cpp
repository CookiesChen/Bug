#include "SimpleAudioEngine.h"
#include "LayerLogin.h"
#include "LayerLoginAndRegisterBackground.h"
#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"
#include "SceneMenu.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "Helpers.h"

using namespace rapidjson;



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

    labelVersion = Label::createWithSystemFont("Connecting to server...", "微软雅黑", 20);
    labelVersion->setAnchorPoint(Vec2(0, 0));
    labelVersion->setPosition(Vec2(0, 0));
    this->addChild(labelVersion, 1);

    this->getNewVersion();

   
    return true;
}

void SceneLoginAndRegister::getNewVersion() {

    auto res = Singleton<Net>::getInstance()->Get("http://127.0.0.1:30081/game/new");
    log("res: %s\n", res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if (d.HasParseError()) {
        labelVersion->setString("Connect to server failed!");
    }
    if (d.IsObject() && d.HasMember("status")) {
        auto data = d["data"].GetObjectW();
        string version(data["title"].GetString());
        version.append(data["versionStr"].GetString());
        labelVersion->setString(version);
    }
    else {
        labelVersion->setString("Connect to server failed!");
    }


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
