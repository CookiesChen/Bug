#include "ServiceRoom.h"
#include "ServiceUser.h"
#include "Helpers.h"
#include "ServiceAPI.h"
#include <thread>
#include "cocos2d.h"

ModelRoom ServiceRoom::getRoom()
{
    return this->room;
}

bool ServiceRoom::IsInRoom()
{
    return this->isInRoom;
}

bool ServiceRoom::createRoom()
{
    this->isInRoom = true;
    startHeart();
    return true;
}

bool ServiceRoom::joinInRoom(int roomId, string password)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->JoinRoom(roomId, password);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    this->isInRoom = true;
    startHeart();
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
    room.IsRandom = roomData["isRandom"].GetBool();
    room.GameMap = roomData["gameMap"].GetString();
    room.MaxPalyer = roomData["maxPlayer"].GetInt();
    room.fireX = roomData["fireX"].GetInt();
    room.fireY = roomData["fireY"].GetInt();
    room.randSeed = roomData["randSeed"].GetInt();
    room.Mode = roomData["mode"].GetString();
    room.Password = roomData["password"].GetString();
    room.Playing = roomData["playing"].GetBool();
    if (d["players"].IsNull()) return false;
    room.Players.clear();
    for (auto& player : d["players"].GetArray()) {
        PlayerInfo newPlayer;
        auto playerData = player["player"].GetObjectW();
        auto playerDataInfo = player["info"].GetObjectW();
        newPlayer.userId = playerData["userId"].GetString();
        newPlayer.gameId = playerData["gameId"].GetInt();
        newPlayer.roleId = playerData["roleId"].GetString();
        newPlayer.isReady = playerData["isReady"].GetBool();
        newPlayer.team = playerData["team"].GetInt();
        newPlayer.userName = playerDataInfo["name"].GetString();
        newPlayer.avatar = playerDataInfo["avatar"].GetString();
        newPlayer.gender = playerDataInfo["gender"].GetInt();
        room.Players.push_back(newPlayer);
    }
    return true;
}

bool ServiceRoom::heart()
{
    auto d = Singleton<ServiceAPI>::GetInstance()->RoomHeart();
    return d == "true" ? true : false;
}


bool ServiceRoom::setReady(bool isReady)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetReady(isReady);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
    
}

bool ServiceRoom::setTeam(int team)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetTeam(team);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}
bool ServiceRoom::setRole(string role)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetRole(role);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}

// 房主专用
bool ServiceRoom::startGame()
{
    auto d = Singleton<ServiceAPI>::GetInstance()->startGame();
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}


bool ServiceRoom::setPlay(bool isPlay)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetPlay(isPlay);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}

bool ServiceRoom::setInfo(string title, string password, string map, int maxPlayer)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetRoomInfo(title, password, map, maxPlayer);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}

bool ServiceRoom::setOwn(string userId)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->SetRoomOwn(userId);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}

bool ServiceRoom::outSb(string userId)
{
    auto d = Singleton<ServiceAPI>::GetInstance()->OutSbfromRoom(userId);
    if (d.HasParseError() || !d.IsObject() || !d.HasMember("status")) return false;
    if (strcmp(d["status"].GetString(), "success") != 0) return false;
    return true;
}

bool ServiceRoom::HavePassword()
{
    return this->room.Password == "password";
}

void ServiceRoom::startHeart()
{
    isStopHeart = false;
    auto t = new std::thread(&ServiceRoom::heartLoop, this);
}

void ServiceRoom::heartLoop()
{
    while (1) {
        Sleep(1599);
        if (IsInRoom() && !isStopHeart) {
            heart();
        }
        else {
            isStopHeart = false;
            break;
        }
    }
}

void ServiceRoom::stopHeart()
{
    this->isStopHeart = true;
}
