#ifndef HELPER_H_
#define HELPER_H_

#include <gbdk/console.h>
#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void HardwareInit();
void PrintAt(uint8_t x, uint8_t y, char* str);
void ClearText(uint8_t x, uint8_t y, char* str);
void WaitForButton(uint8_t button);

#endif