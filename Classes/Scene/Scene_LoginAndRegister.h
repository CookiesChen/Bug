#ifndef __SCENE_LOGIN_AND_REGISTER_H__
#define __SCENE_LOGIN_AND_REGISTER_H__

#include "cocos2d.h"
USING_NS_CC;

class Scene_LoginAndRegister : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Scene_LoginAndRegister);
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__
