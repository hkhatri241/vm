#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

//TODO Checks for memory and stack size during calculation
//create a new vm
struct vMachine* newVM() {

	struct vMachine* vm = (struct vMachine*)(malloc(sizeof(struct vMachine)));
	vm->registers.pc = 0; //initialize program counter to first instruction
	vm->registers.sp = -1;
	vm->registers.ir.code = 0; //0 does not correspond to any instruction
	vm->registers.ir.arg = 0;
	clearFlag(&vm->registers.flag);
	//allocate stack and code memory
	vm->stack = (int16_t*)(malloc(STACK_SIZE*sizeof(uint16_t)));
	vm->code = (int16_t*)(malloc(CODE_MEMORY_SIZE*sizeof(uint16_t)));
	return vm;
}

//free up the vm
void delVM(struct vMachine* vm) {

	free(vm->stack);
	free(vm->code);
	free(vm);
}

//fetches the next instruction and sets code part of instruction register
void fetch(struct vMachine* vm) {

	int16_t code = vm->code[vm->registers.pc];
	vm->registers.pc++; //increment pc
	vm->registers.ir.code = code;
}

/*Reads in opcode from ir.code
* Checks whether it has operand
* No operand - Increments pc 
* Operand - Stores it in ir.arg
* Current design of bytecode permits only 1 16 bit argument with PUSH
*/
void decode(struct vMachine* vm) {

	uint16_t code = vm->registers.ir.code;
	switch(code){

		case PUSH:
			vm->registers.ir.arg = vm->code[vm->registers.pc];
			vm->registers.pc++;
			break;

		default: //All else instructions have no arguments
			break;
	}

}

//Take the instruction 

void execute(struct vMachine *vm) {


}

void run(struct vMachine *vm) {

	do{
		fetch(vm);
		decode(vm);
		execute(vm);

	}while(1);
}

int main() {

	struct vMachine* vm = newVM();
	vm->code[0] = 1;
	vm->code[1] = 3;
	vm->code[2] = 4;
	vm->code[3] = 20;
	vm->code[4] = 10;
	
	

	return 0;
}