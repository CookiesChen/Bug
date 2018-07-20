#include "Helpers.h"
#include "LayerJoinRoom.h"
#include "ServiceAPI.h"

LayerBase* LayerJoinRoom::createLayer()
{
    return LayerJoinRoom::create();
}

bool LayerJoinRoom::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // 房间列表背景
    auto background = Sprite::create("Graphics/Pictures/background.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);

    // 页码显示
    auto currentPage = Label::createWithTTF("0 /", "Fonts/arial.ttf", 20);
    auto maxPage = Label::createWithTTF("0", "Fonts/arial.ttf", 20);

    currentPage->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height / 2 - 300));
    maxPage->setPosition(Vec2(visibleSize.width / 2 + 20, visibleSize.height / 2 - 300));

    // 按钮
    auto backButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::backMenu, this));
    auto prepageButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::changePage, this, false));
    auto nextpageButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::changePage, this, true));
    auto backInputNo = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::backMenu, this));

    auto quickjoin = MenuItemLabel::create(Label::createWithTTF("Join Game", "Fonts/arial.ttf", 30), CC_CALLBACK_1(LayerJoinRoom::quickJoin, this));
    auto search = MenuItemLabel::create(Label::createWithTTF("Join Game", "Fonts/arial.ttf", 30), CC_CALLBACK_1(LayerJoinRoom::search, this));

    backButton->setPosition(Vec2(100, visibleSize.height - 50));
    prepageButton->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 300));
    nextpageButton->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 300));

    backButton->setScale(0.5);
    prepageButton->setScale(0.5);
    nextpageButton->setScale(0.5);

    menu->addChild(backButton, 2);
    menu->addChild(prepageButton, 2);
    menu->addChild(nextpageButton, 2);

    this->addChild(menu, 2);
    this->addChild(currentPage, 1);
    this->addChild(maxPage, 1);
    this->addChild(background, 1);


    // 定时扫描
    schedule(schedule_selector(LayerJoinRoom::getRoomList), 2.0f, kRepeatForever, 0);

    return true;
}

void LayerJoinRoom::backMenu(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromJoinRoomOrNewRoomToMenu);
}

void LayerJoinRoom::getRoomList(float dt)
{
    // todo 获取房间列表API
    if (this->getActive() == false) return;
    auto d = Singleton<ServiceAPI>::GetInstance()->GetRoomsList(1, 5);
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            auto padding = 20;
            auto itemwidth = 400.0f;
            auto itemheight = 100.0f;
            auto mapimagewidth = 70.0f;
            for (auto i = 0; i < 5; i++)
            {
                auto itembackground = Sprite::create("Graphics/System/BtnBack.png");
                itembackground->setContentSize(Size::Size(itemwidth, itemheight));
                itembackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 220 - i *itemheight - padding));

                auto mapimage = Sprite::create("Graphics/Pictures/background.png");
                mapimage->setContentSize(Size::Size(mapimagewidth, mapimagewidth));
                mapimage->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 220 - i * itemheight - padding));

                auto roomname = Label::createWithTTF("Room Name: ", "Fonts/arial.ttf", 15);
                roomname->setColor(Color3B::BLACK);
                roomname->setAnchorPoint(Vec2(0, 0.5));
                roomname->setPosition(Vec2(visibleSize.width / 2 - 110, visibleSize.height / 2 + 240 - i * itemheight - padding));

                auto owner = Label::createWithTTF("Owner: ", "Fonts/arial.ttf", 15);
                owner->setColor(Color3B::BLACK);
                owner->setAnchorPoint(Vec2(0, 0.5));
                owner->setPosition(Vec2(visibleSize.width / 2 - 110, visibleSize.height / 2 + 220 - i * itemheight - padding));

                auto mapname = Label::createWithTTF("Map: ", "Fonts/arial.ttf", 15);
                mapname->setColor(Color3B::BLACK);
                mapname->setAnchorPoint(Vec2(0, 0.5));
                mapname->setPosition(Vec2(visibleSize.width / 2 - 110, visibleSize.height / 2 + 200 - i * itemheight - padding));

                // 是否有密码
                if (true) {
                    auto lock = Sprite::create("Graphics/System/lock.jpg");
                    lock->setContentSize(Size::Size(25, 25));
                    lock->setPosition(Vec2(visibleSize.width / 2 + 90, visibleSize.height / 2 + 240 - i * itemheight - padding));
                    this->addChild(lock, 3);
                }

                // 房间状态 waiting / playing
                auto status = Label::createWithTTF("", "Fonts/arial.ttf", 15);
                status->setAnchorPoint(Vec2(1, 0.5));
                if (true)
                {
                    status->setString("waiting");
                    status->setColor(Color3B::GREEN);
                }
                else
                {
                    status->setString("playing");
                    status->setColor(Color3B::YELLOW);
                }
                status->setPosition(Vec2(visibleSize.width / 2 + 160, visibleSize.height / 2 + 240 - i * itemheight - padding));

                // 游戏模式 random / optional
                auto mode = Label::createWithTTF("Mode: optional", "Fonts/arial.ttf", 15);
                mode->setAnchorPoint(Vec2(1, 0.5));
                mode->setColor(Color3B::BLACK);
                mode->setPosition(Vec2(visibleSize.width / 2 + 160, visibleSize.height / 2 + 220 - i * itemheight - padding));

                auto count = Label::createWithTTF("10/10", "Fonts/arial.ttf", 15);
                count->setAnchorPoint(Vec2(1, 0.5));
                count->setColor(Color3B::BLACK);
                count->setPosition(Vec2(visibleSize.width / 2 + 160, visibleSize.height / 2 + 200 - i * itemheight - padding));

                this->addChild(status, 3);
                this->addChild(roomname, 3);
                this->addChild(owner, 3);
                this->addChild(mapname, 3);
                this->addChild(mode, 3);
                this->addChild(count, 3);
                this->addChild(mapimage, 3);
                this->addChild(itembackground, 2);
                
            }
            // 根据数据生成房间列表
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

void LayerJoinRoom::changePage(Ref* pSender, bool ifnext) {

}

void LayerJoinRoom::quickJoin(Ref* pSender) {

}

void LayerJoinRoom::search(Ref* pSender) {

}
