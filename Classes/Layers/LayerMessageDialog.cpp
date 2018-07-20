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

    layerColor = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height * 2);
    layerColor->setPosition(Vec2(0, -visibleSize.height));
    layerColor->setOpacity(0);

    auto background = Sprite::createWithSpriteFrameName("Dialog.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto backButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerMessageDialog::back, this));
    backButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
    backButton->setScale(0.5f);

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(origin);

    label = Label::create("hello, world", "Fonts/arial.ttf", 24);
    label->setDimensions(background->getContentSize().width - 50, background->getContentSize().height - 50);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(label, 3);
    this->addChild(menu, 2);
    this->addChild(background, 1);
    this->addChild(layerColor, 0);

    this->setPosition(Vec2(0, visibleSize.height));

    return true;
}

void LayerMessageDialog::setString(const string& str)
{
    label->setString(str);
}

void LayerMessageDialog::show()
{
    this->setActive(true);
    this->setVisible(true);

    auto moveTo = MoveTo::create(0.25, Vec2::ZERO);
    auto fadeTo = FadeTo::create(0.3, 150);
    layerColor->runAction(fadeTo);
    this->runAction(moveTo);
}

void LayerMessageDialog::back(Ref * pSender)
{
    auto moveTo = MoveTo::create(0.25, Vec2(0, Director::getInstance()->getVisibleSize().height));
    auto fadeTo = FadeTo::create(0.3, 0);
    auto fn = CallFunc::create([this]() -> void
    {
        this->setActive(false);
        this->setVisible(false);
    });
    auto sequence = Sequence::create(moveTo, fn, nullptr);
    layerColor->runAction(fadeTo);
    this->runAction(sequence);
}
