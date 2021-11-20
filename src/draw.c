#include "draw.h"

const uint8_t SpriteData[] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

const  uint8_t NUM_PADDLES         = 2;
const  uint8_t PADDLE_SPRITE_PARTS = 3;
static uint8_t BALL_TILE_INDEX;

void InitSprites()
{
    BALL_TILE_INDEX = NUM_PADDLES + 1;

    set_sprite_data(0, 4, SpriteData);
    set_bkg_data(0x66, 3, PongTiles);

    InitPaddleSprites();
    InitBallSprite();
}

void InitLogo()
{
    set_bkg_tiles(  0,
                    0,
                    PongLogoWidth,
                    PongLogoHeight,
                    PongLogo);
}

void InitBackground()
{
    set_bkg_tiles(  0,
                    0,
                    PongBackgroundWidth,
                    PongBackgroundHeight,
                    PongBackground);
}

void InitPaddleSprites()
{
    int i;
    int j;

    for(i = 0; i < NUM_PADDLES; i++)
    {
        for(j = 0; j < PADDLE_SPRITE_PARTS; j++)
        {
            set_sprite_tile((i << 2) + j, i);
        }
    }
}

void InitBallSprite()
{
    set_sprite_tile(BALL_TILE_INDEX, 2);
}

void UpdateSprites(PongState* state)
{
    UpdatePaddleSprites(state);
    UpdateBallSprite(state);
}

void UpdatePaddleSprites(PongState* state)
{
    uint8_t i;
    uint8_t j;

    uint8_t x;
    uint8_t y;
    uint8_t originY;

    for(i = 0; i < NUM_PADDLES; i++)
    {
        x = (i == 0) ? state->p1.x : state->p2.x;
        originY = (i == 0) ? state->p1.y : state->p2.y;

        for(j = 0; j < PADDLE_SPRITE_PARTS; j++)
        {
            y = (j == 0) ? originY : originY  + (8 << (j - 1));
            move_sprite((i << 2) + j, x, y);
        }
    }
}

void UpdateBallSprite(PongState* state)
{
    move_sprite(BALL_TILE_INDEX, state->ball.x, state->ball.y);
}
