#include "LayerMenu.h"

LayerBase* LayerRoom::createLayer()
{
    return LayerRoom::create();
}

bool LayerRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
