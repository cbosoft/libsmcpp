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
	double rv = double(intger);
	double den = 2.0;
	int mask = 1 << 7;

	// TODO: is this right?
	for (int i = 0; i < fraclen; i++) {
		rv += (frac_part & mask) ? (1.0/den) : (0.0);
		mark /= 2;
		den *= 2.0;
	}

	rv *= neg ? -1.0 : 1.0;
	return rv;

}

double SMCData::from_fpe2(uint8_t *data)
{
	int integer += data[0] << 6;
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











void SMCData::get_data(uint32_t type, uint8_t **data, uint32_t &size) const
{
	// TODO: convert from data into requested type.
	// data param must be allocd to > 4 bytes before passed into this method.
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

void SMCData::set_sp78(double d)
{
	uint8_t *c_data = (uint8_t *)&d;
	memcpy(this->data, c_data, 8);
	this->dataSize = 8;
	this->dataType = TO_UINT(DATA_TYPE_SP78);
}





double SMCData::from_fpe2(uint8_t *data) const
{
	int ans = 0;

    // FPE2 assumedly means fixed point, with 2 exponent bits
    // http://stackoverflow.com/questions/22160746/fpe2-and-sp78-data-types
    ans += data[0] << 6;
    ans += data[1] >> 2;// this is changed over upstream; is upstream broken? Or am I making a mistake in changing this?

    int frac = data[1] & 3;


    return ans;
}

double SMCData::int_from_sp78(uint8_t *data)
{
	double rv = data[0]; // no!
	int ans = 0;

	int sign = (data[0] >> 7) & 1;
	ans += (data[0] & ((1 << 7) - 1)) << 6;
	ans += data[]
	return rv;
}

double SMCData::flt_from_flt(uint8_t *data)
{
	// fun bit of c-ish goodness
	// pointer to the first location in the data array, cast to float*
	// and dereferenced to get the float value
	float f = *((float*)&(data[0]));
	return double(f);
}

int SMCData::get_int_value() const
{
	switch (this->dataType) {
		case TO_UINT(DATA_TYPE_FPE2):
			return this->int_from_fpe2();

		case TO_UINT(DATA_TYPE_SP78):
			return int(this->flt_from_sp78());

		case TO_UINT(DATA_TYPE_FLT_):
			return int(this->flt_from_flt());
	}

	throw SMCError(Formatter() << "Unrecognised type: " << this->type_string());
}

double SMCData::get_float_value() const
{
	switch (this->dataType) {
		case TO_UINT(DATA_TYPE_FPE2):
			return double(this->int_from_fpe2());

		case TO_UINT(DATA_TYPE_SP78):
			return this->flt_from_sp78();

		case TO_UINT(DATA_TYPE_FLT_):
			return this->flt_from_flt();
	}

	throw SMCError(Formatter() << "Unrecognised type: " << this->type_string());
}

SMCData SMCData::cast_as_type(uint32_t type)
{
	int i = int(*this);
	double f = double(*this);

	switch (type) {
		case TO_UINT(DATA_TYPE_FPE2):
			return SMCData(i);

		case TO_UINT(DATA_TYPE_FLT_):
		case TO_UINT(DATA_TYPE_SP78):
			return SMCData(f, type);

	}

	throw SMCError(Formatter() << "Unrecognised type: " << this->type_string());
}







