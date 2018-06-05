#ifndef __LAYER_LOGIN_H__
#define __LAYER_LOGIN_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerLogin : public Layer
{
public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(LayerLogin);
    void login(Ref* pSender);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
