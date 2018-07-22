#include "ServicePlayer.h"

void ServicePlayer::SetPlayer(ModelPlayer p)
{
    this->Player = p;
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
