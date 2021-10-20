@REM make for using color sprites and backgrounds
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j  -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o main.gb main.o

@rem command to delete generated files, we wont need this
del *.lst *.o *.map *.sym

@REM command for executing the program
.\main.gb