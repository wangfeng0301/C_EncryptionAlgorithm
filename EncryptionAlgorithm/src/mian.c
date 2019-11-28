#include <stdio.h>
#include "type.h"
#include "AES.h"
#include "DES.h"
#include "SM4.h"
#include "SHA1.h"
#include "SHA224.h"
#include "SHA256.h"
#include "SHA384.h"
#include "SHA512MY.h"
#include "CRC.h"

int main()
{
	/******************************************************************/
	u16 i,j;
	u8 DES_plaintext[8]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};//明文
	u8 DES_key[8]={0x13,0x34,0x57,0x79,0x9b,0xbc,0xdf,0xf1};	//秘钥
	u8 DES_ciphertext[8]={0};

	u8 SM4_plaintext[16]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};//明文
	u8 SM4_key[16]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};	//秘钥
	u8 SM4_ciphertext[16]={0};

	u8 AES_plaintext[16]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};//明文
	u8 AES_key[16]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};	//秘钥
	u8 AES_ciphertext[16];

	//u8 SHA1_plaintext[]="abcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaa";//明文
	u8 SHA1_plaintext[]="abc";
	u8 SHA1_ciphertext[20]={0};//返回摘要长度为160bit，即20字节

	//u8 SHA256_plaintext[]="abcdefghigklmnopqrstuvwxyz";//明文
	u8 SHA224_plaintext[]="abcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaa";//明文
	u8 SHA224_ciphertext[28]={0};//返回摘要长度为224bit，即28字节

	u8 SHA256_plaintext[]="abc";
	//u8 SHA256_plaintext[]="abcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaa";//明文
	u8 SHA256_ciphertext[32]={0};//返回摘要长度为256bit，即32字节

	u8 SHA384_plaintext[]="abc";
	//u8 SHA384_plaintext[]="abcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaa";//明文
	u8 SHA384_ciphertext[48]={0};//返回摘要长度为384bit，即48字节

	u8 SHA512MY_plaintext[]="abc";//明文
	//u8 SHA512MY_plaintext[]="abcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaaabcdefghigklmnopqrstuvwxyzabcdefghigklmnopqrstuvwxyzabcdefgaaaaa";//明文
	u8 SHA512MY_ciphertext[64]={0};//返回摘要长度为512bit，即64字节

	u8 crc[]={0x02,0x2f,0x04,0x02,0x2e,0x62,0x0b,0xf8};
	u16 table[256]={0};
	u8 crcHighTable[256];
	u8 crcLowTable[256];
	u8 crc8Table[256];
	/**************************** DES **************************************/
	printf("***************************** DES ********************************\r\n");
	DES(DES_plaintext,DES_key, DES_ciphertext);
	printf("plaintext:");
	for(i=0;i<8;i++)	
		printf("%2x ",DES_plaintext[i]);
	printf("\r\n");
	printf("ciphertext:");
	for(i=0;i<8;i++)	
		printf("%2x ",DES_ciphertext[i]);
	printf("\r\n");	

	/**************************** AES **************************************/
	printf("***************************** AES ********************************\r\n");
	AES(AES_plaintext, AES_key, AES_ciphertext);
	printf("plaintext is :");
	for(i=0;i<16;i++)
		printf("%2x",AES_plaintext[i]);
	printf("\r\n");
	printf("ciphertext is :");
	for(i=0;i<16;i++)
		printf("%2x",AES_ciphertext[i]);
	printf("\r\n\r\n");

	DeAES(AES_ciphertext, AES_key, AES_plaintext);
	printf("ciphertext is :");
	for(i=0;i<16;i++)
		printf("%2x",AES_ciphertext[i]);
	printf("\r\n");
	printf("plaintext is :");
	for(i=0;i<16;i++)
		printf("%2x",AES_plaintext[i]);
	printf("\r\n");

	/***************************** SM4 *************************************/
	printf("***************************** SM4 ********************************\r\n");
	SM4(SM4_plaintext,SM4_key, SM4_ciphertext);
	//for(i=0;i<1000000;i++)
	//{
	//	SM4(SM4_plaintext,SM4_key, SM4_ciphertext);
	//	for(j=0;j<16;j++)
	//		SM4_plaintext[j] = SM4_ciphertext[j];
	//}
	printf("plaintext:");
	for(i=0;i<16;i++)	
		printf("%2x ",SM4_plaintext[i]);
	printf("\r\n");
	printf("ciphertext:");
	for(i=0;i<16;i++)	
		printf("%2x ",SM4_ciphertext[i]);
	printf("\r\n\r\n");

	DeSM4(SM4_ciphertext,SM4_key,SM4_plaintext);
	printf("ciphertext:");
	for(i=0;i<16;i++)	
		printf("%2x ",SM4_ciphertext[i]);
	printf("\r\n");
	printf("plaintext:");
	for(i=0;i<16;i++)	
		printf("%2x ",SM4_plaintext[i]);
	printf("\r\n\r\n");

	/***************************** SHA1 *************************************/
	printf("***************************** SHA1 ********************************\r\n");
	SHA1(SHA1_plaintext,sizeof(SHA1_plaintext)-1, SHA1_ciphertext);
	printf("plaintext:");
	for(i=0;i<sizeof(SHA1_plaintext)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA1_plaintext[i]);
		
	}
	printf("\r\n");
	printf("ciphertext:\r\n");
	for(i=0;i<20;i++)	
		printf("%2x ",SHA1_ciphertext[i]);
	printf("\r\n\r\n");

	/***************************** SHA224 *************************************/
	printf("***************************** SHA224 ********************************\r\n");
	SHA224(SHA224_plaintext,sizeof(SHA224_plaintext)-1, SHA224_ciphertext);
	printf("plaintext:");
	for(i=0;i<sizeof(SHA224_plaintext)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA224_plaintext[i]);
		
	}
	printf("\r\n");

	printf("ciphertext:");
	for(i=0;i<28;i++)
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA224_ciphertext[i]);
	}
	printf("\r\n\r\n");

	/***************************** SHA256 *************************************/
	printf("***************************** SHA256 ********************************\r\n");
	SHA256(SHA256_plaintext,sizeof(SHA256_plaintext)-1, SHA256_ciphertext);
	printf("plaintext:");
	for(i=0;i<sizeof(SHA256_plaintext)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA256_plaintext[i]);	
	}
	printf("\r\n");

	printf("ciphertext:");
	for(i=0;i<32;i++)
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA256_ciphertext[i]);
	}
	printf("\r\n\r\n");

	/***************************** SHA384 *************************************/
	printf("***************************** SHA384 ********************************\r\n");
	SHA384(SHA384_plaintext,sizeof(SHA384_plaintext)-1, SHA384_ciphertext);
	printf("plaintext:");
	for(i=0;i<sizeof(SHA384_plaintext)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA384_plaintext[i]);		
	}
	printf("\r\n");

	printf("ciphertext:");
	for(i=0;i<48;i++)
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA384_ciphertext[i]);
	}
	printf("\r\n\r\n");

	/***************************** SHA512MY *************************************/
	printf("***************************** SHA512MY ********************************\r\n");
	SHA512MY(SHA512MY_plaintext,sizeof(SHA512MY_plaintext)-1, SHA512MY_ciphertext);
	printf("plaintext:");
	for(i=0;i<sizeof(SHA512MY_plaintext)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA512MY_plaintext[i]);		
	}
	printf("\r\n");

	printf("ciphertext:");
	for(i=0;i<64;i++)
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",SHA512MY_ciphertext[i]);
	}
	printf("\r\n\r\n");

	/***************************** CRC *************************************/
	printf("***************************** CRC ********************************\r\n");
	printf("plaintext:");
	for(i=0;i<sizeof(crc)-1;i++)	
	{
		if(i%16 == 0)
			printf("\r\n");
		printf("%2x ",crc[i]);		
	}
	printf("\r\n");

	printf("ciphertext:\r\n");
	//printf("%x \r\n",crc16(crc,sizeof(crc)-1,0xffff));
	printf("crc16_IBM: %x \r\n",crc16_IBM(crc,sizeof(crc)-1));
	printf("crc16_CCITT_FALSE: %x \r\n",crc16_CCITT_FALSE(crc,sizeof(crc)-1));
	printf("crc16_MAXIM: %x \r\n",crc16_MAXIM(crc,sizeof(crc)-1));
	
	/***************************** CRC *************************************/
	GenerateCrc16Table(crcHighTable,crcLowTable);
	for(i=0;i<256;i++)
	{
		if(!(i%8))
			printf("\r\n");
		printf("%02x ",crcHighTable[i]);
	}
	printf("\r\n");
	for(i=0;i<256;i++)
	{
		if(!(i%8))
			printf("\r\n");
		printf("%02x ",crcLowTable[i]);
	}
	printf("\r\n");
	printf("Crc16withTable: %x \r\n",Crc16withTable(crc,sizeof(crc)-1,crcHighTable,crcLowTable)); 

	GenerateCrc8Table(crc8Table);

	system("pause");
	return 0;
}