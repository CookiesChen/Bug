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

    map = experimental::TMXTiledMap::create("Map/Jungle.tmx");
    map->setScale(Director::getInstance()->getContentScaleFactor());
    map->setPosition(Vec2::ZERO);
    maxWidth = map->getContentSize().width;
    maxHeight = map->getContentSize().height;

    auto boundBody = PhysicsBody::createEdgeBox(map->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f), 3);
    boundBody->setCategoryBitmask(0x80000000);
    boundBody->setCollisionBitmask(0xFFFFFFFF);
    boundBody->setContactTestBitmask(0x00000001);
    boundBody->setDynamic(false);
    map->setPhysicsBody(boundBody);

    this->addChild(map, 3);

    player = Sprite::create("Graphics/Pictures/Uang/Armature_BugMove_0.png");
    player->setScale(0.2f);
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    auto playerBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 0.0f));
    playerBody->setCategoryBitmask(0x00000001);
    playerBody->setCollisionBitmask(0xFFFFFFFF);
    playerBody->setContactTestBitmask(0x80000000);
    playerBody->setRotationEnable(false);
    playerBody->setDynamic(true);
    player->setPhysicsBody(playerBody);

    this->addChild(player, 10);
    Singleton<ServicePlayer>::GetInstance()->SetPlayerSprite(player);

    auto others = Singleton<ServicePlayer>::GetInstance()->GetOtherPlayer();
    for (auto &p : others)
    {
        auto sprite = Sprite::create("Graphics/Pictures/Uang/Armature_BugMove_0.png");
        sprite->setScale(0.2f);
        auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 0.0f));
        spriteBody->setCategoryBitmask(0x00000001);
        spriteBody->setCollisionBitmask(0xFFFFFFFF);
        spriteBody->setContactTestBitmask(0x80000000);
        spriteBody->setRotationEnable(false);
        spriteBody->setDynamic(true);
        sprite->setPhysicsBody(spriteBody);

        this->addChild(sprite, 10);
        Singleton<ServicePlayer>::GetInstance()->SetOtherSpriteById(p.Id, sprite);
    }

    return true;
}
