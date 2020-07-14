#include <iostream>
#include <list>
#include "smc.hpp"

void list_all_keys()
{
	std::list<char> valid_chars = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '
	};

	SMC s;
	char perm[5] = {0};
	for (auto a : valid_chars) {
		(void) a;
		perm[0] = 'T';
		for (auto b : valid_chars) {
			(void) b;
			perm[1] = 'C';
			for (auto c : valid_chars) {
				perm[2] = c;
				for (auto d : valid_chars) {
					perm[3] = d;
					bool res = s.check_key(perm);

					if (res) {
						std::cout << perm << std::endl;
					}
				}
			}
		}
	}

}

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