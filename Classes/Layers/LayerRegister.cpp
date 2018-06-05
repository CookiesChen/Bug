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
    confirm->setPlaceHolder("confirm password");
    confirm->setMaxLength(8);
    confirm->setFontColor(Color3B::BLACK);
    confirm->setFont("fonts/arial.ttf", 18);
    confirm->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // ÓÊÏäÊäÈë¿ò
    auto email = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    email->setPlaceHolder("email");
    email->setMaxLength(8);
    email->setFontColor(Color3B::BLACK);
    email->setFont("fonts/arial.ttf", 18);
    email->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // ·µ»ØµÇÂ½°´Å¥
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("back", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::turnToLogin, this));
    //×¢²á°´Å¥
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::Register, this));

	account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    confirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    email->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu);
	this->addChild(account);
	this->addChild(password);
    this->addChild(confirm);
    this->addChild(email);
	return true;
}

void LayerRegister::turnToLogin(Ref* pSender) {
    (this->getParent())->getChildByName("Login")->setVisible(true);
    auto rotate = RotateBy::create(0.5f, -180.0f);
    (this->getParent())->getChildByName("Background")->getChildByName("compass")->runAction(rotate);
    this->setVisible(false);
}

void LayerRegister::Register(Ref* pSender) {

}
