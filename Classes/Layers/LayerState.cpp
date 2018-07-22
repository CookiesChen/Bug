#include "LayerState.h"

LayerBase* LayerState::createLayer()
{
    return LayerState::create();
}

bool LayerState::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    //hp条
    Sprite* sp0 = Sprite::create("Graphics/System/hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
    Sprite* sp = Sprite::create("Graphics/System/hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

    //使用hp条设置progressBar
    hpBar = ProgressTimer::create(sp);
    hpBar->setScaleX(90);
    hpBar->setAnchorPoint(Vec2(0, 0));
    hpBar->setType(ProgressTimerType::BAR);
    hpBar->setBarChangeRate(Point(1, 0));
    hpBar->setMidpoint(Point(0, 1));
    hpBar->setPercentage(100);
    hpBar->setPosition(Vec2(origin.x + 14 * hpBar->getContentSize().width, origin.y + visibleSize.height - 2 * hpBar->getContentSize().height));

    this->addChild(hpBar, 1);

    return true;
}
