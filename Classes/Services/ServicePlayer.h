#ifndef __SERVICE_PLAYER_H__
#define __SERVICE_PLAYER_H__

#include <vector>

#include "ModelPlayer.h"
#include "ServiceGame.h"

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

private:
    ModelPlayer Player;
    vector<ModelPlayer> other;
    float v;
};

#endif // __SERVICE_PLAYER_H__
