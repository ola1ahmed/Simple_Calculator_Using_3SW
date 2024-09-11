#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#include "STD_TYPES.h"
void CLCD_voidSendCmd(uint8 Copy_u8Cmd);

void CLCD_voidSendData(uint8 Copy_u8Data);

void CLCD_voidInit(void);

uint8 CLCD_u8SendString(const char* Copy_u8PchString);
sint32 CLCD_u8SendNumber(sint32 Copy_s32number);
void voidGotoXY(uint8 Copy_u8Xposition,uint8 Copy_u8Yposition);
uint8 CLCD_u8SendSpecialChar(uint8 Copy_u8Location_num,uint8 *Copy_pu8Pattern ,uint8 Copy_u8Xposition,uint8 Copy_u8Yposition);

#endif
