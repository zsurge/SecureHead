#include "delay.h"

static u8  fac_us=0;							//us��ʱ������
static u16 fac_ms=0;							//ms��ʱ������
/*******************************************************************************
* Function Name  : delay_init
* Description    : ��ʼ���ӳٺ�����ʹ��SysTick����ͨ����ģʽ���ӳٽ��й��� 
* Input          : ϵͳʱ��Ƶ��(Mhx)
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;//ѡ���ڲ�ʱ�� HCLK/8
	fac_us = SYSCLK / 8;      
	fac_ms = fac_us * 1000;
}            

/*******************************************************************************
* Function Name  : delay_init
* Description    : ��ʱNms��Nms <= 0xffffff * 8 / SYSCLK����72M������,Nms <= 1864
* Input          : ��ʱNms
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_ms(uint16_t nms)
{         
	uint32_t temp;     
	SysTick->LOAD = nms * fac_ms;				//ʱ�����
	SysTick->VAL  = 0x00;						//��ռ�����
	SysTick->CTRL = 0x01;						//��ʼ����  
	do {
		temp=SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL = 0x00;       				//�رռ�����
	SysTick->VAL  = 0X00;       				//��ռ�����        
}
 
/*******************************************************************************
* Function Name  : delay_us
* Description    : ��ʱNus
* Input          : ��ʱNus
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_us(uint32_t Nus)
{  
	uint32_t temp;       
	SysTick->LOAD = Nus * fac_us;				//ʱ�����      
	SysTick->VAL  = 0x00;						//��ռ�����
	SysTick->CTRL = 0x01;						//��ʼ����   
	do {
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL = 0x00;       				//�رռ�����
	SysTick->VAL  = 0X00;       				//��ռ�����     
}
