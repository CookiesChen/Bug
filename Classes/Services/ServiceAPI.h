#ifndef __SERVICE_API__
#define __SERVICE_API__

#include <string>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace std;

class ServiceAPI final
{
public:
    rapidjson::Document Login(string username, string password);
    rapidjson::Document Register(string username, string password, string email);
    rapidjson::Document GetEmailCode();
    rapidjson::Document VerifyEmail(string code);
    rapidjson::Document Logout();
    rapidjson::Document SetUserInfo(string name, int gender, string avatar);
    rapidjson::Document GetUserInfo(string userID = "");

    string RoomHeart();
    rapidjson::Document GetRoomDetail();
    rapidjson::Document GetRoomsList(int page, int maxSizePerPage);
    rapidjson::Document CreateRoom(string title, string password, string map, string mode, int maxPlayer);
    rapidjson::Document JoinRoom(int id, string password = "");
    rapidjson::Document SetReady(bool isReady);
    rapidjson::Document SetTeam(int team);
    rapidjson::Document SetRole(string role);
    rapidjson::Document QuitRoom();

    rapidjson::Document SetRoomInfo(string title, string password, string gameMap, int maxPlayer);
    rapidjson::Document SetRoomOwn(string userId);
    rapidjson::Document OutSbfromRoom(string userId);
    rapidjson::Document startGame();

    rapidjson::Document GetNewVersion();
private:
    static const string apiUrl;
};

#endif // __SERVICE_API__
