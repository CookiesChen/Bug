#ifndef __SERVICE_PLAYER_H__
#define __SERVICE_PLAYER_H__

#include "ModelPlayer.h"
#include <vector>

class ServicePlayer final
{
public:
    void SetMap(Node* m);
    void SetPlayer(ModelPlayer p);
    void SetPlayerSprite(Sprite* s);
    void ClearOther();
    void AddOther(ModelPlayer p);
    ModelPlayer GetPlayer();
    vector<ModelPlayer> GetOtherPlayer();
    void MovePlayer(int dir);

private:
    Node* map;
    ModelPlayer Player;
    vector<ModelPlayer> other;
};

#endif // __SERVICE_PLAYER_H__
