/**
 \file 		millionaire_prob_test.cpp
 \author	sreeram.sadasivam@cased.de
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
 \brief		Millionaire problem Test class implementation.
 */

#include <getopt.h>
//Utility libs
#include <ENCRYPTO_utils/crypto/crypto.h>
//ABY Party class
#include "../../abycore/aby/abyparty.h"
#include "../../abycore/MAC_verify/macverify.h"

#include "common/millionaire_prob.h"

int main(int argc, char** argv) {
	int c;
	e_role role;
	uint32_t bitlen = 32, nvals = 31, secparam = 128, nthreads = 1;
	uint16_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
	std::string mac_key = "mac_key";
	bool malicious = false;

  // Read command-line options
  while((c = getopt(argc, argv, "r:b:s:a:p:m:k")) != -1) {
    switch(c) {
      case 'r':
        role = (e_role) atoi(optarg);
        break;
      case 'b':
        bitlen = atoi(optarg);
        break;
      case 's':
        secparam = atoi(optarg);
        break;
      case 'a':
        address = optarg;
        break;
      case 'p':
        port = atoi(optarg);
        break;
      case 'm':
        malicious = atoi(optarg) == 1 ? true : false;
        break;
      case 'k':
        mac_key = optarg;
        break;
      default:
        std::cout << "Invalid option" << std::endl;
        exit(0);
    }
  }

	seclvl seclvl = get_sec_lvl(secparam);

	//evaluate the millionaires circuit using Yao
	test_millionaire_prob_circuit(role, address, port, seclvl, 32,
			nthreads, mt_alg, S_YAO, mac_key, malicious);
	//evaluate the millionaires circuit using GMW
	//test_millionaire_prob_circuit(role, address, port, seclvl, 32,
	//		nthreads, mt_alg, S_BOOL, mac_key, malicious);

	return 0;
}

