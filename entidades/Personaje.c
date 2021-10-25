#include <gb/gb.h>

typedef struct Personaje{
    UINT8 posX;
    UINT8 posY;
    UINT8 colisionXoffset;
    UINT8 colisionYoffset;
    UINT8 ancho;
    UINT8 largo;
    UBYTE spriteIDs[16];
} Personaje;
