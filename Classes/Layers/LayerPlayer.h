#ifndef _LAYER_PLAYER_H__
#define _LAYER_PLAYER_H__

#include "LayerBase.h"

class LayerPlayer final: public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setPlayerPosition(Vec2 position);
    void movePlayer(Vec2 offset, char direction);
    void stopPlayer();

    Sprite * player;

    CREATE_FUNC(LayerPlayer);
private:
    Animation* move;
};

#endif // !_LAYER_PLAYER_H
