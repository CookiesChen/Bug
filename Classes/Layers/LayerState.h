#ifndef _LAYER_STATE_H__
#define _LAYER_STATE_H__

#include "LayerBase.h"

class LayerState final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;
    void update(float dt);

    CREATE_FUNC(LayerState);

private:
    ProgressTimer* hpBar;
    ProgressTimer* spBar;
};

#endif // _LAYER_STATE_H__
