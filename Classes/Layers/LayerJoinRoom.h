#ifndef __LAYER_JOIN_ROOM_H__
#define __LAYER_JOIN_ROOM_H__

#include "LayerBase.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class LayerJoinRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void backMenu(Ref* pSender);
    void getRoomList(float dt);

    void prePage(Ref* pSender);
    void nextPage(Ref* pSender);

    CREATE_FUNC(LayerJoinRoom);

private:
};

#endif // __LAYER_JOIN_ROOM_H__
