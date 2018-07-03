#include "Helpers.h"
#include "LayerLogin.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include <iostream>

using namespace std;
using namespace rapidjson;

USING_NS_CC_EXT;

LayerBase* LayerLogin::createLayer()
{
    return LayerLogin::create();
}

bool LayerLogin::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 账号输入框
    account = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    account->setPlaceHolder("account");
    account->setMaxLength(88);
    account->setFontColor(Color3B::BLACK);
    account->setFont("fonts/arial.ttf", 18);

    // 密码输入框
    password = EditBox::create(Size(250, 30), Scale9Sprite::create("input.png"));
    password->setPlaceHolder("password");
    password->setMaxLength(88);
    password->setFontColor(Color3B::BLACK);
    password->setFont("fonts/arial.ttf", 18);
    password->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);

    // 登陆按钮
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::loginEvent, this));
    // 注册按钮
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::turnToRegister, this));

    // 背景框
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


void LayerLogin::loginEvent(Ref* pSender)
{

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valAccount, valPass;
    valAccount.SetString(account->getText(), allocator);
    valPass.SetString(Hash::sha512(password->getText()).c_str() , allocator);
    document.AddMember("name", valAccount, allocator);
    document.AddMember("password", valPass, allocator);
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::getInstance()->Post(
        "http://127.0.0.1:30081/user/login",
        buffer.GetString()
    );

    log("Res:%s\n", res.c_str());


    // this->updateScene();
}

void LayerLogin::turnToRegister(Ref* pSender)
{
    this->updateLayer();
}
