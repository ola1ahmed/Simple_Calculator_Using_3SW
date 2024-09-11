#define FOUR_MODE 		1
#define EIGHT_MODE 		2

#define GND_CONNECTED 	1
#define DIO_CONNECTED 	1

#if CLCD_u8BIT_MODE==FOUR_MODE
static void voidSetHalfDataPort(uint8 Copy_u8Data);
#endif

static void voidSendEnablePulse(void);
