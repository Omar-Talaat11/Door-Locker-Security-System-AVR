
#include "buzzer.h"
#include "timer1.h"
#include "uart.h"
#include "DcMotor.h"
#include "twi.h"
#include "external_eeprom.h"
#include "gpio.h"
#include "util/delay.h"


uint8 g_key1[5];
uint8 g_key2[5];
uint8 g_lastOption;
uint8 g_time;

uint8 APP_readFirstPass(void);
uint8 APP_readSecondPass(void);
uint8 APP_comparePasses(void);
uint8 APP_takeOption(void);
uint8 APP_verifyPass(void);
void APP_alarm(void);
void APP_openGate(void);
void APP_timer1TickProccessing1(void);
void APP_timer1TickProccessing2(void);
void APP_timer1TickProccessing3(void);

int main(void)
{
	Buzzer_init();
	UART_ConfigType UART_Config={UART_8_Bit,No_Partiy,Stop_OneBit,UART_Rate_9600};
	UART_init(&UART_Config);
	uint8 state=0;
	while(1)
	{
		switch(state)
		{
		case 0:
		{
			state=APP_readFirstPass();
			break;
		}
		case 1:
		{
			state=APP_readSecondPass();
			break;
		}
		case 2:
		{
			state=APP_comparePasses();
			break;
		}
		case 3:
		{
			state=APP_takeOption();
			break;
		}
		};


	}
	return 0;
}

uint8 APP_readFirstPass(void)
{
	uint8 i=0;
	while(i<5)
	{
		g_key1[i]=UART_recieveByte();
		i++;
	}
	return 1;
}

uint8 APP_readSecondPass(void)
{
	uint8 i=0;
	while(i<5)
	{
		g_key2[i]=UART_recieveByte();
		i++;
	}
	return 2;
}

uint8 APP_comparePasses(void)
{
	uint8 i;
	for(i=0;i<5;i++)
	{
		if(g_key1[i]!=g_key2[i])
		{
			UART_sendByte('0');
			return 0;
		}
	}
	UART_sendByte('2');
	for(i=0;i<5;i++)
	{
		EEPROM_writeByte(PASS_ADDRESS+i,g_key1[i]);
		_delay_ms(10);
	}

	return 3;
}

uint8 APP_takeOption(void)
{
	uint8 option,ver;
	option = UART_recieveByte();

	if(option=='e')
	{
		APP_alarm();
		UART_sendByte('o');
		return 3;
	}

	ver=APP_verifyPass();

	if(ver==0)
	{
		g_lastOption=option;
		UART_sendByte('5');
		return 3;
	}
	if(option=='r')
	{
		//UART_sendByte('k');
		option=g_lastOption;

	}

	if(option=='g')
	{
		g_lastOption=option;
		UART_sendByte('G');
		APP_openGate();
		return 3;
	}
	else if(option=='p')
	{
		g_lastOption=option;
		UART_sendByte('0');
		return 0;
	}
}

uint8 APP_verifyPass(void)
{
	uint8 i;
	APP_readFirstPass();
	uint8 val=0;
	for(i=0;i<5;i++)
	{
		EEPROM_readByte(PASS_ADDRESS+i,&val);
		_delay_ms(10);
		if(val!=g_key1[i])return 0;
	}
	return 1;
}

void APP_openGate(void)
{
	DcMotor_Init();
	Timer1_setCallBack(&APP_timer1TickProccessing1);
	Timer1_ConfigType Timer1_Config={TIMER1_DEFAULT_INITIAL,TIMER1_NOT_COMPARE,Prescaler_64,Timer1_Normal_Mode};
	DcMotor_Rotate(CW,Fourth_Speed);
	Timer1_init(&Timer1_Config);
	while(!g_time);
	g_time=0;
	DcMotor_Rotate(Stop,Fourth_Speed);
	Timer1_setCallBack(&APP_timer1TickProccessing2);
	while(!g_time);
	g_time=0;
	DcMotor_Rotate(A_CW,Fourth_Speed);
	Timer1_setCallBack(&APP_timer1TickProccessing1);
	while(!g_time);
	g_time=0;
	DcMotor_Rotate(Stop,Fourth_Speed);
	Timer1_deInit();
}


void APP_timer1TickProccessing1(void)
{
	static uint8 count=0;
	if(count==29)
	{
		g_time=1;
		count=0;
		return;
	}
	count++;
}

void APP_timer1TickProccessing2(void)
{
	static uint8 count=0;
	if(count==6)
	{
		g_time=1;
		count=0;
		return;
	}
	count++;
}

void APP_alarm(void)
{
	Buzzer_on();
	DcMotor_Init();
	Timer1_setCallBack(&APP_timer1TickProccessing3);
	Timer1_ConfigType Timer1_Config={TIMER1_DEFAULT_INITIAL,TIMER1_NOT_COMPARE,Prescaler_64,Timer1_Normal_Mode};
	Timer1_init(&Timer1_Config);
	while(!g_time);
	Timer1_deInit();
	g_time=0;
	Buzzer_off();
}

void APP_timer1TickProccessing3(void)
{
	static uint8 count=0;
	if(count==115)
	{
		g_time=1;
		count=0;
		return;
	}
	count++;
}
