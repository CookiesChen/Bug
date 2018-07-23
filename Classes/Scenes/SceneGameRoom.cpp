#include <thread>

#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "LayerMapMini.h"
#include "LayerState.h"
#include "SceneGameRoom.h"
#include "ServiceGame.h"
#include "ServicePlayer.h"
#include "SceneMenu.h"


Scene* SceneGameRoom::createPhysicsScene()
{
    srand((unsigned) 0);
    auto physicsScene = Scene::createWithPhysics();
    physicsScene->getPhysicsWorld()->setAutoStep(true);
    physicsScene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    //physicsScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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


    // 菜单
    menu = Menu::create();
    menu->setPosition(origin);
    // 返回菜单
    auto buttonBack = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(SceneGameRoom::backMenu, this));
    buttonBack->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    menu->addChild(buttonBack, 1);
    menu->setVisible(false);

    this->addChild(menu, 1);


    msgLabel = Label::createWithTTF("", "Fonts/arial.ttf", 30);
    msgLabel->setAnchorPoint(Vec2::ZERO);
    msgLabel->setPosition(Vec2::ZERO);
    this->addChild(msgLabel, 99);

    gameOverLabel = Label::createWithTTF("", "Fonts/arial.ttf", 50);
    gameOverLabel->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2 + 100));
    this->addChild(gameOverLabel, 99);

    schedule(schedule_selector(SceneGameRoom::JoinGame), 1.0f, kRepeatForever, 0);

    auto t = new std::thread(&SceneGameRoom::GetState, this);

    layermap = (LayerMap*) LayerMap::createLayer();
    layermap->setContentSize(layermap->map->getContentSize());

    layerMapMini = LayerMapMini::createLayer();
    layerState = LayerState::createLayer();
    this->addChild(layerMapMini, 10);
    this->addChild(layerState, 11);

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

    schedule(schedule_selector(SceneGameRoom::updateMiniMap), 0.5f, kRepeatForever, 0);

    schedule(schedule_selector(SceneGameRoom::update), 1.0f / 60.0f, kRepeatForever, 0);
    schedule(schedule_selector(SceneGameRoom::send), 1.0f / 20, kRepeatForever, 0);

    return true;
}

void SceneGameRoom::backMenu(Ref* pSender)
{
    Director::getInstance()->replaceScene(SceneMenu::createScene());
}


void SceneGameRoom::setNextFire() {
    float fireX = Singleton<ServiceGame>::GetInstance()->fireX;
    float fireY = Singleton<ServiceGame>::GetInstance()->fireY;
    float fireDis = Singleton<ServiceGame>::GetInstance()->fireDis;

    int range = (int)(fireDis * (1 - FIREFACTOR) * sqrt(2));

    int nextX = range / 2 - rand() % range + MAPWIDTH / 2;
    int nextY = range / 2 - rand() % range + MAPHEIGHT / 2;

    Singleton<ServiceGame>::GetInstance()->fireX = Singleton<ServiceGame>::GetInstance()->fireXN;
    Singleton<ServiceGame>::GetInstance()->fireY = Singleton<ServiceGame>::GetInstance()->fireYN;
    Singleton<ServiceGame>::GetInstance()->fireXN = nextX;
    Singleton<ServiceGame>::GetInstance()->fireYN = nextY;

    Singleton<ServiceGame>::GetInstance()->fireDis = (int)(fireDis * FIREFACTOR);
    Singleton<ServiceGame>::GetInstance()->fireC++;

    ((LayerMapMini*)layerMapMini)->setMap(nextX, nextY, fireDis * FIREFACTOR, 1);
}

void SceneGameRoom::updateMiniMap(float dt)
{
    // test
    // Singleton<ServiceGame>::GetInstance()->frame++;

    int frame = Singleton<ServiceGame>::GetInstance()->frame;
    log("%d", frame);

    float fireX = Singleton<ServiceGame>::GetInstance()->fireX;
    float fireY = Singleton<ServiceGame>::GetInstance()->fireY;
    float fireXN = Singleton<ServiceGame>::GetInstance()->fireXN;
    float fireYN = Singleton<ServiceGame>::GetInstance()->fireYN;
    float fireDis = Singleton<ServiceGame>::GetInstance()->fireDis;

    int classInterval = FIREINTERVAL + FIREDOWN;
    if (frame > classInterval && frame < classInterval * FIRECLASS) {
        int fireClass = Singleton<ServiceGame>::GetInstance()->fireC;
        while (fireClass < (frame / classInterval)) {
            setNextFire();
            fireClass = Singleton<ServiceGame>::GetInstance()->fireC;
            fireXN = Singleton<ServiceGame>::GetInstance()->fireXN;
            fireYN = Singleton<ServiceGame>::GetInstance()->fireYN;
            fireX = Singleton<ServiceGame>::GetInstance()->fireX;
            fireY = Singleton<ServiceGame>::GetInstance()->fireY;
            fireDis = Singleton<ServiceGame>::GetInstance()->fireDis;
        }
        if (((frame - FIREINTERVAL) / classInterval) >= fireClass) {
            // 收缩时间
            float pre = ((classInterval * (fireClass + 1) - frame) / (float)FIREDOWN);
            fireDis += pre * (fireDis / (float)FIREFACTOR - fireDis);
            fireX += (fireXN - fireX) * (1-pre);
            fireY += (fireYN - fireY) * (1-pre);
        }
        else {
            fireDis = fireDis / (float)FIREFACTOR ;
        }
        ((LayerMapMini*)layerMapMini)->setMap(fireX, fireY, fireDis, 0);
    }
    // 扣血
    auto p = Singleton<ServicePlayer>::GetInstance()->GetPlayer();
    if ((p.x - fireX) * (p.x - fireX) + (p.y - fireY) * (p.y - fireY) > fireDis * fireDis) {
        Singleton<ServiceGame>::GetInstance()->SendInput(2, 0, 0, 0);
        Singleton<ServicePlayer>::GetInstance()->SetPlayer(p);
    }
    // 人物位置
    float x = layermap->player->getPosition().x;
    float y = layermap->player->getPosition().y;
    ((LayerMapMini*)layerMapMini)->setPlayer(x, y);
}

void SceneGameRoom::GetState()
{
    Singleton<ServiceGame>::GetInstance()->GetFrame([&](vector<frameState> fsv) -> void {
        Singleton<ServicePlayer>::GetInstance()->SetData(fsv);
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
        log("try");
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
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(SceneGameRoom::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SceneGameRoom::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void SceneGameRoom::send(float dt)
{
    if (Singleton<ServiceGame>::GetInstance()->GetJoinState() == false) return;
    int dir = move();
    float x = layermap->player->getPosition().x - layermap->map->getPosition().x;
    float y = layermap->player->getPosition().y - layermap->map->getPosition().y;
    Singleton<ServicePlayer>::GetInstance()->SetXYandDir(x, y, dir);
    if (input['J'])
    {
        Singleton<ServiceGame>::GetInstance()->SendInput(1, x, y, dir);
        input['J'] = false;
    }
    else
    {
        Singleton<ServiceGame>::GetInstance()->SendInput(0, x, y, dir);
    }
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
        Singleton<ServicePlayer>::GetInstance()->PlayerAttack();
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
    Singleton<ServicePlayer>::GetInstance()->MovePlayer(move());
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
    Singleton<ServicePlayer>::GetInstance()->MovePlayer(move());
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
    return dir;
}

void SceneGameRoom::update(float time)
{
    Singleton<ServicePlayer>::GetInstance()->DealData();
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

    bool isWin = true;
    for (auto &p : Singleton<ServicePlayer>::GetInstance()->GetOtherPlayer())
    {
        if (!p.dead) {
            isWin = false;
        }
        if (!p.dead && p.hp <= 0) {
            msgLabel->setString(p.userName + " deads.");
            Singleton<ServicePlayer>::GetInstance()->SetDeadPlayerById(p.Id);
        }
    }

    auto p = Singleton<ServicePlayer>::GetInstance()->GetPlayer();
    if (!p.dead && p.hp <= 0)
    {
        isWin = false;
        Singleton<ServicePlayer>::GetInstance()->SetDeadPlayerById(p.Id);
        Singleton<ServiceGame>::GetInstance()->OutRoom();
        this->getEventDispatcher()->removeEventListener(keyboardListener);
        gameOverLabel->setString("You die.");
        menu->setVisible(true);
    }
    if (isWin) {
        Singleton<ServiceGame>::GetInstance()->OutRoom();
        this->getEventDispatcher()->removeEventListener(keyboardListener);
        this->unscheduleUpdate();
        gameOverLabel->setString("You Win!");
        menu->setVisible(true);
    }
}
