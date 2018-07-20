#include "ServiceRoom.h"
#include "ServiceUser.h"
#include "Helpers.h"
#include "ServiceAPI.h"


ModelRoom ServiceRoom::getRoom()
{
    return this->room;
}

bool ServiceRoom::IsInRoom()
{
    return this->isInRoom;
}

bool ServiceRoom::joinInRoom(int roomId, string password)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->JoinRoom(roomId, password);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    this->isInRoom = true;
    return true;
}

bool ServiceRoom::quitRoom()
{
    auto d = Singleton<ServiceAPI>::GetInstance()->QuitRoom();
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    this->isInRoom = false;
    return true;
}

bool ServiceRoom::refreshInfo()
{
    if (!this->isInRoom) return false;
    auto d = Singleton<ServiceAPI>::GetInstance()->GetRoomDetail();
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    auto roomData = d["room"].GetObjectW();
    room.Id = roomData["id"].GetInt();
    room.Title = roomData["title"].GetString();
    room.OwnId = roomData["ownId"].GetString();
    room.IsOwn = Singleton<ServiceUser>::GetInstance()->GetUserId() == room.OwnId;
    room.Port = roomData["port"].GetInt();
    return true;
}

bool ServiceRoom::heart()
{
    return false;

}

bool ServiceRoom::setTeam(int team)
{
    return false;
}
bool ServiceRoom::setRole(string role)
{
    return false;

}

// 房主专用
bool ServiceRoom::startGame()
{

    return false;
}

bool ServiceRoom::setInfo(string title, string password, string map, int maxPlayer)
{
    return false;

}

bool ServiceRoom::setOwn(string userId)
{
    return false;

}

bool ServiceRoom::outSb(string userId)
{
    return false;

}
