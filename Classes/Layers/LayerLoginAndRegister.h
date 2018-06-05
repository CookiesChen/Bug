#pragma once
#ifndef __LAYER_LOGIN_AND_REGISTER_H__
#define __LAYER_LOGIN_AND_REGISTER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class LayerLoginAndRegister : public Scene
{
public:
	LayerLoginAndRegister();

	EditBox* getAccount();
	EditBox* getPassword();
	/*
	Label getAccountText();
	Label getPasswordText();
	*/
private:
	void createAccount();
	void createPassword();
	// ‰»ÎøÚ
	EditBox* account;
	EditBox* password;

	Label accountText;
	Label passwordText;
};

#endif // __SCENE_LOGIN_AND_REGISTER_H__