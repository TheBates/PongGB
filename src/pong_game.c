#include "pong_game.h"

const uint8_t P1_START_X = 16;
const uint8_t P2_START_X = 152;
const uint8_t P_START_Y  = 64;
const uint8_t P_MAX_Y    = 124;
const uint8_t P_MIN_Y    = 28;

const uint8_t B_START_X     = 84;
const uint8_t B_START_Y     = 72;
const uint8_t B_START_SPEED = 1;
const uint8_t B_MAX_SPEED   = 10;

const uint8_t GAME_MAX_SCORE  = 10;

void InitGame(PongState* state, uint8_t resetScore)
{
    state->p1.x   = P1_START_X;
    state->p1.y   = P_START_Y;

    state->p2.x   = P2_START_X;
    state->p2.y   = P_START_Y;

    state->ball.x = B_START_X;
    state->ball.y = B_START_Y;

    state->ball.speedX = (GetRandom() % 2) ? B_START_SPEED : -B_START_SPEED;
    state->ball.speedY = (GetRandom() % 2) ? B_START_SPEED : -B_START_SPEED;

    state->pauseBtn.code  = J_START;
    state->pauseBtn.ticks = 0;
    state->pauseBtn.state = BUTTON_IDLE;

    state->paused = 0;

    if(resetScore)
    {
        state->p1.score = 0;
        state->p2.score = 0;
        state->done = 0;
    }
}

void UpdateInput(PongState* state, uint8_t input)
{
    state->input = input;

    if(DebounceButton(&state->pauseBtn) == BUTTON_PRESS)
    {
        state->paused = !state->paused;
    }
}

void UpdatePaddles(PongState* state)
{
    UpdatePaddleP1(state);
    UpdatePaddleP2(state);
}

void UpdatePaddleP1(PongState* state)
{
    if(state->input & J_UP)
    {
        state->p1.y -= 2;
        if(state->p1.y < P_MIN_Y)
        {
            state->p1.y = P_MIN_Y;
        }
    }
    else if(state->input & J_DOWN)
    {
        state->p1.y += 2;
        if(state->p1.y > P_MAX_Y)
        {
            state->p1.y = P_MAX_Y;
        }
    }
}

void UpdatePaddleP2(PongState* state)
{
    int8_t distY = (int8_t) (state->p2.y - state->ball.y);
    int8_t distX = (int8_t) (state->p2.x - state->ball.x);
    int8_t moveThres = distX / 10;

    if(distY > -moveThres)
    {
        state->p2.y -= 2;
        if(state->p2.y < P_MIN_Y)
        {
            state->p2.y = P_MIN_Y;
        }
    }

    if(distY < moveThres)
    {
        state->p2.y += 2;
        if(state->p2.y > P_MAX_Y)
        {
            state->p2.y = P_MAX_Y;
        }
    }
}

uint8_t UpdateBall(PongState* state)
{
    uint8_t hitPaddle = 0;

    state->ball.x += state->ball.speedX;
    state->ball.y += state->ball.speedY;

    // Check for bounce on top/bottom of screen
    if( (state->ball.y < P_MIN_Y) ||
        (state->ball.y > (P_MAX_Y + 24)))
    {
        state->ball.speedY = -state->ball.speedY;
    }

    // Check for bounce from paddles
    if(state->ball.x < (P1_START_X + 8))
    {
        if( (state->ball.y > state->p1.y) &&
            (state->ball.y < (state->p1.y + 24)) &&
            (state->ball.speedX < 0))
        {
            state->ball.speedX = -state->ball.speedX;
            hitPaddle = 1;
        }
    }
    else if(state->ball.x > (P2_START_X - 8))
    {
        if( (state->ball.y > state->p2.y) &&
            (state->ball.y < (state->p2.y + 24)) &&
            (state->ball.speedX > 0))
        {
            state->ball.speedX = -state->ball.speedX;
            hitPaddle = 2;
        }
    }

    return hitPaddle;
}

uint8_t UpdateScore(PongState* state)
{
    uint8_t goal = 0;

    if(state->ball.x < state->p1.x)
    {
        state->p2.score++;
        state->done = (state->p2.score >= GAME_MAX_SCORE) ? 1 : 0;
        goal = 1;
    }
    else if(state->ball.x > state->p2.x)
    {
        state->p1.score++;
        goal = 1;
    }

    if(goal)
    {
        state->done = ( (state->p1.score >= GAME_MAX_SCORE) ||
                        (state->p2.score >= GAME_MAX_SCORE));
    }

    return goal;
}