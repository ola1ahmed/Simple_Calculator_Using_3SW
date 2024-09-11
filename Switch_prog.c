#include "ErrorState.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Switch_interface.h"



uint8 Switch_u8GetState(const Switch_config_t *Copy_pu8Switchcfg ,Switch_State_t *Copy_pu8state){
	uint8 Local_u8Err_State=OK;
	uint8 Local_u8Get_State=OK;
	if((Copy_pu8Switchcfg!=NULL) && (Copy_pu8state!=NULL))
	{
		Local_u8Err_State=DIO_u8ReadPinValue(Copy_pu8Switchcfg->Switch_u8port,Copy_pu8Switchcfg->Switch_u8pin,&Local_u8Get_State);

			if(Copy_pu8Switchcfg->Switch_PullType== Pull_up)
			{
				if(Local_u8Get_State==DIO_u8PIN_HIGH)
				{
					*Copy_pu8state=Switch_Released ;
				}
				else
				{
					*Copy_pu8state=Switch_pressed;
				}
			}
			else if(Copy_pu8Switchcfg->Switch_PullType== Pull_down )
			{
				if(Local_u8Get_State==DIO_u8PIN_HIGH)
				{
					*Copy_pu8state=Switch_pressed ;
				}
				else
				{
					*Copy_pu8state=Switch_Released;
				}
			}
		else
		{
			Local_u8Err_State=NOK;
		}
	}
	else
	{
		Local_u8Err_State=NULL_PTR;
	}

	return Local_u8Err_State;
}/*
uint8 Switch_Init(const Switch_config_t *Copy_pu8Switchcfg ){

	uint8 Local_u8Err_State=OK;
	uint8 Local_u8Iterator =0;

	if(Copy_pu8Switchcfg!=NULL)
	{
		for (Local_u8Iterator=0; Local_u8Iterator < SW_NUM ; Local_u8Iterator++)
		{
			if ((Copy_pu8Switchcfg[Local_u8Iterator].Switch_u8pin) <= DIO_u8PIN7)
			{
				DIO_u8SetPinDirection(Copy_pu8Switchcfg[Local_u8Iterator].Switch_u8port,Copy_pu8Switchcfg[Local_u8Iterator].Switch_u8pin,DIO_u8PIN_INPUT);
				if(Copy_pu8Switchcfg[Local_u8Iterator].Switch_PullType==Pull_up)
				{

					DIO_u8SetPinValue(Copy_pu8Switchcfg[Local_u8Iterator].Switch_u8port,Copy_pu8Switchcfg[Local_u8Iterator].Switch_u8pin,DIO_u8PIN_HIGH);
				}

			}
			else
			{
				Local_u8Err_State=NOK;
				break;
			}
		}
	}
	else
	{
		Local_u8Err_State=NULL_PTR;
	}

	return Local_u8Err_State;


}*/
