#include "LayerLoginAndRegisterBackground.h"

LayerBase* LayerLoginAndRegisterBackground::createLayer()
{
    return LayerLoginAndRegisterBackground::create();
}

bool LayerLoginAndRegisterBackground::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 罗盘
    compass_1 = Sprite::createWithSpriteFrameName("compass_1.png");
    compass_2 = Sprite::createWithSpriteFrameName("compass_2.png");
    compass_3 = Sprite::createWithSpriteFrameName("compass_3.png");

    compass_1->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_2->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_3->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));

    // 背景图

    this->addChild(compass_1, 3);
    this->addChild(compass_2, 2);
    this->addChild(compass_3, 1);

    transitionCount = false;

    return true;
}

void LayerLoginAndRegisterBackground::transition()
{
    if (transitionCount)
    {
        compass_1->runAction(RotateTo::create(0.5f, 0.0f));
        compass_2->runAction(RotateTo::create(0.5f, 0.0f));
        compass_3->runAction(RotateTo::create(0.5f, 0.0f));
    }
    else
    {
        compass_1->runAction(RotateTo::create(0.5f, 180.0f));
        compass_2->runAction(RotateTo::create(0.5f, -180.0f));
        compass_3->runAction(RotateTo::create(0.5f, 180.0f));
    }
    transitionCount = !transitionCount;
}

