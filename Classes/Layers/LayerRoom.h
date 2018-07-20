#ifndef __LAYER_ROOM_H__
#define __LAYER_ROOM_H__

#include "LayerBase.h"

class LayerRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void SetRoomId(string id);

    CREATE_FUNC(LayerRoom);

private:
    string roomID;
};

#endif // __LAYER_ROOM_H__s
