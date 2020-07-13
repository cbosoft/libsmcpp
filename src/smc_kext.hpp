#pragma once

#include <IOKit/IOKitLib.h>

#include <cstdint>

// Apple SMC kernel extension definitions

/**
Defined by AppleSMC.kext. See SMCParamStruct.

These are SMC specific return codes
*/
typedef enum {
    kSMCSuccess     = 0,
    kSMCError       = 1,
    kSMCKeyNotFound = 0x84
} kSMC_t;


/**
Defined by AppleSMC.kext. See SMCParamStruct.

Function selectors. Used to tell the SMC which function inside it to call.
*/
typedef enum {
    kSMCUserClientOpen  = 0,
    kSMCUserClientClose = 1,
    kSMCHandleYPCEvent  = 2,
    kSMCReadKey         = 5,
    kSMCWriteKey        = 6,
    kSMCGetKeyCount     = 7,
    kSMCGetKeyFromIndex = 8,
    kSMCGetKeyInfo      = 9
} selector_t;


/**
Defined by AppleSMC.kext. See SMCParamStruct.
*/
typedef struct {
    unsigned char  major;
    unsigned char  minor;
    unsigned char  build;
    unsigned char  reserved;
    unsigned short release;
} SMCVersion;


/**
Defined by AppleSMC.kext. See SMCParamStruct.
*/
typedef struct {
    uint16_t version;
    uint16_t length;
    uint32_t cpuPLimit;
    uint32_t gpuPLimit;
    uint32_t memPLimit;
} SMCPLimitData;


/**
Defined by AppleSMC.kext. See SMCParamStruct.

- dataSize : How many values written to SMCParamStruct.bytes
- dataType : Type of data written to SMCParamStruct.bytes. This lets us know how
             to interpret it (translate it to human readable)
*/
typedef struct {
    IOByteCount dataSize;
    uint32_t    dataType;
    uint8_t     dataAttributes;
} SMCKeyInfoData;


/**
Defined by AppleSMC.kext.

This is the predefined struct that must be passed to communicate with the
AppleSMC driver. While the driver is closed source, the definition of this
struct happened to appear in the Apple PowerManagement project at around
version 211, and soon after disappeared. It can be seen in the PrivateLib.c
file under pmconfigd.

https://www.opensource.apple.com/source/PowerManagement/PowerManagement-211/
*/
typedef struct {
    uint32_t       key;
    SMCVersion     vers;
    SMCPLimitData  pLimitData;
    SMCKeyInfoData keyInfo;
    uint8_t        result;
    uint8_t        status;
    uint8_t        data8;
    uint32_t       data32;
    uint8_t        bytes[32];
} SMCParamStruct;

/**
Name of the SMC IOService as seen in the IORegistry. You can view it either via
command line with ioreg or through the IORegistryExplorer app (found on Apple's
developer site - Hardware IO Tools for Xcode)
*/
#define IOSERVICE_SMC "AppleSMC"


/**
IOService for getting machine model name
*/
#define IOSERVICE_MODEL "IOPlatformExpertDevice"


/**
SMC data types - 4 byte multi-character constants

Sources: See TMP SMC keys in smc.h

http://stackoverflow.com/questions/22160746/fpe2-and-sp78-data-types
*/
#define DATA_TYPE_UINT8  "ui8 "
#define DATA_TYPE_UINT16 "ui16"
#define DATA_TYPE_UINT32 "ui32"
#define DATA_TYPE_FLAG   "flag"
#define DATA_TYPE_FPE2   "fpe2"
#define DATA_TYPE_SFDS   "{fds"
#define DATA_TYPE_SP78   "sp78"
#define DATA_TYPE_FLT_   "flt "

#define SMC_KEY_SIZE 	 4
#define DATA_TYPE_SIZE 	 4