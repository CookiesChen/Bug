#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "LayerBase.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"
using namespace cocos2d::ui;


class LayerLogin final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerLogin);

private:
    // 登陆按钮事件
    void loginEvent(Ref* pSender);
    // 跳转注册事件
    void turnToRegister(Ref* pSender);

    EditBox* account;

    EditBox* password;

};

#endif // __LAYER_LOGIN_H__
