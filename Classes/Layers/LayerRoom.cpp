#include "LayerRoom.h"
#include "Helpers.h"
#include "ServiceRoom.h"

LayerBase* LayerRoom::createLayer()
{
    return LayerRoom::create();
}

bool LayerRoom::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // 标题
    float Height1 = visibleSize.height - 100;
    labelTitle = Label::createWithTTF("A room", "Fonts/arial.ttf", 38);
    labelTitle->setAnchorPoint(Vec2(0, 0));
    labelTitle->setPosition(Vec2(visibleSize.width / 2, Height1));
    this->addChild(labelTitle, 1);
    // 玩家
    float Height2 = visibleSize.height - 180;
    labelPlayer = Label::createWithTTF("Player 1/1", "Fonts/arial.ttf", 38);
    labelPlayer->setAnchorPoint(Vec2(0, 0));
    labelPlayer->setPosition(Vec2(visibleSize.width / 2, Height2));
    this->addChild(labelPlayer, 1);

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

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);
    // 退出
    auto buttonBack = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerRoom::quitRoom, this));
    buttonBack->setPosition(Vec2(150, visibleSize.height - 50));
    buttonBack->setScale(0.5f);
    menu->addChild(buttonBack, 1);
    // 准备/开始
    auto buttonReady = MenuItemImage::create("Graphics/System/BtnRegister.png", "Graphics/System/BtnRegister_click.png", CC_CALLBACK_1(LayerRoom::SetReady, this));
    buttonReady->setPosition(Vec2(visibleSize.width / 2 - 100, 100));
    buttonReady->setScale(0.5f);
    menu->addChild(buttonReady, 1);

    this->addChild(menu, 1);

    schedule(schedule_selector(LayerRoom::heart), 1.0f, kRepeatForever, 0);
    schedule(schedule_selector(LayerRoom::refreshData), 2.0f, kRepeatForever, 0);

    return true;
}


void LayerRoom::quitRoom(Ref* pSender)
{

}

void LayerRoom::setReady(Ref* pSender)
{

}

void LayerRoom::drawInfo()
{
    labelTitle->setString(this->room.Title + "'s room");
    labelPlayer->setString("Player " + to_string(this->room.players.size()) + "/" + to_string(this->room.MaxPalyer));
    drawPlayers();
}

void LayerRoom::drawPlayers() {
    for (auto& player : this->playerNode) {
        player->removeAllChildrenWithCleanup(true);
        player->removeFromParentAndCleanup(true);
    }
    this->playerNode.clear();

    auto height = 240;
    for (auto& player : this->room.players) {
        auto newPlayerNode = Node::create();
        // 用户名
        auto labelUserName = Label::createWithTTF("A room", "Fonts/arial.ttf", 38);
        labelUserName->setAnchorPoint(Vec2(1, 0));
        labelUserName->setPosition(Vec2(visibleSize.width / 2 - 100, height));
        newPlayerNode->addChild(labelUserName, 1);
        // 准备状态
        if (player.userId == this->room.OwnId) {
            auto labelOwn = Label::createWithTTF("Own", "Fonts/arial.ttf", 38);
            labelOwn->setAnchorPoint(Vec2(1, 0));
            labelOwn->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelOwn, 1);
        }
        else if (player.isReady) {
            auto labelReady = Label::createWithTTF("Ready", "Fonts/arial.ttf", 38);
            labelReady->setAnchorPoint(Vec2(1, 0));
            labelReady->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelReady, 1);
        }
        else {
            auto labelReady = Label::createWithTTF("Waiting", "Fonts/arial.ttf", 38);
            labelReady->setAnchorPoint(Vec2(1, 0));
            labelReady->setPosition(Vec2(visibleSize.width / 2 + 100, height));
            newPlayerNode->addChild(labelReady, 1);
        }
        this->playerNode.push_back(newPlayerNode);
        this->addChild(newPlayerNode, 1);
        height += 50;
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
        Singleton<ServiceRoom>::GetInstance()->refreshInfo();
        room = Singleton<ServiceRoom>::GetInstance()->getRoom();
        drawInfo();
    }
    else {
        // 返回菜单
    }
}
