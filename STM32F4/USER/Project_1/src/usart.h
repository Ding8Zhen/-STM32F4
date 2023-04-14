#ifndef __USART_H__
#define __USART_H__
#include "stm32f4xx.h"
#include <stdio.h>

void usart_init(void);
extern uint8_t recv_byte;
#endif