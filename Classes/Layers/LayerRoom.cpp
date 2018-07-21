#include "LayerRoom.h"
#include "Helpers.h"
#include "ServiceRoom.h"
#include "ServiceUser.h"

LayerBase* LayerRoom::createLayer()
{
    return LayerRoom::create();
}

bool LayerRoom::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();

    // todo 显示玩家信息和准备状态以及所选角色
    // todo 显示这个房间的游戏模式和地图
    // todo 准备
    // todo 选择队伍
    // todo 选择角色
    // todo 退出房间
    // -------------仅房主显示-----------
    // todo 踢人
    // todo 转移房主
    // todo 设置房间信息
    // todo 开始游戏

    auto origin = Director::getInstance()->getVisibleOrigin();
    // 菜单
    if (menu != nullptr) {
        menu->removeAllChildrenWithCleanup(true);
        menu->removeFromParentAndCleanup(true);
    }
    menu = Menu::create();
    menu->setPosition(origin);
    // 退出
    buttonBack = MenuItemImage::create("Graphics/System/BtnQuit.png", "Graphics/System/BtnQuit_click.png", CC_CALLBACK_1(LayerRoom::quitRoom, this));
    buttonBack->setPosition(Vec2(150, visibleSize.height - 50));
    buttonBack->setScale(0.5f);
    menu->addChild(buttonBack, 1);
    // 准备/开始
    buttonReady = MenuItemImage::create("Graphics/System/BtnReady.png", "Graphics/System/BtnReady_click.png", CC_CALLBACK_1(LayerRoom::setReady, this));
    buttonReady->setPosition(Vec2(visibleSize.width / 2, 100));
    menu->addChild(buttonReady, 1);

    this->addChild(menu, 1);


    schedule(schedule_selector(LayerRoom::heart), 1.5f, kRepeatForever, 0.0f);
    schedule(schedule_selector(LayerRoom::refreshData), 1.0f, kRepeatForever, 0.0f);

    return true;
}


void LayerRoom::quitRoom(Ref* pSender)
{
    Singleton<ServiceRoom>::GetInstance()->quitRoom();
    this->updateScene(Tag::SceneFromRoomToMenu);
}

void LayerRoom::setReady(Ref* pSender)
{
    if (!this->getActive() || !this->buttonReady->isEnabled()) return;
    if (room.IsOwn == true) {
        Singleton<ServiceRoom>::GetInstance()->setPlay(true);
        this->updateLayer(Tag::LayerFromRoomToReady);
    }
    else {
        auto res = Singleton<ServiceRoom>::GetInstance()->setReady(!isReady);
        if (!res) {
            this->dialog("Oop");
        }
        else {
            this->isReady = !this->isReady;
        }
    }
}

void LayerRoom::drawInfo()
{
    // 标题
    float Height1 = visibleSize.height - 100;
    if (labelTitle != nullptr) labelTitle->removeFromParentAndCleanup(true);
    labelTitle = Label::createWithTTF(this->room.Title, "Fonts/arial.ttf", 38);
    labelTitle->setPosition(Vec2(visibleSize.width / 2, Height1));
    this->addChild(labelTitle, 1);
    // 地图
    float Height2 = visibleSize.height - 150;
    if (labelMap != nullptr) labelMap->removeFromParentAndCleanup(true);
    labelMap = Label::createWithTTF("Map: " + this->room.GameMap, "Fonts/arial.ttf", 25);
    labelMap->setPosition(Vec2(visibleSize.width / 2, Height2));
    this->addChild(labelMap, 1);
    // 模式
    float Height3 = visibleSize.height - 200;
    if (labelMode != nullptr) labelMode->removeFromParentAndCleanup(true);
    labelMode = Label::createWithTTF("Map: " + this->room.Mode, "Fonts/arial.ttf", 25);
    labelMode->setPosition(Vec2(visibleSize.width / 2, Height3));
    this->addChild(labelMode, 1);
    // 玩家
    float Height4 = visibleSize.height - 250;
    if (labelPlayer != nullptr) labelPlayer->removeFromParentAndCleanup(true);
    labelPlayer = Label::createWithTTF("Player " + to_string(this->room.Players.size()) + "/" + to_string(this->room.MaxPalyer), "Fonts/arial.ttf", 28);
    labelPlayer->setPosition(Vec2(visibleSize.width / 2, Height4));
    this->addChild(labelPlayer, 1);

    if (room.OwnId != Singleton<ServiceUser>::GetInstance()->GetUserId()) {
        if (this->isReady) {
            buttonReady->setNormalImage(Sprite::create("Graphics/System/BtnReady_click.png"));
            buttonReady->setSelectedImage(Sprite::create("Graphics/System/BtnReady_click.png"));
        }
        else {
            buttonReady->setNormalImage(Sprite::create("Graphics/System/BtnReady.png"));
            buttonReady->setSelectedImage(Sprite::create("Graphics/System/BtnReady_click.png"));
        }
    }
    drawPlayers();
}

void LayerRoom::drawPlayers() {
    for (auto& player : this->playerNode) {
        player->removeAllChildrenWithCleanup(true);
        player->removeFromParentAndCleanup(true);
    }
    this->playerNode.clear();

    float height = visibleSize.height - 320;
    bool allReady = true;
    for (auto& player : this->room.Players) {
        auto newPlayerNode = Node::create();
        if (player.isReady == false) allReady = false;
        // 用户名
        auto labelUserName = Label::createWithTTF(player.userName, "Fonts/arial.ttf", 26);
        if (player.userId == Singleton<ServiceUser>::GetInstance()->GetUserId()) {
            labelUserName->setString(player.userName + "(Me)");
        }
        labelUserName->setAnchorPoint(Vec2(1, 0));
        labelUserName->setPosition(Vec2(visibleSize.width / 2 - 100, height));
        newPlayerNode->addChild(labelUserName, 1);
        // 准备状态
        if (player.userId == this->room.OwnId) {
            auto labelOwn = Label::createWithTTF("Own", "Fonts/arial.ttf", 26);
            labelOwn->setAnchorPoint(Vec2(1, 0));
            labelOwn->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelOwn, 1);
        }
        else if (player.isReady) {
            auto labelReady = Label::createWithTTF("Ready", "Fonts/arial.ttf", 26);
            labelReady->setAnchorPoint(Vec2(1, 0));
            labelReady->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelReady, 1);
        }
        else {
            auto labelReady = Label::createWithTTF("Waiting", "Fonts/arial.ttf", 26);
            labelReady->setAnchorPoint(Vec2(1, 0));
            labelReady->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelReady, 1);
        }
        this->playerNode.push_back(newPlayerNode);
        this->addChild(newPlayerNode, 1);
        height -= 50;
    }

    if (room.OwnId == Singleton<ServiceUser>::GetInstance()->GetUserId() && (!allReady || room.Players.size() < 2)) {
        buttonReady->setNormalImage(Sprite::create("Graphics/System/BtnStart_disabled.png"));
        buttonReady->setSelectedImage(Sprite::create("Graphics/System/BtnStart_click.png"));
        this->buttonReady->setEnabled(false);
    }
    else if (room.OwnId == Singleton<ServiceUser>::GetInstance()->GetUserId()) {
        buttonReady->setNormalImage(Sprite::create("Graphics/System/BtnStart.png"));
        buttonReady->setSelectedImage(Sprite::create("Graphics/System/BtnStart_click.png"));
        this->buttonReady->setEnabled(true);
    }
       
}

void LayerRoom::heart(float dt)
{
    if (!this->getActive()) return;
    if (Singleton<ServiceRoom>::GetInstance()->IsInRoom()) {
        Singleton<ServiceRoom>::GetInstance()->heart();
    }
    else {
        // 返回菜单
    }
}

void LayerRoom::refreshData(float dt)
{
    if (!this->getActive()) return;
    if (Singleton<ServiceRoom>::GetInstance()->IsInRoom()) {
        auto res = Singleton<ServiceRoom>::GetInstance()->refreshInfo();
        if (!res) {
            // 返回菜单
            return;
        }
        room = Singleton<ServiceRoom>::GetInstance()->getRoom();
        if (room.Playing) {
            this->updateLayer(Tag::LayerFromRoomToReady);
        }
        else {
            drawInfo();
        }
    }
    else {
        // 返回菜单
    }
}
