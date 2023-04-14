#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f4xx.h"
#include "../SYSTEM/systick.h"

void motor_init(int n);
void motor_run(void);

static void Set_La(uint8_t value);
static void Set_Lb(uint8_t value);
static void Set_Ra(uint8_t value);
static void Set_Rb(uint8_t value);

void Go_Up(void);//前进
void Go_Right(void);//右转
void Go_Down(void);//后退
void Go_Left(void);//左转
void Stop(void);

#endif