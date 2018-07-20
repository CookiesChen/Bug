#include "Helpers.h"
#include "LayerJoinRoom.h"
#include "ServiceAPI.h"

LayerBase* LayerJoinRoom::createLayer()
{
    return LayerJoinRoom::create();
}

bool LayerJoinRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 菜单
    auto menu = Menu::create();
    menu->setPosition(origin);

    // 页码显示
    auto currentPage = Label::createWithTTF("0 /", "Fonts/arial.ttf", 20);
    auto maxPage = Label::createWithTTF("0", "Fonts/arial.ttf", 20);

    currentPage->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height / 2 - 300));
    maxPage->setPosition(Vec2(visibleSize.width / 2 + 20, visibleSize.height / 2 - 300));

    // 按钮
    auto backButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::backMenu, this));
    auto prepageButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::prePage, this));
    auto nextpageButton = MenuItemImage::create("Graphics/System/BtnBack.png", "Graphics/System/BtnBack_click.png", CC_CALLBACK_1(LayerJoinRoom::nextPage, this));
    
    backButton->setPosition(Vec2(100, visibleSize.height - 50));
    prepageButton->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 300));
    nextpageButton->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 300));

    backButton->setScale(0.5);
    prepageButton->setScale(0.5);
    nextpageButton->setScale(0.5);

    // 房间列表
    auto roomList = ListView::create();
    roomList->setDirection(ui::ScrollView::Direction::VERTICAL);
    roomList->setTouchEnabled(true);
    roomList->setBounceEnabled(true);
    roomList->setBackGroundImage("Graphics/Pictures/background.png");
    roomList->setSize(Size(720, 480));
    roomList->ignoreContentAdaptWithSize(false);
    roomList->setAnchorPoint(Vec2(0.5, 0.5));
    roomList->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // 模板列表项
    auto modelltItem = Layout::create();
    modelltItem->setTouchEnabled(true);
    auto image = Sprite::create("Graphics/System/BtnBack.png");
    image->setScale(0.3);
    modelltItem->setSize(image->getContentSize());
    modelltItem->addChild(image);

    roomList->setItemModel(modelltItem);

    for (int i = 0; i < 4; ++i)
    {
        roomList->pushBackDefaultItem();//加载默认项目模板5个
    }

    menu->addChild(backButton, 2);
    menu->addChild(prepageButton, 2);
    menu->addChild(nextpageButton, 2);

    this->addChild(menu, 2);
    this->addChild(currentPage, 1);
    this->addChild(maxPage, 1);
    this->addChild(roomList, 2);

    // 定时扫描
    schedule(schedule_selector(LayerJoinRoom::getRoomList), 2.0f, kRepeatForever, 0);

    return true;
}

void LayerJoinRoom::backMenu(Ref* pSender)
{
    if (!this->getActive()) return;
    this->updateLayer(Tag::LayerFromJoinRoomOrNewRoomToMenu);
}

void LayerJoinRoom::getRoomList(float dt)
{
    // todo 获取房间列表API
    if (this->getActive() == false) return;
    auto d = Singleton<ServiceAPI>::GetInstance()->GetRoomsList(1, 5);
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            
            // 根据数据生成房间列表
        }
        else
        {
            // 参数错误的提示
        }
    }
    else
    {
        // 解析失败的提示
        return;
    }
}

void LayerJoinRoom::prePage(Ref* pSender) {

}

void LayerJoinRoom::nextPage(Ref* pSender) {

}
