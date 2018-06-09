#include "cocos2d.h"

#include "Net.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "curl/include/win32/curl/curl.h"
#endif

Net::Net()
{
    curl_global_init(CURL_GLOBAL_ALL);
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
    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Net::writeString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &res);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

string Net::Post(string url, string query)
{
    string res;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Net::writeString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &res);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
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
