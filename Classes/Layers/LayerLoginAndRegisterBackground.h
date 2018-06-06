#ifndef __LAYER_BACKGROUND_H__
#define __LAYER_BACKGROUND_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerLoginAndRegisterBackground : public Layer
{
public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(LayerLoginAndRegisterBackground);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
