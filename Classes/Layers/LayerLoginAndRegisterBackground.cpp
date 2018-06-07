#include "LayerLoginAndRegisterBackground.h"
#include "SceneLoginAndRegister.h"

Layer* LayerLoginAndRegisterBackground::createLayer()
{
    return LayerLoginAndRegisterBackground::create();
}

bool LayerLoginAndRegisterBackground::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 罗盘
    auto compass_1 = Sprite::createWithSpriteFrameName("compass_1.png");
    auto compass_2 = Sprite::createWithSpriteFrameName("compass_2.png");
    auto compass_3 = Sprite::createWithSpriteFrameName("compass_3.png");

    compass_1->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_2->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_3->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));

    // 背景图

    this->addChild(compass_1, 3, "compass_1");
    this->addChild(compass_2, 2, "compass_2");
    this->addChild(compass_3, 1, "compass_3");

    return true;
}

