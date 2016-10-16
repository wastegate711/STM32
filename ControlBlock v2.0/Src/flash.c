#include "flash.h"

uint32_t ReadAdresFlash(uint32_t adres)
{
    return *(uint32_t*) adres;
}
