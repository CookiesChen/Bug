#include "LayerMapMini.h"

LayerBase* LayerMapMini::createLayer()
{
    return LayerMapMini::create();
}

bool LayerMapMini::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

   

    return true;
}
