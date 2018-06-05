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

    // 登陆按钮事件
    void LogIn(Ref* pSender);
    
    // 跳转注册事件
    void turnToRegister(Ref* pSender);
    CREATE_FUNC(LayerLogin);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
