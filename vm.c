#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#define VPUSH(vm,v) vm->stack[++vm->registers.sp]=v
//Pushes v to stack of vm
#define VPOP(vm) vm->stack[vm->registers.sp--]



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

	uint16_t code = vm->registers.ir.code;
	switch(code){

		case POP: {
				vm->registers.sp--;
				break;
			}
		case PUSH: {
				vm->registers.sp++;
				vm->stack[vm->registers.sp] = vm->registers.ir.arg;
				break;
			}
		case EQU: ;{  //Semicolon inserted because c grammer does not allow decalaration after a label
				int16_t a = VPOP(vm);  // See http://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
				int16_t b = VPOP(vm);
				a == b ? setZero(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				VPUSH(vm, b);
				VPUSH(vm, a);
				break;
			} // scope of variables is entire switch block; Hence,the braces.
		case DUP: ; {
				int16_t a = VPOP(vm);
				VPUSH(vm, a);
				VPUSH(vm, a);
				break;
			}
		case FLIP: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);
				VPUSH(vm, a);
				VPUSH(vm, b);
				break;
			}
		case LST: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);
				a < b ? setZero(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				break;
			}
		case GRT: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);
				a > b ? setZero(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				break;
			}
		case NOP:
			break;



	}
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
	delVM(vm);
	

	return 0;
}