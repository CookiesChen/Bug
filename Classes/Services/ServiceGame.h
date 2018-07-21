#ifndef __SERVICE_GAME__
#define __SERVICE_GAME__

#include <functional>

using namespace std;

class ServiceGame
{
public:
    void InitGame(int id, int port);
    void JoinRoom();
    void SendInput(int input, float x, float y);
    void GetFrame(function<void(string)> callBack);
    void OutRoom();

    bool GetJoinState();
    bool GetOutState();
private:
    int frame;
    int id;
    int port;
    bool isJoin;
    bool isOut;
};

#endif // __SERVICE_GAME__
