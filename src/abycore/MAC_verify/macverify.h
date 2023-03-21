
#ifndef __MACVERIFY_H__
#define __MACVERIFY_H__

#include <iostream>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>

using namespace std;

class ArithmeticMAC {
public:
  ArithmeticMAC(const string& key);
  ~ArithmeticMAC();

  string ComputeMAC(const string& message);

  bool VerifyMAC(const string& message, const string& mac_str);

private:
  string key_;
};

#endif //__MACVERIFY_H__