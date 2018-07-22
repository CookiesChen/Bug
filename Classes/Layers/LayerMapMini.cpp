#include "LayerMapMini.h"

LayerBase* LayerMapMini::createLayer()
{
    return LayerMapMini::create();
}

bool LayerMapMini::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    mapBack = Sprite::create("Map/minimapdark.png");
    mapBack->setScale(0.3);
    mapBack->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 80));
    this->addChild(mapBack, 1);
    setMap(0.5,0.5,1);
    setPlayer(0.5, 0.5);

    return true;
}

void LayerMapMini::setPlayer(float x, float y)
{
    if (player != nullptr) player->removeFromParentAndCleanup(true);
    player = Sprite::create("Graphics/System/playerPoint.png");
    float xBegin = 828;
    float yBegin = 622;
    x = xBegin + x * 193;
    y = yBegin + y * 137;
    player->setPosition(Vec2(x, y));
    this->addChild(player, 20);
}


void LayerMapMini::setMap(float x, float y, float pre)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (clipper != nullptr) clipper->removeFromParentAndCleanup(true);
    //自画一个形状来录stencil
    auto stencil = DrawNode::create();
    stencil->setAnchorPoint(Vec2(0.5, 0.5));
    //多边形定点个数;
    Vec2 points[720];
    //圆心，相对坐标;
    float xBegin = 0;
    float yBegin = 0;
    x = xBegin + (x - 0.5) * 193;
    y = yBegin + (y - 0.5) * 137;
    Vec2 center(x, y);
    //半径;
    float R = 100 * pre;
    for (int i = 0; i < 720; i++)
    {
        float x = center.x + cos(0.5*i*3.14 / 180) * R;
        float y = center.y + sin(0.5*i*3.14 / 180) * R;
        points[i] = Vec2(x, y);
    }
    //画多边形;
    stencil->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(0, 1, 0, 0), 1, Color4F(1, 0, 0, 1));
    //裁剪node
    clipper = ClippingNode::create();
    clipper->setAnchorPoint(Point(0.5, 0.5));
    clipper->setStencil(stencil);
    clipper->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 80));
    this->addChild(clipper, 10);

    Sprite *sp = Sprite::create("Map/minimap.png");
    sp->setScale(0.3);
    clipper->addChild(sp, 10);
}
