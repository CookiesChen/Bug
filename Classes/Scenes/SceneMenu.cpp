#include "Helpers.h"
#include "LayerMenu.h"
#include "LayerJoinRoom.h"
#include "LayerNewRoom.h"
#include "LayerNewUser.h"
#include "SceneLoginAndRegister.h"
#include "SceneMenu.h"
#include "SceneRoom.h"
#include "ServiceUser.h"
#include "LayerJoinRoomCard.h"
Scene* SceneMenu::createScene()
{
    return SceneMenu::create();
}

bool SceneMenu::init()
{
    if (!SceneBase::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // 添加层
    layerMenu = LayerMenu::createLayer();
    layerJoinRoom = LayerJoinRoom::createLayer();
    layerNewRoom = LayerNewRoom::createLayer();
    layerNewUser = LayerNewUser::createLayer();

    layerJoinRoom->setVisible(false);
    layerNewRoom->setVisible(false);
    layerNewUser->setVisible(false);
    layerJoinRoom->setActive(false);
    layerNewRoom->setActive(false);
    layerNewUser->setActive(false);

    this->addChild(layerMenu, 10, "Menu");
    this->addChild(layerJoinRoom, 10, "JoinRoom");
    this->addChild(layerNewRoom, 10, "NewRoom");
    this->addChild(layerNewUser, 10, "NewUser");

    if (Singleton<ServiceUser>::GetInstance()->GetNikename() == "new_user") {
        this->updateLayer(Tag::LayerFromMenuToNewUser);
    }
    else {
        this->updateUserInfo();
    }

    return true;
}

void SceneMenu::addCardLayer(ModelRoom r, int index) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto card = LayerJoinRoomCard::createLayerWithRoom(r);
    card->setPosition(Vec2((visibleSize.width - card->getContentSize().width) / 2, visibleSize.height - 120 - index * card->getContentSize().height));
    this->addChild(card, 20);
    cards.push_back(card);
}

void SceneMenu::updateUserInfo()
{
    if (Singleton<ServiceUser>::GetInstance()->RefreshInfo())
    {
        ((LayerMenu*)layerMenu)->UpdateUserInfo();
    }
    else
    {
        this->dialog("Can't get user info from server.");
    }
}

void SceneMenu::updateLayer(Tag tag)
{
    switch (tag)
    {
    case Tag::LayerFromMenuToJoinRoom: // 加入房间
        this->layerJoinRoom->setVisible(true);
        this->layerJoinRoom->setActive(true);
        this->layerMenu->setVisible(false);
        this->layerMenu->setActive(false);
        this->layerNewUser->setVisible(false);
        this->layerNewUser->setActive(false);
        break;
    case Tag::LayerFromMenuToNewRoom: // 新建房间
        this->layerNewRoom->setVisible(true);
        this->layerNewRoom->setActive(true);
        ((LayerNewRoom*)this->layerNewRoom)->refreshRoomName();
        this->layerMenu->setVisible(false);
        this->layerMenu->setActive(false);
        this->layerNewUser->setVisible(false);
        this->layerNewUser->setActive(false);
        break;
    case Tag::LayerFromNewUserToMenu:
        this->updateUserInfo();
    case Tag::LayerFromJoinRoomOrNewRoomToMenu: // 返回菜单
        for (auto& card : cards) {
            card->removeFromParentAndCleanup(true);
        }
        cards.clear();
        this->layerMenu->setVisible(true);
        this->layerMenu->setActive(true);
        this->layerJoinRoom->setVisible(false);
        this->layerJoinRoom->setActive(false);
        this->layerNewRoom->setVisible(false);
        this->layerNewRoom->setActive(false);
        this->layerNewUser->setVisible(false);
        this->layerNewUser->setActive(false);
        break;
    case Tag::LayerFromMenuToNewUser: // 修改用户信息
        this->layerNewUser->setVisible(true);
        this->layerNewUser->setActive(true);
        this->layerMenu->setVisible(false);
        this->layerMenu->setActive(false);
        this->layerJoinRoom->setVisible(false);
        this->layerJoinRoom->setActive(false);
        this->layerNewRoom->setVisible(false);
        this->layerNewRoom->setActive(false);
        break;
    }
}

void SceneMenu::updateScene(Tag tag)
{
    switch (tag)
    {
    case Tag::SceneFromMenuToLoginAndRegister:
        Director::getInstance()->replaceScene(SceneLoginAndRegister::createScene());
        break;
    case Tag::SceneFromMenuToRoom:
        Director::getInstance()->replaceScene(SceneRoom::createScene());
        break;
    }
}
