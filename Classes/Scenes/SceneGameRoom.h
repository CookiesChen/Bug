#ifndef __SCENE_GAME_ROOM_H__
#define __SCENE_GAME_ROOM_H__

#include "LayerMap.h"
#include "SceneBase.h"

class SceneGameRoom final : public SceneBase
{
public:
    static Scene * createPhysicsScene();

    virtual bool init() override;
    virtual void updateLayer(Tag tag) override;
    virtual void updateScene(Tag tag) override;
    void update(float time);
    void addKeyboardListener();
    void onKeyPressed(EventKeyboard::KeyCode code, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event* event);
    void GetState();
    void JoinGame(float dt);
    void ExitGame(float dt);

    CREATE_FUNC(SceneGameRoom);

private:
    int move();

    Size visibleSize;

    Label * msgLabel;
    int id;
    int port;

    LayerMap* layermap;
    LayerBase* layerMapMini;
    Scene* physicsScene;

    Vec2 offset;
    Vec2 playerPos;

    map<char, bool> input;
};

#endif // __SCENE_GAME_ROOM_H__
