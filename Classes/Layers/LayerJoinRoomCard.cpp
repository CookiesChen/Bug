#include "LayerJoinRoomCard.h"

LayerBase* LayerJoinRoomCard::createLayerWithRoom(const ModelRoom& room)
{
    auto layer = LayerJoinRoomCard::create();
    layer->room = room;
    return layer;
}

bool LayerJoinRoomCard::init()
{
    if (!LayerBase::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto padding = 20;
    auto width = 400.0f;
    auto height = 100.0f;
    auto mapImageWidth = 70.0f;

    int i = 0;

    this->setContentSize(Size(width, height));

    auto itembackground = Sprite::create("Graphics/System/BtnBack.png");
    itembackground->setContentSize(Size::Size(width, height));
    itembackground->setPosition(Vec2(width / 2, height / 2));

    auto mapimage = Sprite::create("Graphics/Pictures/background.png");
    mapimage->setContentSize(Size(mapImageWidth, mapImageWidth));
    mapimage->setPosition(Vec2(width / 2 - 150, height / 2));

    auto roomname = Label::createWithTTF(string("Room Name: ") + room.Title, "Fonts/arial.ttf", 15);
    roomname->setColor(Color3B::BLACK);
    roomname->setAnchorPoint(Vec2(0, 0.5));
    roomname->setPosition(Vec2(width / 2 - 110, height / 2 - padding));

    auto owner = Label::createWithTTF(string("Owner: ") + room.OwnId, "Fonts/arial.ttf", 15);
    owner->setColor(Color3B::BLACK);
    owner->setAnchorPoint(Vec2(0, 0.5));
    owner->setPosition(Vec2(width / 2 - 110, height / 2));

    auto mapname = Label::createWithTTF(string("Map: ") + room.GameMap, "Fonts/arial.ttf", 15);
    mapname->setColor(Color3B::BLACK);
    mapname->setAnchorPoint(Vec2(0, 0.5));
    mapname->setPosition(Vec2(width / 2 - 110, height / 2 + padding));

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

    auto count = Label::createWithTTF("10/10", "Fonts/arial.ttf", 15);
    count->setAnchorPoint(Vec2(1, 0.5));
    count->setColor(Color3B::BLACK);
    count->setPosition(Vec2(width / 2 + 160, height / 2 - padding));

    this->addChild(status, 3);
    this->addChild(roomname, 3);
    this->addChild(owner, 3);
    this->addChild(mapname, 3);
    this->addChild(mode, 3);
    this->addChild(count, 3);
    this->addChild(mapimage, 3);
    this->addChild(itembackground, 2);

    return true;
}

