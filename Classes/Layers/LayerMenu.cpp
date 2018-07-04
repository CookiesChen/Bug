#include "LayerMenu.h"

LayerBase* LayerMenu::createLayer()
{
    return LayerMenu::create();
}

bool LayerMenu::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto buttonJoin = MenuItemLabel::create(Label::createWithTTF("Join Room", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerMenu::joinRoom, this));
    auto buttonNew = MenuItemLabel::create(Label::createWithTTF("New Room", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerMenu::newRoom, this));

    buttonJoin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    buttonNew->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(buttonJoin);
    menu->addChild(buttonNew);

    this->addChild(menu, 1);

    return true;
}

void LayerMenu::joinRoom(Ref* pSender) {

}

void LayerMenu::newRoom(Ref* pSender) {

}
