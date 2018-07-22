#include "Helpers.h"
#include "LayerState.h"
#include "ServicePlayer.h"

LayerBase* LayerState::createLayer()
{
    return LayerState::create();
}

bool LayerState::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    Sprite* box = Sprite::create("Graphics/System/BloodBox.png");
    Sprite* hp = Sprite::create("Graphics/System/blood.png");
    Sprite* sp = Sprite::create("Graphics/System/energy.png");

    hpBar = ProgressTimer::create(hp);
    hpBar->setScaleX(11.2);
    hpBar->setAnchorPoint(Vec2(0, 0));
    hpBar->setType(ProgressTimerType::BAR);
    hpBar->setBarChangeRate(Point(1, 0));
    hpBar->setMidpoint(Point(0, 1));
    hpBar->setPercentage(100);
    hpBar->setPosition(Vec2(origin.x + 30, origin.y + visibleSize.height - 45));

    spBar = ProgressTimer::create(sp);
    spBar->setScaleX(10.4);
    spBar->setAnchorPoint(Vec2(0, 0));
    spBar->setType(ProgressTimerType::BAR);
    spBar->setBarChangeRate(Point(1, 0));
    spBar->setMidpoint(Point(0, 1));
    spBar->setPercentage(100);
    spBar->setPosition(Vec2(origin.x + 40, origin.y + visibleSize.height - 65));

    box->setAnchorPoint(Vec2(0, 0));
    box->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 70));

    this->addChild(box, 1);
    this->addChild(spBar, 0);
    this->addChild(hpBar, 0);

    this->schedule(schedule_selector(LayerState::update), 1.0f / 20, kRepeatForever, 0);

    return true;
}

void LayerState::update(float dt)
{
    int hp = Singleton<ServicePlayer>::GetInstance()->GetPlayer().hp;
    int sp = Singleton<ServicePlayer>::GetInstance()->GetPlayer().sp;
    if (hp != hpBar->getPercentage())
    {
        hpBar->setPercentage(hp);
    }
    if (sp != spBar->getPercentage())
    {
        spBar->setPercentage(sp);
    }
}
