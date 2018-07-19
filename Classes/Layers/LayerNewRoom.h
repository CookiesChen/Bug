#ifndef __LAYER_NEW_ROOM_H__
#define __LAYER_NEW_ROOM_H__

#include "LayerBase.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;

class LayerNewRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void backMenu(Ref* pSender);
    void newRoom(Ref* pSender);

    CREATE_FUNC(LayerNewRoom);

private:
    TextField * roomName;
    Label* labelRoomPlayer;
    Slider* slider;
    int playerCount;
};

#endif // __LAYER_NEW_ROOM_H__
