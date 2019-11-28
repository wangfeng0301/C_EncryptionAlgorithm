#ifndef __DES_H__
#define __DES_H__

#include "type.h"

#define DES_ENCRYPT_NUM		16			//¼ÓÃÜÂÖÊı
void DES(u8 *plaintext,u8 *key, u8 *ciphertext);

#endif