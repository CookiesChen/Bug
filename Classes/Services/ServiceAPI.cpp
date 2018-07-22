#include "Helpers.h"
#include "ServiceAPI.h"

// const string ServiceAPI::apiUrl = "http://127.0.0.1:30081";
const string ServiceAPI::apiUrl = "http://111.230.240.70:30081";

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

rapidjson::Document ServiceAPI::JoinRoom(int id, string password)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valPassword;
    valPassword.SetString(password.c_str(), allocator);
    document.AddMember("password", valPassword, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/join/" + to_string(id), buffer.GetString());
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

rapidjson::Document ServiceAPI::SetUserInfo(string name, int gender, string avatar)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valName, valGender, valAvatar;
    valName.SetString(name.c_str(), allocator);
    document.AddMember("name", valName, allocator);
    valGender.SetInt(gender);
    document.AddMember("gender", valGender, allocator);
    valAvatar.SetString(avatar.c_str(), allocator);
    document.AddMember("avatar", valAvatar, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/info", buffer.GetString());
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::VerifyEmail(string code)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value valVCode;
    valVCode.SetString(code.c_str(), allocator);
    document.AddMember("vCode", valVCode, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/user/valid", buffer.GetString());
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

rapidjson::Document ServiceAPI::GetUserInfo(string userID)
{
    if (userID == "") userID = "self";
    auto res = Singleton<Net>::GetInstance()->Get(apiUrl + "/user/info/" + userID);
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

string ServiceAPI::RoomHeart()
{
    return Singleton<Net>::GetInstance()->Get(apiUrl + "/room/heart");
}

rapidjson::Document ServiceAPI::GetRoomDetail()
{
    auto res = Singleton<Net>::GetInstance()->Get(apiUrl + "/room/detail");
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::SetReady(bool isReady)
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/ready/" + (isReady ? "true" : "false"));
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::SetPlay(bool isPlay)
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/play/" + (isPlay ? "true" : "false"));
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}


rapidjson::Document ServiceAPI::SetTeam(int team)
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/team/" + to_string(team));
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::SetRole(string role)
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/role/" + role);
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::QuitRoom()
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/quit");
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}

rapidjson::Document ServiceAPI::SetRoomInfo(string title, string password, string gameMap, int maxPlayer)
{
    // todo 设置房间信息
    return nullptr;
}

rapidjson::Document ServiceAPI::SetRoomOwn(string userId)
{
    // todo 设置房主
    return nullptr;
}

rapidjson::Document ServiceAPI::OutSbfromRoom(string userId)
{
    // todo 踢人
    return nullptr;
}

rapidjson::Document ServiceAPI::startGame()
{
    auto res = Singleton<Net>::GetInstance()->Post(apiUrl + "/room/start");
    rapidjson::Document d;
    d.Parse<0>(res.c_str());
    return d;
}
