#include "Helpers.h"
#include "ServiceAPI.h"

const string ServiceAPI::apiUrl = "http://127.0.0.1:30081";

rapidjson::Document ServiceAPI::Login(string username, string password)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valUsername, valPassword;
    valUsername.SetString(username.c_str(), allocator);
    valPassword.SetString(Hash::Sha512(password).c_str(), allocator);
    document.AddMember("name", valUsername, allocator);
    document.AddMember("password", valPassword, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/login", buffer.GetString());
    rapidjson::Document d;
    d.Parse(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::Logout()
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/logout");
    rapidjson::Document d;
    d.Parse(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::CreateRoom(string title, string password, string map, string mode, int maxPlayer)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valTitle, valPassword, valMap, valMode, valMaxPlayer;
    valTitle.SetString(title.c_str(), allocator);
    valPassword.SetString(password.c_str(), allocator);
    valMap.SetString(map.c_str(), allocator);
    valMode.SetString(mode.c_str(), allocator);
    valMaxPlayer.SetInt(maxPlayer);
    document.AddMember("title", valTitle, allocator);
    document.AddMember("password", valPassword, allocator);
    document.AddMember("gameMap", valMap, allocator);
    document.AddMember("gameMode", valMode, allocator);
    document.AddMember("maxPlayer", valMaxPlayer, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/new", buffer.GetString());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}
