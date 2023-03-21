#include <iostream>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>

using namespace std;

class ArithmeticMAC {
public:
    ArithmeticMAC(const string& key) : key_(key) {}

    string ComputeMAC(const string& message) {
        // Compute the MAC using HMAC-SHA256
        unsigned char mac[SHA256_DIGEST_LENGTH];
        HMAC_CTX *ctx = HMAC_CTX_new();
        HMAC_Init_ex(ctx, key_.c_str(), key_.length(), EVP_sha256(), NULL);
        HMAC_Update(ctx, (unsigned char*)message.c_str(), message.length());
        HMAC_Final(ctx, mac, NULL);
        HMAC_CTX_free(ctx);

        // Convert the MAC to a hex string
        string mac_str;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            mac_str += to_string(mac[i]);
        }
        return mac_str;
    }

    bool VerifyMAC(const string& message, const string& mac_str) {
        // Convert the received MAC string to binary
        unsigned char mac[SHA256_DIGEST_LENGTH];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            mac[i] = stoi(mac_str.substr(i * 2, 2), nullptr, 16);
        }

        // Compute the MAC using HMAC-SHA256
        HMAC_CTX *ctx = HMAC_CTX_new();
        HMAC_Init_ex(ctx, key_.c_str(), key_.length(), EVP_sha256(), NULL);
        HMAC_Update(ctx, (unsigned char*)message.c_str(), message.length());
        unsigned char computed_mac[SHA256_DIGEST_LENGTH];
        HMAC_Final(ctx, computed_mac, NULL);
        HMAC_CTX_free(ctx);

        // Compare the computed MAC to the received MAC
        return memcmp(mac, computed_mac, SHA256_DIGEST_LENGTH) == 0;
    }

private:
    string key_;
};