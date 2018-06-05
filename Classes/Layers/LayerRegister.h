#ifndef __LAYER_REGISTER_H__
#define __LAYER_REGISTER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerRegister : public Layer
{
public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(LayerRegister);

    // ��ת��½�¼�
    void turnToLogin(Ref* pSender);
    
    // ע�ᰴť�¼�
    void Register(Ref* pSender);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
