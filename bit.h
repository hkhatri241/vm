#ifndef BIT
#define BIT

#include <stdint.h>
#include <stdbool.h>
// Util Lib to help set flag register.
//CURRENT IMPLEMENTATION IN VM.C DOES NOT MAKE USE OF SET PARITY.
//CHANGES ARE NOT REFLECTED TO PARITY BIT IN FLAG REGISTER.

void setBit(uint8_t *flag,int x);

void clearBit(uint8_t *flag,int x);

void clearFlag(uint8_t* flag); 

bool isSet(uint8_t* flag, int bitPosition);

void setNegative(uint8_t* flag);

void setZero(uint8_t* flag);

void setAC(uint8_t* flag);

void setParity(uint8_t* flag);

void setCarry(uint8_t* flag);

size_t highestOneBitPosition(int16_t x);

bool isAddSafe(int16_t a, int16_t b);

bool isMulSafe(int16_t a, int16_t b); 


#endif