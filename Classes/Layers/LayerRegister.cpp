#include "cocos-ext.h"

#include "LayerRegister.h"

USING_NS_CC_EXT;

LayerBase* LayerRegister::createLayer()
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
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerRegister::registerEvent, this));

    // 背景框
    auto registerBox = Sprite::createWithSpriteFrameName("RegisterBox.png");
    registerBox->setScale(0.85f);

    account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    confirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    email->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));
    registerBox->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2 + 50));


    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu, 1);
    this->addChild(account, 1);
    this->addChild(password, 1);
    this->addChild(confirm, 1);
    this->addChild(email, 1);
    this->addChild(registerBox, 0);
    return true;
}

void LayerRegister::turnToLogin(Ref* pSender)
{
    this->updateLayer();
}

void LayerRegister::registerEvent(Ref* pSender)
{

}
