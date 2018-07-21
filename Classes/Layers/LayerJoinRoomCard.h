#ifndef __LAYER_JOIN_ROOM_CARD_H__
#define __LAYER_JOIN_ROOM_CARD_H__

#include "LayerBase.h"
#include "ModelRoom.h"

class LayerJoinRoomCard final : public LayerBase
{
public:
    static LayerBase* createLayerWithRoom(const ModelRoom& rooms);

    virtual bool init() override;

    CREATE_FUNC(LayerJoinRoomCard);

private:
    void join(Ref* pSender);

    static ModelRoom room;

    int roomId;
    bool needPassword;
};

#endif // __LAYER_JOIN_ROOM_CARD_H__
