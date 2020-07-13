#include <iostream>
#include "formatter.hpp"
#include "data.hpp"


void pass(std::string name)
{
	std::cerr << name << " passed!" << std::endl;
}

void fail(std::string name, std::string because)
{
	std::cerr << name << " failed: " << because << std::endl;
	exit(1);
}



void data_conv_i2i_test()
{

	std::string name = "data_conv_i2i_test";
	int i = 5;

	SMCData d(i);

	int o = d;

	if (o == i) {
		pass(name);
	}
	else {
		fail(name, Formatter() << i << " != " << o);
	}

}

void data_conv_f2f_test()
{

	std::string name = "data_conv_f2f_test";
	float i = 3.14;

	SMCData d(i);

	float o = d;

	if (o == i) {
		pass(name);
	}
	else {
		fail(name, Formatter() << i << " != " << o);
	}

}



int main(void)
{
	data_conv_f2f_test();
	data_conv_i2i_test();
}