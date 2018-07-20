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

rapidjson::Document ServiceAPI::Register(string username, string password, string email)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valName, valEmail, valPassword;
    valName.SetString(username.c_str(), allocator);
    valEmail.SetString(email.c_str(), allocator);
    valPassword.SetString(Hash::Sha512(password).c_str(), allocator);
    document.AddMember("name", valName, allocator);
    document.AddMember("email", valEmail, allocator);
    document.AddMember("password", valPassword, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/register", buffer.GetString());
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

rapidjson::Document ServiceAPI::GetEmailCode()
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/email");
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::SetUserInfo(string name, int gender)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valName, valGender;
    valName.SetString(name.c_str(), allocator);
    document.AddMember("title", valName, allocator);
    valGender.SetInt(gender);
    document.AddMember("gender", valGender, allocator);
    document.AddMember("avatar", "default", allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/info", buffer.GetString());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::GetNewVersion()
{
    auto res = Singleton<Net>::GetInstance()->Get(apiUrl + "/game/new");
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::GetRoomsList(int page, int maxSizePerPage)
{
    string query("size=");
    query.append(to_string(maxSizePerPage));
    auto res = Singleton<Net>::GetInstance()->Get(apiUrl + "/room/list/" + to_string(page), query);
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}
