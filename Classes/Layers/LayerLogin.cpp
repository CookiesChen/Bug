#include "LayerLogin.h"
#include "SceneLoginAndRegister.h"
#include "SceneMenu.h"

Layer * LayerLogin::createLayer()
{
	return LayerLogin::create();
}

bool LayerLogin::init()
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

    // µÇÂ½°´Å¥
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::LogIn, this));
    //×¢²á°´Å¥
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::turnToRegister, this));

    // ±³¾°¿ò
    auto LoginBox = Sprite::createWithSpriteFrameName("LonInBox.png");

	account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));
    LoginBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu, 1);
	this->addChild(account, 1);
	this->addChild(password, 1);
    this->addChild(LoginBox, 0);
	return true;
}

void LayerLogin::LogIn(Ref* pSender) {
    Director::getInstance()->replaceScene(SceneMenu::createScene());
}

void LayerLogin::turnToRegister(Ref* pSender) {
    auto rotate1 = RotateTo::create(0.5f, 180.0f);
    auto rotate2 = RotateTo::create(0.5f, -180.0f);
    auto rotate3 = RotateTo::create(0.5f, 180.0f);

    (this->getParent())->getChildByName("Background")->getChildByName("compass_1")->runAction(rotate1);
    (this->getParent())->getChildByName("Background")->getChildByName("compass_2")->runAction(rotate2);
    (this->getParent())->getChildByName("Background")->getChildByName("compass_3")->runAction(rotate3);

    (this->getParent())->getChildByName("Register")->setVisible(true);
    this->setVisible(false);
}
