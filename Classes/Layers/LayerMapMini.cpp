#include "LayerMap.h"

LayerBase* LayerMap::createLayer()
{
    return LayerMap::create();
}

bool LayerMap::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    
    this->addChild(map, 1);

    return true;
}
