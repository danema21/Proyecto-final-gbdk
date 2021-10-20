#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "sprites/Sprites.h"
#include "sprites/StartscreenData.h"
#include "tilemaps/StartscreenMap.h"

#include "entidades/Personaje.c"

const UWORD backgroundPalletes[] = {
    startscreenDataCGBPal0c0,
    startscreenDataCGBPal0c1,
    startscreenDataCGBPal0c2,
    startscreenDataCGBPal0c3
};

const UWORD spritePalletes[] = {
    spritesCGBPal0c0,
    spritesCGBPal0c1,
    spritesCGBPal0c2,
    spritesCGBPal0c3,

    spritesCGBPal1c0,
    spritesCGBPal1c1,
    spritesCGBPal1c2,
    spritesCGBPal1c3
};

Personaje jugador;

void performanDelay(UINT8);
void initMenuBackground();
void initSprites();
void checkInput();
void moveGameCharacter(Personaje* character, UINT8 x, UINT8 y);


void main(){
    SPRITES_8x8;
    initMenuBackground();
    initSprites();

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while(1){
        checkInput();
        performanDelay(3);
    }
}



void performanDelay(UINT8 numloops){
    UINT8 i;
    for(i=0; i<numloops; i++){
        wait_vbl_done();
    }
}

void initMenuBackground(){
    set_bkg_palette(0, 1, &backgroundPalletes[0]);
    set_bkg_data(0, 19, startscreenData);

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, startscreenMapPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, startscreenMapPLN0);
}

void initSprites(){
    set_sprite_palette(0, 2, &spritePalletes[0]);
    set_sprite_data(0, 4, sprites);

    jugador.posX = 40;
    jugador.posY = 128;
    jugador.ancho = 8;
    jugador.largo = 16;
    jugador.spriteIDs[0] = 0;
    jugador.spriteIDs[1] = 1;

    set_sprite_tile(0, 0);
    set_sprite_prop(0, 0);
    move_sprite(0, jugador.posX, jugador.posY);

    set_sprite_tile(1, 1);
    set_sprite_prop(1, 1);
    move_sprite(1, jugador.posX, jugador.posY + 8);
}

void moveGameCharacter(Personaje* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteIDs[0], x, y);
    move_sprite(character->spriteIDs[1], x, y + 8);
}

void checkInput(){
    switch (joypad()){
        case J_RIGHT:
            jugador.posX += 1;
            moveGameCharacter(&jugador, jugador.posX, jugador.posY);
            break;
    }
}