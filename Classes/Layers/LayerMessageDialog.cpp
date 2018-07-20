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

    auto background = Sprite::createWithSpriteFrameName("Dialog.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto backButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerMessageDialog::back, this));
    backButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
    backButton->setScale(0.5f);

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(origin);

    label = Label::create("hello, world", "Fonts/arial.ttf", 32);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(label, 2);
    this->addChild(menu, 1);
    this->addChild(background, 0);

    return true;
}

void LayerMessageDialog::setString(const string& str)
{
    label->setString(str);
}

void LayerMessageDialog::back(Ref * pSender)
{
    this->setActive(false);
    this->setVisible(false);
}
