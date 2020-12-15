#include "ST7920.h"

BusOut DB(D5, D6, D7, D8, D9, D10, D11, D12); // DB0 - DB7 RESPECTIVAMENTE
//BusOut DB(D12, D11, D10, D9, D8, D7, D6, D5); // DB7 - DB0 RESPECTIVAMENTE

DigitalOut RS(D2);
DigitalOut RW(D3);
DigitalOut EN(D4);


void ST7920_Init()
{
    //function set  8-bit mode
    wait_ms(100);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = FUNCTION_SET | DATA_LENGTH_DL;
    wait_us(100);
    EN = 0;

    //function set  8-bit mode again
    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = FUNCTION_SET | DATA_LENGTH_DL;
    wait_us(100);
    EN = 0;

    // display on
    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = DISPLAY_CONTROL | DISPLAY_ON_D;
    wait_us(100);
    EN = 0;

    // cursor - Display shift right by 1, cursor also follows to shift.
    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x1C;
    wait_us(100);
    EN = 0;

    // clear screen
    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = DISPLAY_CLEAR;
    wait_us(100);
    EN = 0;

    // Returns to home. Cursor moves to starting point
    wait_ms(1);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = RETURN_HOME;
    wait_us(100);
    EN = 0;

    // Setting location to write characters. In this case 0,0 - Top Left Corner
    wait_ms(1);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x80;
    wait_us(100);
    EN = 0;
}

void ST7920_Clear()
{
    //=========== This function set all the pixels to off in the graphic controller =================
    for(int y = 0; y < 64; y++) 
    {
        if(y < 32) 
        {
            wait_us(100);//wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80 | y;
            wait_us(100);
            EN = 0;
            wait_us(100);

            wait_us(100);//wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80;
            wait_us(100);
            EN = 0;
            wait_us(100);
        }

        else 
        {
            wait_us(100);//wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80 | (y - 32);
            wait_us(100);
            EN = 0;
            wait_us(100);

            wait_us(100);//wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x88;
            wait_us(100);
            EN = 0;
            wait_us(100);
        }

        for(int x = 0; x < 16; x++) 
        {
            wait_us(100);//wait_us(1000);
            RS = 1;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x00;
            wait_us(100);
            EN = 0;
            wait_us(20);
        }
    }
}

void ST7920_SetGraphicsMode()
{
    wait_us(1000);
    RS = 0;
    RW = 0;
    EN = 1;
    wait_us(100);
    DB = EXTENDED_FUNCTION_SET | DATA_LENGTH_DL;
    wait_us(100);
    EN = 0;

    wait_us(1000);
    RS = 0;
    RW = 0;
    EN = 1;
    wait_us(100);
    DB = EXTENDED_FUNCTION_SET | DATA_LENGTH_DL | EXTENDED_INSTRUCTION_RE;
    EN = 0;

    wait_us(100);
    RS = 0;
    RW = 0;
    EN = 1;
    wait_us(100);
    DB = EXTENDED_FUNCTION_SET | DATA_LENGTH_DL | EXTENDED_INSTRUCTION_RE | GRAPHIC_ON_G;
    EN = 0;
}

void ST7920_SetTextMode()
{
    wait_us(100);
    RS = 0;
    RW = 0;
    EN = 1;
    DB = FUNCTION_SET | DATA_LENGTH_DL;
    EN = 0;
}

void ST7920_DrawHorizontalLine(uint8_t X, uint8_t Y,  uint8_t LEN)
{
    //desenhando uma linha de tamanho T em Y, com X offset

    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x80 | Y;
    wait_us(100);
    EN = 0;
    wait_us(100);

    wait_us(1000);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x80 | X;
    wait_us(100);
    EN = 0;
    wait_us(100);

    for(int i = 0; i < (LEN / 8); i++) 
    {
        wait_us(1000);
        RS = 1;
        RW = 0;
        wait_us(100);
        EN = 1;
        DB = 255;
        wait_us(100);
        EN = 0;
        wait_us(20);
    }

    if(LEN%8 != 0) 
    {
        int LEN_rest = LEN - ((LEN / 8) * 8);
        int bus_rest;

        switch (LEN_rest) 
        {
            case 1:
                bus_rest = 0x80;
                break;
            case 2:
                bus_rest = 0xC0;
                break;
            case 3:
                bus_rest = 0xE0;
                break;
            case 4:
                bus_rest = 0xF0;
                break;
            case 5:
                bus_rest = 0xF8;
                break;
            case 6:
                bus_rest = 0xFC;
                break;
            case 7:
                bus_rest = 0xFE;
                break;
        }
        //pc.printf("%x\n\r",bus_rest);
        wait_us(1000);
        RS = 1;
        RW = 0;
        wait_us(100);
        EN = 1;
        DB = bus_rest; // tem que ser 254 no exemplo de T 255
        wait_us(100);
        EN = 0;
        wait_us(20);
    }
}

void ST7920_DrawVerticalLine(uint8_t X, uint8_t Y,  uint8_t LEN)
{
    wait_us(100);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x80 | Y;
    wait_us(100);
    EN = 0;
    wait_us(100);

    wait_us(100);
    RS = 0;
    RW = 0;
    wait_us(100);
    EN = 1;
    DB = 0x80 | X;
    wait_us(100);
    EN = 0;
    wait_us(100);

    for(int y = 0; y < LEN; y++) 
    {
        if(y < 32) {
            wait_us(100);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80 | y;
            wait_us(100);
            EN = 0;
            wait_us(100);

            wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80;
            wait_us(100);
            EN = 0;
            wait_us(100);
        }

        else 
        {
            wait_us(100);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x80 | (y - 32);
            wait_us(100);
            EN = 0;
            wait_us(100);

            wait_us(1000);
            RS = 0;
            RW = 0;
            wait_us(100);
            EN = 1;
            DB = 0x88;
            wait_us(100);
            EN = 0;
            wait_us(100);
        }

        wait_us(100);
        RS = 1;
        RW = 0;
        wait_us(100);
        EN = 1;
        DB = 0x80;
        wait_us(100);
        EN = 0;
        wait_us(20);
    }
}

void ST7920_DisplayString(int Row,int Column,unsigned char *ptr,int length)
{
    int i=0;

    switch (Row) 
    {
        case 0:
            Column|=0x80;
            break;
        case 1:
            Column|=0x90;
            break;
        case 2:
            Column|=0x88;
            break;
        case 3:
            Column|=0x98;
            break;
        default:
            Column=0x80;
            break;
    }

    if (Column%2!=0) 
    {
        Column-=1;
        i=1;
    }

    wait_us(100);
    RS = 0;
    RW = 0;
    EN = 1;
    wait_us(100);
    DB = Column;
    EN = 0;

    if (i==1) 
    {
        wait_us(100);
        RS = 1;
        RW = 0;
        EN = 1;
        DB = ' ';
        EN = 0;
    }
    for (i=0; i<length; i++) 
    {
        wait_us(100);
        RS = 1;
        RW = 0;
        EN = 1;
        DB = ((unsigned int)ptr[i]);
        EN = 0;
    }
}
