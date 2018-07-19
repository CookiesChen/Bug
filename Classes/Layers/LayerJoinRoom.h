#ifndef __LAYER_JOIN_ROOM_H__
#define __LAYER_JOIN_ROOM_H__

#include "LayerBase.h"

class LayerJoinRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void backMenu(Ref* pSender);
    void getRoomList(float dt);

    CREATE_FUNC(LayerJoinRoom);

private:
};

#endif // __LAYER_JOIN_ROOM_H__
