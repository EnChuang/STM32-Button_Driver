#include	"main.h"
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
	*	CCE 20231207
	*	Button_Driver v1
	*	
  ******************************************************************************
  */
void bsp_Init(void)
{
	Button_Inital();
	BLE_ON;
	RST_ON;
	ACTIVE_OFF;
}


void bsp_RunPer10ms(void)
{
    Button_Process();
}

void bsp_RunPer1ms(void)
{
	
}

void bsp_Idle(void)
{
	
}


