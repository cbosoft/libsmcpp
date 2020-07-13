#include <iostream>

#include "smc.hpp"

void p(SMCData d)
{
	std::cerr << double(d) << std::endl;
}

int main(void)
{
	SMC s;

	// do something with s
	int res1 = s.read("F0Ac");
	int res2 = s.read("F1Ac");

	std::cerr << res1 << " " << res2 << std::endl;
}