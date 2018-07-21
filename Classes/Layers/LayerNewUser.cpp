#include "LayerNewUser.h"
#include "Helpers.h"
#include "ServiceAPI.h"

LayerBase* LayerNewUser::createLayer()
{
    return LayerNewUser::create();
}

bool LayerNewUser::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    float LabelX = visibleSize.width / 2 - 300;
    // 欢迎语
    float Height1 = visibleSize.height - 100;
    auto labelWelcome = Label::createWithTTF("Welcome to Bug World", "Fonts/arial.ttf", 30);
    labelWelcome->setAnchorPoint(Vec2(0.5, 0.5));
    labelWelcome->setPosition(Vec2(visibleSize.width / 2, Height1));
    this->addChild(labelWelcome, 1);
    // 用户名称
    float Height2 = visibleSize.height - 200;
    auto labelUserName = Label::createWithTTF("Your nikename: ", "Fonts/arial.ttf", 20);
    labelUserName->setAnchorPoint(Vec2(1, 0.5));
    labelUserName->setPosition(Vec2(LabelX, Height2));
    this->addChild(labelUserName, 1);
    // 用户名称输入框
    userName = ui::TextField::create("", "Arial", 20);
    userName->setPlaceHolder("Please input your nikename");
    userName->setMaxLengthEnabled(true);
    userName->setMaxLength(20);
    userName->setAnchorPoint(Vec2(0, 0.5));
    userName->setTextHorizontalAlignment(TextHAlignment::LEFT);
    userName->setTextVerticalAlignment(TextVAlignment::CENTER);
    userName->setPosition(Vec2(labelUserName->getPosition().x + 50, Height2));
    this->addChild(userName, 1);

    // 性别选择
    float Height3 = visibleSize.height - 300;
    auto labelGender = Label::createWithTTF("Gender: ", "Fonts/arial.ttf", 20);
    labelGender->setAnchorPoint(Vec2(1, 0.5));
    labelGender->setPosition(Vec2(LabelX, Height3));
    this->addChild(labelGender, 1);
    // man
    checkGenderMan = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkGenderMan->setPosition(Vec2(labelGender->getPosition().x + 50, Height3));
    checkGenderMan->addEventListener(CC_CALLBACK_2(LayerNewUser::checkBoxManCallback, this));
    checkGenderMan->setSelected(true);
    this->isMan = true;
    this->addChild(checkGenderMan, 1);
    auto labelModePerson = Label::createWithTTF("Man", "Fonts/arial.ttf", 20);
    labelModePerson->setPosition(Vec2(checkGenderMan->getPosition().x + checkGenderMan->getContentSize().width + 20, Height3));
    this->addChild(labelModePerson, 1);
    // woman
    checkGenderWoman = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkGenderWoman->setPosition(Vec2(labelModePerson->getPosition().x + labelModePerson->getContentSize().width + 50, Height3));
    checkGenderWoman->addEventListener(CC_CALLBACK_2(LayerNewUser::checkBoxWomanCallback, this));
    checkGenderWoman->setSelected(false);
    this->addChild(checkGenderWoman, 1);
    auto labelModeTeam = Label::createWithTTF("Woman", "Fonts/arial.ttf", 20);
    labelModeTeam->setPosition(Vec2(checkGenderWoman->getPosition().x + checkGenderWoman->getContentSize().width + 20, Height3));
    this->addChild(labelModeTeam, 1);

    // 用户选择头像 (暂时不做)


    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);
    // 提交
    auto buttonCommit = MenuItemImage::create("Graphics/System/BtnRegister.png", "Graphics/System/BtnRegister_click.png", CC_CALLBACK_1(LayerNewUser::setUserInfo, this));
    buttonCommit->setPosition(Vec2(visibleSize.width / 2, 100));
    buttonCommit->setScale(0.5f);
    menu->addChild(buttonCommit, 1);

    this->addChild(menu, 1);
    return true;
}

void LayerNewUser::checkBoxManCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->isMan = true;
    this->checkGenderMan->setSelected(true);
    this->checkGenderWoman->setSelected(false);
}

void LayerNewUser::checkBoxWomanCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->isMan = false;
    this->checkGenderWoman->setSelected(true);
    this->checkGenderMan->setSelected(false);

}

void LayerNewUser::setUserInfo(Ref* pSender)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetUserInfo(
        this->userName->getString(),
        this->isMan ? 0 : 1,
        "default"
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            // 跳转到房间页面
            this->dialog("Set user info success!");
            this->updateLayer(Tag::LayerFromNewUserToMenu);
        }
        else
        {
            this->dialog("error userName!");
            // 参数错误的提示
        }
    }
    else
    {
        this->dialog("Oop!");
        // 解析失败的提示
        return;
    }
}
