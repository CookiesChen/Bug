#include "LayerNewRoom.h"
#include "ui/CocosGUI.h"
#include "Helpers.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace rapidjson;
LayerBase* LayerNewRoom::createLayer()
{
    return LayerNewRoom::create();
}

bool LayerNewRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 返回菜单
    auto buttonBack = MenuItemImage::create("BtnBack.png", "BtnBack_click.png",
        CC_CALLBACK_1(LayerNewRoom::backMenu, this));
    // 提交
    auto buttonCommit = MenuItemLabel::create(Label::createWithTTF("Create", "fonts/arial.ttf", 30), CC_CALLBACK_1(LayerNewRoom::newRoom, this));
    // todo 房间密码 LayerNewRoom
    /*auto checkbox = ui::CheckBox::create("CheckBox_Normal.png",
        "CheckBox_Press.png",
        "CheckBoxNode_Normal.png",
        "CheckBox_Disable.png",
        "CheckBoxNode_Disable.png");
    checkbox->setPosition(Vec2(400, visibleSize.height - 50));
    this->addChild(checkbox, 1);*/
    // 房间名称
    auto labelRoomName = Label::createWithTTF("Room Name: ", "fonts/arial.ttf", 20);
    labelRoomName->setAnchorPoint(Vec2(0, 0));

    roomName = ui::TextField::create("", "Arial", 18);
    roomName->setPlaceHolder("Name");
    roomName->setMaxLengthEnabled(true);
    roomName->setMaxLength(20);
    roomName->setSize(Size(250, 30));
    roomName->setTextHorizontalAlignment(TextHAlignment::LEFT);
    roomName->setTextVerticalAlignment(TextVAlignment::CENTER);

    // 房间人数
    labelRoomPlayer = Label::createWithTTF("Players Count: ", "fonts/arial.ttf", 20);
    labelRoomPlayer->setAnchorPoint(Vec2(0, 0));
    slider = ui::Slider::create();
    slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setMaxPercent(8);
    slider->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            char str[50];
            this->playerCount = this->slider->getPercent();
            sprintf(str, "Players Count: %d", this->slider->getPercent());
            this->labelRoomPlayer->setString(str);
            break;
        default:
            break;
        }
    });

    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 10));
    labelRoomPlayer->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 40));

    roomName->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
    labelRoomName->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 120));

    buttonBack->setPosition(Vec2(150, visibleSize.height - 50));
    buttonCommit->setPosition(Vec2(visibleSize.width / 2, 100));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(buttonBack);
    menu->addChild(buttonCommit);

    this->addChild(menu, 1);
    this->addChild(roomName, 1);
    this->addChild(labelRoomName, 1);
    this->addChild(labelRoomPlayer, 1);
    this->addChild(slider, 1);


    return true;
}


void LayerNewRoom::backMenu(Ref* pSender) {
    this->targetLayer = 0;
    this->updateLayer();
}

void LayerNewRoom::newRoom(Ref* pSender) {

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valTitle, valPlayer;
    valTitle.SetString(roomName->getString().c_str(), allocator);
    valPlayer.SetInt(this->playerCount);
    document.AddMember("title", valTitle, allocator);
    document.AddMember("password", "", allocator);
    document.AddMember("gameMap", "default", allocator);
    document.AddMember("gameMode", "personal", allocator);
    document.AddMember("maxPlayer", valPlayer, allocator);
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::getInstance()->Post(
        "room/new",
        buffer.GetString()
    );

    log("Res:%s\n", res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status")) {
        if (strcmp(d["status"].GetString(), "success") == 0) {
            // todo 加入游戏 LayerNewRoom
            this->updateScene();
        }
        else {
            // todo 参数错误的提示 LayerNewRoom
        }
    }
    else {
        // todo 解析失败的提示 LayerNewRoom
        return;
    }
}
