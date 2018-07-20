#include "Helpers.h"
#include "LayerEmail.h"
#include "ServiceAPI.h"
#include "ServiceUser.h"

LayerBase* LayerEmail::createLayer()
{
    return LayerEmail::create();
}

bool LayerEmail::init()
{
    if (!LayerBase::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::create("Verify Your Email", "Fonts/arial.ttf", 24);
    email = Label::create("", "Fonts/arial.ttf", 20);
    email->setContentSize(Size(250, 30));

    auto resendButton = MenuItemImage::create("Graphics/System/BtnRegister.png", "Graphics/System/BtnRegister_click.png", CC_CALLBACK_1(LayerEmail::resend, this));
    auto verifyButton = MenuItemImage::create("Graphics/System/BtnLogin.png", "Graphics/System/BtnLogin_click.png", CC_CALLBACK_1(LayerEmail::verify, this));
    resendButton->setScale(0.5f);
    verifyButton->setScale(0.5f);

    // 背景框
    auto box = Sprite::createWithSpriteFrameName("Dialog.png");
    auto codeBg = Sprite::create("Graphics/System/input.png");
    codeBg->setOpacity(20);

    // 输入框
    code = TextField::create("", "Arial", 18);
    code->setPlaceHolder("Code");
    code->setMaxLengthEnabled(true);
    code->setMaxLength(20);
    code->setSize(Size(250, 30));
    code->setTextHorizontalAlignment(TextHAlignment::LEFT);
    code->setTextVerticalAlignment(TextVAlignment::CENTER);

    box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 60));
    email->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2));
    code->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 - 50));
    codeBg->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 - 50));
    resendButton->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2));
    verifyButton->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(resendButton);
    menu->addChild(verifyButton);

    this->addChild(label, 2);
    this->addChild(email, 2);
    this->addChild(menu, 2);
    this->addChild(code, 2);
    this->addChild(codeBg, 1);
    this->addChild(box, 0);

    return true;
}

void LayerEmail::setActive(bool active)
{
    if (active)
    {
        email->setString(Singleton<ServiceUser>::GetInstance()->GetEmail());
        auto d = Singleton<ServiceAPI>::GetInstance()->GetEmailCode();
        if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
        {
            if (strcmp(d["status"].GetString(), "success") == 0)
            {
                this->dialog("Send email successfully.");
            }
            else
            {
                this->dialog("Send email failed. Is your logged?");
            }
        }
        else
        {
            this->dialog("Ooops, a system error occurs. Please check your Network.");
        }
    }
    LayerBase::setActive(active);
}

void LayerEmail::resend(Ref * pSender)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->GetEmailCode();
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            this->dialog("Send email successfully.");
        }
        else
        {
            this->dialog("Send email failed. Is your logged?");
        }
    }
    else
    {
        this->dialog("Ooops, a system error occurs. Please check your Network.");
    }
}

void LayerEmail::verify(Ref * pSender)
{
    
}
