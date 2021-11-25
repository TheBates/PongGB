#include "helper.h"
#include "draw.h"
#include "sound.h"

const char* serveText = "Press 'A'";

void ShowTitleScreen()
{
    PrintAt(0, 14, "Press Start");
    InitLogo();
    WaitForButton(J_START);
}

void ServePrompt()
{
    PrintAt(0, 14, serveText);
    WaitForButton(J_A);
    ClearText(0, 14, serveText);
}

void DrawScore(PongState* state)
{
    char bufP1[16];
    char bufP2[16];
    sprintf(bufP1, "%d", state->p1.score);
    sprintf(bufP2, "%d", state->p2.score);
    PrintAt(6, 2, bufP1);
    PrintAt(13, 2, bufP2);
}

void main(void)
{
    PongState state;
    uint8_t hit = 0;
    uint8_t scored = 0;
    uint8_t reset = 1;
    uint8_t buttons;

    InitSprites();
    HardwareInit();
    ShowTitleScreen();

    cls();
    InitBackground();

    while(1)
    {
		// Game main loop processing goes here
        InitGame(&state, reset);
        UpdateSprites(&state);
        DrawScore(&state);
        ServePrompt();

        reset = 0;
        scored = 0;

        while(!scored)
        {
            buttons = joypad();
            UpdateInput(&state, buttons);

            if(!state.paused)
            {
                UpdatePaddles(&state);
                hit = UpdateBall(&state);

                if(!hit)
                {
                    scored = UpdateScore(&state);
                }
                else
                {
                    PaddleHitSound(hit);
                }

                UpdateSprites(&state);
            }

            // Done processing, yield CPU and wait for start of next frame
            wait_vbl_done();
        }

        ScoreSound();
        reset = state.done;
    }
}
