/*
 * main.c
 *
 *  Created on: Sep 2, 2024
 *      Author: olaah
 */
#include "DIO_interface.h"
#include "Switch_interface.h"
#include "CLCD_interface.h"

extern Switch_config_t SW_CONFIG_ARR[SW_NUM];
uint8 arrow[8]={
		0b00000000,0b00000000,
		0b00010000,0b00110000,
		0b01010100,0b00010000,
		0b00010000,0b00010000
};
uint8 Local_arr[]={'+','-','*','/'};
uint8 Local_arrowcounter=0;
uint8 Local_opercounter=0;
sint8 number1=0;
sint8 number2=0;
sint8 result=0;
uint8 remdresult=0;


void main()
{
/**/
	Switch_State_t Copy_pu8statesw1;
	Switch_State_t Copy_pu8statesw2;
	Switch_State_t Copy_pu8statesw3;


	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);

	DIO_u8SetPinDirection (DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTA, DIO_u8PIN3, DIO_u8PIN_OUTPUT);
	DIO_u8SetPortDirection (DIO_u8PORTB, DIO_u8PORT_OUTPUT) ;
	CLCD_voidInit();



		/*initial state*/
		voidGotoXY(0,0);
		CLCD_voidSendData(' ');
		voidGotoXY(1,0);
		CLCD_u8SendNumber(number1);
		voidGotoXY(2,0);
		CLCD_voidSendData(Local_arr[0]);
		voidGotoXY(3,0);
		CLCD_u8SendNumber(number2);
		voidGotoXY(4,0);
		CLCD_voidSendData('=');
		voidGotoXY(5,0);
		CLCD_u8SendNumber(result);
		CLCD_u8SendSpecialChar(0,&arrow,Local_arrowcounter,1);


	while(1)
	{
		//up switch
		Switch_u8GetState(&SW_CONFIG_ARR[0],&Copy_pu8statesw1);
		//down switch
		Switch_u8GetState(&SW_CONFIG_ARR[1],&Copy_pu8statesw2);
		//enter switch
	 	 Switch_u8GetState(&SW_CONFIG_ARR[2],&Copy_pu8statesw3);

			if(Copy_pu8statesw3==Switch_pressed)
			{
				Switch_u8GetState(&SW_CONFIG_ARR[2],&Copy_pu8statesw3);
				while(Copy_pu8statesw3==Switch_pressed)
				{
					Switch_u8GetState(&SW_CONFIG_ARR[2],&Copy_pu8statesw3);
				}
				Local_arrowcounter++;

					if(Local_arrowcounter==6)
					{

							voidGotoXY(Local_arrowcounter-1,1);
							CLCD_voidSendData(' ');
							Local_arrowcounter=0;
					}

					CLCD_u8SendSpecialChar(0,&arrow,Local_arrowcounter,1);

					if(Local_arrowcounter>0)
					{
						voidGotoXY(Local_arrowcounter-1,1);
						CLCD_voidSendData(' ');
					}
					if(Local_arrowcounter==5)
					{
						voidGotoXY(5,0);

						switch(Local_opercounter)
						{
						case 0:
							result=number1+number2;
							CLCD_u8SendNumber(result);
							CLCD_voidSendData('.');
							CLCD_u8SendNumber(remdresult);

							break;
						case 1:
							result=number1-number2;
							CLCD_u8SendNumber(result);
							CLCD_voidSendData('.');
							CLCD_u8SendNumber(remdresult);
							break;
						case 2:
							result=number1*number2;
							CLCD_u8SendNumber(result);
							CLCD_voidSendData('.');
							CLCD_u8SendNumber(remdresult);
							break;
						case 3:
							if(number2 !=0)
							{
								result=number1/number2;
								remdresult=number1%number2;
								CLCD_u8SendNumber(result);
								CLCD_voidSendData('.');
								CLCD_u8SendNumber(remdresult);

							}
							else
							{
								CLCD_u8SendString("!!");
							}
							break;
						}
					}

			}
			if( (Copy_pu8statesw1==Switch_pressed)&&(Local_arrowcounter!=0))
			{
				/*reinitialize result*/
				remdresult=0;
				voidGotoXY(5,0);
				CLCD_voidSendData(' ');
				voidGotoXY(6,0);
				CLCD_voidSendData(' ');
				voidGotoXY(7,0);
				CLCD_voidSendData(' ');
				voidGotoXY(8,0);
				CLCD_voidSendData(' ');

				Switch_u8GetState(&SW_CONFIG_ARR[0],&Copy_pu8statesw1);
				while(Copy_pu8statesw1==Switch_pressed)
				{
					Switch_u8GetState(&SW_CONFIG_ARR[0],&Copy_pu8statesw1);
				}

				switch(Local_arrowcounter)
				{
				case 1:
					number1++;
					if(number1==10)
					{
						number1=0;
					}

					voidGotoXY(1,0);
					CLCD_u8SendNumber(number1);
					break;
				case 2:
					Local_opercounter++;
					if(Local_opercounter==4)
					{
						Local_opercounter=0;
					}
					voidGotoXY(2,0);
					CLCD_voidSendData(Local_arr[Local_opercounter]);

					break;
				case 3:
					number2++;
					if(number2==10)
					{
						number2=0;
					}

					voidGotoXY(3,0);
					CLCD_u8SendNumber(number2);

					break;


				}


			}
			if( (Copy_pu8statesw2==Switch_pressed)&&(Local_arrowcounter!=0))
			{
				/*reinitialize result*/
				remdresult=0;
				voidGotoXY(5,0);
				CLCD_voidSendData(' ');
				voidGotoXY(6,0);
				CLCD_voidSendData(' ');
				voidGotoXY(7,0);
				CLCD_voidSendData(' ');
				voidGotoXY(8,0);
				CLCD_voidSendData(' ');

				Switch_u8GetState(&SW_CONFIG_ARR[1],&Copy_pu8statesw2);
				while(Copy_pu8statesw2==Switch_pressed)
				{
					Switch_u8GetState(&SW_CONFIG_ARR[1],&Copy_pu8statesw2);
				}

				switch(Local_arrowcounter)
				{
				case 1:
					number1--;
					if(number1==-1)
					{
						number1=9;
					}

					voidGotoXY(1,0);
					CLCD_u8SendNumber(number1);
					break;
				case 2:
					Local_opercounter--;
					if(Local_opercounter==255)
					{
						Local_opercounter=3;
					}
					voidGotoXY(2,0);
					CLCD_voidSendData(Local_arr[Local_opercounter]);

					break;
				case 3:
					number2--;
					if(number2==-1)
					{
						number2=9;
					}

					voidGotoXY(3,0);
					CLCD_u8SendNumber(number2);

					break;


				}


			}



	}
}
