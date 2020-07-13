#include <cstring>
#include "util.hpp"
#include "smc_kext.hpp"


uint32_t to_uint32_t(char *key)
{
    return to_uint32_t( (const char *) key);
}


uint32_t to_uint32_t(const char *key)
{
    uint32_t ans   = 0;
    uint32_t shift = 24;

    // SMC key is expected to be 4 bytes - thus 4 chars
    if (strlen(key) != SMC_KEY_SIZE) {
        return 0;
    }

    for (int i = 0; i < SMC_KEY_SIZE; i++) {
        ans += key[i] << shift;
        shift -= 8;
    }

    return ans;
}