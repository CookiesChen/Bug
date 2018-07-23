#ifndef __SCENE_GAME_ROOM_H__
#define __SCENE_GAME_ROOM_H__

#include "LayerMap.h"
#include "SceneBase.h"

// 火圈范围递减因子
#define FIREFACTOR 0.6
// 火圈收缩级数
#define FIRECLASS 7
// 火圈收缩等待时间
#define FIREINTERVAL 900
// 火圈收缩等待时间递减因子
// #define FIREINTERVALFACTOR 0.8;
// 火圈收缩持续时间
#define FIREDOWN 600
// 火圈收缩持续时间递减因子
// #define FIREDOWNFACTOR 0.6;

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
    void updateMiniMap(float dt);
    void setNextFire();
    void backMenu(Ref* pSender);

    CREATE_FUNC(SceneGameRoom);

private:
    int move();
    void send(float dt);

    Size visibleSize;

    Label * msgLabel;
    Label * gameOverLabel;
    EventListenerKeyboard* keyboardListener;
    int id;
    int port;

    LayerMap* layermap;
    LayerBase* layerMapMini;
    LayerBase* layerState;
    Scene* physicsScene;

    Menu* menu;

    Vec2 offset;
    Vec2 playerPos;

    map<char, bool> input;
};

#endif // __SCENE_GAME_ROOM_H__
