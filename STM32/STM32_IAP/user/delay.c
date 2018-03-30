#include "delay.h"

static u8  fac_us=0;							//us延时倍乘数
static u16 fac_ms=0;							//ms延时倍乘数
/*******************************************************************************
* Function Name  : delay_init
* Description    : 初始化延迟函数，使用SysTick的普通计数模式对延迟进行管理 
* Input          : 系统时钟频率(Mhx)
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;//选择内部时钟 HCLK/8
	fac_us = SYSCLK / 8;      
	fac_ms = fac_us * 1000;
}            

/*******************************************************************************
* Function Name  : delay_init
* Description    : 延时Nms，Nms <= 0xffffff * 8 / SYSCLK，对72M条件下,Nms <= 1864
* Input          : 延时Nms
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_ms(uint16_t nms)
{         
	uint32_t temp;     
	SysTick->LOAD = nms * fac_ms;				//时间加载
	SysTick->VAL  = 0x00;						//清空计数器
	SysTick->CTRL = 0x01;						//开始倒数  
	do {
		temp=SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//等待时间到达   
	SysTick->CTRL = 0x00;       				//关闭计数器
	SysTick->VAL  = 0X00;       				//清空计数器        
}
 
/*******************************************************************************
* Function Name  : delay_us
* Description    : 延时Nus
* Input          : 延时Nus
* Output         : None
* Return         : None
* Author         : Jery Ouyang
* Date           : 2017-03-05
*******************************************************************************/
void delay_us(uint32_t Nus)
{  
	uint32_t temp;       
	SysTick->LOAD = Nus * fac_us;				//时间加载      
	SysTick->VAL  = 0x00;						//清空计数器
	SysTick->CTRL = 0x01;						//开始倒数   
	do {
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16)));	//等待时间到达   
	SysTick->CTRL = 0x00;       				//关闭计数器
	SysTick->VAL  = 0X00;       				//清空计数器     
}
