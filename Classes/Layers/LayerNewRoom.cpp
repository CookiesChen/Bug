#include "Helpers.h"
#include "LayerNewRoom.h"
#include "ServiceAPI.h"
#include "ServiceUser.h"
#include "ServiceRoom.h"

LayerBase* LayerNewRoom::createLayer()
{
    return LayerNewRoom::create();
}

bool LayerNewRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // 标题
    auto labelTitle = Label::createWithTTF("Create a room", "Fonts/arial.ttf", 38);
    labelTitle->setAnchorPoint(Vec2(0, 0));
    labelTitle->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height - 100));
    this->addChild(labelTitle, 1);
    // 房间名称
    float LabelX = visibleSize.width / 2 - 300;
    float Height1 = visibleSize.height - 200;
    auto labelRoomName = Label::createWithTTF("Room Name: ", "Fonts/arial.ttf", 20);
    labelRoomName->setAnchorPoint(Vec2(1, 0.5));
    labelRoomName->setPosition(Vec2(LabelX, Height1));
    this->addChild(labelRoomName, 1);
    // 房间名称输入框
    roomName = ui::TextField::create("", "Arial", 20);
    roomName->setPlaceHolder("Please Input Room Name");
    roomName->setText("my room");
    roomName->setMaxLengthEnabled(true);
    roomName->setMaxLength(27);
    roomName->setAnchorPoint(Vec2(0, 0.5));
    roomName->setTextHorizontalAlignment(TextHAlignment::LEFT);
    roomName->setTextVerticalAlignment(TextVAlignment::CENTER);
    roomName->setPosition(Vec2(labelRoomName->getPosition().x + 50, Height1));
    this->addChild(roomName, 1);

    // 模式选择
    float Height2 = visibleSize.height - 280;
    auto labelMode = Label::createWithTTF("Mode: ", "Fonts/arial.ttf", 20);
    labelMode->setAnchorPoint(Vec2(1, 0.5));
    labelMode->setPosition(Vec2(LabelX, Height2));
    this->addChild(labelMode, 1);
    // 个人模式
    checkModePerson = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkModePerson->setPosition(Vec2(labelMode->getPosition().x + 50, Height2));
    checkModePerson->addEventListener(CC_CALLBACK_2(LayerNewRoom::checkBoxPersonCallback, this));
    checkModePerson->setSelected(true);
    this->mode = "personal";
    this->addChild(checkModePerson, 1);
    auto labelModePerson = Label::createWithTTF("Personal", "Fonts/arial.ttf", 20);
    labelModePerson->setAnchorPoint(Vec2(0, 0.5));
    labelModePerson->setPosition(Vec2(checkModePerson->getPosition().x + checkModePerson->getContentSize().width, Height2));
    this->addChild(labelModePerson, 1);
    // 团队模式
    checkModeTeam = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkModeTeam->setPosition(Vec2(labelModePerson->getPosition().x + labelModePerson->getContentSize().width + 50, Height2));
    checkModeTeam->addEventListener(CC_CALLBACK_2(LayerNewRoom::checkBoxTeamCallback, this));
    checkModeTeam->setSelected(false);
    checkModeTeam->setEnabled(false);
    this->addChild(checkModeTeam, 1);
    auto labelModeTeam = Label::createWithTTF("Team(Coming soon)", "Fonts/arial.ttf", 20);
    labelModeTeam->setAnchorPoint(Vec2(0, 0.5));
    labelModeTeam->setPosition(Vec2(checkModeTeam->getPosition().x + checkModeTeam->getContentSize().width, Height2));
    this->addChild(labelModeTeam, 1);

    // 地图选择
    float Height3 = visibleSize.height - 360;
    auto labelMap = Label::createWithTTF("Map: ", "Fonts/arial.ttf", 20);
    labelMap->setAnchorPoint(Vec2(1, 0.5));
    labelMap->setPosition(Vec2(LabelX, Height3));
    this->addChild(labelMap, 1);
    // 丛林地图模式
    checkMapJungle = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkMapJungle->setPosition(Vec2(labelMap->getPosition().x + 50, Height3));
    checkMapJungle->addEventListener(CC_CALLBACK_2(LayerNewRoom::checkBoxMapJungleCallback, this));
    checkMapJungle->setSelected(true);
    this->addChild(checkMapJungle, 1);
    auto labelMapJungle = Label::createWithTTF("Jungle", "Fonts/arial.ttf", 20);
    labelMapJungle->setAnchorPoint(Vec2(0, 0.5));
    labelMapJungle->setPosition(Vec2(checkMapJungle->getPosition().x + checkMapJungle->getContentSize().width, Height3));
    this->addChild(labelMapJungle, 1);
    // 海岛地图模式
    checkMapIsland = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkMapIsland->setPosition(Vec2(labelMapJungle->getPosition().x + labelMapJungle->getContentSize().width + 50, Height3));
    checkMapIsland->addEventListener(CC_CALLBACK_2(LayerNewRoom::checkBoxMapIslandCallback, this));
    checkMapIsland->setSelected(false);
    checkMapIsland->setEnabled(false);
    this->addChild(checkMapIsland, 1);
    auto labelMapIsland = Label::createWithTTF("Island(Coming soon)", "Fonts/arial.ttf", 20);
    labelMapIsland->setAnchorPoint(Vec2(0, 0.5));
    labelMapIsland->setPosition(Vec2(checkMapIsland->getPosition().x + checkMapIsland->getContentSize().width, Height3));
    this->addChild(labelMapIsland, 1);

    // 随机角色
    float Height4 = visibleSize.height - 440;
    auto labelRandom = Label::createWithTTF("Random Role: ", "Fonts/arial.ttf", 20);
    labelRandom->setAnchorPoint(Vec2(1, 0.5));
    labelRandom->setPosition(Vec2(LabelX, Height4));
    this->addChild(labelRandom, 1);
    checkRandom = ui::CheckBox::create("Graphics/System/CheckBox_Normal.png",
        "Graphics/System/CheckBox_Press.png",
        "Graphics/System/CheckBoxNode_Normal.png",
        "Graphics/System/CheckBox_Disable.png",
        "Graphics/System/CheckBoxNode_Disable.png");
    checkRandom->setPosition(Vec2(labelRandom->getPosition().x + 50, Height4));
    checkRandom->setSelected(true);
    //---
    checkRandom->setEnabled(false);
    //---
    this->addChild(checkRandom, 1);

    // 房间人数
    float Height5 = visibleSize.height - 520;
    labelRoomPlayer = Label::createWithTTF("Players Count: ", "Fonts/arial.ttf", 20);
    labelRoomPlayer->setAnchorPoint(Vec2(1, 0.5));
    labelRoomPlayer->setPosition(Vec2(LabelX, Height5));
    this->addChild(labelRoomPlayer, 1);
    labelRoomPlayerCount = Label::createWithTTF("2", "Fonts/arial.ttf", 20);
    labelRoomPlayerCount->setAnchorPoint(Vec2(0, 0.5));
    labelRoomPlayerCount->setPosition(Vec2(labelRoomPlayer->getPosition().x + 20, Height5));
    this->addChild(labelRoomPlayerCount, 1);
    // 进度条
    slider = ui::Slider::create();
    slider->loadBarTexture("Graphics/System/Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("Graphics/System/SliderNode_Normal.png", "Graphics/System/SliderNode_Press.png", "Graphics/System/SliderNode_Disable.png");
    slider->loadProgressBarTexture("Graphics/System/Slider_PressBar.png");
    slider->setMaxPercent(6);
    slider->setAnchorPoint(Vec2(0, 0.5));
    slider->setPosition(Vec2(labelRoomPlayerCount->getPosition().x + 50, Height5));
    slider->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
    {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            char str[50];
            this->playerCount = this->slider->getPercent() + 2;
            sprintf(str, "%d", this->slider->getPercent() + 2);
            this->labelRoomPlayerCount->setString(str);
            break;
        default:
            break;
        }
    });
    this->playerCount = 2;
    this->addChild(slider, 1);


    // 房间密码
    float Height6 = visibleSize.height - 600;
    auto labelRoomPassword = Label::createWithTTF("Room Password: ", "Fonts/arial.ttf", 20);
    labelRoomPassword->setAnchorPoint(Vec2(1, 0.5));
    labelRoomPassword->setPosition(Vec2(LabelX, Height6));
    this->addChild(labelRoomPassword, 1);
    // 密码输入框
    roomPassword = ui::TextField::create("", "Arial", 20);
    roomPassword->setPlaceHolder("No password");
    roomPassword->setMaxLengthEnabled(true);
    roomPassword->setMaxLength(20);
    roomPassword->setPasswordEnabled(true);
    roomPassword->setAnchorPoint(Vec2(0, 0.5));
    roomPassword->setTextHorizontalAlignment(TextHAlignment::LEFT);
    roomPassword->setTextVerticalAlignment(TextVAlignment::CENTER);
    roomPassword->setPosition(Vec2(labelRoomPassword->getPosition().x + 50, Height6));
    roomPassword->setEnabled(false);
    this->addChild(roomPassword, 1);

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);
    // 返回菜单
    auto buttonBack = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerNewRoom::backMenu, this));
    buttonBack->setPosition(Vec2(150, visibleSize.height - 50));
    buttonBack->setScale(0.5f);
    menu->addChild(buttonBack, 1);
    // 提交
    auto buttonCommit = MenuItemImage::create("Graphics/System/BtnCreate.png", "Graphics/System/BtnCreate_click.png", CC_CALLBACK_1(LayerNewRoom::newRoom, this));
    buttonCommit->setPosition(Vec2(visibleSize.width / 2, 100));
    buttonCommit->setScale(0.5f);
    menu->addChild(buttonCommit, 1);

    this->addChild(menu, 1);

    return true;
}

void LayerNewRoom::backMenu(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromJoinRoomOrNewRoomToMenu);
}

void LayerNewRoom::refreshRoomName()
{
    this->roomName->setText(Singleton<ServiceUser>::GetInstance()->GetNikename() + "'s room");
}

void LayerNewRoom::checkBoxPersonCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->mode = "personal";
    this->checkModePerson->setSelected(true);
    this->checkModeTeam->setSelected(false);
}

void LayerNewRoom::checkBoxTeamCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->mode = "team";
    this->checkModeTeam->setSelected(true);
    this->checkModePerson->setSelected(false);

}

void LayerNewRoom::checkBoxMapJungleCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->checkMapJungle->setSelected(true);
}

void LayerNewRoom::checkBoxMapIslandCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    this->checkMapIsland->setSelected(true);
}

void LayerNewRoom::newRoom(Ref* pSender)
{
    // todo 新建房间的API
    auto d = Singleton<ServiceAPI>::GetInstance()->CreateRoom(
        roomName->getString(),
        roomPassword->getString(),
        "jungle",
        this->mode,
        this->playerCount
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            // 跳转到房间页面
            Singleton<ServiceRoom>::GetInstance()->createRoom();
            this->updateScene(Tag::SceneFromMenuToRoom);
        }
        else
        {
            this->dialog("Error req");
            // 参数错误的提示
        }
    }
    else
    {
        this->dialog("Error data");
        // 解析失败的提示
        return;
    }
}
