#ifndef DRAW_H_
#define DRAW_H_

#include <stdint.h>
#include <gb/gb.h>
#include "pong_game.h"

void InitSprites();
void InitPaddleSprites();
void InitBallSprite();
void UpdateSprites(PongState* state);
void UpdatePaddleSprites(PongState* state);
void UpdateBallSprite(PongState* state);

#endif