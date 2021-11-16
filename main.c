#include "helper.h"
#include "draw.h"

void ShowTitleScreen()
{
    PrintAt(0, 0, "Pong");
    PrintAt(0, 2, "Press Start");
    WaitForButton(J_START);
}

void ServePrompt()
{
    PrintAt(0, 0, "'A' to Serve!");
    WaitForButton(J_A);
    ClearText(0, 0, "'A' to Serve!");
}

void main(void)
{
    PongState state;
    uint8_t hit = 0;
    uint8_t scored = 0;
    uint8_t reset = 1;

    InitSprites();
    HardwareInit();
    ShowTitleScreen();

    cls();

    while(1)
    {

		// Game main loop processing goes here
        InitGame(&state, reset);
        UpdateSprites(&state);
        ServePrompt();
        reset = 0;
        scored = 0;

        while(!scored)
        {
            UpdateInput(&state, joypad());
            UpdatePaddles(&state);
            hit = UpdateBall(&state);

            if(!hit)
            {
                scored = UpdateScore(&state);
            }
            else
            {
                //
            }

            UpdateSprites(&state);

            // Done processing, yield CPU and wait for start of next frame
            wait_vbl_done();
        }

        reset = state.done;
    }
}
