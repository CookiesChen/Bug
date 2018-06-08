#include "LayerMessageDialog.h"

LayerBase* LayerMessageDialog::createLayer()
{
    return LayerMessageDialog::create();
}

bool LayerMessageDialog::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::create("hello, world", "fonts/arial.ttf", 32);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));

    auto menuItem = MenuItemFont::create("Enter");
    menuItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
    auto menu = Menu::create(menuItem);

    this->addChild(label);
    this->addChild(menu);

    return true;
}

