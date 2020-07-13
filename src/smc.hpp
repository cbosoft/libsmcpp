#pragma once

#include "smc_kext.hpp"
#include "data.hpp"

class SMC {
private:
	SMCParamStruct last_output;
	SMCData in, out;

	io_connect_t conn;
	SMCParamStruct &call(const SMCParamStruct &input);
	SMCData &read(char *key);
	void write(char *key, SMCData &in);

public:
	SMC();
	~SMC();
	
};