#include "Helpers.h"
#include "LayerLogin.h"
#include "ModelUser.h"
#include "ServiceAPI.h"
#include "ServiceUser.h"

LayerBase* LayerLogin::createLayer()
{
    return LayerLogin::create();
}

bool LayerLogin::init()
{
    if (!LayerBase::init()) return false;

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
    password->setMaxLengthEnabled(true);
    password->setMaxLength(20);
    password->setSize(Size(250, 30));
    password->setPasswordEnabled(true);
    password->setTextHorizontalAlignment(TextHAlignment::LEFT);
    password->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 按钮
    auto loginButton = MenuItemImage::create("Graphics/System/BtnLogin.png", "Graphics/System/BtnLogin_click.png", CC_CALLBACK_1(LayerLogin::loginEvent, this));
    auto registerButton = MenuItemImage::create("Graphics/System/BtnRegister.png", "Graphics/System/BtnRegister_click.png", CC_CALLBACK_1(LayerLogin::turnToRegister, this));
    loginButton->setScale(0.5f);
    registerButton->setScale(0.5f);


    // 背景框
    auto loginBox = Sprite::createWithSpriteFrameName("LoginBox.png");
    auto accountBackground = Sprite::create("Graphics/System/input.png");
    accountBackground->setOpacity(20);
    auto passwordBackground = Sprite::create("Graphics/System/input.png");
    passwordBackground->setOpacity(20);

    account->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    password->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    loginButton->setPosition(Vec2(visibleSize.width / 2 - 70, visibleSize.height / 2 - 60));
    registerButton->setPosition(Vec2(visibleSize.width / 2 + 70, visibleSize.height / 2 - 60));
    loginBox->setPosition(Vec2(visibleSize.width / 2 - 25, visibleSize.height / 2));
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
    this->addChild(loginBox, 0);

    return true;
}


void LayerLogin::loginEvent(Ref* pSender)
{
    if (!this->getActive()) return;
    if (account->getString().size() == 0 || password->getString().size() == 0)
    {
        this->dialog("Please input username/email and password.");
        return;
    }
    auto d = Singleton<ServiceAPI>::GetInstance()->Login(
        account->getString(),
        password->getString()
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        string status(d["status"].GetString());
        if (status == "success")
        {
            string msg(d["msg"].GetString());
            if (msg == "new_user")
            {
                // todo 新用户
            }
            else
            {
                // todo 用户名为msg
                //Singleton<ModelUser>::GetInstance()->setUserId(account->getString());
                this->updateScene(Tag::SceneFromLoginAndRegisterToMenu);
            }
        }
        else if (status == "not_valid")
        {
            Singleton<ServiceUser>::GetInstance()->SetEmail(d["msg"].GetString());
            this->updateLayer(Tag::LayerFromLoginOrRegisterToEmail);
        }
        else
        {
            this->dialog("Error username/email or password.");
        }
    }
    else
    {
        this->dialog("Ooops, a system error occurs. Please check your Network.");
    }
}

void LayerLogin::turnToRegister(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromLoginToRegister);
}
