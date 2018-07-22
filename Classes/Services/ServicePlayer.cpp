#include "ServicePlayer.h"

void ServicePlayer::SetPlayer(ModelPlayer p)
{
    this->Player = p;
}

void ServicePlayer::SetPlayerSprite(Sprite * s)
{
    this->Player.sprite = s;
    for (int i = 0; i < 24; i++)
    {
        char szName[100] = { 0 };
        sprintf(szName, "Graphics/Pictures/Uang/Armature_BugMove_%d.png", i);
        moveVector.pushBack(SpriteFrame::create(szName, Rect(0, 0, 473, 620)));
    }
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
        auto move = Animation::createWithSpriteFrames(moveVector);
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
                p.moving = abs(p.x - fc.x) > 1 || abs(p.y - fc.y) > 1;
                p.x = fc.x;
                p.y = fc.y;
                if (fc.dir != 360) p.dir = fc.dir;
                if (p.moving)
                {
                    p.sprite->setPosition(Vec2(p.x - Player.x + Player.sprite->getPosition().x, p.y - Player.y + Player.sprite->getPosition().y));
                }
                p.sprite->setRotation(p.dir);
                if (p.moving && p.sprite->getActionByTag(0) == nullptr)
                {
                    auto move = Animation::createWithSpriteFrames(moveVector);
                    move->setDelayPerUnit(0.8f / 24.0f);
                    move->setRestoreOriginalFrame(true);
                    auto action = RepeatForever::create(Animate::create(move));
                    action->setTag(0);
                    p.sprite->runAction(action);
                }
                else if (p.moving == false)
                {
                    p.sprite->stopActionByTag(0);
                    p.sprite->getPhysicsBody()->setVelocity(Vec2::ZERO);
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
