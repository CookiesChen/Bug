#include "LayerReady.h"
#include "Helpers.h"
#include "ServiceRoom.h"
#include "ServiceUser.h"
#include "ServiceGame.h"
#include "ServiceUser.h"
#include "ServicePlayer.h"

LayerBase* LayerReady::createLayer()
{
    return LayerReady::create();
}

bool LayerReady::init()
{
    if (!LayerBase().init()) return false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    LabelWait = Label::create("Waiting other player...", "fonts/arial.ttf", 40);
    LabelWait->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(LabelWait, 1);
    return true;
}

void LayerReady::beginReady()
{
    time = 5;
    schedule(schedule_selector(LayerReady::waitTime), 1.0f, kRepeatForever, 0);
}



void LayerReady::waitTime(float dt)
{
    if (!this->getActive()) return;
    if (time > 0) {
        LabelWait->setString("Game Start after " + to_string(time) + "s");
        time--;
    }
    else {
        LabelWait->setString("Waiting other player...");
        auto res = Singleton<ServiceRoom>::GetInstance()->refreshInfo();
        if (!res) {
            // 返回菜单
            return;
        }
        auto room = Singleton<ServiceRoom>::GetInstance()->getRoom();

        // 如果是房主
        if (room.OwnId == Singleton<ServiceUser>::GetInstance()->GetUserId()) {
            Singleton<ServiceRoom>::GetInstance()->startGame();
        }
        if (!room.Playing) {
            unschedule(schedule_selector(LayerReady::waitTime));
            this->updateLayer(Tag::LayerFromReadyToRoom);
            return;
        }
        if (room.Port != -1) {
            unschedule(schedule_selector(LayerReady::waitTime));
            auto gameId = -1;
            Singleton<ServicePlayer>::GetInstance()->ClearOther();
            for (auto& player : room.Players) {
                ModelPlayer p;
                p.userId = player.userId;
                p.userName = player.userName;
                p.Id = player.gameId;
                p.roleId = player.roleId;
                p.team = player.team;
                p.hp = 100;
                p.sp = 100;
                if (player.userId == Singleton<ServiceUser>::GetInstance()->GetUserId()) {
                    gameId = player.gameId;
                    Singleton<ServicePlayer>::GetInstance()->SetPlayer(p);
                }
                else {
                    Singleton<ServicePlayer>::GetInstance()->AddOther(p);
                }
            }
            if (gameId == -1) {
                this->updateLayer(Tag::LayerFromReadyToRoom);
            }
            Singleton<ServiceRoom>::GetInstance()->stopHeart();
            Singleton<ServiceGame>::GetInstance()->InitGame(gameId, room.Port);
            Singleton<ServiceGame>::GetInstance()->fireX = room.fireX / 100.0f;
            Singleton<ServiceGame>::GetInstance()->fireY = room.fireY / 100.0f;
            this->updateScene(Tag::SceneFromRoomToGame);
        }
    }
}
