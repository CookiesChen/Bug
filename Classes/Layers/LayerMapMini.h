#ifndef _LAYER_MAP_MINI_H__
#define _LAYER_MAP_MINI_H__

#include "LayerBase.h"

class LayerMapMini final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;


    CREATE_FUNC(LayerMapMini);

};

#endif // !_LAYER_MAP_MINI_H__
