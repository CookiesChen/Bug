#ifndef __SERVICE_API__
#define __SERVICE_API__

#include <string>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace std;

class ServiceAPI final
{
public:
    rapidjson::Document Login(string username, string password);

    rapidjson::Document CreateRoom(string title, string password, string map, string mode, int maxPlayer);

    rapidjson::Document Logout();

private:
    static const string apiUrl;
};

#endif // __SERVICE_API__
