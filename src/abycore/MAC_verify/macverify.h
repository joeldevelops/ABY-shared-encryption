
#ifndef __MACVERIFY_H__
#define __MACVERIFY_H__

#include <iostream>
#include <cstring>
#include <openssl/sha.h>

using namespace std;

class ArithmeticMAC {
private:
  SHA256_CTX sha256_;

public:
  ArithmeticMAC(const string key);
  uint64_t ComputeMAC(string message);
};

#endif //__MACVERIFY_H__