#ifndef __SERVICE_PLAYER_H__
#define __SERVICE_PLAYER_H__

#include <vector>

#include "ModelPlayer.h"
#include "ServiceGame.h"
#include "cocos2d.h"

class ServicePlayer final
{
public:
    ServicePlayer() : v(300) {}

    void SetPlayer(ModelPlayer p);
    void SetPlayerSprite(Sprite* s);
    void ClearOther();
    void AddOther(ModelPlayer p);
    void SetOtherSpriteById(int id, Sprite* s);
    ModelPlayer GetPlayer();
    vector<ModelPlayer> GetOtherPlayer();
    void SetXYandDir(float x, float y, int dir);
    void MovePlayer(int dir);
    void MoveOthers(vector<frameCommand> fcv);
    void SetHighVelocity();
    void SetLowVelocity();

    void PlayerAttack();
    void OthersAttack(vector<frameCommand> fcv);

    void SetData(vector<frameState> data);
    void DealData();
    void SetDeadPlayerById(int id);

private:
    ModelPlayer Player;
    vector<ModelPlayer> other;
    Vector<SpriteFrame*> moveVector;
    Vector<SpriteFrame*> attackVector;
    list<frameState> frameData;
    float v;
    std::mutex mtx;
    int dir_s;
};

#endif // __SERVICE_PLAYER_H__
