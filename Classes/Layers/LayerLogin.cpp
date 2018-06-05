#include "LayerLogin.h"

Layer * LayerLogin::createLayer()
{
	return LayerLogin::create();
}

bool LayerLogin::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// ÕËºÅÊäÈë¿ò
	auto account = EditBox::create(Size(300, 35), Scale9Sprite::create("HelloWorld.png"));
	account->setPlaceHolder("account");
	account->setMaxLength(8);
	account->setFontColor(Color3B::BLACK);

	// ÃÜÂëÊäÈë¿ò
	auto password = EditBox::create(Size(300, 35), Scale9Sprite::create("HelloWorld.png"));
	password->setPlaceHolder("password");
	password->setMaxLength(8);
	password->setFontColor(Color3B::BLACK);

    // µÇÂ½°´Å¥
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/arial.ttf", 36), CC_CALLBACK_1(LayerLogin::login, this));
    //×¢²á°´Å¥
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 36), CC_CALLBACK_1(LayerLogin::login, this));

	account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu);
	this->addChild(account);
	this->addChild(password);
	return true;
}

void LayerLogin::login(Ref* pSender) {

}
