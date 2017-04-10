#ifndef VM
#define VM
#define STACK_SIZE 32768   //sp is 16  bits
#define CODE_MEMORY_SIZE 65536

#include <stdint.h>
#include <stdbool.h>

/*DESIGN: Program memory size is 2^16,stack size = 2^16
* Each instruction has a constant size(like RISC) of 4 bytes
* ,i.e. occupies 2 memory locations.Memory is a int16_t array.
* Stack is int16_t array.
* 
*/

enum opCode{
	READ = 1,
	WRTD = 2,
	ADD = 3,
	SUB = 4,
	MUL = 5,
	DIV = 6,
	POP = 7,
	EQU = 8,
	GRT = 9,
	LST = 10,
	GOTO = 11,
	GOIF = 12,
	GOUN = 13,
	END = 14,
	DUP = 15,
	FLIP = 16,
	NOP = 17,
	PUSH = 18
};

struct instruction {  //encapsulates opcode +plus arg, every arg is 16 bit long
	int16_t code;
	int16_t arg;
};

struct reg {// pc = program counter,sp = stack pointer,ir = instruction register and flag is defined in docs
	uint16_t pc; //max code size is 65536
	int16_t sp; //Only time sp is negative is initially = -1. All else 0<= sp <32768
	struct instruction ir;
	uint8_t flag;
};

struct vMachine{
	struct reg registers;
	int16_t* stack;
	int16_t* code;
};


void setBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be set");
	}
	*flag |= 1 << x;

}

void clearBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be set");
	}
	*flag &= ~(1 << x);

}

void clearFlag(uint8_t* flag) {
	int i;
	for(i = 0; i < 8; i++)
		clearBit(flag, i);
}

void setNegative(uint8_t* flag) {

	setBit(flag, 7);
}

void setZero(uint8_t* flag) {

	setBit(flag, 6);
}

void setAC(uint8_t* flag) {

	setBit(flag, 4);
}

void setParity(uint8_t* flag) {

	setBit(flag, 1);
}

void setCarry(uint8_t* flag) {

	setBit(flag, 0);
}

#endif