///Header Gaurd

#ifndef SPI_HEADER_H_
#define SPI_HEADER_H_
#include "STD_TYPES.h"

void SPI_voidMaster_Init(void);
void SPI_voidSlave_Init(void);
void SPI_u8Transceive(u8 data);
u8 SPI_u8Receive(void);



#endif //SPI_HEADER_H_