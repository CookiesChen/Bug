#ifndef _LAYER_MAP_MINI_H__
#define _LAYER_MAP_MINI_H__

#include "LayerBase.h"
#define MAPHEIGHT 3840
#define MAPWIDTH 5120

class LayerMapMini final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setMap(float x, float y, float dis, int type);

    void setPlayer(float x, float y);

    CREATE_FUNC(LayerMapMini);

private:
    ClippingNode * circleBig;
    ClippingNode * circleSmall;
    Sprite * player;
    Vec2 centerPoint;
    Size mapMiniSize;
};

#endif // !_LAYER_MAP_MINI_H__
