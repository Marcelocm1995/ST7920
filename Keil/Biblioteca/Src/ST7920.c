#include "ST7920.h"

//BusOut DB(D5, D6, D7, D8, D9, D10, D11, D12); // DB0 - DB7 RESPECTIVAMENTE

static void BusOut(uint8_t value)
{	
	uint8_t val1 = (value & 0x80) >> 7;
	uint8_t val2 = (value & 0x40) >> 6;
	uint8_t val3 = (value & 0x20) >> 5;
	uint8_t val4 = (value & 0x10) >> 4;
	uint8_t val5 = (value & 0x08) >> 3;
	uint8_t val6 = (value & 0x04) >> 2;
	uint8_t val7 = (value & 0x02) >> 1;
	uint8_t val8 = (value & 0x01) >> 0;

	HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, val8);
	HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, val7);
	HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, val6);
	HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, val5);
	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, val4);
	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, val3);
	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, val2);
	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, val1);
}


void ST7920_Init()
{
		delay_init();
   
		//function set  8-bit mode
		HAL_Delay(100); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(FUNCTION_SET | DATA_LENGTH_DL);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
		//function set  8-bit mode again
    delay_us(1000); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(FUNCTION_SET | DATA_LENGTH_DL);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
    // display on
    delay_us(1000); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(DISPLAY_CONTROL | DISPLAY_ON_D);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
		
		// cursor - Display shift right by 1, cursor also follows to shift.
    delay_us(1000); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(0x1C);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
    // clear screen
    delay_us(1000); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
		BusOut(DISPLAY_CLEAR);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
		// Returns to home. Cursor moves to starting point
    HAL_Delay(1); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(RETURN_HOME);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);    
		
		// Setting location to write characters. In this case 0,0 - Top Left Corner
		HAL_Delay(1); 
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(0x80);
		delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);   
}

void ST7920_Clear()
{
    //=========== This function set all the pixels to off in the graphic controller =================
   for(int y = 0; y < 64; y++)
   {
       if(y < 32)
       {
            delay_us(100);//delay_us(1000);
             HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80 | y);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
            
            delay_us(100);//delay_us(1000);
             HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
       }
       
       else
       {
            delay_us(100);//delay_us(1000);
             HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80 | (y - 32));
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
            
            delay_us(100);//delay_us(1000);
             HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x88);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
       }
       
       for(int x = 0; x < 16; x++)
       {
            delay_us(100);//delay_us(1000);
            HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
             HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x00);
            delay_us(100);
             HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(20);
       }    
   }
}

void ST7920_SetGraphicsMode()
{    
    delay_us(1000);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    delay_us(100);
    BusOut(EXTENDED_FUNCTION_SET | DATA_LENGTH_DL);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
    delay_us(1000);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    delay_us(100);
    BusOut(EXTENDED_FUNCTION_SET | DATA_LENGTH_DL | EXTENDED_INSTRUCTION_RE);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    
    delay_us(100);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    delay_us(100);
    BusOut(EXTENDED_FUNCTION_SET | DATA_LENGTH_DL | EXTENDED_INSTRUCTION_RE | GRAPHIC_ON_G);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}

void ST7920_SetTextMode() 
{
    delay_us(100);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(FUNCTION_SET | DATA_LENGTH_DL);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}

void ST7920_DrawHorizontalLine(uint8_t X, uint8_t Y,  uint8_t LEN)
{   
		//desenhando uma linha de tamanho T em Y, com X offset
    
    delay_us(1000);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(0x80 | Y);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    delay_us(100);
    
    delay_us(1000);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(0x80 | X);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    delay_us(100);
    
    for(int i = 0; i < (LEN / 8); i++)
    {
        delay_us(1000);
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
        delay_us(100);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
        BusOut(255);
        delay_us(100);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
        delay_us(20);
    }

    if(LEN%8 != 0)
    {
        int LEN_rest = LEN - ((LEN / 8) * 8);
        int bus_rest;
        
        switch (LEN_rest) 
        {
            case 1: bus_rest = 0x80; break;
            case 2: bus_rest = 0xC0; break;
            case 3: bus_rest = 0xE0; break;
            case 4: bus_rest = 0xF0; break;
            case 5: bus_rest = 0xF8; break;
            case 6: bus_rest = 0xFC; break;
            case 7: bus_rest = 0xFE; break;
        }
        //pc.printf("%x\n\r",bus_rest);
        delay_us(1000);
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
        delay_us(100);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
        BusOut(bus_rest); // tem que ser 254 no exemplo de T 255
        delay_us(100);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
        delay_us(20);
    }
}

void ST7920_DrawVerticalLine(uint8_t X, uint8_t Y,  uint8_t LEN)
{    
    delay_us(100);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
		BusOut(0x80 | Y);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    delay_us(100);
    
    delay_us(100);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    BusOut(0x80 | X);
    delay_us(100);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    delay_us(100);
    
    for(int y = 0; y < LEN; y++)
   {
       if(y < 32)
       {
            delay_us(100);
            HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80 | y);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
            
            delay_us(1000);
            HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
       }
       
       else
       {
            delay_us(100);
            HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x80 | (y - 32));
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
            
            delay_us(1000);
            HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
            BusOut(0x88);
            delay_us(100);
            HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
            delay_us(100);
       }     
    
       delay_us(100);
       HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
       HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
       delay_us(100);
       HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
       BusOut(0x80);
       delay_us(100);
       HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
       delay_us(20);
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

    if (Column%2!=0) {
        Column-=1;
        i=1;
    }
    
    delay_us(100);
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    delay_us(100);
    BusOut(Column);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

    if (i==1) 
    {
        delay_us(100);
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
        BusOut(' ');
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    }
    for (i=0; i<length; i++) 
    {
        delay_us(100);
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
        BusOut(((unsigned int)ptr[i]));
        HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    }
}
