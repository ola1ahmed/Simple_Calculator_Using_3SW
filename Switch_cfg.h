#ifndef _SWITCH_CFG_H_
#define _SWITCH_CFG_H_

#include "STD_TYPES.h"
#include "Switch_prv.h"
#include "DIO_interface.h"

#define SW_NUM   3
typedef struct {

	uint8 Switch_u8port;
	uint8 Switch_u8pin;
	Switch_State_t Switch_PullType;

}Switch_config_t;


#endif
