#include "LayerLoginAndRegister.h"

LayerLoginAndRegister::LayerLoginAndRegister()
{
	createAccount();
	createPassword();
}

EditBox* LayerLoginAndRegister::getAccount()
{
	return account;
}

EditBox* LayerLoginAndRegister::getPassword()
{
	return password;
}

void LayerLoginAndRegister::createAccount()
{
	account = EditBox::create(Size(300, 35), Scale9Sprite::create("HelloWorld.png"));
	account->setPlaceHolder("account");
	account->setMaxLength(8);
	account->setFontColor(Color3B::BLACK);
}

void LayerLoginAndRegister::createPassword()
{
	password = EditBox::create(Size(300, 35), Scale9Sprite::create("HelloWorld.png"));
	password->setPlaceHolder("password");
	password->setMaxLength(8);
	password->setFontColor(Color3B::BLACK);
}