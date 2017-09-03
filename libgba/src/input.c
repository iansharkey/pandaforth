//---------------------------------------------------------------------------------
#include "gba_input.h"
//---------------------------------------------------------------------------------
typedef struct{
	u16 Up,
		Down,
		Held,
		Last;
	}__attribute__ ((packed)) KeyInput;

//---------------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------------
static KeyInput Keys = { 0,0,0.0 };

static u8 repeat = 30, count = 0;

//---------------------------------------------------------------------------------
void SetRepeat( int rpt)
//---------------------------------------------------------------------------------
{
	repeat = rpt;
}

//---------------------------------------------------------------------------------
void ScanKeys()
//---------------------------------------------------------------------------------
{
	Keys.Last = Keys.Held;
	Keys.Held = (REG_KEYINPUT & 0x03ff) ^ 0x03ff; // upper 6 bits clear on hw not emulated
	if ( (count++ > repeat) && (repeat != 0 ) )
	{
		Keys.Last = count = 0;
	}
	if ( Keys.Last != Keys.Held) count = 0;
}

//---------------------------------------------------------------------------------
u16	KeysDown()
//---------------------------------------------------------------------------------
{
	Keys.Down = Keys.Held & (Keys.Last ^ 0x03ff);

	return Keys.Down;
}

//---------------------------------------------------------------------------------
u16	KeysUp()
//---------------------------------------------------------------------------------
{
	Keys.Up = ((Keys.Held ^ 0x03ff) & Keys.Last);

	return Keys.Up;
}

//---------------------------------------------------------------------------------
u16	KeysHeld()
//---------------------------------------------------------------------------------
{
	return Keys.Held;
}

