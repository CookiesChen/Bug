#include "SceneRoom.h"
#include "LayerRoom.h"
#include "SceneMenu.h"
#include "SceneGameRoom.h"
#include "LayerBackground.h"
#include "LayerReady.h"

Scene* SceneRoom::createScene()
{
    return SceneRoom::create();
}

bool SceneRoom::init()
{
    if (!SceneBase::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 背景层
    auto layerBackground = LayerBackground::createLayer();
    this->addChild(layerBackground, 0, "Background");


    layerRoom = LayerRoom::createLayer();
    layerReady = LayerReady::createLayer();

    this->addChild(layerRoom, 1);
    this->addChild(layerReady, 1);

    layerReady->setVisible(false);
    layerReady->setActive(false);

    return true;
}

void SceneRoom::updateLayer(Tag tag)
{
    switch (tag)
    {
    case Tag::LayerFromRoomToReady:
        layerReady->setVisible(true);
        layerReady->setActive(true);
        ((LayerReady*)layerReady)->beginReady();
        layerRoom->setVisible(false);
        layerRoom->setActive(false);
        break;
    case Tag::LayerFromReadyToRoom:
        layerReady->setVisible(false);
        layerReady->setActive(false);
        layerRoom->setVisible(true);
        layerRoom->setActive(true);
        break;
    }
}

void SceneRoom::updateScene(Tag tag)
{
    switch (tag)
    {
    case Tag::SceneFromRoomToGame:
        Director::getInstance()->replaceScene(SceneGameRoom::createScene());
        break;
    case Tag::SceneFromRoomToMenu:
        Director::getInstance()->replaceScene(SceneMenu::createScene());
        break;
    }
}
