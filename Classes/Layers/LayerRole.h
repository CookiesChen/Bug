#ifndef __LAYER_ROLE_H__
#define __LAYER_ROLE_H__

#include "LayerBase.h"

class LayerRole final : public LayerBase
{
public:
    static LayerBase* createLayer();



    virtual bool init() override;

    CREATE_FUNC(LayerRole);

private:
};

#endif // __LAYER_ROLE_H__
