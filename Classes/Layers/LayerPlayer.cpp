#include "LayerPlayer.h"

LayerBase* LayerPlayer::createLayer()
{
    return LayerPlayer::create();
}

bool LayerPlayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    player = Sprite::create("Graphics/Pictures/Uang/Armature_BugMove_0.png");
    player->setScale(0.2);
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(player, 1);

    return true;
}


void LayerPlayer::setPlayerPosition(Vec2 position) {
    player->setPosition(position);
}

void LayerPlayer::movePlayer(Vec2 offset, char direction) {
    player->setPosition(player->getPosition() - offset);
    auto angle = 0;
    switch (direction)
    {
    case 'W':
        angle = 0;
        break;
    case 'S':
        angle = 180;
        break;
    case 'A':
        angle = 270;
        break;
    case 'D':
        angle = 90;
        break;
    default:
        break;
    }
    player->runAction(RotateTo::create(0.0f, angle));
    if (player->getActionByTag(0) == NULL) {
        move = Animation::create();
        for (int i = 0; i < 24; i++) {
            char szName[100] = { 0 };
            sprintf(szName, "Graphics/Pictures/Uang/Armature_BugMove_%d.png", i);
            move->addSpriteFrameWithFile(szName);
        }
        move->setDelayPerUnit(0.8f / 24.0f);
        move->setRestoreOriginalFrame(true);
        auto action = Animate::create(move);
        action->setTag(0);
        this->player->runAction(action);
    }
}

void LayerPlayer::stopPlayer() {
    player->stopActionByTag(0);
}
