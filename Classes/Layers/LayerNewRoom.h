#ifndef __LAYER_NEW_ROOM_H__
#define __LAYER_NEW_ROOM_H__

#include "LayerBase.h"

class LayerNewRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerNewRoom);

private:
};

#endif // __LAYER_NEW_ROOM_H__
