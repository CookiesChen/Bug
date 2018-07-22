#include "Helpers.h"
#include "LayerMap.h"
#include "ServicePlayer.h"

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

    auto boundBody = PhysicsBody::createEdgeBox(map->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f), 3);
    boundBody->setCategoryBitmask(0x80000000);
    boundBody->setCollisionBitmask(0xFFFFFFFF);
    boundBody->setContactTestBitmask(0x00000001);
    map->setPhysicsBody(boundBody);

    this->addChild(map, 3);

    player = ModelPlayer::create("Graphics/Pictures/Uang/Armature_BugMove_0.png");
    player->setScale(0.2f);
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 0.0f));
    playerBody->setCategoryBitmask(0x00000001);
    playerBody->setCollisionBitmask(0xFFFFFFFF);
    playerBody->setContactTestBitmask(0x80000000);
    playerBody->setDynamic(true);
    player->setPhysicsBody(playerBody);

    Singleton<ServicePlayer>::GetInstance()->SetPlayer(player, this);

    return true;
}
