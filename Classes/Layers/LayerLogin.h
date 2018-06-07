#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerLogin : public Layer
{
public:
    static Layer* createLayer();
    virtual bool init();

    // 登陆按钮事件
    void LogIn(Ref* pSender);

    // 跳转注册事件
    void turnToRegister(Ref* pSender);
    CREATE_FUNC(LayerLogin);
};

#endif // __LAYER_LOGIN_H__
