#include "LayerMap.h"

LayerBase* LayerMap::createLayer()
{
    return LayerMap::create();
}

bool LayerMap::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    map = TMXTiledMap::create("Map/Jungle.tmx");
    map->setScale(Director::getInstance()->getContentScaleFactor());
    map->setPosition(Vec2::ZERO);
    maxWidth = map->getContentSize().width;
    maxHeight = map->getContentSize().height;
    this->addChild(map, 3);

    return true;
}
