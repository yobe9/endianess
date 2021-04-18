// 313268393 Yoav Berger
#include <stdio.h>
#include "ex1.h"

/*
the logic is that long got 8 byte which every byte contains 2 digit of hexa, so we need to check the last digits
and see if they are store in the begining or in the end
*/
int is_big_endian() {
    //checking to see how number is set in memory
    long endianCheck = 0x765432;
    
    // using char pointer to scope to byte per byte
    char* checkFirstBit = (char*) &endianCheck;
    
    /*self check for reading the bits
	for (int i = 0; i < sizeof(long); i++)
	{
		printf("the bit is %x\n", checkFirstBit[i]);

	}
    */

    // if the first byte is 32 that means the last byte is saved first and it's little endiann
    if (checkFirstBit[0] == 0x32)
    {
        return 0;
    }
    // in case the first byte is not 32 means the first byte (00) is saved first and it's big endiann
    else
    {
        return 1;
    }
}

// extracting halfs of the hex number using shifting and connecting them
unsigned long merge_bytes(unsigned long x, unsigned long int y){
    
    //extracting the digits of the first half of x by moving 8 digits in hex (32 bits)
    unsigned long shiftX = x >> 32;
    shiftX = shiftX << 32;
    //printf("the first move is %lx\n", shiftX);
    
    //extracting the digits of the second half of y by moving 8 digits in hex (32 bits)
    unsigned long shiftY = y << 32;
    shiftY = shiftY >> 32;
    //printf("the fsecond move is %lx\n", shiftY);
    
    //connecting the two halfs
    unsigned long sum = shiftY + shiftX;

    return sum;
}

unsigned long put_byte(unsigned long x, unsigned char b, int i){
    /*moving the bytes and extracting the digits that needs to be befor the new byte
    using overall number of bytes in long minus the place that the new byte will be in
    */
    unsigned long fromXBeforeChar = x;
    int j;
    for (j = 0; j < (8 - i); j++)
    {
        fromXBeforeChar = fromXBeforeChar >> 8;
    }
    //printf("the first move is %lx\n", fromXBeforeChar);
    
    //making room to the new byte and inserting it
    fromXBeforeChar = fromXBeforeChar << 8;
    unsigned long finalX = fromXBeforeChar + b;
    //printf("the third move is %lx\n", finalX);

    //moving back the bytes so we will be able to add the the reamaning part of the number
    for (j = 0; j < (8 - i - 1); j++)
    {
        finalX = finalX << 8;
    }
    //printf("the second move is %lx\n", finalX);
    /*moving the bytes and extracting the digits that needs to be after the new byte
    using overall number of bytes befor the new one (argument i) + 1 byte for the new byte
    */
    unsigned long fromXAfterChar = x;
    for (j = 0; j < i +1; j++)
    {
        fromXAfterChar = fromXAfterChar << 8;
    }
    //printf("the fourth move is %lx\n", fromXAfterChar);

    //moving back the bytes so we will be able to add the the reamaning part of the number
    for (j = 0; j < i +1; j++)
    {
        fromXAfterChar = fromXAfterChar >> 8;
    }
    //printf("the thith move is %lx\n", fromXAfterChar);

    //adding both parts together
    finalX = finalX + fromXAfterChar;
    //printf("the second move is %lx\n", finalX);
    
    return finalX;
}