#pragma once
#include <Singleton.h>
#include <Net.h>
#include <functional>

class GameService {
public:
    void JoinRoom(int port, int id, std::function<void(string)> callBack);
    void SendInput(int input);
    void GetFrame( std::function<void(string)> callBack);
    void OutRoom();
private:
    int frame;
    int id;
};
