#include <sstream>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include "Helpers.h"
#include "ServiceGame.h"

using namespace cocos2d;

void ServiceGame::JoinRoom(int port, int id, function<void(string)> callBack)
{
    frame = 0;
    this->id = id;

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "0";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->InitSocket(30082);
    Singleton<Net>::GetInstance()->Send(req);
    callBack("Join in Room success");
}

void ServiceGame::SendInput(int input)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);
    document.AddMember("input", input, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "1";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->Send(req);
}


void ServiceGame::GetFrame(function<void(string)> callBack)
{

    while (true)
    {
        DWORD t1, t2;
        t1 = timeGetTime();
        string res = Singleton<Net>::GetInstance()->GetState();
        t2 = timeGetTime();
        stringstream ss;
        ss << "Delay: " << (t2 - t1)*1.0 << "ms\n";
        log("get: %s\n", res.c_str());
        rapidjson::Document d;
        d.Parse<0>(res.c_str());
        if (!d["data"].IsArray()) continue;
        int maxFrame = 0;
        for (auto& frameState : d["data"].GetArray())
        {
            int i = frameState.GetObjectW()["frameID"].GetInt();
            if (i > maxFrame)
            {
                maxFrame = i;
                for (auto& str : frameState.GetObjectW()["commends"].GetArray())
                {
                    ss << "id: " << str["id"].GetInt() << '\n';
                    ss << "input: " << str["input"].GetInt() << '\n';
                }
            }
        }
        if (maxFrame > frame)
        {
            frame = maxFrame;
            rapidjson::Document document;
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            document.AddMember("id", id, allocator);
            document.AddMember("frame", frame, allocator);
            CCLOG("send: %d\n", frame);
            ss << frame << endl;

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            string req = "2";
            req.append(buffer.GetString());
            Singleton<Net>::GetInstance()->Send(req);
        }
        callBack(ss.str());
    }
}


void ServiceGame::OutRoom()
{
    Singleton<Net>::GetInstance()->Send("3");
}
