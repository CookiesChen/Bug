#include "ServicePlayer.h"

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

void ServicePlayer::SetOtherSpriteById(int id, Sprite * s)
{
    for (auto &i : other)
    {
        if (i.Id == id)
        {
            i.sprite = s;
            break;
        }
    }
}

ModelPlayer ServicePlayer::GetPlayer()
{
    return this->Player;
}

vector<ModelPlayer> ServicePlayer::GetOtherPlayer()
{
    return this->other;
}

void ServicePlayer::SetXYandDir(float x, float y, int dir)
{
    Player.x = x;
    Player.y = y;
    Player.dir = dir;
}

void ServicePlayer::MovePlayer(int dir)
{
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

void ServicePlayer::MoveOthers(vector<frameCommand> fcv)
{
    for (auto &fc : fcv)
    {
        for (auto &p : other)
        {
            if (p.Id == fc.userId)
            {
                if (p.x != fc.x || p.y != fc.y)
                {
                    p.moving = 1;
                }
                p.x = fc.x;
                p.y = fc.y;
                p.dir = fc.dir;
                p.sprite->setPosition(Vec2(p.x - Player.x, p.y - Player.y));
                p.sprite->setRotation(p.dir);
                if (p.moving)
                {
                    // todo 动画
                }
            }
        }
    }
}

void ServicePlayer::SetHighVelocity()
{
    v = 500;
}

void ServicePlayer::SetLowVelocity()
{
    v = 300;
}
