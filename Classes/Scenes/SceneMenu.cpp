#include "SceneMenu.h"
#include "LayerMenu.h"
#include "LayerJoinRoom.h"
#include "LayerNewRoom.h"

Scene* SceneMenu::createScene()
{
    return SceneMenu::create();
}

bool SceneMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // 添加层
    layerMenu = LayerMenu::createLayer();
    layerJoinRoom = LayerJoinRoom::createLayer();
    layerNewRoom = LayerNewRoom::createLayer();
    layerJoinRoom->setVisible(false);
    layerNewRoom->setVisible(false);
    layerJoinRoom->setActive(false);
    layerNewRoom->setActive(false);

    this->addChild(layerMenu, 10, "Menu");
    this->addChild(layerJoinRoom, 10, "JoinRoom");
    this->addChild(layerNewRoom, 10, "NewRoom");

    return true;
}

void SceneMenu::updateLayer()
{
    if (this->targetLayer == 1) { // 加入房间
        this->layerJoinRoom->setVisible(true);
        this->layerJoinRoom->setActive(true);
        this->layerMenu->setVisible(false);
        this->layerMenu->setActive(false);
    }
    else if (this->targetLayer == 2) { // 新建房间
        this->layerNewRoom->setVisible(true);
        this->layerNewRoom->setActive(true);
        this->layerMenu->setVisible(false);
        this->layerMenu->setActive(false);
    } else if(this->targetLayer == 0){ // 返回菜单
        this->layerMenu->setVisible(true);
        this->layerMenu->setActive(true);
        this->layerJoinRoom->setVisible(false);
        this->layerJoinRoom->setActive(false);
        this->layerNewRoom->setVisible(false);
        this->layerNewRoom->setActive(false);
    }
}

void SceneMenu::updateScene()
{

}
