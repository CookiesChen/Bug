#ifndef __LAYER_NEW_ROOM_H__
#define __LAYER_NEW_ROOM_H__

#include "LayerBase.h"
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

    void refreshRoomName();

    void checkBoxPersonCallback(cocos2d::Ref * ref, CheckBox::EventType type);
    void checkBoxTeamCallback(cocos2d::Ref * ref, CheckBox::EventType type);
    void checkBoxMapJungleCallback(cocos2d::Ref * ref, CheckBox::EventType type);
    
    CREATE_FUNC(LayerNewRoom);

private:
    CheckBox* checkModePerson;
    CheckBox* checkModeTeam;
    CheckBox* checkRandom;
    CheckBox* checkMapJungle;
    TextField* roomName;
    TextField* roomPassword;
    Label* labelRoomPlayer;
    Label* labelRoomPlayerCount;
    Slider* slider;
    int playerCount;
    string mode;
};

#endif // __LAYER_NEW_ROOM_H__
