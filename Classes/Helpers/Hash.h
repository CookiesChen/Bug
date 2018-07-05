#ifndef __HASH_H__
#define __HASH_H__

#include <string>

using namespace std;

class Hash
{
public:
    static string Sha512(string value);
};

#endif // __HASH_H__
