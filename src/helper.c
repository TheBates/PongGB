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
