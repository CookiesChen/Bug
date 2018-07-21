#include "Helpers.h"
#include "LayerJoinRoom.h"
#include "LayerJoinRoomCard.h"
#include "ServiceAPI.h"
#include "SceneMenu.h"

LayerBase* LayerJoinRoom::createLayer()
{
    return LayerJoinRoom::create();
}

bool LayerJoinRoom::init()
{
    if (!LayerBase::init()) return false;
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // 房间列表背景
    auto background = Sprite::create("Graphics/Pictures/background.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);

    // 页码显示
    auto currentPage = Label::createWithTTF("0  /", "Fonts/arial.ttf", 20);
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

    pageNum = 1;

    // 定时扫描
    schedule(schedule_selector(LayerJoinRoom::getRoomList), 1.0f, kRepeatForever, 0);

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
    auto d = Singleton<ServiceAPI>::GetInstance()->GetRoomsList(pageNum, 5);
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            if (d["rooms"].IsNull())
            {
                this->dialog("No room found.");
                return;
            }
            int index = 0;
            for (auto &room : d["rooms"].GetArray())
            {
                index++;
                ModelRoom r;
                r.Id = room["id"].GetInt();
                r.OwnId = room["ownId"].GetString();
                r.OwnName = room["ownName"].GetString();
                r.Port = room["port"].GetInt();
                r.Title = room["title"].GetString();
                r.IsRandom = room["isRandom"].GetBool();
                r.GameMap = room["gameMap"].GetString();
                r.MaxPalyer = room["maxPlayer"].GetInt();
                r.Mode = room["mode"].GetString();
                r.Password = room["password"].GetString();
                r.Playing = room["playing"].GetBool();
                r.Players.reserve(room["players"].GetArray().Size());

                auto scene = (SceneMenu*)this->getParent();
                scene->addCardLayer(r, index);
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
