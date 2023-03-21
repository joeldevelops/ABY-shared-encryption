/**
 \file 		macverify.cpp
 \author	j.a.milligan@student.vu.nl
 \copyright	ABY - A Framework for Efficient Mixed-protocol Secure Two-party Computation
			Copyright (C) 2019 Engineering Cryptographic Protocols Group, TU Darmstadt
			This program is free software: you can redistribute it and/or modify
            it under the terms of the GNU Lesser General Public License as published
            by the Free Software Foundation, either version 3 of the License, or
            (at your option) any later version.
            ABY is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
            GNU Lesser General Public License for more details.
            You should have received a copy of the GNU Lesser General Public License
            along with this program. If not, see <http://www.gnu.org/licenses/>.
 \brief		ArithmeticMAC Class implementation for secure message codes.
 */
#include <iostream>
#include <cstring>
#include <openssl/sha.h>

#include "macverify.h"

using namespace std;

/**
 * Constructor for the ArithmeticMAC class.
 * @param key The encryption key to use for the MAC.
*/
ArithmeticMAC::ArithmeticMAC(const string key) {
    // Initialize the SHA-256 context with the key
    SHA256_Init(&sha256_);
    SHA256_Update(&sha256_, key.c_str(), key.size());
}

/**
 * Computes the MAC for a given message.
 * @param message The message to compute the MAC for.
*/
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