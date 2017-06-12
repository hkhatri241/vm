#include <stdio.h>
#include <stdlib.h>
#include "bit.h"

void setBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be set");
	}
	*flag |= 1 << x;

}

void clearBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be cleared");
	}
	*flag &= ~(1 << x);

}

void clearFlag(uint8_t* flag) {
	int i;
	for(i = 0; i < 8; i++)
		clearBit(flag, i);
}

//returns true if bit at bitPostion is set.
//NOTE: bitPosition = 1 correspods to bit 1.
//Not  zero indexed, like C arrays. 
bool isSet(uint8_t* flag, int bitPosition){
	
	return (temp & (1 << (bitPosition - 1)))? true: false;
}

inline void setNegative(uint8_t* flag) {

	setBit(flag, 7);
}

inline void setZero(uint8_t* flag) {

	setBit(flag, 6);
}

inline void setAC(uint8_t* flag) {

	setBit(flag, 4);
}

inline void setParity(uint8_t* flag) {

	setBit(flag, 1);
}

inline void setCarry(uint8_t* flag) {

	setBit(flag, 0);
}

size_t highestOneBitPosition(int16_t x) {

    size_t bits=0;
    while (x != 0) {
        ++bits;
        x>>=1;
    };
    return bits;
}

bool isAddSafe(int16_t a, int16_t b) {

    size_t a_bits = highestOneBitPosition(a), b_bits=highestOneBitPosition(b);
    return (a_bits < 16 && b_bits < 16);
}

bool isMulSafe(int16_t a, int16_t b) {

    size_t a_bits=highestOneBitPosition(a), b_bits=highestOneBitPosition(b);
    return (a_bits+b_bits <= 16);
}

