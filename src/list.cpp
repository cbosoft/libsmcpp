#include <list>
#include <sstream>

#include "util.hpp"
#include "smc.hpp"


std::string attr_to_str(uint8_t attr)
{
  std::stringstream ss;
  // attr names with help from https://github.com/acidanthera/VirtualSMC/blob/master/Docs/SMCKeys.txt
  char names[8] = {
    'r', // user readable
    'w', // user writable
    'u', // unknown
    'f', // function
    'c', // constant value
    'a', // atomic
    'R', // private read
    'W'  // private write
  };
  for (int shift = 7, i=0; shift >= 0; shift--, i++) {
    bool set = (attr >> shift) & 1;
    ss << (set?names[i]:'-');
  }
  return ss.str();
}

void list_all_keys()
{
	std::list<char> valid_chars = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '_'
	};

	SMC s;
  SMCKeyInfoData info;
	char perm[5] = {0};
	for (auto a : valid_chars) {
		perm[0] = a;
		for (auto b : valid_chars) {
			perm[1] = b;
			for (auto c : valid_chars) {
				perm[2] = c;
				for (auto d : valid_chars) {
					perm[3] = d;

					bool res = s.check_key(perm, &info);

					if (res) {
						std::cout
              << "\r"
              << perm
              << " " << type_to_str(info.dataType)
              << " " << attr_to_str(info.dataAttributes)
              << std::endl;
					}
          else {
						std::cout << "\r" << perm << "...";
          }

				}
			}
		}
	}

}
