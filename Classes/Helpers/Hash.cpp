#include "cocos2d.h"

#include "Hash.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "openssl/include/win32/openssl/crypto.h"
#include "openssl/include/win32/openssl/sha.h"
#endif

#pragma comment(lib, "libcrypto.lib") 
#pragma comment(lib, "libssl.lib") 

string Hash::Sha512(string value)
{
    SHA512_CTX c;
    unsigned char md[SHA512_DIGEST_LENGTH];
    SHA512((const unsigned char*) value.c_str(), value.size(), md);
    SHA512_Init(&c);
    SHA512_Update(&c, value.c_str(), value.size());
    SHA512_Final(md, &c);
    OPENSSL_cleanse(&c, sizeof(c));
    string hash;
    for (size_t i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        char lhs = (md[i] / 16 >= 10 ? md[i] / 16 + 'a' - 10 : md[i] / 16 + '0');
        char rhs = (md[i] % 16 >= 10 ? md[i] % 16 + 'a' - 10 : md[i] % 16 + '0');
        hash = hash + lhs + rhs;
    }
    return hash;
}
