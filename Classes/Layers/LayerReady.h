#ifndef __LAYER_READY_H__
#define __LAYER_READY_H__

#include "LayerBase.h"

class LayerReady final : public LayerBase
{
public:
    static LayerBase* createLayer();



    virtual bool init() override;

    void waitTime(float dt);

    void beginReady();

    CREATE_FUNC(LayerReady);

private:
    Label * LabelWait;
    int time;
};

#endif // __LAYER_READY_H__
