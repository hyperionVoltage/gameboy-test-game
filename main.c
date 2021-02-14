#include <gb/gb.h>
#include <stdio.h>
#include "bird_sprite.c"

void init();
void checkInput();
void update();
void updateBirdDirection();
void birdFlap();
UINT8 collisionCheck(UINT8, UINT8, UINT8, UINT8, UINT8, UINT8, UINT8, UINT8);

UINT8 birdPosY;
UINT8 birdSpeed;
UINT8 isFlapping;
UINT8 maxBirdDownFallSpeed;

void main()
{
    init();

    while (1)
    {
        wait_vbl_done();

        checkInput();

        update();
    }
}

void init()
{
    maxBirdDownFallSpeed = 1;
    isFlapping = 0;
    birdPosY = 50;
    birdSpeed = 0;

    DISPLAY_ON;      // Turn on the display
    NR52_REG = 0x8F; // Turn on the sound
    NR51_REG = 0x11; // Enable the sound channels
    NR50_REG = 0x77; // Increase the volume to its max

    SPRITES_8x8;
    set_sprite_data(0, 8, birdSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, birdPosY, 50);
    SHOW_SPRITES;
}

void checkInput()
{
    if (joypad() & J_A)
    {
        if (isFlapping == 0)
        {
            isFlapping = 1;
        }
    }
    else
    {
        isFlapping = 0;
    }
}

void update()
{
    move_sprite(0, 50, birdPosY);

    if (isFlapping == 0)
    {
        birdSpeed += 1;
        birdPosY += birdSpeed;
    }
    else
    {
        birdSpeed = 3;
        birdPosY -= birdSpeed;
    }

    if (birdSpeed > maxBirdDownFallSpeed)
    {
        birdSpeed = maxBirdDownFallSpeed;
    }
}