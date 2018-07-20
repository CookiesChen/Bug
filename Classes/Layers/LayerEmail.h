#ifndef __LAYER_EMAIL_H__
#define __LAYER_EMAIL_H__

#include "ui/CocosGUI.h"

#include "LayerBase.h"

using namespace cocos2d::ui;

class LayerEmail final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;
    virtual void setActive(bool active) override;

    CREATE_FUNC(LayerEmail);

private:
    void resend(Ref* pSender);
    void verify(Ref* pSender);

    Label * email;
    TextField* code;
};

#endif // __LAYER_EMAIL_H__
