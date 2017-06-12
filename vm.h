#ifndef VM
#define VM
#define STACK_SIZE 32767   //sp is 16  bits
#define CODE_MEMORY_SIZE 65535

#include <stdint.h>
#include "instructions.h"

/*DESIGN: Program memory size is 2^16,stack size = 2^16
* Each instruction has a constant size(like RISC) of 4 bytes
* ,i.e. occupies 2 memory locations.Memory is a int16_t array.
* Stack is int16_t array.
* 
*/


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

#endif