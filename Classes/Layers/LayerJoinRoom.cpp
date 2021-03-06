﻿#include "Helpers.h"
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

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);

    // 页码显示
    currentPage = Label::createWithTTF("0  /", "Fonts/arial.ttf", 20);
    maxPage = Label::createWithTTF("0", "Fonts/arial.ttf", 20);

    currentPage->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height / 2 - 300));
    maxPage->setPosition(Vec2(visibleSize.width / 2 + 20, visibleSize.height / 2 - 300));

    // 按钮
    auto backButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::backMenu, this));
    auto prepageButton = MenuItemImage::create("Graphics/System/BtnLastPage.png", "Graphics/System/BtnLastPage_click.png", CC_CALLBACK_1(LayerJoinRoom::changePage, this, false));
    auto nextpageButton = MenuItemImage::create("Graphics/System/BtnNextPage.png", "Graphics/System/BtnNextPage_click.png", CC_CALLBACK_1(LayerJoinRoom::changePage, this, true));
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
        string status(d["status"].GetString());
        if (status == "success")
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
                for (size_t i = 0; i < room["players"].GetArray().Size(); i++)
                {
                    r.Players.push_back(PlayerInfo());
                }

                auto scene = (SceneMenu*)this->getParent();
                scene->removeAllCardLayer();
                scene->addCardLayer(r, index);
            }
            int count = d["count"].GetInt();
            maxPageNum = (count + 5 - 1) / 5;
            if (count != 0)
            {
                currentPage->setString(to_string(pageNum) + "  /");
                maxPage->setString(to_string(maxPageNum));
            }
            else
            {
                auto scene = (SceneMenu*) this->getParent();
                scene->removeAllCardLayer();
                currentPage->setString("0  /");
                maxPage->setString("0");
            }
            // 根据数据生成房间列表
        }
        else if (status == "null")
        {
            auto scene = (SceneMenu*) this->getParent();
            scene->removeAllCardLayer();
            currentPage->setString("0  /");
            maxPage->setString("0");
        }
        else if (status == "bad_req")
        {
            auto scene = (SceneMenu*) this->getParent();
            scene->removeAllCardLayer();
            this->dialog("Request failed.");
        }
        else
        {
            this->dialog(string("Unknown status: ") + status);
        }
    }
    else
    {
        this->dialog("Ooops, a system error occurs. Please check your Network.");
        // 解析失败的提示
    }
}

void LayerJoinRoom::changePage(Ref* pSender, bool ifnext) {
    if (ifnext)
    {
        if (pageNum == maxPageNum) return;
        pageNum++;
        this->getRoomList(0.f);
    }
    else
    {
        if (pageNum == 1) return;
        pageNum--;
        this->getRoomList(0.f);
    }
}

void LayerJoinRoom::quickJoin(Ref* pSender) {

}

void LayerJoinRoom::search(Ref* pSender) {

}
