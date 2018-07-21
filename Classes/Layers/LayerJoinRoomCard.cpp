#include "Helpers.h"
#include "LayerJoinRoomCard.h"
#include "ServiceRoom.h"

ModelRoom LayerJoinRoomCard::room;

LayerBase* LayerJoinRoomCard::createLayerWithRoom(const ModelRoom& r)
{
    room = r;
    return LayerJoinRoomCard::create();
}

bool LayerJoinRoomCard::init()
{
    if (!LayerBase::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto padding = 20;
    auto width = 700.0f;
    auto height = 100.0f;
    auto mapImageWidth = 70.0f;

    int i = 0;

    this->setContentSize(Size(width, height));

    auto itembackground = Sprite::create("Graphics/System/BtnBack.png");
    itembackground->setContentSize(Size::Size(width, height));
    itembackground->setPosition(Vec2(width / 2, height / 2));

    auto mapimage = Sprite::create("Graphics/Pictures/background.png");
    mapimage->setContentSize(Size(mapImageWidth, mapImageWidth));
    mapimage->setPosition(Vec2(width / 2 - 250, height / 2));

    auto roomname = Label::createWithTTF(string("Room Name: ") + room.Title, "Fonts/arial.ttf", 15);
    roomname->setColor(Color3B::BLACK);
    roomname->setAnchorPoint(Vec2(0, 0.5));
    roomname->setPosition(Vec2(width / 2 - 210, height / 2 - padding));

    auto owner = Label::createWithTTF(string("Owner: ") + room.OwnId, "Fonts/arial.ttf", 15);
    owner->setColor(Color3B::BLACK);
    owner->setAnchorPoint(Vec2(0, 0.5));
    owner->setPosition(Vec2(width / 2 - 210, height / 2));

    auto mapname = Label::createWithTTF(string("Map: ") + room.GameMap, "Fonts/arial.ttf", 15);
    mapname->setColor(Color3B::BLACK);
    mapname->setAnchorPoint(Vec2(0, 0.5));
    mapname->setPosition(Vec2(width / 2 - 210, height / 2 + padding));

    // 是否有密码
    if (room.Password.size())
    {
        auto lock = Sprite::create("Graphics/System/lock.jpg");
        lock->setContentSize(Size::Size(25, 25));
        lock->setPosition(Vec2(width / 2 + 90, height / 2 + padding));
        this->addChild(lock, 3);
    }

    // 房间状态 waiting / playing
    auto status = Label::createWithTTF("", "Fonts/arial.ttf", 15);
    status->setAnchorPoint(Vec2(1, 0.5));
    if (!room.Playing)
    {
        status->setString("waiting");
        status->setColor(Color3B::GREEN);
    }
    else
    {
        status->setString("playing");
        status->setColor(Color3B::YELLOW);
    }
    status->setPosition(Vec2(width / 2 + 160, height / 2 + padding));

    // 游戏模式 random / optional
    auto mode = Label::createWithTTF(string("Mode: ") + room.Mode, "Fonts/arial.ttf", 15);
    mode->setAnchorPoint(Vec2(1, 0.5));
    mode->setColor(Color3B::BLACK);
    mode->setPosition(Vec2(width / 2 + 160, height / 2));

    auto count = Label::createWithTTF(to_string(room.Players.size()) + "/" + to_string(room.MaxPalyer), "Fonts/arial.ttf", 15);
    count->setAnchorPoint(Vec2(1, 0.5));
    count->setColor(Color3B::BLACK);
    count->setPosition(Vec2(width / 2 + 160, height / 2 - padding));

    auto btn = MenuItemImage::create("Graphics/System/BtnVerify.png", "Graphics/System/BtnVerify_click.png", CC_CALLBACK_1(LayerJoinRoomCard::join, this));
    btn->setScaleX(50.0f / btn->getContentSize().width);
    btn->setScaleY(50.0f / btn->getContentSize().height);
    btn->setPosition(Vec2(width / 2 + 200, height / 2));
    auto menu = Menu::create(btn, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(status, 3);
    this->addChild(roomname, 3);
    this->addChild(owner, 3);
    this->addChild(mapname, 3);
    this->addChild(mode, 3);
    this->addChild(count, 3);
    this->addChild(mapimage, 3);
    this->addChild(menu, 2);
    this->addChild(itembackground, 1);

    needPassword = (room.Password.size() ? true : false);
    roomId = room.Id;

    return true;
}

void LayerJoinRoomCard::join(Ref * pSender)
{
    if (!this->getActive()) return;
    if (needPassword)
    {
        // todo
    }
    else
    {
        if (Singleton<ServiceRoom>::GetInstance()->joinInRoom(roomId))
        {
            this->updateScene(Tag::SceneFromMenuToRoom);
        }
        else
        {
            this->dialog("Join room failed.");
        }
    }
}

