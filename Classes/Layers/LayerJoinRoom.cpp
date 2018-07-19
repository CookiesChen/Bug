#include "LayerJoinRoom.h"
#include "Helpers.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include <iostream>

using namespace std;
using namespace rapidjson;

LayerBase* LayerJoinRoom::createLayer()
{
    return LayerJoinRoom::create();
}

bool LayerJoinRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


    auto buttonBack = MenuItemImage::create("BtnBack.png", "BtnBack_click.png",
        CC_CALLBACK_1(LayerJoinRoom::backMenu, this));

    buttonBack->setPosition(Vec2(150, visibleSize.height - 50));

    auto menu = Menu::create();
    menu->setPosition(origin);
    menu->addChild(buttonBack);

    // 定时扫描
    schedule(schedule_selector(LayerJoinRoom::getRoomList), 2.0f, kRepeatForever, 0);

    this->addChild(menu, 1);

    return true;
}

void LayerJoinRoom::backMenu(Ref* pSender) {
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromJoinRoomOrNewRoomToMenu);
}

void LayerJoinRoom::getRoomList(float dt) {
    // todo 获取房间列表API
    if (this->getActive() == false) return;
    auto res = Singleton<Net>::GetInstance()->Get("room/list/1?size=5");

    log("Res:%s\n", res.c_str());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status")) {
        if (strcmp(d["status"].GetString(), "success") == 0) {
            
            // 根据数据生成房间列表
        }
        else {
            // 参数错误的提示
        }
    }
    else {
        // 解析失败的提示
        return;
    }
}
