#include "helper.h"

void HardwareInit()
{
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4;
    SHOW_BKG; SHOW_SPRITES;
}

void PrintAt(uint8_t x, uint8_t y, char* str)
{
    gotoxy(x,y);
    puts(str);
}

void ClearText(uint8_t x, uint8_t y, char* str)
{
    int i;
    gotoxy(x,y);

    for(i = 0; i < strlen(str); i++)
    {
        putchar(' ');
    }
}

void WaitForButton(uint8_t button)
{
    uint8_t buttons = 0;
    while (!(buttons & button))
    {
        buttons = joypad();
        wait_vbl_done();
    }
}

ButtonState DebounceButton(uint8_t button, uint8_t* ticks, ButtonState* lastState)
{
    const uint8_t pressThres = 3;
    const uint8_t releaseThres = 1;
    uint8_t curTicks = (*ticks);

    ButtonState state = BUTTON_IDLE;
    uint8_t buttons = joypad();
    uint8_t buttonDown = (buttons & button);

    if(buttonDown && (curTicks < pressThres))
    {
        curTicks++;
    }
    else if((!buttonDown) && (curTicks > 0))
    {
        curTicks--;
    }

    if(curTicks >= pressThres)
    {
        if((*lastState) == BUTTON_IDLE)
        {
            state = BUTTON_PRESS;
        }
        else
        {
            state = BUTTON_HELD;
        }
    }
    else if(curTicks <= releaseThres)
    {
        if((*lastState) == BUTTON_PRESS)
        {
            state = BUTTON_RELEASE;
        }
        else
        {
            state = BUTTON_IDLE;
        }
    }

    *ticks = curTicks;
    *lastState = state;

    return state;
}
