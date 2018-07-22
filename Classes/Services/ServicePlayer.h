#ifndef __SERVICE_PLAYER_H__
#define __SERVICE_PLAYER_H__

#include "ModelPlayer.h"
#include <vector>

class ServicePlayer final
{
public:
    void SetPlayer(ModelPlayer p);
    void ClearOther();
    void AddOther(ModelPlayer p);
    ModelPlayer GetPlayer();
    vector<ModelPlayer> GetOtherPlayer();
private:
    ModelPlayer Player;
    vector<ModelPlayer> other;
};

#endif // __SERVICE_PLAYER_H__
