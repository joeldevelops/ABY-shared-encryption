#include <iostream>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>

#include "macverify.h"

using namespace std;

ArithmeticMAC::ArithmeticMAC(const string key) {
    // Initialize the SHA-256 context with the key
    SHA256_Init(&sha256_);
    SHA256_Update(&sha256_, key.c_str(), key.size());
}

// Compute the MAC for a given message
uint64_t ArithmeticMAC::ComputeMAC(string message) {
    // Compute the SHA-256 hash of the message
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    sha256 = sha256_;
    SHA256_Update(&sha256, message.c_str(), message.size());
    SHA256_Final(hash, &sha256);

    // Convert the hash to a 64-bit integer
    uint64_t mac = 0;
    for (int i = 0; i < 8; i++) {
        mac = (mac << 8) | hash[i];
    }

    return mac;
}

// ArithmeticMAC::ArithmeticMAC(const string key) {
//     key_ = key;
//     SHA256_CTX sha256_;
//     // Initialize the SHA-256 context with the key
//     SHA256_Init(&sha256_);
//     SHA256_Update(&sha256_, key.c_str(), key.size());
// }

// uint64_t ArithmeticMAC::ComputeMAC(const string& message) {
//     // Compute the MAC using SHA256
//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256_CTX sha256;
//     sha256 = sha256_;
//     SHA256_Update(&sha256, message.c_str(), message.size());
//     SHA256_Final(hash, &sha256);

//     // Convert the MAC to a uint64_t
//     uint64_t mac = 0;
//     for (int i = 0; i < 8; i++) {
//         mac = (mac << 8) | hash[i];
//     }
//     return mac;
// }

// uint64_t ArithmeticMAC::ComputeMAC(const string& message) {
//     // Compute the MAC using HMAC-SHA256
//     unsigned char mac[SHA256_DIGEST_LENGTH];
//     HMAC_CTX *ctx = HMAC_CTX_new();
//     HMAC_Init_ex(ctx, key_.c_str(), key_.length(), EVP_sha256(), NULL);
//     HMAC_Update(ctx, (unsigned char*)message.c_str(), message.length());
//     HMAC_Final(ctx, mac, NULL);
//     HMAC_CTX_free(ctx);

//     cout << "MAC: " << mac << endl;

//     return (uint64_t) mac;

//     // Convert the MAC to a hex string
//     // string mac_str;
//     // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//     //     mac_str += to_string(mac[i]);
//     // }
//     // return mac_str;
// }

// bool ArithmeticMAC::VerifyMAC(const string& message, const string& mac_str) {
//     // Convert the received MAC string to binary
//     unsigned char mac[SHA256_DIGEST_LENGTH];
//     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//         mac[i] = stoi(mac_str.substr(i * 2, 2), nullptr, 16);
//     }

//     // Compute the MAC using HMAC-SHA256
//     HMAC_CTX *ctx = HMAC_CTX_new();
//     HMAC_Init_ex(ctx, key_.c_str(), key_.length(), EVP_sha256(), NULL);
//     HMAC_Update(ctx, (unsigned char*)message.c_str(), message.length());
//     int result = HMAC_Final(ctx, mac, NULL);
//     HMAC_CTX_free(ctx);

//     if (result == 0) {
//         cout << "HMAC_Final failed" << endl;
//         return false;
//     }

//     // Compare the computed MAC with the received MAC
//     return (memcmp(mac, mac_str.c_str(), SHA256_DIGEST_LENGTH) == 0);
// }