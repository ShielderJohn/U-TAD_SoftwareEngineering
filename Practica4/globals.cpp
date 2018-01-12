#include "stdafx.h"
#include "atmosphere.h"
#include "globals.h"


Atmosphere* atmosphere		= new Atmosphere(WORLD_WIDTH);
HANDLE	hConsole			= GetStdHandle(STD_OUTPUT_HANDLE);
char	input				= 0;