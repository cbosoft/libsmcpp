#include <iostream>

#include "smc.hpp"
#include "list.hpp"


void p(SMCData d)
{
	std::cerr << double(d) << std::endl;
}

int main(int argc, const char **argv)
{

	argc--; argv++;

	if (argc && (strcmp(argv[0], "list") == 0)) {
		list_all_keys();
		return 0;
	}

	SMC s;
	double res1 = s.read("F0Ac");
	double res2 = s.read("F1Ac");
	double res3 = s.read("TC0P");
	double res4 = (argc ? double(s.read(argv[0])) : 0.5);

	std::cerr << res1 << " " << res2 << " " << res3 << " " << res4 << std::endl;
}