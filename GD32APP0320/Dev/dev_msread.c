#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "usb_endp.h"
#include "Mylib.h"

#undef TK1buf
#define TK1buf ((uint8_t *)Track1Data.Value)					//��һ�ŵ����ݻ���
#undef TK2buf
#define TK2buf ((uint8_t *)Track2Data.Value)					//�ڶ��ŵ����ݻ���
#undef TK3buf
#define TK3buf ((uint8_t *)Track3Data.Value)					//�����ŵ����ݻ���

#undef TK1len
#define TK1len Track1Data.Length								//��һ�ŵ����ݳ���
#undef TK2len
#define TK2len Track2Data.Length								//�ڶ��ŵ����ݳ���
#undef TK3len
#define TK3len Track3Data.Length								//�����ŵ����ݳ���

//uint8_t MAGBuf[500];
SHA1Context foo;
AES_KEY key;
 uint8_t *sha;
/**************************************************************************************
//	*** �� �� ��:	void MSR_SendData(void)
//	*** ���������� �ŵ����ݼ������ͺ���
//	*** ��    ��: 
//	*** �� �� ֵ: ����ĳ���  	 	
//	*** ģ����Ϣ: Ouyangweiquan 2012.04.24����
***************************************************************************************/
void MSR_SendData(void)
{
	uint8_t *ch = (uint8_t *)TrackBitFlow.Value, ivec[16],*ch1,randbuff[8],s=0,lp;
	uint16_t len = 0x10,j;
	uint8_t lrc,bcc,block1,block2,block3;
	uint8_t extralength,tp1,ts1,tp2,ts2,tp3,ts3,Preamblelen,Postamblelen;
	uint16_t templen = 0;

	uint8_t setseparator[1] = {0};
	uint8_t account[20] = {0};
	
	

	memset(account,0x00,sizeof(account));
	memset(sha,0x00,sizeof(sha));

	extralength=tp1=ts1=tp2=ts2=tp3=ts3=Preamblelen=Postamblelen=0;
	
	tp1= strlen((const char *)ENC_KEY.temp.track1prefix);
	
    tp2= strlen((const char *)ENC_KEY.temp.track2prefix);
    tp3= strlen((const char *)ENC_KEY.temp.track3prefix);

    ts1= strlen((const char *)ENC_KEY.temp.track1suffix);
    ts2= strlen((const char *)ENC_KEY.temp.track2suffix);
    ts3= strlen((const char *)ENC_KEY.temp.track3suffix);

    Preamblelen= strlen((const char *)ENC_KEY.temp.Preamble);

    Postamblelen= strlen((const char *)ENC_KEY.temp.Postamble);

    extralength=tp1+ts1+tp2+ts2+tp3+ts3+Preamblelen+Postamblelen;


	if(ENC_KEY.temp.enabledevice == 0x30)
	{
	    return;
	}
		
	if(ENC_KEY.temp.level < 0x30 && ENC_KEY.temp.level > 0x34 )	//���ܼ���ʧЧ
	{
		goto ERRORDATA;											//��ԿʧЧ���ش���
	}
	
	if (1 == ENC_KEY.temp.status)								//���Ļ��ʹŵ�����
	{
		encryptdatastatus = 0xBF;								//���÷������ݵ�����
		templen = 0;
//		printf("ENC_KEY.temp.encway===1\r\n");		
		/*���ȼ�84 = 8�����ݰ�ͷ + 60 ����ϣֵ + 10��KSN +16����Կ+ 2��У���� + 1�������� + extralength */
		if(0x32 == ENC_KEY.temp.encway)							//���AES������ÿ��16�ֽ� 
		{
//			printf("aes\r\n");
			block1 = ceil((TK1len-1)/16.0);//��ȡÿһ����ͷ���ݳ���
			block2 = ceil((TK2len-1)/16.0);
			block3 = ceil((TK3len-1)/16.0);         //84
			len = block1*16 + block2*16 + block3*16 + 84 + extralength ;		//���㷵�����ݳ���
		}
		else													//���DES������ÿ��8�ֽ�
		{
//			printf("des\r\n");
			block1 = ceil((TK1len-1)/8.0);
			block2 = ceil((TK2len-1)/8.0);
			block3 = ceil((TK3len-1)/8.0);       //84
			len = block1*8 + block2*8 + block3*8 + 84 + extralength ;  		//���㷵�����ݳ���

		}
//		printf("ENC_KEY.temp.Enhancedstatue %d\r\n",ENC_KEY.temp.Enhancedstatue);
		if(!block1 && !block2 && !block3)						//������дŵ���Ϊ�գ�ˢ��ʧ��
			goto ERRORDATA;
		
		if(!TK1len)
		{												   	
			encryptdatastatus &= 0xF6;							//��һ�ŵ����ݷ���Ϊ��
			len -= (20 + tp1 + ts1);
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK1buf[1], TK1len-1);			//�����һ�ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha);						
		}
		if(!TK2len)
		{
			encryptdatastatus &= 0xED;							//�ڶ��ŵ����ݷ���Ϊ��
			len -= (20 + tp2 + ts2);
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK2buf[1], TK2len-1);			//����ڶ��ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha+20);			
		}
		if(!TK3len)
		{
		 	encryptdatastatus &= 0xDB;							//�����ŵ����ݷ���Ϊ��
			len -= (20 + tp3 + ts3);
		}
		else
		{
			SHA1Init (&foo);
			SHA1Update (&foo, &TK3buf[1], TK3len-1);			//��������ŵ����ݹ�ϣֵ
			SHA1Final (&foo, sha+40);
			
		}		
    		
		//            0  1   2   3  4    5   6   7   8  9						
		//memcpy(ch,"\x02\x00\x00\x80\x3F\x00\x00\x00\x00\x01",10);//10���ֽ����ݰ�ͷ
		memset(ch,0x00,sizeof(ch));
		ch[0]=0x02;
		ch[1] = (uint8_t)(len-7);								 //�ſ������ܱ��泤��
		ch[2] = ((len-7)>>8);

    ch[3]=0x00;	//card encoding type (0: ISO/ABA, 4: for Raw Mode)
//		//ռ��λ
		
		ch[4]=0x3f; //track 1  status (bit 0,1,2:T1,2,3 decode, bit 3,4,5:T1,2,3

		
		if(TK1len)ch[5] = TK1len-1;//1��ͷ���ݳ���

		if(TK2len)ch[6] = TK2len-1;//2��ͷ���ݳ���
		if(TK3len)ch[7] = TK3len-1;//3��ͷ���ݳ���
        //�����ʼ��
        templen = 8;        
		memcpy(ch+templen,ENC_KEY.temp.Preamble,Preamblelen);
		templen += Preamblelen;
    
		if (0x31 == ENC_KEY.temp.encmode)				   		//DUKPT����
		{
//			memset("");
			CalcCryptoKey();									//����DUKPT������Կ  ENC_KEY.temp.key
//			DBG_H("CryptoKeyAAS",CryptoKey,16);
      
		}
		else if (0x30 == ENC_KEY.temp.encmode)			 		//FIX����
		{
			memcpy(CryptoKey,ENC_KEY.temp.fix,16);				//����FIX��Կ
//			DBG_H("ENC_KEY.temp.key",CryptoKey,16);
		}
		
//		printf("block1 %d\r\n",block1);
//		printf("block2 %d\r\n",block2);
//		printf("block3 %d\r\n",block3);
//		
//		DBG_H("TK1buf",TK1buf,TK1len);
//			DBG_H("TK2buf",TK2buf,TK2len);
//			DBG_H("TK3buf",TK3buf,TK3len);
		if( 0x30 == ENC_KEY.temp.encway)						//DES����
		{
			goto ERRORDATA;
		}
		else if(0x31 == ENC_KEY.temp.encway)					//three DES���� 
		{
			
//			for(s=0;s<8;s++)
//			randbuff[s]=rand()%127;
//			DBG_H("randbuff",randbuff,strlen(randbuff));		
//			xor(TK1buf+1,randbuff,8);
			
			tri_des(TK1buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block1;j++)							//���ܵ�һ�ŵ�����
			{
				
				xor(TK1buf+1+j*8,TK1buf+j*8-7,8);
				tri_des(TK1buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			
//      printf("templen11 %d\r\n",templen);
					  
				memcpy(ch+templen,ENC_KEY.temp.track1prefix,tp1);
				templen += tp1;

				//����1�ŵ���Ϣ
				memcpy(ch+templen,TK1buf,(block1*8)+1);
			
			  
				templen += block1*8;
			  templen +=1;
//			printf("templen %d\r\n",templen);
//			DBG_H("TK1buf",TK1buf,templen);
			
            //����ŵ���׺
						
	        memcpy(ch+templen,ENC_KEY.temp.track1suffix,ts1);
			templen += ts1;
			

//      DBG_H("ch1",ch,templen);
			
			tri_des(TK2buf+1,CryptoKey,CryptoKey+8,0);
			for(j = 1;j< block2;j++)							//���ܵڶ��ŵ�����
			{
//				printf("j001 %d\r\n",j);
				xor(TK2buf+1+j*8,TK2buf+j*8-7,8);
				tri_des(TK2buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			
			//memcpy(ch+11+block1*8,TK2buf+1,block2*8);
			
			//��Ӵŵ�ǰ׺	
     			
			memcpy(ch+templen,ENC_KEY.temp.track2prefix,tp2);
			templen += tp2;
			
      
//			 printf("templen44 %d\r\n",templen); 
			//����2�ŵ���Ϣ
			memcpy(ch+templen,TK2buf,block2*8+1);//memcpy(ch+templen,TK2buf+1,block2*8);ԭ����  �������������ʼ����ȥ��  ��ע��
            templen += block2*8+1;
//			DBG_H("TK2buf",TK2buf,templen);
//			templen+=TK2len;
//			templen+=1;
//			  printf("ts2 %d\r\n",ts2);
//        DBG_H("ch2",ch,templen);
//			   printf("templen55 %d\r\n",templen); 
            //����ŵ���׺
      
	        memcpy(ch+templen,ENC_KEY.temp.track2suffix,ts2);
			templen += ts2;		
							
//			 printf("templen66 %d\r\n",templen); 
//			for(s=0;s<8;s++)
//			randbuff[s]=rand()%127;
//			DBG_H("randbuff",randbuff,strlen(randbuff));		
//			xor(TK3buf+1,randbuff,8);
			
			tri_des(TK3buf+1,CryptoKey-7,CryptoKey+8,0);
			for(j = 1;j< block3;j++)							//���ܵ����ŵ�����
			{
				xor(TK3buf+1+j*8,TK3buf+j*8-7,8);
				tri_des(TK3buf+1+j*8,CryptoKey,CryptoKey+8,0);
			}
			
//			memcpy(ch+11+block1*8+block2*8,TK3buf+1,block3*8);

			//��Ӵŵ�ǰ׺
      				
			memcpy(ch+templen,ENC_KEY.temp.track3prefix,tp3);
			templen += tp3;
			
			//����3�ŵ���Ϣ
			
			memcpy(ch+templen,TK3buf,block3*8+1);
			templen += block3*8+1;  
//			DBG_H("TK3buf",TK3buf,TK3len);
//			templen+=TK3len;
//			templen+=1;
//			printf("ts3 %d\r\n",ts3);
//      DBG_H("ch3",ch,templen);
            //����ŵ���׺
			
	    memcpy(ch+templen,ENC_KEY.temp.track3suffix,ts3);
			templen += ts3;	
			
				
			
		}
		else if(0x32 == ENC_KEY.temp.encway)					//AES����
		{
			AES_set_encrypt_key(CryptoKey,128,&key);
			printf("aes jiami \r\n");

			/* ���ܵ�һ�ŵ����� */
			if(block1)
			{
				memset(ivec,0,sizeof(ivec));

				//��Ӵŵ�ǰ׺
				memcpy(ch+templen,ENC_KEY.temp.track1prefix,tp1);
			    templen += tp1;		
			    
				memcpy(ch+templen,TK1buf,block1*16);                
				templen+=1;
				//AES_cbc_encrypt(ch+11,ch+11,block1*16,&key,ivec,1);
				AES_cbc_encrypt(ch+templen,ch+templen,block1*16,&key,ivec,1);
//				AES_cbc_encrypt(ch+templen,TK1buf+1,block1*16,&key,ivec,1);
				templen += block1*16;
//        templen+=TK1len;
				//����ŵ���׺
    	        memcpy(ch+templen,ENC_KEY.temp.track1suffix,ts1);
    			templen += ts1;
			
			}
//			DBG_H("ch1",ch,templen);
			/* ���ܵڶ��ŵ����� */
			if(block2)
			{
				memset(ivec,0,sizeof(ivec));

				//��Ӵŵ�ǰ׺
				memcpy(ch+templen,ENC_KEY.temp.track2prefix,tp2);
			    templen += tp2;		
			    
				memcpy(ch+templen,TK2buf,block2*16);
				templen+=1;
//				AES_cbc_encrypt(ch+templen,TK2buf,block2*16,&key,ivec,1);
				AES_cbc_encrypt(ch+templen,ch+templen,block2*16,&key,ivec,1);
				templen += block2*16;
//				templen+=TK2len;
				
				//����ŵ���׺
    	        memcpy(ch+templen,ENC_KEY.temp.track2suffix,ts2);
    			templen += ts2;
				
			}
//			DBG_H("ch2",ch,templen);
			/* ���ܵ����ŵ����� */
			if(block3)
			{
				memset(ivec,0,sizeof(ivec));

				//��Ӵŵ�ǰ׺
				memcpy(ch+templen,ENC_KEY.temp.track3prefix,tp3);
			    templen += tp3;	
			    
				memcpy(ch+templen,TK3buf,block3*16);
				templen+=1;
//				AES_cbc_encrypt(ch+templen,TK3buf+1,block3*16,&key,ivec,1);
				AES_cbc_encrypt(ch+templen,ch+templen,block3*16,&key,ivec,1);
                templen += block3*16;  
//             templen+= TK3len ; 
				//����ŵ���׺
    	        memcpy(ch+templen,ENC_KEY.temp.track3suffix,ts3);
    			templen += ts3;
			}
//			DBG_H("ch3",ch,templen);
		}
	 	else
		{
			goto ERRORDATA;
		}

		
	    //���������
		memcpy(ch+templen,ENC_KEY.temp.Postamble,Postamblelen);
	    templen += Postamblelen;
		
//		printf("ENC_KEY.temp.level %d\r\n",ENC_KEY.temp.level);
//		printf("ENC_KEY.temp.Enhancedstatue %d\r\n",ENC_KEY.temp.Enhancedstatue);
//		DBG_H("haxifull",sha,60);//
		if(ENC_KEY.temp.Enhancedstatue==0x31)///ǿ���������ʽ
		{
//			printf("0012\r\n");
			if(ENC_KEY.temp.level==0x32)//ǿ�Ƽ��ܵȼ�3��ʱ��	 ǿ�Ƽ��ܵ�DUKPT��FIX�����ǰ�KSN��SN���  DUKPT���---KSN    FIX�������SN
			{
				if(ENC_KEY.temp.HASHSET==0x01)//���Ǽ��� ȷ�����1��ϣֵ�Ƿ���
					{
					  if(block1)
					 {
						 memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
						 templen+=20;
//						 DBG_H("chff0011",ch,templen);
//						 DBG_H("haxi111",sha,20);//
					 }						
				  }
					if(ENC_KEY.temp.HASHSET==0x02) //���Ǽ��� ȷ�����2��ϣֵ�Ƿ���
					{
						if(block2)
						{
              memcpy(ch+templen,sha+20,20);					//�����2�ŵ����ݹ�ϣֵ
						  templen+=20;
						}							            						
					}
					if(ENC_KEY.temp.HASHSET==0x04) //���Ǽ��� ȷ�����3��ϣֵ�Ƿ���
					{
						if(block3)
						{
              memcpy(ch+templen,sha+40,20);					//�����3�ŵ����ݹ�ϣֵ
						  templen+=40;
						}							            						
					}
					
         if(ENC_KEY.temp.HASHSET==0x07)
				 {
					 if(block1)
					 {
						 memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
						 templen+=20;
//					 DBG_H("chff0011",ch,templen);
//					 DBG_H("haxi111",sha,20);//
					 }
					 if(block2)
					 {				
						 memcpy(ch+templen,sha+20,20);					//�����2�ŵ����ݹ�ϣֵ
						 templen+=20;						 
					 }
					 if(block3)
					 {
						 memcpy(ch+templen,sha+40,20);					//�����2�ŵ����ݹ�ϣֵ
						 templen+=20;					 
					 }					 
				 }
				 
//					len=len-20;	   					
					if(0x31 == ENC_KEY.temp.encmode)//��dukpt���ܷ�ʽ  �򷵻�ksn
				    memcpy(ch+templen,ENC_KEY.temp.ksn,10);
			
					if(0x30 == ENC_KEY.temp.encmode)//��fix���ܷ�ʽ  �򷵻�sn
						memcpy(ch+templen,ENC_KEY.temp.sn,10);
          
         templen+=10;					
//				DBG_H("chffqqqw11",ch,templen);
		  }
			
			if(ENC_KEY.temp.level==0x33)//ǿ�Ƽ��ܵȼ�4��ʱ��
			{
				memcpy(ch+templen,ENC_KEY.temp.sid,8);//���SSID  ֻ���ڼ��ܵȼ���4��ʱ�� �����SSID
				templen+=8;
//        printf("templen-* %d\r\n",templen);
//				DBG_H("chff**",ch,templen);
				if(ENC_KEY.temp.HASHSET==0x01)//���Ǽ��� ȷ�����1��ϣֵ�Ƿ���
					{
					  if(block1)
					 {
						 memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
						 templen+=20;
//						 DBG_H("chff00**",ch,templen);
//						 DBG_H("haxi1**",sha,20);//
					 }						
				  }
					if(ENC_KEY.temp.HASHSET==0x02) //���Ǽ��� ȷ�����2��ϣֵ�Ƿ���
					{
						if(block2)
						{
							memcpy(ch+templen,sha+20,20);					//�����1�ŵ����ݹ�ϣֵ
						  templen+=20;						
						}            						
					}
					if(ENC_KEY.temp.HASHSET==0x04) //���Ǽ��� ȷ�����3��ϣֵ�Ƿ���
					{
						if(block3)
						{
							memcpy(ch+templen,sha+40,20);					//�����3�ŵ����ݹ�ϣֵ
						  templen+=20;						
						}					
					}
         if(ENC_KEY.temp.HASHSET==0x07)
				 {
					 if(block1)
						{
							memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
						  templen+=20;						
						}
						
						if(block2)
						{
							memcpy(ch+templen,sha+20,20);					//�����2�ŵ����ݹ�ϣֵ
						  templen+=20;						
						}
						
					 if(block3)
						{
							memcpy(ch+templen,sha+40,20);					//�����3�ŵ����ݹ�ϣֵ
						  templen+=20;						
						}
//					 DBG_H("haxi2**",sha+20,20);//
//					 DBG_H("chffwww**",ch,templen);
				 }
				 
//					len=len-20;	   					
					if(0x31 == ENC_KEY.temp.encmode)//��dukpt���ܷ�ʽ  �򷵻�ksn
				    memcpy(ch+templen,ENC_KEY.temp.ksn,10);
			
					if(0x30 == ENC_KEY.temp.encmode)//��fix���ܷ�ʽ  �򷵻�sn
						memcpy(ch+templen,ENC_KEY.temp.sn,10);
          
         templen+=10;	
			
				
			}
			
    }
		
////		memcpy(ch,TK1buf,TK1len);//���ع��1���ܹ�������
		if(ENC_KEY.temp.Enhancedstatue==0x30)//��ͨ���������ʽ
		{
			
//			printf("00FF\r\n");
//			printf("ENC_KEY.temp.level %d\r\n",ENC_KEY.temp.level);
//			printf("ENC_KEY.temp.HASHSET %d\r\n",ENC_KEY.temp.HASHSET);
//			DBG_H("haxi3",sha+40,20);//
//					DBG_H("haxi2",sha+20,20);//
//					DBG_H("haxi1",sha,20);//
				if(ENC_KEY.temp.level==0x32)  //�ȼ�3����  ��ͨ���������ʽֻ��Ҫ���͹��1�͹��2�Ĺ�ϣֵ����
				{
//					memcpy(ch+templen,ENC_KEY.temp.sid,8);//���SSID
//				templen+=8;

				if(block1)
				{
//					DBG_H("haxiff1**",sha,20);
					memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
					templen+=20;
				}
				if(block2)
				{
					memcpy(ch+templen,sha+20,20);					//�����2�ŵ����ݹ�ϣֵ
					templen+=20;
//					DBG_H("haxiff2**",sha+20,20);
				}
				 
//					len=len-20;	   					
					if(0x31 == ENC_KEY.temp.encmode)//��dukpt���ܷ�ʽ  �򷵻�ksn
				    memcpy(ch+templen,ENC_KEY.temp.ksn,10);
			
					if(0x30 == ENC_KEY.temp.encmode)//��fix���ܷ�ʽ  �򷵻�sn
						memcpy(ch+templen,ENC_KEY.temp.sn,10);
          
         templen+=10;					
//				DBG_H("chffqqqw11",ch,templen);				
			}
				
			
			if(ENC_KEY.temp.level==0x33)  //�ȼ�4����  ��ͨ���������ʽֻ��Ҫ���͹��1�͹��2�Ĺ�ϣֵ����
			{
				
					memcpy(ch+templen,ENC_KEY.temp.sid,8);//���SSID
					templen+=8;
				
//        printf("templen %d\r\n",templen);
//				DBG_H("chff",ch,templen);
				if(block1)
				 {
					 memcpy(ch+templen,sha,20);					//�����1�ŵ����ݹ�ϣֵ
					 templen+=20;
//					 DBG_H("chff00**",ch,templen);
//					 DBG_H("haxi1**",sha,20);//
				 } 
					if(block2)
				 {
					 memcpy(ch+templen,sha+20,20);					//�����2�ŵ����ݹ�ϣֵ
					 templen+=20;
//					 DBG_H("chff00**",ch,templen);
//					 DBG_H("haxi1**",sha,20);//
				 }  
		
//					 DBG_H("haxi2",sha+20,20);//
//					 DBG_H("chffwww",ch,templen);
				 
				    					
					if(0x31 == ENC_KEY.temp.encmode)//��dukpt���ܷ�ʽ  �򷵻�ksn
				    memcpy(ch+templen,ENC_KEY.temp.ksn,10);
			
					if(0x30 == ENC_KEY.temp.encmode)//��fix���ܷ�ʽ  �򷵻�sn
						memcpy(ch+templen,ENC_KEY.temp.sn,10);
          
         templen+=10;					
				
			}
			
	}
//    
//		for(j = 4,lrc = 0,bcc = 0;j<len-3;j++)					//����У����
	  for(j = 4,lrc = 0,bcc = 0;j<templen-3;j++)					//����У����
		{
			lrc ^= ch[j];
			bcc += ch[j];
		}

		templen+=3;
		ch[templen-3] = lrc;
		ch[templen-2] = bcc;
		ch[templen-1] = 0x03;
		
//		DBG_H("chffqqqw",ch,templen);
		UsbSendBuff(ch, templen, 5000);
		memset(TK3buf,0x00,sizeof(TK3buf));
		memset(TK2buf,0x00,sizeof(TK2buf));
		memset(TK1buf,0x00,sizeof(TK1buf));
	}
	else if(0 == ENC_KEY.temp.status)			  					//���Ļ�������
	{	
//    printf("ENC_KEY.temp.encway00000\r\n");
//		DBG_S("ENC_KEY.temp.Terminator = %d\r\n",ENC_KEY.temp.Terminator);

		//ȥ����ʼ��FF
		//ch[0]=0xFF;
		//templen = 1;
		
		if(TK3len)TK3buf[TK3len-1] = ENC_KEY.temp.Terminator;
		if(TK2len)TK2buf[TK2len-1] = ENC_KEY.temp.Terminator;
		if(TK1len)TK1buf[TK1len-1] = ENC_KEY.temp.Terminator;
	    
        templen = 0;


//        DBG_S("ENC_KEY.temp.settrack2format = %d\r\n",ENC_KEY.temp.settrack2format);
        
        if(ENC_KEY.temp.settrack2format == 0x31 || ENC_KEY.temp.settrack2format == 0x33)
        {
            //�����ʼ��

    		memcpy(ch+templen,ENC_KEY.temp.Preamble,Preamblelen);

    		templen += Preamblelen;

    		//��Ӵŵ�ǰ׺			
    		memcpy(ch+templen,ENC_KEY.temp.track1prefix,tp1);
    		templen += tp1;
		}
        
		//����1�ŵ���Ϣ
		if(ENC_KEY.temp.settrack2format == 0x30 || ENC_KEY.temp.settrack2format == 0x32)
		{
		    DeleteChars(TK1buf,"+,-;?%"); //ɾ��"; %"
		    TK1len = strlen((const char*)TK1buf);
		    memcpy(ch+templen,TK1buf,TK1len);
            templen += TK1len;		    
		}
		else
		{
            memcpy(ch+templen,TK1buf,TK1len);
            templen += TK1len;
        }

//        DBG_S("TK1buft = %d\r\n",TK1len);

        if(ENC_KEY.temp.settrack2format == 0x31 || ENC_KEY.temp.settrack2format == 0x33)
        {
            //����ŵ���׺
            memcpy(ch+templen,ENC_KEY.temp.track1suffix,ts1);
    		templen += ts1;
    		////////////////////////////

    		//��ӹ����������Ҫ�ж�ǰ��ŵ��Ƿ�������
    		//�ж�tarck1 ����
    		if(TK1len > 20 && TK2len > 20 && ENC_KEY.temp.setseparator != 0x00)
    		{
    		    //��ӹ���ָ��
    		   setseparator[0] = ENC_KEY.temp.setseparator;
    		   memcpy(ch+templen,setseparator,1); 
    		   templen += 1;
    		}

    		//��Ӵŵ�ǰ׺			
    		memcpy(ch+templen,ENC_KEY.temp.track2prefix,tp2);
    		templen += tp2;
		}

		//����2�ŵ���Ϣ
		if(ENC_KEY.temp.settrack2format == 0x32 || ENC_KEY.temp.settrack2format == 0x33)
		{
		    GetAccount(TK2buf, account);	
		    TK2len = strlen((const char*)account);
		    memcpy(ch+templen,account,TK2len);
            templen += TK2len;		    
		}
		else if(ENC_KEY.temp.settrack2format == 0x30)
		{
		    DeleteChars(TK2buf,"+,-;?%"); //ɾ��"; %"
		    TK2len = strlen((const char*)TK2buf);
		    memcpy(ch+templen,TK2buf,TK2len);
            templen += TK2len;	    
		}
		else
		{		
            memcpy(ch+templen,TK2buf,TK2len);
            templen += TK2len;
        }

//        DBG_S("TK2buft = %d\r\n",TK2len);
        
        if(ENC_KEY.temp.settrack2format == 0x31 || ENC_KEY.temp.settrack2format == 0x33)
        {
            //����ŵ���׺
            memcpy(ch+templen,ENC_KEY.temp.track2suffix,ts2);
    		templen += ts2;

    		///////////////////////

    		//��ӹ����������Ҫ�ж�ǰ��ŵ��Ƿ�������
    		//�ж�tarck1 ����
    		if(TK2len > 20 && TK3len > 20 && ENC_KEY.temp.setseparator != 0x00)
    		{
    		    //��ӹ���ָ��
    		   setseparator[0] = ENC_KEY.temp.setseparator;
    		   memcpy(ch+templen,setseparator,1); 
    		   templen += 1;
    		}
    		

    		//��Ӵŵ�ǰ׺			
    		memcpy(ch+templen,ENC_KEY.temp.track3prefix,tp3);
    		templen += tp3;
		}


		//����3�ŵ���Ϣ
		if(ENC_KEY.temp.settrack2format == 0x30 || ENC_KEY.temp.settrack2format == 0x32)
		{
		    DeleteChars(TK3buf,"+,-;?%"); //ɾ��"; %"
		    TK3len = strlen((const char*)TK3buf);
		    memcpy(ch+templen,TK3buf,TK3len);
            templen += TK3len;		    
		}
		else
		{
            memcpy(ch+templen,TK3buf,TK3len);
            templen += TK3len;
        }

//        DBG_S("TK3buft = %d\r\n",TK3len);

        if(ENC_KEY.temp.settrack2format == 0x31 || ENC_KEY.temp.settrack2format == 0x33)
        {
            //����ŵ���׺
            memcpy(ch+templen,ENC_KEY.temp.track3suffix,ts3);
    		templen += ts3;
    			
    		//���������
    		memcpy(ch+templen,ENC_KEY.temp.Postamble,Postamblelen);
    	    templen += Postamblelen;	
	    }
		
		len = TK3len+TK2len+TK1len+extralength;
//		DBG_S("totle len : %d\r\n",len);	
			UsbSendBuff(ch, len, 5000);
	}
	else
	{
ERRORDATA:
    	len = 10;
    	memset(ch, 0xFF, templen);	
	}
	
	
	
//	UsbSendBuff(ch, templen, 5000);
	
	

	
//	dev_com_write(TK1buf, TK1len);
//	dev_com_write(TK2buf, TK2len);
//	dev_com_write(TK3buf, TK3len);
	
//	dev_com_write(ch, len);
//	dev_com_write(TK1buf, TK1len);
//		dev_com_write(TK2buf, TK2len);
//		dev_com_write(TK3buf, TK3len);
	
	return;
}

