#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "cocos-ext.h"
#include "LayerBase.h"

USING_NS_CC_EXT;


class LayerLogin : public LayerBase
{
public:
    static LayerBase* createLayer();
    virtual bool init();

    // 登陆按钮事件
    void logIn(Ref* pSender);
    // 跳转注册事件
    void turnToRegister(Ref* pSender);

    CREATE_FUNC(LayerLogin);
};

#endif // __LAYER_LOGIN_H__
