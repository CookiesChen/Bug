#ifndef _LAYER_MAP_MINI_H__
#define _LAYER_MAP_MINI_H__

#include "LayerBase.h"

class LayerMapMini final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setMap(float x, float y, float pre);

    void setPlayer(float x, float y);

    CREATE_FUNC(LayerMapMini);

private:
    Node * mapBack;
    ClippingNode * clipper;
};

#endif // !_LAYER_MAP_MINI_H__
