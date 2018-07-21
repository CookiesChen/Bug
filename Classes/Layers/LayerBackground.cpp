#include "LayerBackground.h"

LayerBase* LayerBackground::createLayer()
{
    return LayerBackground::create();
}

bool LayerBackground::init()
{
    if (!LayerBase::init()) return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("Graphics/Pictures/background.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    float xScale = visibleSize.width / background->getContentSize().width;
    float yScale = visibleSize.height / background->getContentSize().height;
    background->setScale(xScale > yScale ? xScale : yScale);
    this->addChild(background, 0);

    auto backLeaves = Sprite::create("Graphics/Pictures/back_leaves.png");
    backLeaves->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    xScale = visibleSize.width / backLeaves->getContentSize().width;
    yScale = visibleSize.height / backLeaves->getContentSize().height;
    backLeaves->setScale(xScale > yScale ? xScale : yScale);
    this->addChild(backLeaves, 0);
    return true;
}
