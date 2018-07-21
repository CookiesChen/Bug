#ifndef __LAYER_ROOM_H__
#define __LAYER_ROOM_H__

#include "LayerBase.h"
#include "ModelRoom.h"

class LayerRoom final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void heart(float dt);

    void refreshData(float dt);

    void drawPlayers();

    void drawInfo();

    void quitRoom(Ref* pSender);

    void setReady(Ref* pSender);

    CREATE_FUNC(LayerRoom);

private:
    Size visibleSize;
    vector<Node*> playerNode;
    bool isReady;
    ModelRoom room;
    Label * labelTitle;
    Label * labelMap;
    Label * labelMode;
    Label * labelPlayer;
    MenuItemImage * buttonReady;
    MenuItemImage * buttonBack;
    Menu * menu;
};

#endif // __LAYER_ROOM_H__s
