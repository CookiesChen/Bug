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
    document.AddMember("i", id, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "0";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->Send(req);
}

void ServiceGame::SendInput(int command, float x, float y, int dir)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("i", this->id, allocator);
    document.AddMember("c", command, allocator);
    rapidjson::Value locX, locY, valDir;
    locX.SetFloat(x);
    locY.SetFloat(y);
    valDir.SetInt(dir);
    document.AddMember("x", locX, allocator);
    document.AddMember("y", locY, allocator);
    document.AddMember("d", valDir, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "1";
    req.append(buffer.GetString());
    Singleton<Net>::GetInstance()->Send(req);
}

void ServiceGame::InitGame(int id, int port) {
    this->frame = -1;
    this->id = id;
    this->isJoin = false;
    this->isOut = false;
    this->port = port;
    Singleton<Net>::GetInstance()->InitSocket(this->port);
}


void ServiceGame::GetFrame(function<void(vector<frameState>)> callBack)
{
    while (true)
    {
        string res(Singleton<Net>::GetInstance()->GetState());
        log("%s\n", res.c_str());
        if (res == "join") {
            this->isJoin = true;
            continue;
        }
        if (res == "out") {
            this->isOut = true;
            continue;
        }
        rapidjson::Document d;
        d.Parse<0>(res.c_str());
        if (!d["d"].IsNull() && !d["d"].IsArray()) continue;
        int maxFrame = frame;
        vector<frameState> data;
        for (auto& f : d["d"].GetArray())
        {
            auto frameD = f.GetObjectW();
            int i = frameD["f"].GetInt();
            if (i > maxFrame) {
                frameState currentFrame;
                maxFrame = i;
                for (auto& com : frameD["c"].GetArray())
                {
                    frameCommand currentCommand;
                    currentCommand.userId = com["i"].GetInt();
                    currentCommand.input = com["c"].GetInt();
                    currentCommand.x = com["x"].GetFloat();
                    currentCommand.y = com["y"].GetFloat();
                    currentCommand.dir = com["d"].GetInt();
                    currentFrame.commands.push_back(currentCommand);
                }
                data.push_back(currentFrame);
            }
        }
        // 发送回执
        if (maxFrame > frame)
        {
            frame = maxFrame;
            rapidjson::Document document;
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            document.AddMember("i", id, allocator);
            document.AddMember("f", frame, allocator);

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            string req = "2";
            req.append(buffer.GetString());
            Singleton<Net>::GetInstance()->Send(req);
        }
        callBack(data);
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
