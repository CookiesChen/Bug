﻿#ifndef __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__
#define __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__

#include "LayerBase.h"

class LayerLoginAndRegisterBackground final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void transition();

    CREATE_FUNC(LayerLoginAndRegisterBackground);

private:
    Sprite* compass_1;
    Sprite* compass_2;
    Sprite* compass_3;

    bool transitionCount;
};

#endif // __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__
