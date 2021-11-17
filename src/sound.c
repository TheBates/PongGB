#include "sound.h"

void PaddleHitSound(uint8_t paddle)
{
    if(paddle == 1)
    {
        NR10_REG = 0x70;
        NR11_REG = 0x80;
        NR12_REG = 0x90;
        NR13_REG = 0x86;
        NR14_REG = 0x86;
    }
    else
    {
        NR10_REG = 0x70;
        NR11_REG = 0x80;
        NR12_REG = 0x90;
        NR13_REG = 0x22;
        NR14_REG = 0x86;
    }
}

void ScoreSound()
{
    NR10_REG = 0x0B;
    NR11_REG = 0x83;
    NR12_REG = 0xF4;
    NR13_REG = 0xAE;
    NR14_REG = 0x86;
}
