#ifndef VM
#define VM
#define STACK_SIZE 65536   //sp is int16_t
#define MEMORY_SIZE 65536

#include <stdint.h>
#include <stdbool.h>

/*DESIGN: Program memory size is 2^16,stack size = 2^16
* Each instruction has a constant size(like RISC) of 4 bytes
* ,i.e. occupies 2 memory locations.Memory is a int16_t array.
* Stack is int16_t array.
* 
*/

enum opCode{
	READ = 0,
	WRTD = 1,
	ADD = 2,
	SUB = 3,
	MUL = 4,
	DIV = 5,
	POP = 6,
	EQU = 7,
	GRT = 8,
	LST = 9,
	GOTO = 10,
	GOIF = 11,
	GOUN = 12,
	END = 13,
	DUP = 14,
	FLIP = 15,
	GET = 16,
	PUT = 17,
	NOP = 18,
	PUSH = 19
};

struct instruction {  //encapsulates opcode +plus arg, every arg is 16 bit long
	int16_t code;
	int16_t arg;
};

struct reg {// pc = program counter,sp = stack pointer,ir = instruction register and flag is defined in docs
	int16_t pc;
	int16_t sp;
	struct instruction ir;
	uint8_t flag;
};

struct vMachine{
	struct reg registers;
	int16_t* stack;
	int16_t* code;
};


bool setBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be set");
	}
	*flag |= 1 << x;

}

bool clearBit(uint8_t *flag,int x){

	if(x > 7){
		printf("Invalid bit to be set");
	}
	*flag &= ~(1 << x);

}

bool setNegative(uint8_t* flag) {

	setBit(flag, 7);
}

bool setZero(uint8_t* flag) {

	setBit(flag, 6);
}

bool setAC(uint8_t* flag) {

	setBit(flag, 4);
}

bool setParity(uint8_t* flag) {

	setBit(flag, 1);
}

bool setCarry(uint8_t* flag) {

	setBit(flag, 0);
}

#endif