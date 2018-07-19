#include "Helpers.h"
#include "LayerLogin.h"
#include "ServiceAPI.h"
#include "UserModel.h"

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
    account = TextField::create("", "Arial", 18);
    account->setPlaceHolder("UserName/Email");
    account->setMaxLengthEnabled(true);
    account->setMaxLength(20);
    account->setSize(Size(250, 30));
    account->setTextHorizontalAlignment(TextHAlignment::LEFT);
    account->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 密码输入框
    password = TextField::create("", "Arial", 18);
    password->setPlaceHolder("password");
    account->setMaxLengthEnabled(true);
    password->setMaxLength(20);
    password->setSize(Size(250, 30));
    password->setPasswordEnabled(true);
    account->setTextHorizontalAlignment(TextHAlignment::LEFT);
    account->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 登陆按钮
    auto loginButton = MenuItemLabel::create(Label::createWithTTF("Login", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::loginEvent, this));
    // 注册按钮
    auto registerButton = MenuItemLabel::create(Label::createWithTTF("Register", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerLogin::turnToRegister, this));

    // 背景框
    auto LoginBox = Sprite::createWithSpriteFrameName("LonInBox.png");
    auto accountBackground = Sprite::create("input.png");
    accountBackground->setOpacity(20);
    auto passwordBackground = Sprite::create("input.png");
    passwordBackground->setOpacity(20);

    account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 50));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 50));
    LoginBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    accountBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    passwordBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu, 1);
    this->addChild(account, 2);
    this->addChild(password, 2);
    this->addChild(accountBackground, 1);
    this->addChild(passwordBackground, 1);
    this->addChild(LoginBox, 0);

    return true;
}


void LayerLogin::loginEvent(Ref* pSender)
{
    if (!this->getActive()) return;
    auto d = Singleton<ServiceAPI>::GetInstance()->Login(
        account->getString(),
        password->getString()
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            this->updateScene();
        }
        else
        {
            // todo 密码错误或用户不存在的提示 LayerLogin
        }
    }
    else
    {
        // todo 解析失败的提示 LayerLogin
        return;
    }
}

void LayerLogin::turnToRegister(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromLoginToRegister);
}
