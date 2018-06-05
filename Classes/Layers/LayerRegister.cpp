#include "LayerRegister.h"
#include "SceneLoginAndRegister.h"

Layer * LayerRegister::createLayer()
{
	return LayerRegister::create();
}

bool LayerRegister::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// ÕËºÅÊäÈë¿ò
	auto account = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
	account->setPlaceHolder("account");
	account->setMaxLength(8);
	account->setFontColor(Color3B::BLACK);
    account->setFont("fonts/arial.ttf",18);

	// ÃÜÂëÊäÈë¿ò
	auto password = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
	password->setPlaceHolder("password");
	password->setMaxLength(8);
	password->setFontColor(Color3B::BLACK);
    password->setFont("fonts/arial.ttf", 18);
    password->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // ÖØ¸´ÃÜÂë¿ò
    auto confirm = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    confirm->setPlaceHolder("confirm");
    confirm->setMaxLength(8);
    confirm->setFontColor(Color3B::BLACK);
    confirm->setFont("fonts/arial.ttf", 18);
    confirm->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // µÇÂ½°´Å¥
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::turnToLogin, this));
    //×¢²á°´Å¥
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::Register, this));

	account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    confirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
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

void LayerRegister::turnToLogin(Ref* pSender) {

}

void LayerRegister::Register(Ref* pSender) {

}
