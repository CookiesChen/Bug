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

    // ��½��ť�¼�
    void LogIn(Ref* pSender);
    
    // ��תע���¼�
    void turnToRegister(Ref* pSender);
    CREATE_FUNC(LayerLogin);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
