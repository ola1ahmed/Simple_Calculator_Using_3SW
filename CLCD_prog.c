
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"
#include "ErrorState.h"

#if CLCD_u8BIT_MODE==FOUR_MODE
static void voidSetHalfDataPort(uint8 Copy_u8Data){
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(Copy_u8Data,3));
	
	

}
#endif

static void voidSendEnablePulse(void){
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN, DIO_u8PIN_LOW);

}

void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin to low for writing*/
#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
#endif
	/*Send the command & enable pulse */
#if CLCD_u8BIT_MODE==EIGHT_MODE
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Cmd);
	voidSendEnablePulse();

#elif CLCD_u8BIT_MODE==FOUR_MODE
	/*Send the higher 4 bit in command*/
	voidSetHalfDataPort(Copy_u8Cmd>>4);
	/*Send enable pulse*/
	voidSendEnablePulse();
	/*Send the lower 4 bit in command*/
	voidSetHalfDataPort(Copy_u8Cmd);
	/*Send enable pulse*/
	voidSendEnablePulse();
#else
#error wrong CLCD_u8BIT_MODE configuration option
#endif
}

void CLCD_voidSendData(uint8 Copy_u8Data)
{
	/*Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_HIGH);

#if CLCD_u8RW_CONN_STS == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
#endif

	/*Send the data*/
#if CLCD_u8BIT_MODE==EIGHT_MODE
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Data);
	voidSendEnablePulse();

#elif CLCD_u8BIT_MODE==FOUR_MODE
	/*Send the higher 4 bit in command*/
	voidSetHalfDataPort(Copy_u8Data>>4);
	/*Send enable pulse*/
	voidSendEnablePulse();
	/*Send the lower 4 bit in command*/
	voidSetHalfDataPort(Copy_u8Data);
	/*Send enable pulse*/
	voidSendEnablePulse();
#else
#error wrong CLCD_u8BIT_MODE configuration option
#endif
}

void CLCD_voidInit(void)
{
	/*Wait for more than 30 ms after power on*/
	_delay_ms(40);

	/*Function set command: 2 lines, Font size: 5x7*/
#if CLCD_u8BIT_MODE==EIGHT_MODE
	CLCD_voidSendCmd(0b00111000);
#elif CLCD_u8BIT_MODE==FOUR_MODE
	voidSetHalfDataPort(0b0010);
	/*Send enable pulse*/
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	/*Send enable pulse*/
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	/*Send enable pulse*/
	voidSendEnablePulse();
#else
#error wrong CLCD_u8BIT_MODE configuration option
#endif
	/*Display on off control : Display on, cursor off, blink cursor off*/
	CLCD_voidSendCmd(0b00001100);

	/*Clear display*/
	CLCD_voidSendCmd(1);
	
}
uint8 CLCD_u8SendString(const char* Copy_u8PchString){
	uint8 Local_ErrorState=NOK;
	uint8 Local_u8counter;
	if(Copy_u8PchString!=NULL)
	{
		for(Local_u8counter=0 ; Copy_u8PchString[Local_u8counter]!='\0' ; Local_u8counter++ )
		{
			CLCD_voidSendData(Copy_u8PchString[Local_u8counter]);
		}
		Local_ErrorState=OK;

	}
	else
	{
		Local_ErrorState=NULL_PTR;
	}

	return Local_ErrorState;
}
sint32 CLCD_u8SendNumber(sint32 Copy_s32number)
{
	char Local_chNumber[10];
	uint8 Local_u8reminder,Local_u8counter1=0;
	sint8 Local_u8counter2;
	if(Copy_s32number==0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		if(Copy_s32number<0)
		{
			Copy_s32number=Copy_s32number*-1;
			CLCD_voidSendData('-');

		}
		while(Copy_s32number!=0)
		{
			Local_u8reminder=(uint8)((uint32)Copy_s32number%10);
			Copy_s32number=Copy_s32number/10;
			Local_chNumber[Local_u8counter1]=Local_u8reminder +'0';
			Local_u8counter1++;
		}
		for(Local_u8counter2=(sint8)Local_u8counter1-1;Local_u8counter2>=0;Local_u8counter2--)
		{


			CLCD_voidSendData(Local_chNumber[(uint8)Local_u8counter2]);
		}

	}

}

void voidGotoXY(uint8 Copy_u8Xposition,uint8 Copy_u8Yposition){
		uint8 Local_u8addressPos;
		if(Copy_u8Yposition==0u){
			Local_u8addressPos=Copy_u8Xposition;
		}
		else if(Copy_u8Yposition==1u)
		{
			Local_u8addressPos=0x40+Copy_u8Xposition;
		}
		/*set bit 7 for DDRAM address*/
		SET_BIT(Local_u8addressPos,7);
		/*Execute set DDRAM*/
		CLCD_voidSendCmd(Local_u8addressPos);


}
uint8 CLCD_u8SendSpecialChar(uint8 Copy_u8Location_num,uint8 *Copy_pu8Pattern ,uint8 Copy_u8Xposition,uint8 Copy_u8Yposition){
uint8 Local_ErrState=OK;

	if(Copy_pu8Pattern!=NULL)
	{
		uint8 Local_u8addressPos;
		uint8 Local_u8Counter;
		Local_u8addressPos=8*Copy_u8Location_num;
		/*set bit 6 for CGRAM address*/
		SET_BIT(Local_u8addressPos,6u);
		/*set ACGRAM Address*/
		CLCD_voidSendCmd(Local_u8addressPos);
		/*write input pattern inside CGRAM*/
		for(Local_u8Counter=0; Local_u8Counter<8u ;Local_u8Counter++)
		{
			CLCD_voidSendData(Local_u8Counter);
		}
		/*go to DDRAM*/
		voidGotoXY(Copy_u8Xposition,Copy_u8Yposition);
		/*Display the special pattern inside CGRAM*/
		CLCD_voidSendData(Copy_u8Location_num);
	}
	else
	{
		Local_ErrState=NULL_PTR;
	}
	return Local_ErrState;
}
