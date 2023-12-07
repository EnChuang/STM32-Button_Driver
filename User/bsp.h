#ifndef BSP_H
#define BSP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "math.h"

#include	"button.h"

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

void bsp_Init(void);
void bsp_Idle(void);
void bsp_RunPer10ms(void);
void bsp_RunPer1ms(void);

#endif
