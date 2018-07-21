#ifndef __LAYER_MENU_H__
#define __LAYER_MENU_H__

#include "LayerBase.h"

class LayerMenu final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void joinRoom(Ref* pSender);
    void newRoom(Ref* pSender);
    void logoutEvent(Ref* pSender);
    void UpdateUserInfo();
    void initUser();

    CREATE_FUNC(LayerMenu);

private:
    MenuItemImage * buttonJoin;
    MenuItemImage * buttonNew;
    MenuItemImage * logoutButton;

    Label * labelUserName;
};

#endif // __LAYER_MENU_H__
