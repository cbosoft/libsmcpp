#include <iostream>
#include <cstring>

#include "data.hpp"
#include "util.hpp"
#include "exception.hpp"

SMCData::SMCData()
{
	this->set_value(0);
}

SMCData::SMCData(double f)
{
	this->set_value(f);
}

SMCData::SMCData(uint8_t *data, uint32_t type)
{
	this->set_value(data, type);
}





void SMCData::set_value(double d)
{
	this->value = d;
}

void SMCData::set_value(uint8_t *data, uint32_t type)
{
	switch (type)
	{
		case TO_UINT(DATA_TYPE_FPE2):
			this->set_value(SMCData::from_fpe2(data));
			break;
		case TO_UINT(DATA_TYPE_SP78):
			this->set_value(SMCData::from_sp78(data));
			break;
		case TO_UINT(DATA_TYPE_FLT_):
			this->set_value(SMCData::from_flt_(data));
			break;
	}

	throw SMCError("Unrecognised type encountered.");
}

double SMCData::from_fixd(int integer, int fraction, int fraclen, bool neg)
{
	double rv = double(integer);
	double den = 2.0;
	int mask = 1 << 7;

	// TODO: is this right?
	for (int i = 0; i < fraclen; i++) {
		rv += (fraction & mask) ? (1.0/den) : (0.0);
		mask /= 2;
		den *= 2.0;
	}

	rv *= neg ? -1.0 : 1.0;
	return rv;

}

double SMCData::from_fpe2(uint8_t *data)
{
	int integer = data[0] << 6;
	integer += data[1] >> 2;

	int fraction = data[1] & 3;

	return SMCData::from_fixd(integer, fraction, 2);
}

double SMCData::from_sp78(uint8_t *data)
{
	bool sign = data[0] >> 7;
	int integer = (data[0] & ((1 << 7) - 1)) << 6;
	int fraction = data[1];
	return SMCData::from_fixd(integer, fraction, 8, sign);
}

double SMCData::from_flt_(uint8_t *data)
{
	float f = *(float *)data;
	return double(f);
}











void SMCData::get_data(uint32_t type, uint8_t *data, uint32_t &size) const
{
	// TODO: convert from data into requested type.

	switch (type)
	{
		case TO_UINT(DATA_TYPE_FPE2):
			this->to_fpe2(data, size);
			break;

		case TO_UINT(DATA_TYPE_SP78):
			this->to_sp78(data, size);
			break;

		case TO_UINT(DATA_TYPE_FLT_):
			this->to_flt_(data, size);
			break;
	}
}

void SMCData::to_fpe2(uint8_t *data, uint32_t &size) const
{
	size = 2;
	int i = this->value;
	data[0] = i >> 6;
    data[1] = (i << 2) ^ (data[0] << 8);
}

void SMCData::to_flt_(uint8_t *data, uint32_t &size) const
{
	size = 4;
	float f = float(this->value);
	uint8_t *c_data = (uint8_t *)&f;
	memcpy(data, c_data, size);
}

void SMCData::to_sp78(uint8_t *data, uint32_t &size) const
{
	// TODO
	(void) data;
	(void) size;
}




