#ifndef __SERVICE_GAME__
#define __SERVICE_GAME__

#include <functional>

using namespace std;


typedef struct {
    int userId;
    int input;
    float x;
    float y;
    int dir;
} frameCommand;

typedef struct {
    int FrameId;
    vector<frameCommand> commands;
} frameState;

class ServiceGame
{
public:
    void InitGame(int id, int port);
    void JoinRoom();
    void SendInput(int command, float x, float y, int dir);
    void GetFrame(function<void(vector<frameState>)> callBack);
    void OutRoom();

    bool GetJoinState();
    bool GetOutState();
    float fireX;
    float fireY;
private:
    int frame;
    int id;
    int port;
    bool isJoin;
    bool isOut;
};

#endif // __SERVICE_GAME__
