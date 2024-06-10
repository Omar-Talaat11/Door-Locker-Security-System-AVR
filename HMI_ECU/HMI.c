
#include "uart.h"
#include "keypad.h"
#include "lcd.h"
#include "util/delay.h"
#include "timer1.h"

uint32 g_time=0;
uint8 g_count=0;

void APP_timer1TickProccessing1(void);
void APP_timer1TickProccessing2(void);
void APP_timer1TickProccessing3(void);
uint8 APP_enterFirstPass(void);
uint8 APP_enterSecondPass(void);
uint8 APP_mainOptions(void);
uint8 APP_passVerify(void);
uint8 APP_wrongInput(void);
uint8 APP_gateOpening(void);
void APP_alarm(void);


int main(void)
{
	UART_ConfigType UART_Config={UART_8_Bit,No_Partiy,Stop_OneBit,UART_Rate_9600};
	UART_init(&UART_Config);
	LCD_init();
	uint8 step='0';

	while(1)
	{

		switch (step)
		{
		case '0': /* Step 1 take first password */
		{
			step=APP_enterFirstPass();
			break;
		}
		case '1': /* Step 1 take second password */
		{
			step=APP_enterSecondPass();
			break;
		}
		case '2': /* Step 2 main options menu */
		{
			g_count=0;
			step=APP_mainOptions();
			break;
		}
		case '3': /* Gate Open */
		{
			step=APP_passVerify();
			break;
		}
		case '4':/* Change Pass */
		{
			step=APP_passVerify();
			break;
		}
		case '5':
		{
			step=APP_wrongInput();
			break;
		}
		case 'G':
		{
			step=APP_gateOpening();
			break;
		}
		};
	}
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

void APP_timer1TickProccessing3(void)
{
	static uint8 count=0;
	LCD_moveCursor(1,14);
	if((uint8)(60-(count/1.9))<10)
	{
		LCD_displayCharacter('0');
	}
	LCD_intgerToString((uint8)(60-(count/1.9)));
	if(count==115)
	{
		g_time=1;
		count=0;
		return;
	}
	count++;
}

uint8 APP_enterFirstPass(void)
{
	uint8 key,i=0;
	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1,0);
	while(1)
	{
		key=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		if(i==4)
		{
			while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(key);
			return '1';
		}

		UART_sendByte(key);
		_delay_ms(500);
		i++;
	}

}

uint8 APP_enterSecondPass(void)
{
	uint8 key,i=0;
	LCD_clearScreen();
	LCD_displayString("Plz Re-Enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass: ");
	while(1)
	{
		key=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		if(i==4)
		{
			while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(key);
			return UART_recieveByte();
		}

		UART_sendByte(key);
		_delay_ms(500);
		i++;
	}

}

uint8 APP_mainOptions(void)
{
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
	key=KEYPAD_getPressedKey();
	_delay_ms(500);

	if(key=='+'){
		UART_sendByte('g');
		return '3';
	}
	else if(key=='-')
	{
		UART_sendByte('p');
		return '4';
	}
	else return '2';

}

uint8 APP_passVerify(void)
{
	uint8 key,i=0;

	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1,0);
	while(1)
	{
		key=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		if(i==4)
		{
			while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(key);
			return UART_recieveByte();
		}

		UART_sendByte(key);
		_delay_ms(500);
		i++;
	}
}

uint8 APP_wrongInput(void)
{
	if (g_count==2)
	{
		UART_sendByte('e');
		APP_alarm();
		while(UART_recieveByte()!='o');
		g_count=0;
		return '2';
	}
	g_count++;
	uint8 key,i=0;
	UART_sendByte('r');
	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1,0);
	while(1)
	{
		key=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		if(i==4)
		{
			while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(key);
			return UART_recieveByte();
		}

		UART_sendByte(key);
		_delay_ms(500);
		i++;
	}

	return UART_recieveByte();
}


uint8 APP_gateOpening(void)
{
	LCD_clearScreen();
	LCD_displayString("Door is Opening");
	Timer1_setCallBack(&APP_timer1TickProccessing1);
	Timer1_ConfigType Timer1_Config={TIMER1_DEFAULT_INITIAL,TIMER1_NOT_COMPARE,Prescaler_64,Timer1_Normal_Mode};
	Timer1_init(&Timer1_Config);
	while(!g_time);
	g_time=0;
	Timer1_setCallBack(&APP_timer1TickProccessing2);
	LCD_clearScreen();
	LCD_displayString("Door is Open");
	while(!g_time);
	g_time=0;
	Timer1_setCallBack(&APP_timer1TickProccessing1);
	LCD_clearScreen();
	LCD_displayString("Door is Closing");
	while(!g_time);
	g_time=0;
	Timer1_deInit();
	return '2';
}

void APP_alarm(void)
{
	LCD_clearScreen();
	LCD_displayString("WRONG PASSWORD");
	LCD_moveCursor(1,0);
	LCD_displayString("SYSTEM LOCKED ");
	Timer1_setCallBack(&APP_timer1TickProccessing3);
	Timer1_ConfigType Timer1_Config={TIMER1_DEFAULT_INITIAL,TIMER1_NOT_COMPARE,Prescaler_64,Timer1_Normal_Mode};
	Timer1_init(&Timer1_Config);
	while(!g_time);
	Timer1_deInit();
	g_time=0;
}
