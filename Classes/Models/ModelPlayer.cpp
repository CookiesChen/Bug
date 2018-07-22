#include "ModelPlayer.h"

ModelPlayer* ModelPlayer::create(const string & file)
{
    auto player = new (std::nothrow) ModelPlayer();
    if (player && player->initWithFile(file))
    {
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}
