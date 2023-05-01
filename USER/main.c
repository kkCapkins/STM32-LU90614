/*
1.��Ŀ���ƣ�LU90614 ���²�������
2.��ʾģ�飺0.96��1306����OLED��
3.����APP����
4.������λ������
5.��Ŀ��ɣ�OLED����STM32���İ塢LU90614�ǽӴ�����ģ��
6.��Ŀ���ܣ�OLED��ʾ����
7.�뿴ģ���ͨ��Э��
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	delay_ms(50);
	uart_init(9600);
	OLED_Init();
	OLED_Clear();
	OLED_ShowCH(0,0,"  ¹С�๤����  ");		
	OLED_ShowCH(0,2," LU90614������� ");
	OLED_ShowCH(0,4,"��ǰ: ����ģʽ  ");
	OLED_ShowCH(0,6,"��ǰ�¶�:   . ��");		
	//��������ģʽָ�� 0XFA 0XC5 0XBF
	USART1_SendData(0XFA);
	USART1_SendData(0XC5);
	USART1_SendData(0XBF);
	delay_ms(50);
	while(1)
	{				
		if(USART_RX_STA&0X8000)//���յ�һ������
		{
			WENDU_H=USART_RX_BUF[2];		
			WENDU_L=USART_RX_BUF[3]/10;
			WENDU_H=WENDU_H&0X00FF;
			OLED_ShowNum(80,6,WENDU_H,2,1);//��ʾ�¶�����λ
			OLED_ShowNum(104,6,WENDU_L,1,1);//��ʾ�¶�С��λ
			USART_RX_STA=0;//�����´ν���
		}
		delay_ms(200);
		//���Ͳ���ָ�� 0XFA 0XCA 0XC4
		USART1_SendData(0XFA);
		USART1_SendData(0XCA);
		USART1_SendData(0XC4);
		
	}
}


