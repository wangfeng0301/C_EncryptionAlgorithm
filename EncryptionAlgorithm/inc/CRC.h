#ifndef __CRC_H__
#define __CRC_H__

#include "type.h"

u16 crc16(u8 *addr, int num,u16 crc) ;
u16 crc16_IBM(u8 *addr, int num);
u16 crc16_CCITT_FALSE(u8 *addr, int num) ;
u16 crc16_MAXIM(u8 *addr, int num) ;

void GenerateCrc16Table(u8 *crcHighTable,u8 *crcLowTable);
u16 Crc16withTable(u8 *addr, int len,u8 *crcHighTable,u8 *crcLowTable);

void GenerateCrc8Table(u8 *crc8Table);
#endif