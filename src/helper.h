#ifndef HELPER_H_
#define HELPER_H_

#include <gbdk/console.h>
#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef enum  {
    BUTTON_RELEASE = 0,
    BUTTON_PRESS = 1,
    BUTTON_IDLE = 2,
    BUTTON_HELD = 3
} ButtonState;

typedef struct {
    uint8_t code;
    uint8_t ticks;
    ButtonState state;
} DebouncedButton;

void HardwareInit();
void PrintAt(uint8_t x, uint8_t y, const char* str);
void ClearText(uint8_t x, uint8_t y, const char* str);
void WaitForButton(uint8_t button);
ButtonState DebounceButton(DebouncedButton* button);

#endif