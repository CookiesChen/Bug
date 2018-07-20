#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "LayerLogin.h"
#include "LayerLoginAndRegisterBackground.h"
#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"
#include "SceneMenu.h"
#include "ServiceAPI.h"


SceneBase* SceneLoginAndRegister::createScene()
{
    return SceneLoginAndRegister::create();
}

bool SceneLoginAndRegister::init()
{
    if (!SceneBase::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加层
    layerLogin = LayerLogin::createLayer();
    layerRegister = LayerRegister::createLayer();
    layerBackground = LayerLoginAndRegisterBackground::createLayer();

    layerRegister->setVisible(false);

    this->addChild(layerLogin, 10);
    this->addChild(layerRegister, 10);
    this->addChild(layerBackground, 0);

    labelVersion = Label::createWithSystemFont("Connecting to server...", "微软雅黑", 20);
    labelVersion->setAnchorPoint(Vec2(0, 0));
    labelVersion->setPosition(Vec2(0, 0));
    this->addChild(labelVersion, 1);

    this->getNewVersion();

    return true;
}

void SceneLoginAndRegister::getNewVersion()
{
    auto d = Singleton<ServiceAPI>::GetInstance()->GetNewVersion();
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            auto data = d["data"].GetObjectW();
            string version = data["title"].GetString();
            version += data["versionStr"].GetString();
            labelVersion->setString(version);
        }
        else
        {
            labelVersion->setString("Occur an error!");
        }
    }
    else
    {
        labelVersion->setString("Connect to server failed!");
    }
}

void SceneLoginAndRegister::updateLayer(Tag tag)
{
    switch (tag)
    {
    case Tag::LayerFromLoginToRegister:
        ((LayerLoginAndRegisterBackground*) layerBackground)->transition();
        layerLogin->setActive(false);
        layerLogin->setVisible(false);
        layerRegister->setVisible(true);
        layerRegister->setActive(true);
        break;
    case Tag::LayerFromRegisterToLogin:
        ((LayerLoginAndRegisterBackground*) layerBackground)->transition();
        layerRegister->setActive(false);
        layerRegister->setVisible(false);
        layerLogin->setVisible(true);
        layerLogin->setActive(true);
        break;
    }
}

void SceneLoginAndRegister::updateScene(Tag tag)
{
    switch (tag)
    {
    case SceneFromLoginAndRegisterToMenu:
        Director::getInstance()->replaceScene(SceneMenu::createScene());
        break;
    }
}
