#include "LayerMenu.h"
#include "Helpers.h"
#include "ServiceAPI.h"

LayerBase* LayerMenu::createLayer()
{
    return LayerMenu::create();
}

bool LayerMenu::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto buttonJoin = MenuItemLabel::create(Label::createWithTTF("Join Game", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerMenu::joinRoom, this));
    auto buttonNew = MenuItemLabel::create(Label::createWithTTF("New Game", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerMenu::newRoom, this));

    // 退出登陆按钮
    auto logoutButton = MenuItemLabel::create(Label::createWithTTF("Logout", "fonts/arial.ttf", 20), CC_CALLBACK_1(LayerMenu::logoutEvent, this));
    logoutButton->setPosition(Vec2(visibleSize.width - 60, visibleSize.height - 60));

    // todo 显示用户基本信息（头像、名字、等级等）
    buttonJoin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    buttonNew->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(buttonJoin);
    menu->addChild(buttonNew);
    menu->addChild(logoutButton);
    
    this->addChild(menu, 1);

    return true;
}

void LayerMenu::joinRoom(Ref* pSender) {
    this->targetLayer = 1;
    this->updateLayer();
}

void LayerMenu::newRoom(Ref* pSender) {
    this->targetLayer = 2;
    this->updateLayer();
}

void LayerMenu::logoutEvent(Ref* pSender)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->Logout();
    this->updateScene();
}
