#include <thread>

#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "SceneGameRoom.h"
#include "ServiceGame.h"
#include "ServicePlayer.h"

Scene* SceneGameRoom::createPhysicsScene()
{
    srand((unsigned) 0);
    auto physicsScene = Scene::createWithPhysics();
    physicsScene->getPhysicsWorld()->setAutoStep(true);
    physicsScene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    physicsScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto scene = SceneGameRoom::create();
    physicsScene->addChild(scene);
    return physicsScene;
}

bool SceneGameRoom::init()
{
    if (!SceneBase::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    offset_x = 0;
    offset_y = 0;

    addKeyboardListener();


    /*msgLabel = Label::createWithTTF("Msg", "Fonts/arial.ttf", 30);

    msgLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(msgLabel);

    srand((unsigned)time(NULL));

    id = rand() % 60000;

    Singleton<ServiceGame>::GetInstance()->InitGame(30082, id);

    schedule(schedule_selector(SceneGameRoom::JoinGame), 1.0f, kRepeatForever, 0);

    auto t = new std::thread(&SceneGameRoom::GetState, this);*/

    layermap = (LayerMap*) LayerMap::createLayer();

    // 随机初始位置
    auto randomx = random(1, 9) / 10.0f * layermap->maxWidth;
    auto randomy = random(1, 9) / 10.0f * layermap->maxHeight;
    auto layerPoint = Vec2::ZERO;
    // 初始化有效修正
    if (randomx <= layermap->maxWidth - visibleSize.width / 2 && visibleSize.width / 2 <= randomx)
    {
        layerPoint.x = randomx;
    }
    else if (randomx <= layermap->maxWidth - visibleSize.width / 2)
    {
        layerPoint.x = visibleSize.width / 2;
    }
    else
    {
        layerPoint.x = layermap->maxWidth - visibleSize.width / 2;
    }
    layerPoint.x = layerPoint.x - visibleSize.width / 2;
    if (randomy <= layermap->maxHeight - visibleSize.height / 2 && visibleSize.height / 2 <= randomy)
    {
        layerPoint.y = randomy;
    }
    else if (randomy <= layermap->maxHeight - visibleSize.height / 2)
    {
        layerPoint.y = visibleSize.height / 2;
    }
    else
    {
        layerPoint.y = layermap->maxHeight - visibleSize.height / 2;
    }
    layerPoint.y = layerPoint.y - visibleSize.height / 2;

    layermap->setPosition(-layerPoint);
    layermap->player->setPosition(Vec2(randomx, randomy));

    this->addChild(layermap);

    schedule(schedule_selector(SceneGameRoom::update), 1.0f / 60.0f, kRepeatForever, 0);

    return true;
}

void SceneGameRoom::GetState()
{
    /*Singleton<ServiceGame>::GetInstance()->GetFrame([&](string res) -> void {
        msgLabel->setString(res);
    });*/
}


void SceneGameRoom::JoinGame(float dt)
{
    if (Singleton<ServiceGame>::GetInstance()->GetJoinState() == true)
    {   // 已经加入房间
        msgLabel->setString("join room success!");
        this->unschedule(schedule_selector(SceneGameRoom::JoinGame));
    }
    else
    {
        // 重连中
        msgLabel->setString("joining...");
        Singleton<ServiceGame>::GetInstance()->JoinRoom();
    }
}

void SceneGameRoom::ExitGame(float dt)
{
    if (Singleton<ServiceGame>::GetInstance()->GetOutState() == true)
    {
        // 已经退出房间
        msgLabel->setString("join room success!");
        this->unschedule(schedule_selector(SceneGameRoom::ExitGame));
    }
    else
    {
        // 重新发送
        msgLabel->setString("joining...");
        Singleton<ServiceGame>::GetInstance()->OutRoom();
    }
}

// 添加键盘事件监听器
void SceneGameRoom::addKeyboardListener()
{
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(SceneGameRoom::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SceneGameRoom::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void SceneGameRoom::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    isMove = true;
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_A:
        //Singleton<ServiceGame>::GetInstance()->SendInput(1, 0 ,0);
        input['A'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    case EventKeyboard::KeyCode::KEY_D:
        //Singleton<ServiceGame>::GetInstance()->SendInput(2, 0, 0);
        input['D'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_W:
    case EventKeyboard::KeyCode::KEY_W:
        //Singleton<ServiceGame>::GetInstance()->SendInput(2, 0, 0);
        input['W'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_S:
    case EventKeyboard::KeyCode::KEY_S:
        //Singleton<ServiceGame>::GetInstance()->SendInput(2, 0, 0);
        input['S'] = true;
        break;
    }
    move();
}

void SceneGameRoom::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
        //Singleton<ServiceGame>::GetInstance()->SendInput(3, 0 , 0);
        input['A'] = false;
        if (moveDirection == 'A') isMove = false;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
        //Singleton<ServiceGame>::GetInstance()->SendInput(4, 0 ,0 );
        input['D'] = false;
        if (moveDirection == 'D') isMove = false;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_W:
    case EventKeyboard::KeyCode::KEY_CAPITAL_W:
        //Singleton<ServiceGame>::GetInstance()->SendInput(4, 0, 0);
        input['W'] = false;
        if (moveDirection == 'W') isMove = false;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_S:
    case EventKeyboard::KeyCode::KEY_CAPITAL_S:
        //Singleton<ServiceGame>::GetInstance()->SendInput(4, 0, 0);
        input['S'] = false;
        if (moveDirection == 'S') isMove = false;
        break;
    }
    move();
}

void SceneGameRoom::updateLayer(Tag tag)
{

}

void SceneGameRoom::updateScene(Tag tag)
{

}

void SceneGameRoom::LayerMove(int direction)
{
    switch (direction)
    {
    case 0:
        offset_x = offset;
        offset_y = 0;
        break;
    case 1:
        offset_x = -offset;
        offset_y = 0;
        break;
    case 2:
        offset_x = 0;
        offset_y = -offset;
        break;
    case 3:
        offset_x = 0;
        offset_y = offset;
        break;
    }
}

void SceneGameRoom::move()
{
    int count = input['W'] + input['A'] + input['S'] + input['D'];
    if (count >= 3 || input['W'] + input['S'] == 2 || input['A'] + input['D'] == 2) return;
    int v = 300;
    if (input['W'] && input['A'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(315);
    }
    else if (input['W'] && input['D'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(45);
    }
    else if (input['S'] && input['A'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(225);
    }
    else if (input['S'] && input['D'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(135);
    }
    else if (input['W'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(0);
    }
    else if (input['A'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(270);
    }
    else if (input['S'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(180);
    }
    else if (input['D'])
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(90);
    }
    else // 停止移动
    {
        Singleton<ServicePlayer>::GetInstance()->MovePlayer(360);
    }
}

void SceneGameRoom::update(float time)
{
    /*auto layerpoint = layerplayer->player->getPosition();
    if ((visibleSize.width / 2 <= layerpoint.x && layerpoint.x <= layermap->maxWidth - visibleSize.width / 2 && offset_x != 0)
        || (visibleSize.height / 2 <= layerpoint.y && layerpoint.y <= layermap->maxHeight - visibleSize.height / 2 && offset_y != 0))
    {
        layermap->setPosition(layermap->getPosition() + Vec2(offset_x, offset_y));
        layerplayer->setPosition(layerplayer->getPosition() + Vec2(offset_x, offset_y));
    }*/
}
