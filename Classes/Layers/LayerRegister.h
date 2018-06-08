#ifndef __LAYER_REGISTER_H__
#define __LAYER_REGISTER_H__

#include "LayerBase.h"

class LayerRegister final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerRegister);

private:
    // 注册按钮事件
    void registerEvent(Ref* pSender);
    // 跳转登陆事件
    void turnToLogin(Ref* pSender);
};

#endif // __LAYER_REGISTER_H__
