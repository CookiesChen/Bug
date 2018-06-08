#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "LayerBase.h"

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
};

#endif // __LAYER_LOGIN_H__
