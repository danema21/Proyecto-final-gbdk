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
Personaje enemigo;

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
    set_sprite_data(0, 64, sprites);

    //Jugador 16x16 //////////////////////////////////////
    jugador.posX = 30;
    jugador.posY = 86;
    jugador.ancho = 16;
    jugador.largo = 16;
    jugador.colisionXoffset = 3;
    jugador.colisionYoffset = 2;
    jugador.spriteIDs[0] = 0;
    jugador.spriteIDs[1] = 1;
    jugador.spriteIDs[2] = 2;
    jugador.spriteIDs[3] = 3;
    set_sprite_tile(0, jugador.spriteIDs[0]);
    set_sprite_prop(0, 0);
    move_sprite(0, jugador.posX, jugador.posY);
    set_sprite_tile(1, jugador.spriteIDs[1]);
    set_sprite_prop(1, 0);
    move_sprite(1, jugador.posX, jugador.posY + 8);
    set_sprite_tile(2, jugador.spriteIDs[2]);
    set_sprite_prop(2, 0);
    move_sprite(2, jugador.posX + 8, jugador.posY);
    set_sprite_tile(3, jugador.spriteIDs[3]);
    set_sprite_prop(3, 0);
    move_sprite(3, jugador.posX + 8, jugador.posY + 8);
    //////////////////////////////////////////////////////

    //Enemigo 32x32 //////////////////////////////////////
    enemigo.posX = 120;
    enemigo.posY = 70;
    enemigo.ancho = 32;
    enemigo.largo = 32;
    enemigo.colisionXoffset = 1;
    enemigo.colisionYoffset = 1;
    enemigo.spriteIDs[0] = 32;
    enemigo.spriteIDs[1] = 33;
    enemigo.spriteIDs[2] = 34;
    enemigo.spriteIDs[3] = 35;
    enemigo.spriteIDs[4] = 36;
    enemigo.spriteIDs[5] = 37;
    enemigo.spriteIDs[6] = 38;
    enemigo.spriteIDs[7] = 39;
    enemigo.spriteIDs[8] = 40;
    enemigo.spriteIDs[9] = 41;
    enemigo.spriteIDs[10] = 42;
    enemigo.spriteIDs[11] = 43;
    enemigo.spriteIDs[12] = 44;
    enemigo.spriteIDs[13] = 45;
    enemigo.spriteIDs[14] = 46;
    enemigo.spriteIDs[15] = 47;
    set_sprite_tile(4, enemigo.spriteIDs[0]);
    set_sprite_prop(4, 1);
    move_sprite(4, enemigo.posX, enemigo.posY);
    set_sprite_tile(5, enemigo.spriteIDs[1]);
    set_sprite_prop(5, 1);
    move_sprite(5, enemigo.posX, enemigo.posY + 8);
    set_sprite_tile(6, enemigo.spriteIDs[2]);
    set_sprite_prop(6, 1);
    move_sprite(6, enemigo.posX + 8, enemigo.posY);
    set_sprite_tile(7, enemigo.spriteIDs[3]);
    set_sprite_prop(7, 1);
    move_sprite(7, enemigo.posX + 8, enemigo.posY + 8);
    
    set_sprite_tile(8, enemigo.spriteIDs[4]);
    set_sprite_prop(8, 1);
    move_sprite(8, enemigo.posX, enemigo.posY + 16);
    set_sprite_tile(9, enemigo.spriteIDs[5]);
    set_sprite_prop(9, 1);
    move_sprite(9, enemigo.posX, enemigo.posY + 24);
    set_sprite_tile(10, enemigo.spriteIDs[6]);
    set_sprite_prop(10, 1);
    move_sprite(10, enemigo.posX + 8, enemigo.posY + 16);
    set_sprite_tile(11, enemigo.spriteIDs[7]);
    set_sprite_prop(11, 1);
    move_sprite(11, enemigo.posX + 8, enemigo.posY + 24);

    set_sprite_tile(12, enemigo.spriteIDs[8]);
    set_sprite_prop(12, 1);
    move_sprite(12, enemigo.posX + 16, enemigo.posY);
    set_sprite_tile(13, enemigo.spriteIDs[9]);
    set_sprite_prop(13, 1);
    move_sprite(13, enemigo.posX + 16, enemigo.posY + 8);
    set_sprite_tile(14, enemigo.spriteIDs[10]);
    set_sprite_prop(14, 1);
    move_sprite(14, enemigo.posX + 24, enemigo.posY);
    set_sprite_tile(15, enemigo.spriteIDs[11]);
    set_sprite_prop(15, 1);
    move_sprite(15, enemigo.posX + 24, enemigo.posY + 8);

    set_sprite_tile(16, enemigo.spriteIDs[12]);
    set_sprite_prop(16, 1);
    move_sprite(16, enemigo.posX + 16, enemigo.posY + 16);
    set_sprite_tile(17, enemigo.spriteIDs[13]);
    set_sprite_prop(17, 1);
    move_sprite(17, enemigo.posX + 16, enemigo.posY + 24);
    set_sprite_tile(18, enemigo.spriteIDs[14]);
    set_sprite_prop(18, 1);
    move_sprite(18, enemigo.posX + 24, enemigo.posY + 16);
    set_sprite_tile(19, enemigo.spriteIDs[15]);
    set_sprite_prop(19, 1);
    move_sprite(19, enemigo.posX + 24, enemigo.posY + 24);
    ///////////////////////////////////////////////////////
}

void moveGameCharacter(Personaje* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteIDs[0], x, y);
    move_sprite(character->spriteIDs[1], x, y + 8);
    move_sprite(character->spriteIDs[2], x + 8, y);
    move_sprite(character->spriteIDs[3], x + 8, y + 8);
}

void checkInput(){
    switch (joypad()){
        case J_RIGHT:
            jugador.posX += 1;
            moveGameCharacter(&jugador, jugador.posX, jugador.posY);
            break;
    }
}