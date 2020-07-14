#pragma once

#include <string>

#include <IOKit/IOKitLib.h>

#include "smc_kext.hpp"

class SMCData {

private:
	double value;

	static double from_fixd(int integer, int fraction, int fraclen, bool neg=false);
	static double from_fpe2(uint8_t *data);
	static double from_sp78(uint8_t *data);
	static double from_flt_(uint8_t *data);
	void to_fpe2(uint8_t *data) const;
	void to_sp78(uint8_t *data) const;
	void to_flt_(uint8_t *data) const;

	void set_value(double d);
	void set_value(uint8_t *data, uint32_t type);

public:
	SMCData();
	SMCData(double f);
	SMCData(uint8_t *data, uint32_t data_type);

	void get_data(uint32_t type, uint8_t *data) const;

	operator double() const
	{
		return this->value;
	}

};