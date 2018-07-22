#ifndef __SCENE_GAME_ROOM_H__
#define __SCENE_GAME_ROOM_H__

#include "LayerBase.h"
#include "SceneBase.h"
#include "cocos2d.h"
#include "LayerMap.h"
#include "LayerPlayer.h"

class SceneGameRoom final : public SceneBase
{
public:
    static SceneBase * createScene();

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
    void LayerMove(int direction);

    CREATE_FUNC(SceneGameRoom);

private:

    Size visibleSize;

    Label * msgLabel;
    int id;
    int port;

    LayerPlayer* layerplayer;

    LayerMap* layermap;

    LayerBase* layerMapMini;

    float offset = 5.0f;
    float offset_x;
    float offset_y;
    bool isMove;
    bool isLayerMove;
    char moveDirection;

};

#endif // __SCENE_GAME_ROOM_H__
