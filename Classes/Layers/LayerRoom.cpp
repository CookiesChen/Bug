#include "LayerRoom.h"

LayerBase* LayerRoom::createLayer()
{
    return LayerRoom::create();
}

bool LayerRoom::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


    // todo 显示玩家信息和准备状态以及所选角色
    // todo 显示这个房间的游戏模式和地图
    // todo 准备
    // todo 选择队伍
    // todo 选择角色
    // todo 退出房间
    // -------------仅房主显示-----------
    // todo 踢人
    // todo 转移房主
    // todo 设置房间信息
    // todo 开始游戏
    return true;
}

void LayerRoom::SetRoomId(string id)
{
    this->roomID = id;
}
