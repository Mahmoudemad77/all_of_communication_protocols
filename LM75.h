#ifndef LM75_H_
#define LM75_H_

#include <stdint.h>

#define LM75_ADDRESS    0x48

uint8_t LM75_ReadTemperature(void);

#endif