#include <tchar.h>

#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "LayerEmail.h"
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

    // 添加界面动画缓存
    auto leaves = Animation::create();
    for (int i = 0; i < 51; i++) {
        char szName[100] = { 0 };
        sprintf(szName, "Graphics/Pictures/Leaves/Armature_newAnimation_%d.png", i);
        leaves->addSpriteFrameWithFile(szName);
    }
    leaves->setDelayPerUnit(1.0f / 51.0f);
    leaves->setRestoreOriginalFrame(true);

    AnimationCache::getInstance()->addAnimation(leaves, "leaves");

    // 添加层
    layerEmail = LayerEmail::createLayer();
    layerLogin = LayerLogin::createLayer();
    layerRegister = LayerRegister::createLayer();
    layerBackground = LayerLoginAndRegisterBackground::createLayer();

    layerEmail->setActive(false);
    layerEmail->setVisible(false);
    layerRegister->setActive(false);
    layerRegister->setVisible(false);

    this->addChild(layerEmail, 10);
    this->addChild(layerLogin, 10);
    this->addChild(layerRegister, 10);
    this->addChild(layerBackground, 0);

    labelVersion = Label::createWithSystemFont("Connecting to server...", "微软雅黑", 20);
    labelVersion->setAnchorPoint(Vec2(0, 0));
    labelVersion->setPosition(Vec2(10, 10));
    this->addChild(labelVersion, 1);

    auto violetLogo = MenuItemImage::create("Graphics/Pictures/violet.png", "Graphics/Pictures/violet.png", CC_CALLBACK_1(SceneLoginAndRegister::website, this));
    violetLogo->setAnchorPoint(Vec2(1, 0));
    violetLogo->setPosition(Vec2(visibleSize.width, 0));
    violetLogo->setScale(0.2f);
    auto menu = Menu::create(violetLogo, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

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

void SceneLoginAndRegister::website(Ref * pSender)
{
    const TCHAR szOperation[] = _T("open");
    const TCHAR szAddress[] = _T("https://oauth.xmatrix.studio/");

    HINSTANCE hRslt = ShellExecute(NULL, szOperation, szAddress, NULL, NULL, SW_SHOWNORMAL);
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
    case Tag::LayerFromLoginOrRegisterToEmail:
        layerLogin->setActive(false);
        layerLogin->setVisible(false);
        layerRegister->setActive(false);
        layerRegister->setVisible(false);
        layerEmail->setActive(true);
        layerEmail->setVisible(true);
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
