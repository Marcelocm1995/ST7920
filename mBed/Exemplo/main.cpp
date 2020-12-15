#include "mbed.h"
#include "ST7920.h"

Serial pc(USBTX, USBRX);

int main()
{
    unsigned char texto[11]= {'O','l','a','!', ' ', 'S', 'T', '7', '9', '2', '0'};
    pc.printf("OI \n\r");

    ST7920_Init();

    ST7920_SetGraphicsMode();

    ST7920_Clear();

    ST7920_DrawHorizontalLine(0, 0, 30);

    ST7920_DrawVerticalLine(0, 0, 50);

    ST7920_SetTextMode();

    ST7920_DisplayString(0, 0, texto, 11);

    while(1) 
    {

    }
}

