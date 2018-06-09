#ifndef __NET_H__
#define __NET_H__

#include <string>

using namespace std;

class Net final
{
public:
    Net();
    ~Net();

    string Get(string url, string query = string());
    string Post(string url, string post = string());

private:
    static size_t writeString(void* buffer, size_t size, size_t nmemb, void* lpVoid);
};

#endif
