#include "Helpers.h"
#include "LayerRegister.h"
#include "ServiceAPI.h"
#include "ServiceUser.h"

LayerBase* LayerRegister::createLayer()
{
    return LayerRegister::create();
}

bool LayerRegister::init()
{
    if (!LayerBase::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 账号输入框
    username = TextField::create("", "Arial", 18);
    username->setPlaceHolder("UserName");
    username->setMaxLengthEnabled(true);
    username->setMaxLength(20);
    username->setSize(Size(250, 30));
    username->setTextHorizontalAlignment(TextHAlignment::LEFT);
    username->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 密码输入框
    password = TextField::create("", "Arial", 18);
    password->setPlaceHolder("Password");
    password->setPasswordEnabled(true);
    password->setMaxLengthEnabled(true);
    password->setMaxLength(20);
    password->setSize(Size(250, 30));
    password->setTextHorizontalAlignment(TextHAlignment::LEFT);
    password->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 重复密码框
    confirm = TextField::create("", "Arial", 18);
    confirm->setPlaceHolder("Confirm Password");
    confirm->setPasswordEnabled(true);
    confirm->setMaxLengthEnabled(true);
    confirm->setMaxLength(20);
    confirm->setSize(Size(250, 30));
    confirm->setTextHorizontalAlignment(TextHAlignment::LEFT);
    confirm->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 邮箱输入框
    email = TextField::create("", "Arial", 18);
    email->setPlaceHolder("Email");
    email->setMaxLengthEnabled(true);
    email->setMaxLength(20);
    email->setSize(Size(250, 30));
    email->setTextHorizontalAlignment(TextHAlignment::LEFT);
    email->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 背景框
    auto registerBox = Sprite::createWithSpriteFrameName("RegisterBox.png");
    auto usernameBg = Sprite::create("Graphics/System/input.png");
    auto passwordBg = Sprite::create("Graphics/System/input.png");
    auto confirmBg = Sprite::create("Graphics/System/input.png");
    auto emailBg = Sprite::create("Graphics/System/input.png");
    registerBox->setScale(0.85f);
    usernameBg->setScale(0.5);
    passwordBg->setScale(0.5);
    emailBg->setScale(0.5);
    confirmBg->setScale(0.5);

    // 按钮
    auto loginButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerRegister::turnToLogin, this));
    auto registerButton = MenuItemImage::create("Graphics/System/BtnRegister.png", "Graphics/System/BtnRegister_click.png", CC_CALLBACK_1(LayerRegister::registerEvent, this));
    loginButton->setScale(0.5f);
    registerButton->setScale(0.5f);

    username->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    usernameBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    passwordBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    confirm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    confirmBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    email->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    emailBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 60));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 60));
    registerBox->setPosition(Vec2(visibleSize.width / 2 - 20, visibleSize.height / 2 + 50));


    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(loginButton);
    menu->addChild(registerButton);

    this->addChild(menu, 2);
    this->addChild(username, 2);
    this->addChild(password, 2);
    this->addChild(confirm, 2);
    this->addChild(email, 2);
    this->addChild(usernameBg, 1);
    this->addChild(passwordBg, 1);
    this->addChild(confirmBg, 1);
    this->addChild(emailBg, 1);
    this->addChild(registerBox, 0);
    return true;
}

void LayerRegister::turnToLogin(Ref* pSender)
{
    this->updateLayer(Tag::LayerFromRegisterToLogin);
}

void LayerRegister::registerEvent(Ref* pSender)
{
    if (!this->getActive()) return;
    if (username->getString().size() == 0 || password->getString().size() == 0 || confirm->getString().size() == 0 || email->getString().size() == 0)
    {
        this->dialog("Please input username, password and email.");
        return;
    }
    if (password->getString() != confirm->getString())
    {
        this->dialog("Confirm Passwords are not the same.");
        return;
    }
    auto d = Singleton<ServiceAPI>::GetInstance()->Register(
        username->getString(),
        password->getString(),
        email->getString()
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        string status(d["status"].GetString());
        if (status == "success")
        {
            Singleton<ServiceUser>::GetInstance()->SetEmail(email->getString());
            this->updateLayer(Tag::LayerFromLoginOrRegisterToEmail);
        }
        else if (status == "invalid_email")
        {
            this->dialog("Invalid email.");
        }
        else if (status == "invalid_name")
        {
            this->dialog("Invalid username.");
        }
        else if (status == "invalid_password")
        {
            this->dialog("Invalid password.");
        }
        else if (status == "exist_email")
        {
            this->dialog("This email is used for another account.");
        }
        else if (status == "exist_name")
        {
            this->dialog("This username is used for another account.");
        }
        else if (status == "reserved_name")
        {
            this->dialog("This username is reserved key.");
        }
        else
        {
            this->dialog(string("Unknown status: ") + status);
        }
    }
    else
    {
        this->dialog("Ooops, a system error occurs. Please check your Network.");
    }
}
