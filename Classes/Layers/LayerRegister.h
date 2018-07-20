#ifndef __LAYER_REGISTER_H__
#define __LAYER_REGISTER_H__

#include "ui/CocosGUI.h"

#include "LayerBase.h"

using namespace cocos2d::ui;

class LayerRegister final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerRegister);

private:
    void registerEvent(Ref* pSender);
    void turnToLogin(Ref* pSender);

    TextField* username;
    TextField* password;
    TextField* confirm;
    TextField* email;
};

#endif // __LAYER_REGISTER_H__
