#include "GameService.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "stdio.h"
#include "cocos2d.h"
using namespace rapidjson;

void GameService::JoinRoom(int port,int id, std::function<void(string)> callBack) {
    frame = 0;
    this->id = id;

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);
    
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "0";
    req.append(buffer.GetString());
    Singleton<Net>::getInstance()->InitSocket(30082);
    Singleton<Net>::getInstance()->Send(req);
    callBack("Join in Room success");
    
}

void GameService::SendInput(int input) {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("id", id, allocator);
    document.AddMember("input", input, allocator);

    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    string req = "1";
    req.append(buffer.GetString());
    Singleton<Net>::getInstance()->Send(req);
}


void GameService::GetFrame(std::function<void(string)> callBack) {

    while (true) {
        DWORD t1, t2;
        t1 = timeGetTime();
        string res = Singleton<Net>::getInstance()->GetState();
        t2 = timeGetTime();
        stringstream ss;
        ss << "Delay: " << (t2 - t1)*1.0 << "ms\n";
        CCLOG("get: %s\n", res.c_str());
        rapidjson::Document d;
        d.Parse<0>(res.c_str());
        if (!d["data"].IsArray()) continue;
        int maxFrame = 0;
        for (auto& frameState : d["data"].GetArray()) {
            int i = frameState.GetObjectW()["frameID"].GetInt();
            if (i > maxFrame) {
                maxFrame = i;
                for (auto& str : frameState.GetObjectW()["commends"].GetArray()) {
                    ss << "id: " << str["id"].GetInt() << '\n';
                    ss << "input: " << str["input"].GetInt() << '\n';
                }
            }
        }
        if (maxFrame > frame) {
            frame = maxFrame;
            rapidjson::Document document;
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            document.AddMember("id", id, allocator);
            document.AddMember("frame", frame, allocator);
            CCLOG("send: %d\n", frame);
            ss << frame << endl;

            StringBuffer buffer;
            rapidjson::Writer<StringBuffer> writer(buffer);
            document.Accept(writer);
            string req = "2";
            req.append(buffer.GetString());
            Singleton<Net>::getInstance()->Send(req);
        }

        callBack(ss.str());
    }


}


void GameService::OutRoom() {
    Singleton<Net>::getInstance()->Send("3");
}
