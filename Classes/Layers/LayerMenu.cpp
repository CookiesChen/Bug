#include "Helpers.h"
#include "LayerMenu.h"
#include "ServiceUser.h"
#include "ServiceAPI.h"

LayerBase* LayerMenu::createLayer()
{
    return LayerMenu::create();
}

bool LayerMenu::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    buttonJoin = MenuItemImage::create("Graphics/System/BtnJoinGame.png", "Graphics/System/BtnJoinGame_click.png", CC_CALLBACK_1(LayerMenu::joinRoom, this));
    buttonNew = MenuItemImage::create("Graphics/System/BtnNewGame.png", "Graphics/System/BtnNewGame_click.png", CC_CALLBACK_1(LayerMenu::newRoom, this));
    logoutButton = MenuItemImage::create("Graphics/System/BtnLogOut.png", "Graphics/System/BtnLogOut_click.png", CC_CALLBACK_1(LayerMenu::logoutEvent, this));
    logoutButton->setScale(0.5);
    labelUserName = Label::createWithTTF("", "Fonts/arial.ttf", 20);

    buttonJoin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    buttonNew->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
    logoutButton->setPosition(Vec2(visibleSize.width - 70, visibleSize.height - 50));
    labelUserName->setPosition(Vec2(100, visibleSize.height - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(buttonJoin);
    menu->addChild(buttonNew);
    menu->addChild(logoutButton);

    this->addChild(labelUserName, 1);
    this->addChild(menu, 1);

    initUser();

    return true;
}

void LayerMenu::joinRoom(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromMenuToJoinRoom);
}

void LayerMenu::newRoom(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromMenuToNewRoom);
}

void LayerMenu::UpdateUserInfo()
{
    this->labelUserName->setString(Singleton<ServiceUser>::GetInstance()->GetNikename());
}

void LayerMenu::logoutEvent(Ref* pSender)
{
    Singleton<ServiceAPI>::GetInstance()->Logout();
    this->updateScene(Tag::SceneFromMenuToLoginAndRegister);
}

void LayerMenu::initUser()
{
    // todo
    //auto userid = Singleton<ModelUser>::GetInstance()->getUserId();
    //auto avator = Singleton<ModelUser>::GetInstance()->getAvatar();
    //auto nickname = Singleton<ModelUser>::GetInstance()->getNickName();
    //auto gender = Singleton<ModelUser>::GetInstance()->getGender();
    //auto level = Singleton<ModelUser>::GetInstance()->getLevel();
}
