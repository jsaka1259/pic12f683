#include <common.h>

#define CS      GP5
#define SCK     GP2
#define SO      GP4
#define SI      GP3

void spi_start(void)
{
    CS = 0;
}

void spi_end(void)
{
    CS = 1;
}

void spi_out(unsigned char data)
{
    int i;
    unsigned char BitPos;
    /* Data Out */
    BitPos = 0x80;
    for(i = 0; i < 8; i++)
    {
        if((data & BitPos) != 0)
        {
            SO = 1;
        }
        else
        {
            SO = 0;
        }
        BitPos = BitPos >> 1;
        SCK = 1;
        SCK = 1;
        SCK = 0;
    }
}

unsigned char spi_rcv(void)
{
    int i;
    unsigned char BitPos, data;
    
    data = 0;
    BitPos = 0x80;
    for(i = 0; i < 8; i++)
    {
        SCK = 1;
        if(SI)
        {
            data |= BitPos;
        }
        BitPos = BitPos >> 1;
        SCK = 0;
    }
    return (data);
}

unsigned int spi_rcv16(void)
{
    int i;
    unsigned int BitPos, data;
    
    data = 0;
    BitPos = 0x8000;
    for(i = 0; i < 16; i++)
    {
        SCK = 1;
        if(SI)
        {
            data |= BitPos;
        }
        BitPos = BitPos >> 1;
        SCK = 0;
    }
    return (data);
}