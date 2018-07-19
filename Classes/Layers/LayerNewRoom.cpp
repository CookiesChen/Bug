#include "Helpers.h"
#include "LayerNewRoom.h"
#include "ServiceAPI.h"
#include "ui/CocosGUI.h"


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
    // todo 房间密码
    // todo 房间地图的选择
    // todo 房间模式的选择（个人、团队）
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
    slider->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
    {
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

void LayerNewRoom::backMenu(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromJoinRoomOrNewRoomToMenu);
}

void LayerNewRoom::newRoom(Ref* pSender)
{
    // todo 新建房间的API
    auto d = Singleton<ServiceAPI>::GetInstance()->CreateRoom(
        roomName->getString(),
        "",
        "default",
        "personal",
        this->playerCount
    );
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            // 跳转到房间页面
            this->updateScene();
        }
        else
        {
            // 参数错误的提示
        }
    }
    else
    {
        // 解析失败的提示
        return;
    }
}
