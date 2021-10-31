@REM make for using color sprites and backgrounds
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o FondoData.o sprites\FondoData.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o FondoMap.o tilemaps\FondoMap.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o Sprites.o sprites\Sprites.c 
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j  -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o main.gb FondoData.o FondoMap.o Sprites.o main.o

@rem command to delete generated files, we wont need this
del *.lst *.o *.map *.sym

@REM command for executing the program
.\main.gb