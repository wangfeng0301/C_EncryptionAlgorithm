#include <stdio.h>
#include "type.h"
#include "CRC.h"

/*****************************************************************************
*function name:reverse
*function: 字节按位取反
*input：
*output:
******************************************************************************/
u8 reverse(u8 data)
{
	return ~data;
}
/*****************************************************************************
*function name:crc16
*function: CRC校验，校验值为16位
*input:addr-数据首地址；num-数据长度（字节）；crc-标准规定的初始值
*output:16位校验值
******************************************************************************/
u16 crc16(u8 *addr, int num,u16 crc)  
{  
	u16 temp;
    //int i;  
    //for (; num > 0; num--)              
    //{  
		
    //    crc = crc ^ (~(*addr++) <<8);		//与crc低8位异或，高8位不变 
    //    for (i = 0; i < 8; i++)         //右移位8次  
    //    {  
    //        if (crc & 0x8000)             
    //            crc = (crc << 1) ^ 0x8005;//0xA001;//移出位为1，与0xA001异或  
    //        else                          
    //            crc <<= 1;               //移出位为0，不做其他处理  
    //    }								  
    //}
	
    //return(~crc);						//返回校验值
	int i;  
    for (; num > 0; num--)              /* Step through bytes in memory */  
    {  
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/  
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */  
        {  
            if (crc & 0x8000)            /* b15 is set... */  
                crc = (crc << 1) ^ 0x1021;    /* rotate and XOR with polynomic */  
            else                          /* b15 is clear... */  
                crc <<= 1;                  /* just rotate */  
        }                             /* Loop for 8 bits */  
        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */  
    }
	return(crc);/* Loop until num=0 */  
} 

/*****************************************************************************
*function name:crc16_IBM
*function: CRC校验，校验值为16位
*input:addr-数据首地址；num-数据长度（字节）
*output:16位校验值
******************************************************************************/
u16 crc16_IBM(u8 *addr, int num)  
{  
	u8 temp=0;
	u16 temp2=0;
	u8 data;
	u16 crc = 0x0000;//初始值
	int i;  
    for (; num > 0; num--)               
    {  
		data = *addr++;
		for(i=0;i<8;i++)						//字节反转
			temp |= ((data>>i) & 0x01)<<(7-i);
        crc = crc ^ (temp<<8) ;					//与crc初始值高8位异或 
        for (i = 0; i < 8; i++)					//循环8位 
        {  
            if (crc & 0x8000)					//左移移出的位为1，左移后与多项式异或
                crc = (crc << 1) ^ 0x8005;    
            else								//否则直接左移
                crc <<= 1;                  
        }                            
        crc &= 0xFFFF;							//确保crc为16位，这句可以屏蔽掉
    }
	for(i=0;i<16;i++)							//计算完后，校验值反转
		temp2 |= ((crc>>i) & 0x0001)<<(15-i);
	crc = temp2^0x0000;							//最后返与结果异或值异或
	return(crc);								//返回最终校验值
}


/*****************************************************************************
*function name:crc16
*function: CRC校验，校验值为16位
*input:addr-数据首地址；num-数据长度（字节）；crc-标准规定的初始值
*output:16位校验值
******************************************************************************/
u16 crc16_CCITT_FALSE(u8 *addr, int num)  
{  
	u8 temp;	
	u8 data;
	u16 crc = 0xffff;//初始值
	int i;  
    for (; num > 0; num--)              /* Step through bytes in memory */  
    {  
		data = (*addr++);
        crc = crc ^ (data << 8);     /* Fetch byte from memory, XOR into CRC top byte*/  
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */  
        {  
            if (crc & 0x8000)            /* b15 is set... */  
                crc = (crc << 1) ^ 0x1021;    /* rotate and XOR with polynomic */  
            else                          /* b15 is clear... */  
                crc <<= 1;                  /* just rotate */  
        }                             /* Loop for 8 bits */  
        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */  
    }
	crc ^= 0x0000;
	return(crc);/* Loop until num=0 */  
}

/*****************************************************************************
*function name:crc16
*function: CRC校验，校验值为16位
*input:addr-数据首地址；num-数据长度（字节）；crc-标准规定的初始值
*output:16位校验值
******************************************************************************/
//u16 crc16_MAXIM(u8 *addr, int num)  
//{  
//	u8 temp=0;
//	u16 temp2=0;
//	u8 data;
//	u16 crc = 0x0000;//初始值
//	int i;  
//    for (; num > 0; num--)              /* Step through bytes in memory */  
//    {  
//		data = *addr++;
//		for(i=0;i<8;i++)			//字节反转
//			temp |= ((data>>i) & 0x01)<<(7-i);
//        crc = crc ^ (temp<<8) ;     /* Fetch byte from memory, XOR into CRC top byte*/  
//        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */  
//        {  
//            if (crc & 0x8000)            /* b15 is set... */  
//                crc = (crc << 1) ^ 0x8005;    /* rotate and XOR with polynomic */  
//            else                          /* b15 is clear... */  
//                crc <<= 1;                  /* just rotate */  
//        }                             /* Loop for 8 bits */  
//        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */  
//    }
//	for(i=0;i<16;i++)				//校验值反转
//		temp2 |= ((crc>>i) & 0x0001)<<(15-i);
//	return(temp2^0xffff);/* Loop until num=0 */  
//}

/*****************************************************************************
*function name:crc16_MAXIM
*function: CRC校验，校验值为16位
*input:addr-数据首地址；num-数据长度（字节）
*output:16位校验值
******************************************************************************/
u16 crc16_MAXIM(u8 *addr, int num)  
{  
	u8 data;
	u16 crc = 0x0000;//初始值
//	u16 crc = 0xffff;//初始值
	int i,j;  
	for (; num > 0; num--)             
	{  
		crc = crc ^ (*addr++) ;     //低8位异或
		for (i = 0; i < 8; i++)             
		{  
			if (crc & 0x0001)       //由于前面和后面省去了反转，所以这里是右移，且异或的值为多项式的反转值
				crc = (crc >> 1) ^ 0xA001;//右移后与多项式反转后异或
			else                   //否则直接右移
				crc >>= 1;                    
		}                               
	}
	return(crc^0xffff);            //返回校验值 
	//for(i=0;i<num;i+=2)
	//{
	//	data = *(addr+i+1);
	//	crc ^= data;
	//	for(j=0;j<8;j++)
	//	{
	//		if (crc & 0x01)       //由于前面和后面省去了反转，所以这里是右移，且异或的值为多项式的反转值
	//			crc = (crc >> 1) ^ 0xA001;//右移后与多项式反转后异或
	//		else                   //否则直接右移
	//			crc >>= 1;
	//	}
	//	data = *(addr+i);
	//	crc ^= data;
	//	for(j=0;j<8;j++)
	//	{
	//		if (crc & 0x01)       //由于前面和后面省去了反转，所以这里是右移，且异或的值为多项式的反转值
	//			crc = (crc >> 1) ^ 0xA001;//右移后与多项式反转后异或
	//		else                   //否则直接右移
	//			crc >>= 1;
	//	}
	//}
	//return crc;
}

/*****************************************************************************
*function name:GenerateCrc16Table
*function: 生成crc16查表法用的表格
*input: table[256]:256大小的数组，即生成的表格首地址 
*output:无
******************************************************************************/
void GenerateCrc16Table(u8 *crcHighTable,u8 *crcLowTable)  
{  
	u16 crc=0;
	u16 i,j;
	for(j = 0;j<256;j++)
	{
		if(!(j%8))
			printf("\r\n");

		crc = j;
		for (i = 0; i < 8; i++)             
		{  
			if (crc & 0x0001)       //由于前面和后面省去了反转，所以这里是右移，且异或的值为多项式的反转值
				crc = (crc >> 1) ^ 0xA001;//右移后与多项式反转后异或
			else                   //否则直接右移
				crc >>= 1;                    
		}
		crcHighTable[j] = (u8)(crc&0xff);//取低字节
		crcLowTable[j] = (u8)((crc>>8)&0xff);//取高字节
		printf("%4x  ",crc);		
	}
	printf("\r\n");
}

/*****************************************************************************
*function name:Crc16withTable
*function: 用查表法计算CRC
*input:  addr：字符串起始地址；len ：字符串长度；table：用到的表格
*output:无
******************************************************************************/
u16 Crc16withTable(u8 *addr, int len,u8 *crcHighTable,u8 *crcLowTable)  
{  
	u8 crcHi = 0x00;
	u8 crcLo = 0x00;
	//u8 crcHi = 0xff;
	//u8 crcLo = 0xff;
	u8 index;
	u16 crc;
	u16 i;
	//for (i=0;i<len;i+=2)             
	//{  
	//	index = crcLo ^ *(addr+i+1);//低8位异或，得到表格索引值
	//	crcLo = crcHi ^ crcHighTable[index];
	//	crcHi = crcLowTable[index];

	//	index = crcLo ^ *(addr+i);//低8位异或，得到表格索引值
	//	crcLo = crcHi ^ crcHighTable[index];
	//	crcHi = crcLowTable[index]; 
	//}
	//crc = (u16)(crcHi<<8 | crcLo);
	//return crc;


	for (i=0;i<len;i++)             
	{  
		index = crcLo ^ *(addr++);//低8位异或，得到表格索引值
		crcLo = crcHi ^ crcHighTable[index];
		crcHi = crcLowTable[index];
	}
	crc = (u16)(crcHi<<8 | crcLo);
	return(crc^0xffff);            //返回校验值	
}


void GenerateCrc8Table(u8 *crc8Table)  
{  
	u8 crc=0;
	u16 i,j;
	for(j = 0;j<256;j++)
	{
		if(!(j%16))
			printf("\r\n");

		crc = (u8)j;
		for (i = 0; i < 8; i++)             
		{  
			if (crc & 0x80)       //由于前面和后面省去了反转，所以这里是右移，且异或的值为多项式的反转值
				crc = (crc << 1) ^ 0x07;//右移后与多项式反转后异或
			else                   //否则直接右移
				crc <<= 1;                    
		}
		crc8Table[j] = crc;//取低字节
		printf("%2x ",crc);		
	}
	printf("\r\n");
}

/*****************************************************************************
*function name:crc8
*function: CRC校验，校验值为8位
*input:addr-数据首地址；num-数据长度（字节）；type-CRC8的算法类型
*output:8位校验值
******************************************************************************/
u8 crc8(u8 *addr, int len,u8 *crc8Table)  
{  
	u8 data;
	u8 crc = 00;                   //初始值
	int i;  
	for (; len > 0; len--)               
	{  
		data = *addr++;
//		if(type.InputReverse == TRUE)
//			data = reverse8(data);                 //字节反转
		crc = crc ^ data ;                     //与crc初始值异或 
		crc = crc8Table[crc];
	}
//	if(type.OutputReverse == TRUE)             //满足条件，反转
//		crc = reverse8(crc);
	crc = crc^0x00;							   //最后返与结果异或值异或
	return(crc);                               //返回最终校验值
}
 