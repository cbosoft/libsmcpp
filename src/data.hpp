#pragma once

#include <string>

#include <IOKit/IOKitLib.h>

#include "smc_kext.hpp"

class SMCData {
private:
	uint8_t data[32];
	uint32_t dataType;
	uint32_t dataSize;
	kSMC_t kSMC;

	int int_from_fpe2() const;
	double flt_from_flt() const;
	double flt_from_sp78() const;

public:
	SMCData();
	SMCData(int i);
	SMCData(double f);
	std::string type_string() const;

	void clear();

	const uint8_t *get_data() const;
	uint32_t get_size() const;
	uint32_t get_type() const;

	// 'low' level setting of data and type
	void set_data(uint8_t data[32]);
	void set_data_type(uint32_t type);

	// helper funcs for setting data and type
	void set_fpe2(int number);
	void set_flt(double number);

	// helper funcs for getting data
	int get_int_value() const;
	double get_float_value() const;

	// operators

	operator int() const
	{
		return this->get_int_value();
	}

	operator double() const
	{
		return this->get_float_value();
	}

};