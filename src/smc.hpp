#pragma once

#include "exception.hpp"
#include "smc_kext.hpp"
#include "data.hpp"

class SMC {

private:
	io_connect_t conn;
	void call(SMCParamStruct *input_struct, SMCParamStruct *output_struct);
	void open();
	void close();

public:
	SMC();
	~SMC();

	SMCData read(const char *key);
	SMCData read(char *key);
	void write(char *key, SMCData in);
	bool check_key(char *key, SMCKeyInfoData *info=nullptr);
	
};
