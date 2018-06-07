#ifndef __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__
#define __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerLoginAndRegisterBackground : public Layer
{
public:
    static Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(LayerLoginAndRegisterBackground);
};

#endif // __LAYER_LOGIN_AND_REGISTER_BACKGROUND_H__
