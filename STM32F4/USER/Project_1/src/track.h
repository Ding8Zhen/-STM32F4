#ifndef _TRACK_H_
#define _TRACK_H_

#include "stm32f4xx.h"
#include "systick.h"
#include "motor.h"

#define WHITE 0
#define BLACK 1

void track_init(void);
void find_way(void);
#endif