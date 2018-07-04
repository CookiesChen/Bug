#include "LayerNewRoom.h"

LayerBase* LayerNewRoom::createLayer()
{
    return LayerNewRoom::create();
}

bool LayerNewRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
