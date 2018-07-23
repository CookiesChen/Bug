#include "LayerMapMini.h"
#include "Helpers.h"
#include "ServiceGame.h"
#define SCALESIZE 0.3

LayerBase* LayerMapMini::createLayer()
{
    return LayerMapMini::create();
}

bool LayerMapMini::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto mapDark = Sprite::create("Map/miniMapDark.png");
    mapDark->setScale(SCALESIZE);
    mapMiniSize = mapDark->getContentSize() * mapDark->getScale();
    centerPoint.x = visibleSize.width - mapMiniSize.width / 2 - 20;
    centerPoint.y = visibleSize.height - mapMiniSize.height / 2 - 10;
    mapDark->setPosition(centerPoint);
    this->addChild(mapDark, 1);


    // 初始毒圈
    float dis = sqrt(MAPWIDTH * MAPWIDTH + MAPHEIGHT * MAPHEIGHT) / 2;
    setMap(MAPWIDTH / 2, MAPHEIGHT / 2, dis, 0);
    setMap(MAPWIDTH / 2, MAPHEIGHT / 2, dis, 1);

    Singleton<ServiceGame>::GetInstance()->fireX = MAPWIDTH / 2;
    Singleton<ServiceGame>::GetInstance()->fireY = MAPHEIGHT / 2;
    Singleton<ServiceGame>::GetInstance()->fireXN = MAPWIDTH / 2;
    Singleton<ServiceGame>::GetInstance()->fireYN = MAPHEIGHT / 2;
    Singleton<ServiceGame>::GetInstance()->fireDis = dis;
    Singleton<ServiceGame>::GetInstance()->fireC = 0;


    // test
    // srand(10086);

    return true;
}

void LayerMapMini::setPlayer(float x, float y)
{
    x /= MAPWIDTH;
    y /= MAPHEIGHT;
    x -= 0.5;
    y -= 0.5;
    x = this->centerPoint.x + x * this->mapMiniSize.width;
    y = this->centerPoint.y + y * this->mapMiniSize.height;

    if (player != nullptr) player->removeFromParentAndCleanup(true);
    player = Sprite::create("Graphics/System/playerPoint.png");
    
    player->setPosition(Vec2(x, y));
    this->addChild(player, 20);
}


void LayerMapMini::setMap(float x, float y, float dis, int type)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //自画一个形状来录stencil
    auto stencil = DrawNode::create();
    stencil->setAnchorPoint(Vec2(0.5, 0.5));
    //多边形定点个数;
    Vec2 points[720];
    //圆心，相对坐标;
    x = (x / MAPWIDTH - 0.5) * this->mapMiniSize.width;
    y = (y / MAPHEIGHT - 0.5) * this->mapMiniSize.height;
    Vec2 center(x, y);
    //半径;
    dis *= mapMiniSize.height / MAPHEIGHT;
    for (int i = 0; i < 720; i++)
    {
        float x = center.x + cos(0.5*i*3.14 / 180) * dis;
        float y = center.y + sin(0.5*i*3.14 / 180) * dis;
        points[i] = Vec2(x, y);
    }
    //画多边形;
    stencil->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(0, 1, 0, 0), 1, Color4F(1, 0, 0, 1));
    //裁剪node

    if (type == 0) {
        if (circleBig != nullptr) circleBig->removeFromParentAndCleanup(true);
        auto map = Sprite::create("Map/miniMap.png");
        map->setScale(SCALESIZE);
        circleBig = ClippingNode::create();
        circleBig->setStencil(stencil);
        circleBig->setPosition(centerPoint);
        circleBig->addChild(map, 10);
        this->addChild(circleBig, 10);
    }
    else {
        if (circleSmall != nullptr) circleSmall->removeFromParentAndCleanup(true);
        auto mapLight = Sprite::create("Map/miniMapLight.png");
        mapLight->setScale(SCALESIZE);
        circleSmall = ClippingNode::create();
        circleSmall->setStencil(stencil);
        circleSmall->setPosition(centerPoint);
        circleSmall->addChild(mapLight, 10);
        this->addChild(circleSmall, 20);
    }

}
