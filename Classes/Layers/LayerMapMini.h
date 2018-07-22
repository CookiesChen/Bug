#ifndef _LAYER_MAP_MINI_H__
#define _LAYER_MAP_MINI_H__

#include "LayerBase.h"

class LayerMapMini final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setMap(int pre);


    CREATE_FUNC(LayerMapMini);

private:
    Node * mapBack;
    ClippingNode * clipper;
};

#endif // !_LAYER_MAP_MINI_H__
