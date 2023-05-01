/*
1.项目名称：LU90614 体温测试例程
2.显示模块：0.96寸1306驱动OLED屏
3.配套APP：无
4.配套上位机：无
5.项目组成：OLED屏、STM32核心板、LU90614非接触测温模块
6.项目功能：OLED显示体温
7.请看模块的通信协议
*/
#include "sys.h"
#include "delay.h"
#include "oled_iic.h"
#include "stdio.h"
#include "usart.h"

int main(void)
{		
	u8 WENDU_H,WENDU_L;
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();
	delay_ms(50);
	uart_init(9600);
	OLED_Init();
	OLED_Clear();
	OLED_ShowCH(0,0,"  鹿小班工作室  ");		
	OLED_ShowCH(0,2," LU90614红外测温 ");
	OLED_ShowCH(0,4,"当前: 体温模式  ");
	OLED_ShowCH(0,6,"当前温度:   . ℃");		
	//发送体温模式指令 0XFA 0XC5 0XBF
	USART1_SendData(0XFA);
	USART1_SendData(0XC5);
	USART1_SendData(0XBF);
	delay_ms(50);
	while(1)
	{				
		if(USART_RX_STA&0X8000)//接收到一次数据
		{
			WENDU_H=USART_RX_BUF[2];		
			WENDU_L=USART_RX_BUF[3]/10;
			WENDU_H=WENDU_H&0X00FF;
			OLED_ShowNum(80,6,WENDU_H,2,1);//显示温度整数位
			OLED_ShowNum(104,6,WENDU_L,1,1);//显示温度小数位
			USART_RX_STA=0;//启动下次接收
		}
		delay_ms(200);
		//发送测温指令 0XFA 0XCA 0XC4
		USART1_SendData(0XFA);
		USART1_SendData(0XCA);
		USART1_SendData(0XC4);
		
	}
}


