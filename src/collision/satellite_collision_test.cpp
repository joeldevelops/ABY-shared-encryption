

#include <getopt.h>
//ABY Party class
#include "../abycore/aby/abyparty.h"

#include "common/collision.h"

int main(int argc, char** argv) {

  e_role role; // 0 = CLIENT, 1 = SERVER
  uint32_t bitlen = 32, nvals = 31, secparam = 128, nthreads = 1;
  uint16_t port = 7766;
  std::string address = "";

  // Read command-line options
  while((c = getopt(argc, argv, "r:b:s:a:p:t")) != -1) {
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
      case 't':
        test_op = atoi(optarg);
        break;
      default:
        std::cout << "Invalid option" << std::endl;
        exit(0);
    }
  }

};