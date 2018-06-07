#ifndef __LAYER_REGISTER_H__
#define __LAYER_REGISTER_H__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerRegister : public Layer
{
public:
    static Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(LayerRegister);

    // 跳转登陆事件
    void turnToLogin(Ref* pSender);

    // 注册按钮事件
    void Register(Ref* pSender);
};

#endif // __LAYER_REGISTER_H__
