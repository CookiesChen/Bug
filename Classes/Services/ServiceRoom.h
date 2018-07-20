#ifndef __SERVICE_ROOM_H__
#define __SERVICE_ROOM_H__

#include "ModelRoom.h"

class ServiceRoom final
{
public:
    bool heart();
    bool refreshInfo();
    bool joinInRoom(int roomId, string password = "");
    bool setTeam(int team);
    bool setRole(string role);
    bool quitRoom();

    // 房主专用
    bool startGame();
    bool setInfo(string title, string password, string map, int maxPlayer);
    bool setOwn(string userId);
    bool outSb(string userId);

    ModelRoom getRoom();
    bool IsInRoom();
private:
    ModelRoom room;
    bool isInRoom;
};

#endif // __SERVICE_ROOM_H__
