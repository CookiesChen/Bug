#ifndef __LAYER_NEW_USER_H__
#define __LAYER_NEW_USER_H__

#include "LayerBase.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;

class LayerNewUser final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setUserInfo(Ref* pSender);

    void checkBoxManCallback(cocos2d::Ref * ref, CheckBox::EventType type);
    void checkBoxWomanCallback(cocos2d::Ref * ref, CheckBox::EventType type);

    CREATE_FUNC(LayerNewUser);

private:
    TextField* userName;
    CheckBox* checkGenderMan;
    CheckBox* checkGenderWoman;
    bool isMan;
};

#endif // __LAYER_NEW_USER_H__
