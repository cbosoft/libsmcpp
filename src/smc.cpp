#include <cstring>

#include <IOKit/IOKitLib.h>

#include "smc.hpp"
#include "exception.hpp"
#include "formatter.hpp"
#include "util.hpp"


SMC::SMC()
{
	this->open();
}


SMC::~SMC()
{
	this->close();
}


void SMC::call(SMCParamStruct *input_struct, SMCParamStruct *output_struct)
{

	size_t s = sizeof(SMCParamStruct);
	kern_return_t result = IOConnectCallStructMethod(this->conn,
		kSMCHandleYPCEvent,
		input_struct, s,
		output_struct, &s);

	if (result != kIOReturnSuccess or output_struct->result != kSMCSuccess) {
		throw SMCError(Formatter() << "Error encountered making call to SMC (" << err_get_code(result) << ")");
	}

}


SMCData SMC::read(const char *key)
{
	return this->read( (char *)key);
}

SMCData SMC::read(char *key)
{

	SMCParamStruct in_struct, out_struct;
	memset(&in_struct, 0, sizeof(SMCParamStruct));
	memset(&out_struct, 0, sizeof(SMCParamStruct));

	// First call: get key info
	in_struct.key = TO_UINT(key);
	in_struct.data8 = kSMCGetKeyInfo;

	this->call(&in_struct, &out_struct);

	uint32_t type = out_struct.keyInfo.dataType;

	// Second call: get the data
	in_struct.keyInfo.dataSize = out_struct.keyInfo.dataSize;
	in_struct.data8 = kSMCReadKey;

	this->call(&in_struct, &out_struct);

	return SMCData(out_struct.bytes, type);
}


void SMC::write(char *key, SMCData in)
{

	SMCParamStruct in_struct, out_struct;
	memset(&in_struct, 0, sizeof(SMCParamStruct));
	memset(&out_struct, 0, sizeof(SMCParamStruct));

	// First call: get key info
	in_struct.key = to_uint32_t(key);
	in_struct.data8 = kSMCGetKeyInfo;

	this->call(&in_struct, &out_struct);

	in_struct.data8 = kSMCWriteKey;
	in_struct.keyInfo.dataSize = out_struct.keyInfo.dataSize;

	in.get_data(out_struct.keyInfo.dataType, in_struct.bytes);

	this->call(&in_struct, &out_struct);

}


void SMC::open()
{
	io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault,
		IOServiceMatching(IOSERVICE_SMC));

	if (!service) {
		throw SMCError(Formatter() << "Error opening SMC: " << IOSERVICE_SMC);
	}

	IOServiceOpen(service, mach_task_self(), 0, &this->conn);
	IOObjectRelease(service);

	std::cerr << "SMC open." << std::endl;
}

void SMC::close()
{
	auto result = IOServiceClose(this->conn);
	if (result) {
		throw SMCError(Formatter() << "Error closing SMC connection! (" << err_get_code(result) << ")");
	}

	std::cerr << "SMC closed." << std::endl;
}









