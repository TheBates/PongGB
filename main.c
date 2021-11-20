#include "helper.h"
#include "draw.h"
#include "sound.h"

const char* scoreFormat = "%d      %d";
const char* serveText = "Press 'A' to Serve!";

void ShowTitleScreen()
{
    PrintAt(0, 0, "Pong");
    PrintAt(0, 2, "Press Start");
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
    char buf[32];
    sprintf(buf, scoreFormat, state->p1.score, state->p2.score);
    PrintAt(6, 2, buf);
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
