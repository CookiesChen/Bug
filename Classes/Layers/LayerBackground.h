#ifndef __LAYER_BACKGROUND_H__
#define __LAYER_BACKGROUND_H__

#include "LayerBase.h"

class LayerBackground final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerBackground);

};

#endif // __LAYER_BACKGROUND_H__
