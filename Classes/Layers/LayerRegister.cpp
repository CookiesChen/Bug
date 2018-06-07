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

    // 账号输入框
    auto account = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    account->setPlaceHolder("account");
    account->setMaxLength(8);
    account->setFontColor(Color3B::BLACK);
    account->setFont("fonts/arial.ttf", 18);

    // 密码输入框
    auto password = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    password->setPlaceHolder("password");
    password->setMaxLength(8);
    password->setFontColor(Color3B::BLACK);
    password->setFont("fonts/arial.ttf", 18);
    password->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // 重复密码框
    auto confirm = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    confirm->setPlaceHolder("confirm password");
    confirm->setMaxLength(8);
    confirm->setFontColor(Color3B::BLACK);
    confirm->setFont("fonts/arial.ttf", 18);
    confirm->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // 邮箱输入框
    auto email = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    email->setPlaceHolder("email");
    email->setMaxLength(20);
    email->setFontColor(Color3B::BLACK);
    email->setFont("fonts/arial.ttf", 18);

    // 返回登陆按钮
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("back", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::turnToLogin, this));
    //注册按钮
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::Register, this));

    // 背景框
    auto RegisterBox = Sprite::createWithSpriteFrameName("RegisterBox.png");
    RegisterBox->setScale(0.85);

    account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    confirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    email->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));
    RegisterBox->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2 + 50));


    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu, 1);
    this->addChild(account, 1);
    this->addChild(password, 1);
    this->addChild(confirm, 1);
    this->addChild(email, 1);
    this->addChild(RegisterBox, 0);
    return true;
}

void LayerRegister::turnToLogin(Ref* pSender)
{
    auto rotate1 = RotateTo::create(0.5f, 0.0f);
    auto rotate2 = RotateTo::create(0.5f, 0.0f);
    auto rotate3 = RotateTo::create(0.5f, 0.0f);

    this->getParent()->getChildByName("Background")->getChildByName("compass_1")->runAction(rotate1);
    this->getParent()->getChildByName("Background")->getChildByName("compass_2")->runAction(rotate2);
    this->getParent()->getChildByName("Background")->getChildByName("compass_3")->runAction(rotate3);

    this->getParent()->getChildByName("Login")->setVisible(true);
    this->setVisible(false);
}

void LayerRegister::Register(Ref* pSender)
{}
