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

SMCData::SMCData(float f)
{
	this->clear();
	this->set_flt(f);
}

void SMCData::clear()
{
	// reset contents to zero
	this->dataSize = 0;
	this->dataType = 0;
	memset(this->data, 0, 32);
}

void SMCData::set_fpe2(int i)
{
	this->data[0] = i >> 6;
    this->data[1] = (i << 2) ^ (this->data[0] << 8);
    this->dataSize = 2;
    this->dataType = to_uint32_t(DATA_TYPE_FPE2);
}

void SMCData::set_flt(float f)
{
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

float SMCData::flt_from_flt() const
{
	// fun bit of c-ish goodness
	// pointer to the first location in the data array, cast to float*
	// and dereferenced to get the float value
	float f = *((float*)&(this->data[0]));
	return f;
}

int SMCData::get_int_value() const
{
	if (this->dataType == to_uint32_t(DATA_TYPE_FPE2)) {
		return this->int_from_fpe2();
	}
	else {
		return int(this->flt_from_flt());
	}
}

float SMCData::get_float_value() const
{
	if (this->dataType == to_uint32_t(DATA_TYPE_FLT_)) {
		return this->flt_from_flt();
	}
	else {
		return float(this->int_from_fpe2());
	}
}