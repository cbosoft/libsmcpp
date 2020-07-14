#include <iostream>

#include "smc.hpp"
#include "list.hpp"


void usage()
{
  std::cerr
    << "  smctool\n"
    << "\n"
    << "  Usage:\n"
    << "    smctool <command> [<args...>]\n"
    << "\n"
    << "  Commands:\n"
    << "    list        lists CMS keys and some metadata\n"
    << "    read <key>  read key value\n"
    ;
}


int main(int argc, const char **argv)
{

	argc--; argv++;

  if (argc < 1) {
    usage();
    return 1;
  }

  const char *command = argv[0];

  if (strcmp(command, "list") == 0) {
    list_all_keys();
  }
  else if (strcmp(command, "read") == 0) {
    if (argc < 2) {
      usage();
      return 1;
    }
    const char *key = argv[1];

    try {
      double v = SMC().read(key);
      std::cout << v << std::endl;
    }
    catch (const SMCError &e) {
      std::cerr << "Error encountered while reading SMC key: " << e.what() << std::endl;
    }

  }
  else {
    usage();
    std::cerr << "  Unknown command " << command << std::endl;
    return 1;
  }
}
