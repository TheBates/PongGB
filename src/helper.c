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

ButtonState DebounceButton(DebouncedButton* button)
{
    const uint8_t pressThres = 3;
    const uint8_t releaseThres = 1;

    ButtonState state = BUTTON_IDLE;
    uint8_t buttons = joypad();
    uint8_t buttonDown = (buttons & button->code);

    if(buttonDown && (button->ticks < pressThres))
    {
        button->ticks++;
    }
    else if((!buttonDown) && (button->ticks > 0))
    {
        button->ticks--;
    }

    if(button->ticks >= pressThres)
    {
        if(button->state == BUTTON_IDLE)
        {
            state = BUTTON_PRESS;
        }
        else
        {
            state = BUTTON_HELD;
        }
    }
    else if(button->ticks <= releaseThres)
    {
        if(button->state == BUTTON_PRESS)
        {
            state = BUTTON_RELEASE;
        }
        else
        {
            state = BUTTON_IDLE;
        }
    }

    button->state = state;

    return state;
}
