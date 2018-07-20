#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "ui\CocosGUI.h"

#include "LayerBase.h"

using namespace cocos2d::ui;


class LayerLogin final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerLogin);

private:
    void loginEvent(Ref* pSender);
    void turnToRegister(Ref* pSender);

    TextField* account;
    TextField* password;
};

#endif // __LAYER_LOGIN_H__
