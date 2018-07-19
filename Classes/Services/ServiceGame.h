#ifndef __SERVICE_GAME__
#define __SERVICE_GAME__

#include <functional>

using namespace std;

class ServiceGame
{
public:
    void JoinRoom(int port, int id, function<void(string)> callBack);
    void SendInput(int input);
    void GetFrame(function<void(string)> callBack);
    void OutRoom();

private:
    int frame;
    int id;
};

#endif // __SERVICE_GAME__
