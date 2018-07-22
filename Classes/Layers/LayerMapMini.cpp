#include "LayerMapMini.h"

LayerBase* LayerMapMini::createLayer()
{
    return LayerMapMini::create();
}

bool LayerMapMini::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    mapBack = Sprite::create("Graphics/Pictures/background.png");
    mapBack->setScale(0.15);
    mapBack->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 60));
    // this->addChild(mapBack, 1);
    setMap(190);


    return true;
}




void LayerMapMini::setMap(int pre)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto s = Director::getInstance()->getWinSize();

    //自画一个形状来录stencil
    DrawNode *stencil = DrawNode::create();
    stencil->setAnchorPoint(Point(0.5, 0.5));
    //多边形定点个数;
    Vec2 points[720];
    //圆心，相对坐标;
    Vec2 center(0, 0);
    //半径;
    float R = 200 * (pre/100);
    for (int i = 0; i < 720; i++)
    {
        float x = center.x + cos(0.5*i*3.14 / 180) * R;
        float y = center.y + sin(0.5*i*3.14 / 180) * R;
        points[i] = Vec2(x, y);
        log("%f,%f", x, y);
    }
    //画多边形;
    stencil->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(0, 1, 0, 0), 1, Color4F(1, 0, 0, 1));
    // stencil->setPosition(Point(50, 50));
    Vec2 p2[4];
    p2[0] = Vec2(-80, -50);
    p2[1] = Vec2(80, -50);
    p2[2] = Vec2(80, 50);
    p2[3] = Vec2(-80, 50);
    DrawNode *rec = DrawNode::create();
    rec->drawPolygon(p2, 4, Color4F(0, 1, 0, 0), 1, Color4F(1, 0, 0, 1));

    //裁剪node
    if (clipper != nullptr) clipper->removeFromParentAndCleanup(true);
    clipper = ClippingNode::create();
    clipper->setAnchorPoint(Point(0.5, 0.5));
    //clipper->setAlphaThreshold(0.05);
    //clipper->setInverted(true);
    clipper->setStencil(stencil);
    // clipper->setPosition(Vec2(visibleSize.width - 140, visibleSize.height - 130));
    // this->addChild(clipper, 10);

    Sprite *sp = Sprite::create("Graphics/Pictures/background.png");
    sp->setScale(0.3);
    clipper->addChild(sp, 10);


    auto clipper2 = ClippingNode::create();
    clipper2->setAnchorPoint(Point(0.5, 0.5));
    clipper2->setStencil(rec);
    clipper2->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 60));
    this->addChild(clipper2, 10);
    clipper2->addChild(clipper, 10);

}
