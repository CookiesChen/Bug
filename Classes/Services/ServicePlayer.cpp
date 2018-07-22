#include "ServicePlayer.h"

void ServicePlayer::SetMap(Node * m)
{
    this->map = m;
}

void ServicePlayer::SetPlayer(ModelPlayer p)
{
    this->Player = p;
}

void ServicePlayer::SetPlayerSprite(Sprite * s)
{
    this->Player.sprite = s;
}

void ServicePlayer::ClearOther()
{
    this->other.clear();
}

void ServicePlayer::AddOther(ModelPlayer p)
{
    this->other.push_back(p);
}

ModelPlayer ServicePlayer::GetPlayer()
{
    return this->Player;
}

vector<ModelPlayer> ServicePlayer::GetOtherPlayer()
{
    return this->other;
}

void ServicePlayer::MovePlayer(int dir)
{
    int v = 300;
    Player.sprite->getPhysicsBody()->setVelocityLimit(v);
    switch (dir)
    {
    case 0:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(0, v));
        break;
    case 45:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(v, v));
        break;
    case 90:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(v, 0));
        break;
    case 135:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(v, -v));
        break;
    case 180:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(0, -v));
        break;
    case 225:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(-v, -v));
        break;
    case 270:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(-v, 0));
        break;
    case 315:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2(-v, v));
        break;
    case 360:
        Player.sprite->getPhysicsBody()->setVelocity(Vec2::ZERO);
        Player.sprite->stopActionByTag(0);
        return;
    }
    Player.sprite->runAction(RotateTo::create(0.0f, dir));
    if (Player.sprite->getActionByTag(0) == NULL)
    {
        auto move = Animation::create();
        for (int i = 0; i < 24; i++)
        {
            char szName[100] = { 0 };
            sprintf(szName, "Graphics/Pictures/Uang/Armature_BugMove_%d.png", i);
            move->addSpriteFrameWithFile(szName);
        }
        move->setDelayPerUnit(0.8f / 24.0f);
        move->setRestoreOriginalFrame(true);
        auto action = RepeatForever::create(Animate::create(move));
        action->setTag(0);
        Player.sprite->runAction(action);
    }
}
