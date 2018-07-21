#include <sstream>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#include "Helpers.h"
#include "ServiceGame.h"

using namespace cocos2d;

void ServiceGame::JoinRoom()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "0";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->InitSocket(this->port);
    Singleton<Net>::GetInstance()->Send(req);
}

void ServiceGame::SendInput(int input, float x, float y)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);
    document.AddMember("input", input, allocator);
    rapidjson::Value locX, locY;
    locX.SetFloat(x);
    locY.SetFloat(y);

    document.AddMember("x", locX, allocator);
    document.AddMember("y", locY, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "1";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->Send(req);
}

void ServiceGame::InitGame(int port, int id) {
    frame = 0;
    this->id = id;
    this->isJoin = false;
    this->isOut = false;
    this->port = port;
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
        ss << "Delay: " << (t2 - t1) * 1.0 << "ms\n";
        log("get: %s\n", res.c_str());

        if (res.compare("join")) {
            this->isJoin = true;
            continue;
        }

        if (res.compare("out")) {
            this->isOut = true;
            continue;
        }

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

bool ServiceGame::GetJoinState()
{
    return this->isJoin;
}

bool ServiceGame::GetOutState()
{
    return this->isOut;
}
