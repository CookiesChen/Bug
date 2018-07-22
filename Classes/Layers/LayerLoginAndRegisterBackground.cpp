#include "LayerLoginAndRegisterBackground.h"

LayerBase* LayerLoginAndRegisterBackground::createLayer()
{
    return LayerLoginAndRegisterBackground::create();
}

bool LayerLoginAndRegisterBackground::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("Graphics/Pictures/background.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    auto backLeaves = Sprite::create("Graphics/Pictures/back_leaves.png");
    backLeaves->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    float xScale = visibleSize.width / background->getContentSize().width;
    float yScale = visibleSize.height / background->getContentSize().height;
    background->setScale(xScale > yScale ? xScale : yScale);

    // 界面动画
    leaves1 = Sprite::create("Graphics/Pictures/Leaves/Armature_newAnimation_0.png");
    leaves2 = Sprite::create("Graphics/Pictures/Leaves/Armature_newAnimation_0.png");
    leaves3 = Sprite::create("Graphics/Pictures/Leaves/Armature_newAnimation_0.png");
    leaves1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    leaves2->runAction(RotateTo::create(0.0f, 90));
    leaves2->setPosition(Vec2(visibleSize.width, visibleSize.height - 200));
    leaves3->runAction(RotateTo::create(0.0f, 270));
    leaves3->setPosition(Vec2(0, 0));


    // 罗盘
    compass_1 = Sprite::createWithSpriteFrameName("compass_1.png");
    compass_2 = Sprite::createWithSpriteFrameName("compass_2.png");
    compass_3 = Sprite::createWithSpriteFrameName("compass_3.png");

    compass_1->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_2->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_3->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));

    this->addChild(compass_1, 3);
    this->addChild(compass_2, 2);
    this->addChild(compass_3, 1);
    this->addChild(background, 0);
    this->addChild(backLeaves, 0);
    this->addChild(leaves1, 0);
    this->addChild(leaves2, 0);
    this->addChild(leaves3, 0);

    transitionCount = false;

    schedule(schedule_selector(LayerLoginAndRegisterBackground::animation), 1.5f, kRepeatForever, 0);
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

void LayerLoginAndRegisterBackground::animation(float time) {
    auto leavesAnimation = AnimationCache::getInstance()->getAnimation("leaves");
    leaves1->runAction(Animate::create(leavesAnimation));
    leaves2->runAction(Animate::create(leavesAnimation));
    leaves3->runAction(Animate::create(leavesAnimation));
}
