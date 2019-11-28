#include <stdio.h>
#include "type.h"
#include "CRC.h"

/*****************************************************************************
*function name:reverse
*function: �ֽڰ�λȡ��
*input��
*output:
******************************************************************************/
u8 reverse(u8 data)
{
	return ~data;
}
/*****************************************************************************
*function name:crc16
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���crc-��׼�涨�ĳ�ʼֵ
*output:16λУ��ֵ
******************************************************************************/
u16 crc16(u8 *addr, int num,u16 crc)  
{  
	u16 temp;
    //int i;  
    //for (; num > 0; num--)              
    //{  
		
    //    crc = crc ^ (~(*addr++) <<8);		//��crc��8λ��򣬸�8λ���� 
    //    for (i = 0; i < 8; i++)         //����λ8��  
    //    {  
    //        if (crc & 0x8000)             
    //            crc = (crc << 1) ^ 0x8005;//0xA001;//�Ƴ�λΪ1����0xA001���  
    //        else                          
    //            crc <<= 1;               //�Ƴ�λΪ0��������������  
    //    }								  
    //}
	
    //return(~crc);						//����У��ֵ
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
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ�
*output:16λУ��ֵ
******************************************************************************/
u16 crc16_IBM(u8 *addr, int num)  
{  
	u8 temp=0;
	u16 temp2=0;
	u8 data;
	u16 crc = 0x0000;//��ʼֵ
	int i;  
    for (; num > 0; num--)               
    {  
		data = *addr++;
		for(i=0;i<8;i++)						//�ֽڷ�ת
			temp |= ((data>>i) & 0x01)<<(7-i);
        crc = crc ^ (temp<<8) ;					//��crc��ʼֵ��8λ��� 
        for (i = 0; i < 8; i++)					//ѭ��8λ 
        {  
            if (crc & 0x8000)					//�����Ƴ���λΪ1�����ƺ������ʽ���
                crc = (crc << 1) ^ 0x8005;    
            else								//����ֱ������
                crc <<= 1;                  
        }                            
        crc &= 0xFFFF;							//ȷ��crcΪ16λ�����������ε�
    }
	for(i=0;i<16;i++)							//�������У��ֵ��ת
		temp2 |= ((crc>>i) & 0x0001)<<(15-i);
	crc = temp2^0x0000;							//����������ֵ���
	return(crc);								//��������У��ֵ
}


/*****************************************************************************
*function name:crc16
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���crc-��׼�涨�ĳ�ʼֵ
*output:16λУ��ֵ
******************************************************************************/
u16 crc16_CCITT_FALSE(u8 *addr, int num)  
{  
	u8 temp;	
	u8 data;
	u16 crc = 0xffff;//��ʼֵ
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
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���crc-��׼�涨�ĳ�ʼֵ
*output:16λУ��ֵ
******************************************************************************/
//u16 crc16_MAXIM(u8 *addr, int num)  
//{  
//	u8 temp=0;
//	u16 temp2=0;
//	u8 data;
//	u16 crc = 0x0000;//��ʼֵ
//	int i;  
//    for (; num > 0; num--)              /* Step through bytes in memory */  
//    {  
//		data = *addr++;
//		for(i=0;i<8;i++)			//�ֽڷ�ת
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
//	for(i=0;i<16;i++)				//У��ֵ��ת
//		temp2 |= ((crc>>i) & 0x0001)<<(15-i);
//	return(temp2^0xffff);/* Loop until num=0 */  
//}

/*****************************************************************************
*function name:crc16_MAXIM
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ�
*output:16λУ��ֵ
******************************************************************************/
u16 crc16_MAXIM(u8 *addr, int num)  
{  
	u8 data;
	u16 crc = 0x0000;//��ʼֵ
//	u16 crc = 0xffff;//��ʼֵ
	int i,j;  
	for (; num > 0; num--)             
	{  
		crc = crc ^ (*addr++) ;     //��8λ���
		for (i = 0; i < 8; i++)             
		{  
			if (crc & 0x0001)       //����ǰ��ͺ���ʡȥ�˷�ת���������������ƣ�������ֵΪ����ʽ�ķ�תֵ
				crc = (crc >> 1) ^ 0xA001;//���ƺ������ʽ��ת�����
			else                   //����ֱ������
				crc >>= 1;                    
		}                               
	}
	return(crc^0xffff);            //����У��ֵ 
	//for(i=0;i<num;i+=2)
	//{
	//	data = *(addr+i+1);
	//	crc ^= data;
	//	for(j=0;j<8;j++)
	//	{
	//		if (crc & 0x01)       //����ǰ��ͺ���ʡȥ�˷�ת���������������ƣ�������ֵΪ����ʽ�ķ�תֵ
	//			crc = (crc >> 1) ^ 0xA001;//���ƺ������ʽ��ת�����
	//		else                   //����ֱ������
	//			crc >>= 1;
	//	}
	//	data = *(addr+i);
	//	crc ^= data;
	//	for(j=0;j<8;j++)
	//	{
	//		if (crc & 0x01)       //����ǰ��ͺ���ʡȥ�˷�ת���������������ƣ�������ֵΪ����ʽ�ķ�תֵ
	//			crc = (crc >> 1) ^ 0xA001;//���ƺ������ʽ��ת�����
	//		else                   //����ֱ������
	//			crc >>= 1;
	//	}
	//}
	//return crc;
}

/*****************************************************************************
*function name:GenerateCrc16Table
*function: ����crc16����õı��
*input: table[256]:256��С�����飬�����ɵı���׵�ַ 
*output:��
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
			if (crc & 0x0001)       //����ǰ��ͺ���ʡȥ�˷�ת���������������ƣ�������ֵΪ����ʽ�ķ�תֵ
				crc = (crc >> 1) ^ 0xA001;//���ƺ������ʽ��ת�����
			else                   //����ֱ������
				crc >>= 1;                    
		}
		crcHighTable[j] = (u8)(crc&0xff);//ȡ���ֽ�
		crcLowTable[j] = (u8)((crc>>8)&0xff);//ȡ���ֽ�
		printf("%4x  ",crc);		
	}
	printf("\r\n");
}

/*****************************************************************************
*function name:Crc16withTable
*function: �ò������CRC
*input:  addr���ַ�����ʼ��ַ��len ���ַ������ȣ�table���õ��ı��
*output:��
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
	//	index = crcLo ^ *(addr+i+1);//��8λ��򣬵õ��������ֵ
	//	crcLo = crcHi ^ crcHighTable[index];
	//	crcHi = crcLowTable[index];

	//	index = crcLo ^ *(addr+i);//��8λ��򣬵õ��������ֵ
	//	crcLo = crcHi ^ crcHighTable[index];
	//	crcHi = crcLowTable[index]; 
	//}
	//crc = (u16)(crcHi<<8 | crcLo);
	//return crc;


	for (i=0;i<len;i++)             
	{  
		index = crcLo ^ *(addr++);//��8λ��򣬵õ��������ֵ
		crcLo = crcHi ^ crcHighTable[index];
		crcHi = crcLowTable[index];
	}
	crc = (u16)(crcHi<<8 | crcLo);
	return(crc^0xffff);            //����У��ֵ	
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
			if (crc & 0x80)       //����ǰ��ͺ���ʡȥ�˷�ת���������������ƣ�������ֵΪ����ʽ�ķ�תֵ
				crc = (crc << 1) ^ 0x07;//���ƺ������ʽ��ת�����
			else                   //����ֱ������
				crc <<= 1;                    
		}
		crc8Table[j] = crc;//ȡ���ֽ�
		printf("%2x ",crc);		
	}
	printf("\r\n");
}

/*****************************************************************************
*function name:crc8
*function: CRCУ�飬У��ֵΪ8λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���type-CRC8���㷨����
*output:8λУ��ֵ
******************************************************************************/
u8 crc8(u8 *addr, int len,u8 *crc8Table)  
{  
	u8 data;
	u8 crc = 00;                   //��ʼֵ
	int i;  
	for (; len > 0; len--)               
	{  
		data = *addr++;
//		if(type.InputReverse == TRUE)
//			data = reverse8(data);                 //�ֽڷ�ת
		crc = crc ^ data ;                     //��crc��ʼֵ��� 
		crc = crc8Table[crc];
	}
//	if(type.OutputReverse == TRUE)             //������������ת
//		crc = reverse8(crc);
	crc = crc^0x00;							   //����������ֵ���
	return(crc);                               //��������У��ֵ
}
 