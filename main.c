#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>

#include "sprites/Sprites.h"
#include "sprites/FondoData.h"
#include "tilemaps/FondoMap.h"

#include "entidades/Personaje.c"

const UWORD backgroundPalletes[] = {
    fondoDataCGBPal0c0,
    fondoDataCGBPal0c1,
    fondoDataCGBPal0c2,
    fondoDataCGBPal0c3
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
UINT8 animationDelay = 0;
UINT8 enemyAnimationDelay = 0;

void performanDelay(UINT8);
void initMenuBackground();
void initSprites();
void checkInput();
void moveGameCharacter(Personaje* character, UINT8 x, UINT8 y);
void animatePLayer(Personaje* character, UINT8 animationType);
void moveGameEnemy(Personaje* character, UINT8 x, UINT8 y);
void animateEnemy(Personaje* character, UINT8 animationType);

void main(){
    BYTE enemyDir = 1;
    SPRITES_8x8;
    initMenuBackground();
    initSprites();

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    
    while(1){
        checkInput();
        if(enemigo.posY >= 100){
            enemyDir = -4;
        }else if(enemigo.posY <= 70){
            enemyDir = 4;
        }
        enemyAnimationDelay++;
        if(enemyAnimationDelay == 0 || enemyAnimationDelay == 20){
            enemigo.posY += enemyDir;
        }
        animateEnemy(&enemigo, 1);
        moveGameEnemy(&enemigo, enemigo.posX, enemigo.posY);

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
    set_bkg_data(0, 15, fondoData);

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, fondoMapPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, fondoMapPLN0);
}

void initSprites(){
    set_sprite_palette(0, 2, &spritePalletes[0]);
    set_sprite_data(0, 64, sprites);

    //Jugador 16x16 (sprites de 0 a 3 son del jugador)////
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

    //Enemigo 32x32 (sprites de 4 a 19 son del enemigo)///
    enemigo.posX = 120;
    enemigo.posY = 70;
    enemigo.ancho = 32;
    enemigo.largo = 32;
    enemigo.colisionXoffset = 1;
    enemigo.colisionYoffset = 1;
    enemigo.spriteIDs[0] = 4;
    enemigo.spriteIDs[1] = 5;
    enemigo.spriteIDs[2] = 6;
    enemigo.spriteIDs[3] = 7;
    enemigo.spriteIDs[4] = 8;
    enemigo.spriteIDs[5] = 9;
    enemigo.spriteIDs[6] = 10;
    enemigo.spriteIDs[7] = 11;
    enemigo.spriteIDs[8] = 12;
    enemigo.spriteIDs[9] = 13;
    enemigo.spriteIDs[10] = 14;
    enemigo.spriteIDs[11] = 15;
    enemigo.spriteIDs[12] = 16;
    enemigo.spriteIDs[13] = 17;
    enemigo.spriteIDs[14] = 18;
    enemigo.spriteIDs[15] = 19;
    set_sprite_tile(4, 32);
    set_sprite_prop(4, 1);
    move_sprite(4, enemigo.posX, enemigo.posY);
    set_sprite_tile(5, 33);
    set_sprite_prop(5, 1);
    move_sprite(5, enemigo.posX, enemigo.posY + 8);
    set_sprite_tile(6, 34);
    set_sprite_prop(6, 1);
    move_sprite(6, enemigo.posX + 8, enemigo.posY);
    set_sprite_tile(7, 35);
    set_sprite_prop(7, 1);
    move_sprite(7, enemigo.posX + 8, enemigo.posY + 8);
    
    set_sprite_tile(8, 36);
    set_sprite_prop(8, 1);
    move_sprite(8, enemigo.posX, enemigo.posY + 16);
    set_sprite_tile(9, 37);
    set_sprite_prop(9, 1);
    move_sprite(9, enemigo.posX, enemigo.posY + 24);
    set_sprite_tile(10, 38);
    set_sprite_prop(10, 1);
    move_sprite(10, enemigo.posX + 8, enemigo.posY + 16);
    set_sprite_tile(11, 39);
    set_sprite_prop(11, 1);
    move_sprite(11, enemigo.posX + 8, enemigo.posY + 24);

    set_sprite_tile(12, 40);
    set_sprite_prop(12, 1);
    move_sprite(12, enemigo.posX + 16, enemigo.posY);
    set_sprite_tile(13, 41);
    set_sprite_prop(13, 1);
    move_sprite(13, enemigo.posX + 16, enemigo.posY + 8);
    set_sprite_tile(14, 42);
    set_sprite_prop(14, 1);
    move_sprite(14, enemigo.posX + 24, enemigo.posY);
    set_sprite_tile(15, 43);
    set_sprite_prop(15, 1);
    move_sprite(15, enemigo.posX + 24, enemigo.posY + 8);

    set_sprite_tile(16, 44);
    set_sprite_prop(16, 1);
    move_sprite(16, enemigo.posX + 16, enemigo.posY + 16);
    set_sprite_tile(17, 45);
    set_sprite_prop(17, 1);
    move_sprite(17, enemigo.posX + 16, enemigo.posY + 24);
    set_sprite_tile(18, 46);
    set_sprite_prop(18, 1);
    move_sprite(18, enemigo.posX + 24, enemigo.posY + 16);
    set_sprite_tile(19, 47);
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

void moveGameEnemy(Personaje* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteIDs[0], x, y);
    move_sprite(character->spriteIDs[1], x, y + 8);
    move_sprite(character->spriteIDs[2], x + 8, y);
    move_sprite(character->spriteIDs[3], x + 8, y + 8);

    move_sprite(character->spriteIDs[4], x, y + 16);
    move_sprite(character->spriteIDs[5], x, y + 24);
    move_sprite(character->spriteIDs[6], x + 8, y + 16);
    move_sprite(character->spriteIDs[7], x + 8, y + 24);

    move_sprite(character->spriteIDs[8], x + 16, y);
    move_sprite(character->spriteIDs[9], x + 16, y + 8);
    move_sprite(character->spriteIDs[10], x + 24, y);
    move_sprite(character->spriteIDs[11], x + 24, y + 8);

    move_sprite(character->spriteIDs[12], x + 16, y + 16);
    move_sprite(character->spriteIDs[13], x + 16, y + 24);
    move_sprite(character->spriteIDs[14], x + 24, y + 16);
    move_sprite(character->spriteIDs[15], x + 24, y + 24);
}

void animatePLayer(Personaje* character, UINT8 animationType){
    switch (animationType){
    case 1:
        if(animationDelay == 0){
            set_sprite_tile(character->spriteIDs[0], 4);
            set_sprite_tile(character->spriteIDs[1], 5);
            set_sprite_tile(character->spriteIDs[2], 6);
            set_sprite_tile(character->spriteIDs[3], 7);
        }else if(animationDelay == 5){
            set_sprite_tile(character->spriteIDs[0], 0);
            set_sprite_tile(character->spriteIDs[1], 1);
            set_sprite_tile(character->spriteIDs[2], 2);
            set_sprite_tile(character->spriteIDs[3], 3);
        }else if(animationDelay == 9){
            animationDelay = -1;
        }
        break;
    }
}

void animateEnemy(Personaje* character, UINT8 animationType){
    switch (animationType){
    case 1:
        if(enemyAnimationDelay == 0){
            set_sprite_tile(character->spriteIDs[0], 48);
            set_sprite_tile(character->spriteIDs[1], 49);
            set_sprite_tile(character->spriteIDs[2], 50);
            set_sprite_tile(character->spriteIDs[3], 51);

            set_sprite_tile(character->spriteIDs[4], 52);
            set_sprite_tile(character->spriteIDs[5], 53);
            set_sprite_tile(character->spriteIDs[6], 54);
            set_sprite_tile(character->spriteIDs[7], 55);

            set_sprite_tile(character->spriteIDs[8], 56);
            set_sprite_tile(character->spriteIDs[9], 57);
            set_sprite_tile(character->spriteIDs[10], 58);
            set_sprite_tile(character->spriteIDs[11], 59);

            set_sprite_tile(character->spriteIDs[12], 60);
            set_sprite_tile(character->spriteIDs[13], 61);
            set_sprite_tile(character->spriteIDs[14], 62);
            set_sprite_tile(character->spriteIDs[15], 63);
        }else if(enemyAnimationDelay == 20){
            set_sprite_tile(character->spriteIDs[0], 32);
            set_sprite_tile(character->spriteIDs[1], 33);
            set_sprite_tile(character->spriteIDs[2], 34);
            set_sprite_tile(character->spriteIDs[3], 35);

            set_sprite_tile(character->spriteIDs[4], 36);
            set_sprite_tile(character->spriteIDs[5], 37);
            set_sprite_tile(character->spriteIDs[6], 38);
            set_sprite_tile(character->spriteIDs[7], 39);

            set_sprite_tile(character->spriteIDs[8], 40);
            set_sprite_tile(character->spriteIDs[9], 41);
            set_sprite_tile(character->spriteIDs[10], 42);
            set_sprite_tile(character->spriteIDs[11], 43);

            set_sprite_tile(character->spriteIDs[12], 44);
            set_sprite_tile(character->spriteIDs[13], 45);
            set_sprite_tile(character->spriteIDs[14], 46);
            set_sprite_tile(character->spriteIDs[15], 47);
        }else if(enemyAnimationDelay == 39){
            enemyAnimationDelay = -1;
        }
        break;
    }
}

void checkInput(){
    if(joypad() & J_RIGHT){
        jugador.posX += 1;
        moveGameCharacter(&jugador, jugador.posX, jugador.posY);
        animatePLayer(&jugador, 1);
        animationDelay++;
    }
    if(joypad() & J_LEFT){
        jugador.posX -= 1;
        moveGameCharacter(&jugador, jugador.posX, jugador.posY);
        animatePLayer(&jugador, 1);
        animationDelay++;
    }
    if(joypad() & J_UP){
        jugador.posY -= 1;
        moveGameCharacter(&jugador, jugador.posX, jugador.posY);
        animatePLayer(&jugador, 1);
        animationDelay++;
    }
    if(joypad() & J_DOWN){
        jugador.posY += 1;
        moveGameCharacter(&jugador, jugador.posX, jugador.posY);
        animatePLayer(&jugador, 1);
        animationDelay++;
    }
}