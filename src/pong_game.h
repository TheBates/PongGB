#ifndef PONG_GAME_H_
#define PONG_GAME_H_

#include <stdint.h>
#include <gb/gb.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t score;
} PongPaddle;

typedef struct {
    uint8_t x;
    uint8_t y;
    int8_t speedX;
    int8_t speedY;
} PongBall;

typedef struct {
    PongPaddle p1;
    PongPaddle p2;
    PongBall ball;
    uint8_t input;
    uint8_t done;
} PongState;

void InitGame(PongState* state, uint8_t resetScore);
void UpdateInput(PongState* state, uint8_t input);
void UpdatePaddles(PongState* state);
void UpdatePaddleP1(PongState* state);
void UpdatePaddleP2(PongState* state);
uint8_t UpdateBall(PongState* state);
uint8_t UpdateScore(PongState* state);

#endif