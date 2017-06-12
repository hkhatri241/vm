#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "bit.h"
#define VPUSH(vm,v) vm->stack[++vm->registers.sp]=v
//Pushes v to stack of vm
#define VPOP(vm) vm->stack[vm->registers.sp--]


//CHANGE THIS.
//Function to  refactor out common code from all variant of goto instructions. 
void jump(struct vMachine* vm){
	//POP NEW PC.
	uint16_t newPc = VPOP(vm);
	//PUSH CURRENT PC ONTO STACK.
	VPUSH(vm,vm->registers.pc);
	//set PC AS NEWPC
	vm->registers.pc = newPc;
}

//TODO Checks for memory and stack size during calculation
//create a new vm
struct vMachine* newVM() {

	struct vMachine* vm = (struct vMachine*)(malloc(sizeof(struct vMachine)));
	vm->registers.pc = 0; //initialize program counter to first instruction
	vm->registers.sp = -1;
	vm->registers.ir.code = 0; //0 does not correspond to any instruction
	clearFlag(&vm->registers.flag);
	//allocate stack and code memory
	vm->stack = (int16_t*)(malloc(STACK_SIZE*sizeof(int16_t)));
	vm->code = (int16_t*)(malloc(CODE_MEMORY_SIZE*sizeof(int16_t)));
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


//Take the instruction 

void execute(struct vMachine *vm) {

	uint16_t code = vm->registers.ir.code;
	switch(code){

		case POP: {
				vm->registers.sp--;
				break;
			}
		case PUSH: {
				//GET 16 BIT DATA VALUE FROM NEXT POSITION AND INC. PC
				int16_t data = vm->code[vm->registers.pc++];
				VPUSH(vm,data);
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
		case ADD: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);

				if(isAddSafe(a,b)){
					clearFlag(&vm->registers.flag);
				} else{
					setCarry(&vm->registers.flag);
				}	

				VPUSH(vm, (a+b));
				break;
			}
		case SUB: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);
				int16_t c = a-b;

				if(!c){
					setZero(&vm->registers.flag);
				} else if(c < 0){
					setNegative(&vm->registers.flag);
				}

				VPUSH(vm,c);				
				break;
			}
		case MUL: ;{
				int16_t a = VPOP(vm);
				int16_t b = VPOP(vm);
				int16_t c = a*b;

				if(a == 0 || b == 0){ // set zero flag if either 0
					setZero(&vm->registers.flag);
					VPUSH(vm,c);

				} else if(isMulSafe(a,b)){
					clearFlag(&vm->registers.flag);
					VPUSH(vm,c);

				} else{
					setCarry(&vm->registers.flag);
					VPUSH(vm,c);
				}
				break;
			}
		case GOTO: ;{
				
				jump(vm);
				break;
			}
		case GOZ: ;{

				if(isSet(&vm->registers.flag,7)){
					jump(vm);
				}
				break;
			}
		case GOC: ;{

				if(isSet(&vm->registers.flag,1)){
					jump(vm);
				}

				break;
			}
		case GOP: ;{

				if(isSet(&vm->registers.flag,2)){
					jump(vm);
				}

				break;
			}
		case GOC: ;{

				if(isSet(&vm->registers.flag,8)){
					jump(vm);
				}

				break;
			}
		case GONZ: ;{

				if(!isSet(&vm->registers.flag,7)){
					jump(vm);
				}
				break;
			}
		case GONZ: ;{

				if(!isSet(&vm->registers.flag,7)){
					jump(vm);
				}
				break;
			}
		case READ: ;{
				//get memory address.
				int16_t memLoc = VPOP(vm);
				int16_t data = vm->code[memLoc];
				VPUSH(vm, data);
				break;
			}
		case WRTD: ;{
				//POP mem address and data.
				int16_t data = VPOP(vm);
				int16_t memLoc = VPOP(vm);
				vm->code[memLoc] = data;
				break;
			}
		default:
				printf("This op is not supported.");
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