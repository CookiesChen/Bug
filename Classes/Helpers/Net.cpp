#include "cocos2d.h"
#include <chrono>
#include "Net.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "curl/include/win32/curl/curl.h"
#endif

Net::Net()
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch());
    cookiesFile = "cookies" + to_string(ms.count()) + ".co";
}

Net::~Net()
{
    curl_global_cleanup();
}

string Net::Get(string url, string query)
{
    string res;
    CURL* curl = curl_easy_init();
    string _url = url + (query.size() ? "?" : "") + query;
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiesFile.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookiesFile.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Net::writeString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &res);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

string Net::Post(string url, string query)
{
    string res;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiesFile.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookiesFile.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Net::writeString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &res);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

void Net::InitSocket(int port)
{
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套接字
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    // 服务器地址信息
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = PF_INET;
    // servAddr.sin_addr.s_addr = inet_addr("111.230.240.70");
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(port);
}

void Net::CloseSocket()
{
    closesocket(sock);
    WSACleanup();
}

void Net::Send(string data)
{
    char *buffer = new char[data.length() + 1];
    strcpy(buffer, data.c_str());
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
}

string Net::GetState()
{
    sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
    char buffer[BUF_SIZE] = { 0 };
    int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &fromAddr, &addrLen);
    if (strLen > BUF_SIZE) {
        return "";
    }
    buffer[strLen] = 0;
    return string(buffer);
}

size_t Net::writeString(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    string* str = dynamic_cast<std::string*>((std::string *) lpVoid);
    if (str == nullptr || buffer == nullptr)
    {
        return -1;
    }
    char* pData = (char*) buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}
