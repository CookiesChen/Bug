#include "LayerRole.h"

LayerBase* LayerRole::createLayer()
{
    return LayerRole::create();
}

bool LayerRole::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // todo 放几只虫子给玩家选择
    return true;
}
