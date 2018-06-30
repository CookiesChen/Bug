#ifndef __NET_H__
#define __NET_H__

#include <string>
#include <WinSock2.h>
#include <stdio.h>
#include <windows.h>
#define BUF_SIZE 4096

using namespace std;

class Net final
{
public:
    Net();
    ~Net();

    string Get(string url, string query = string());
    string Post(string url, string post = string());
    void InitSocket(int port);
    void CloseSocket();
    void Send(string data);
    string GetState();

private:
    static size_t writeString(void* buffer, size_t size, size_t nmemb, void* lpVoid);
    SOCKET sock;
    sockaddr_in servAddr; // 服务器地址
};

#endif
