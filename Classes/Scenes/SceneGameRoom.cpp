#include <thread>

#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "SceneGameRoom.h"
#include "ServiceGame.h"
#include "ServicePlayer.h"
#include "LayerMapMini.h"

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

    addKeyboardListener();


    /*msgLabel = Label::createWithTTF("Msg", "Fonts/arial.ttf", 30);

    msgLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(msgLabel);

    srand((unsigned)time(NULL));

    id = rand() % 60000;

    Singleton<ServiceGame>::GetInstance()->InitGame(30082, id);*/

    schedule(schedule_selector(SceneGameRoom::JoinGame), 1.0f, kRepeatForever, 0);

    // auto t = new std::thread(&SceneGameRoom::GetState, this);

    layermap = (LayerMap*) LayerMap::createLayer();
    layerMapMini = LayerMapMini::createLayer();
    this->addChild(layerMapMini,10);
    layermap->setContentSize(layermap->map->getContentSize());

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
    Singleton<ServiceGame>::GetInstance()->GetFrame([&](vector<frameState> fsv) -> void {
        for (auto &fs : fsv)
        {
            Singleton<ServicePlayer>::GetInstance()->MoveOthers(fs.commands);
        }
    });
}


void SceneGameRoom::JoinGame(float dt)
{
    if (Singleton<ServiceGame>::GetInstance()->GetJoinState() == true)
    {   // 已经加入房间
        // msgLabel->setString("join room success!");
        this->unschedule(schedule_selector(SceneGameRoom::JoinGame));
    }
    else
    {
        // 重连中
        // msgLabel->setString("joining...");
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
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_A:
        input['A'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    case EventKeyboard::KeyCode::KEY_D:
        input['D'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_W:
    case EventKeyboard::KeyCode::KEY_W:
        input['W'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_S:
    case EventKeyboard::KeyCode::KEY_S:
        input['S'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_J:
    case EventKeyboard::KeyCode::KEY_J:
        input['J'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_K:
    case EventKeyboard::KeyCode::KEY_K:
        input['K'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_L:
    case EventKeyboard::KeyCode::KEY_L:
        input['L'] = true;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        Singleton<ServicePlayer>::GetInstance()->SetHighVelocity();
        break;
    }
    int dir = move();
    float x = layermap->map->getPosition().x;
    float y = layermap->map->getPosition().y;
    Singleton<ServicePlayer>::GetInstance()->SetXYandDir(x, y, dir);
    Singleton<ServiceGame>::GetInstance()->SendInput(0, x, y, dir);
}

void SceneGameRoom::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
        input['A'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
        input['D'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_W:
    case EventKeyboard::KeyCode::KEY_CAPITAL_W:
        input['W'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_S:
    case EventKeyboard::KeyCode::KEY_CAPITAL_S:
        input['S'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_J:
    case EventKeyboard::KeyCode::KEY_J:
        input['J'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_K:
    case EventKeyboard::KeyCode::KEY_K:
        input['K'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_CAPITAL_L:
    case EventKeyboard::KeyCode::KEY_L:
        input['L'] = false;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
        Singleton<ServicePlayer>::GetInstance()->SetLowVelocity();
        break;
    }
    int dir = move();
    float x = layermap->map->getPosition().x;
    float y = layermap->map->getPosition().y;
    auto p = Singleton<ServicePlayer>::GetInstance()->GetPlayer();
    if (x != p.x || y != p.y || dir != p.dir)
    {
        Singleton<ServicePlayer>::GetInstance()->SetXYandDir(x, y, dir);
        Singleton<ServiceGame>::GetInstance()->SendInput(0, x, y, dir);
    }
}

void SceneGameRoom::updateLayer(Tag tag)
{

}

void SceneGameRoom::updateScene(Tag tag)
{

}

int SceneGameRoom::move()
{
    int count = input['W'] + input['A'] + input['S'] + input['D'];
    if (count >= 3 || input['W'] + input['S'] == 2 || input['A'] + input['D'] == 2)
    {
        return Singleton<ServicePlayer>::GetInstance()->GetPlayer().dir;
    }
    int v = 300;
    int dir = 360;
    if (input['W'] && input['A']) dir = 315;
    else if (input['W'] && input['D']) dir = 45;
    else if (input['S'] && input['A']) dir = 225;
    else if (input['S'] && input['D']) dir = 135;
    else if (input['W']) dir = 0;
    else if (input['A']) dir = 270;
    else if (input['S']) dir = 180;
    else if (input['D']) dir = 90;
    else dir = 360;
    Singleton<ServicePlayer>::GetInstance()->MovePlayer(dir);
    return dir;
}

void SceneGameRoom::update(float time)
{
    Vec2 layerPoint;
    float randomx = layermap->player->getPosition().x;
    float randomy = layermap->player->getPosition().y;

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
}
