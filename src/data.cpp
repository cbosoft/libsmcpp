#include <iostream>
#include <cstring>

#include "data.hpp"
#include "util.hpp"
#include "exception.hpp"

SMCData::SMCData()
{
	this->clear();
}

SMCData::SMCData(int i)
{
	this->clear();
	this->set_fpe2(i);
}

SMCData::SMCData(double f)
{
	this->clear();
	this->set_flt(f);
}

SMCData::SMCData(uint8_t *data, uint32_t data_type)
{
	uint8_t s = (data_type == to_uint32_t(DATA_TYPE_FLT_)?4:2);
	memset(this->data, 0, 32);
	memcpy(this->data, data, s);
	this->dataSize = s;
	this->dataType = data_type;
}

void SMCData::clear()
{
	// reset contents to zero
	this->dataSize = 0;
	this->dataType = 0;
	memset(this->data, 0, 32);
}

const uint8_t *SMCData::get_data() const
{
	return &(this->data[0]);
}

uint32_t SMCData::get_size() const
{
	return this->dataSize;
}

uint32_t SMCData::get_type() const
{
	return this->dataType;
}

void SMCData::set_fpe2(int i)
{
	this->data[0] = i >> 6;
    this->data[1] = (i << 2) ^ (this->data[0] << 8);
    this->dataSize = 2;
    this->dataType = to_uint32_t(DATA_TYPE_FPE2);
}

void SMCData::set_flt(double d)
{
	float f = float(d);
	uint8_t *c_data = (uint8_t *)&f;

	for (int i = 0; i < 4; i++) {
		// need to flip?
		this->data[i] = c_data[i];
	}
	this->dataSize = 4;
	this->dataType = to_uint32_t(DATA_TYPE_FLT_);
}

int SMCData::int_from_fpe2() const
{
	int ans = 0;

    // FPE2 assumedly means fixed point, with 2 exponent bits
    // http://stackoverflow.com/questions/22160746/fpe2-and-sp78-data-types
    ans += data[0] << 6;
    ans += data[1] >> 2;// this is changed over upstream; is upstream broken? Or am I making a mistake in changing this?
    return ans;
}

double SMCData::flt_from_sp78() const
{
	double rv = this->data[0];
	return rv;
}

double SMCData::flt_from_flt() const
{
	// fun bit of c-ish goodness
	// pointer to the first location in the data array, cast to float*
	// and dereferenced to get the float value
	float f = *((float*)&(this->data[0]));
	return double(f);
}

int SMCData::get_int_value() const
{
	if (this->dataType == to_uint32_t(DATA_TYPE_FPE2))
			return this->int_from_fpe2();

	if (this->dataType == to_uint32_t(DATA_TYPE_SP78))
			return int(this->flt_from_sp78());

	if (this->dataType == to_uint32_t(DATA_TYPE_FLT_))
			return int(this->flt_from_flt());

	throw SMCError(Formatter() << "Unrecognised type: " << this->type_string());
}

double SMCData::get_float_value() const
{
	if (this->dataType == to_uint32_t(DATA_TYPE_FPE2))
			return double(this->int_from_fpe2());

	if (this->dataType == to_uint32_t(DATA_TYPE_SP78))
			return this->flt_from_sp78();

	if (this->dataType == to_uint32_t(DATA_TYPE_FLT_))
			return this->flt_from_flt();

	throw SMCError(Formatter() << "Unrecognised type: " << this->type_string());
}

std::string SMCData::type_string() const
{
	int shift = 24;
	uint32_t val = this->dataType;


	std::string rv;
    for (int i = 0; i < DATA_TYPE_SIZE; i++) {
        // To get each char, we shift it into the lower 8 bits, and then & by
        // 255 to insolate it
        char c = (val >> shift) & 0xff;
        std::cerr << int(c) << std::endl;
        rv += c;
        shift -= 8;
    }

    return rv;
}







