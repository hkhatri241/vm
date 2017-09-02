#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "bit.h"
#include "ram.h"
#include <inttypes.h>

//#define VPUSH(vm,v) vm->stack[++vm->registers.sp]=v
//Pushes v to stack of vm
//#define VPOP(vm) vm->stack[vm->registers.sp--]

static inline void VPUSH(struct vMachine* vm, uint16_t v, struct ram* ram){
	storeStack(ram, ++vm->registers.sp, v);
}

static inline uint16_t VPOP(struct vMachine* vm,  struct ram* ram){
	return loadStack(ram, vm->registers.sp--);
}


//CHANGE THIS.
//Function to  refactor out common code from all variant of goto instructions. 
void jump(struct vMachine* vm, struct ram* ram){
	//POP NEW PC.
	uint16_t newPc = VPOP(vm,ram);
	//PUSH CURRENT PC ONTO STACK.
	//VPUSH(vm,vm->registers.pc);//currently removed. cant return,
	//set PC AS NEWPC-
	//printf("\njumping to  : %u\n",newPc);
	vm->registers.pc = newPc;
}

//TODO Checks for memory and stack size during calculation
//create a new vm
struct vMachine* newVM() {

	struct vMachine* vm = (struct vMachine*)(malloc(sizeof(struct vMachine)));
	vm->registers.pc = 0; //initialize program counter to first instruction
	vm->registers.sp = -1;
	vm->registers.ir.code = 0; //0 does not correspond to any instruction
	vm->registers.count = 0;
	clearFlag(&vm->registers.flag);
	return vm;
}

//free up the vm
void delVM(struct vMachine* vm) {
	free(vm);
}

//fetches the next instruction and sets code part of instruction register
void fetch(struct vMachine* vm,struct ram* ram) {

	uint16_t code = loadMem( ram, vm->registers.pc);
	//printf("\non location : %u",vm->registers.pc);
	vm->registers.pc++; //increment pc
	vm->registers.ir.code = code;
}


//Take the instruction 

bool execute(struct vMachine* vm,struct ram* ram) {

	uint16_t code = vm->registers.ir.code;
	//printf("%u\n",(unsigned int)code);
	switch(code){

		case POP: {
				printf("\nPopped : %u\n",loadStack(ram, vm->registers.sp));
				vm->registers.sp--;
				break;
			}
		case PUSH: {
				//GET 16 BIT DATA VALUE FROM NEXT POSITION AND INC. PC
				uint16_t data = loadMem(ram, vm->registers.pc++);
				printf("\nPushed : %u\n",data);
				VPUSH(vm,data,ram);
				break;
			}
		case EQU: ;{  //Semicolon inserted because c grammer does not allow decalaration after a label
				uint16_t a = VPOP(vm,ram);  // See http://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
				uint16_t b = VPOP(vm,ram);
				a == b ? setZero(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				//printf("Zero Flag : %u",isSet(&vm->registers.flag,7));
				VPUSH(vm, b, ram);
				VPUSH(vm, a, ram);
				break;
			} // scope of variables is entire switch block; Hence,the braces.
		case DUP: ; {
				uint16_t a = VPOP(vm,ram);
				VPUSH(vm, a, ram);
				VPUSH(vm, a, ram);
				break;
			}
		case FLIP: ;{
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);
				VPUSH(vm, a, ram);
				VPUSH(vm, b, ram);
				break;
			}
		case LST: ;{
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);
				a < b ? setNegative(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				break;
			}
		/*case GRT: ;{ //just use lst.
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);
				a > b ? setZero(&vm->registers.flag) : clearFlag(&vm->registers.flag);
				break;
			}*/
		case ADD: ;{
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);

				if(isAddSafe(a,b)){
					clearFlag(&vm->registers.flag);
				} else{
					setCarry(&vm->registers.flag);
				}	

				VPUSH(vm, (a+b), ram);
				break;
			}
		case SUB: ;{
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);
				uint16_t c = a-b;

				if(!c){
					setZero(&vm->registers.flag);
				} else if(c < 0){
					setNegative(&vm->registers.flag);
				}

				VPUSH(vm, c, ram);				
				break;
			}
		case MUL: ;{
				uint16_t a = VPOP(vm,ram);
				uint16_t b = VPOP(vm,ram);
				uint16_t c = a*b;

				if(a == 0 || b == 0){ // set zero flag if either 0
					setZero(&vm->registers.flag);
					VPUSH(vm,c, ram);

				} else if(isMulSafe(a,b)){
					clearFlag(&vm->registers.flag);
					VPUSH(vm,c, ram);

				} else{
					setCarry(&vm->registers.flag);
					VPUSH(vm,c, ram);
				}
				break;
			}
		case GOTO: ;{
				
				jump(vm, ram);
				break;
			}
		case GOZ: ;{

				if(isSet(&vm->registers.flag,7)){
					jump(vm, ram);
				}
				break;
			}
		case GOC: ;{

				if(isSet(&vm->registers.flag,1)){
					jump(vm, ram);
				}

				break;
			}
		case GOP: ;{

				if(isSet(&vm->registers.flag,2)){
					jump(vm, ram);
				}

				break;
			}
		case GONC: ;{

				if(!isSet(&vm->registers.flag,1)){
					jump(vm, ram);
				}

				break;
			}
		case GONZ: ;{

				if(!isSet(&vm->registers.flag,7)){
					setZero(&vm->registers.flag);
					uint16_t addr = loadMem(ram, vm->registers.pc++);
					VPUSH(vm, addr, ram);
					jump(vm, ram);
				}
				break;
			}
		case GONP: ;{

				if(!isSet(&vm->registers.flag,2)){
					jump(vm, ram);
				}
				break;
			}
		case READ: ;{
				//get memory address.
				uint16_t memLoc = VPOP(vm,ram);
				uint16_t data = loadMem(ram, memLoc);
				VPUSH(vm, data, ram);
				break;
			}
		case WRTD: ;{
				//POP mem address and data.
				uint16_t data = VPOP(vm,ram);
				uint16_t memLoc = VPOP(vm,ram);
				storeMem(ram, memLoc, data);
				break;
			}
		case ADDC: ;{
				//increment counter by amount
				uint16_t data = VPOP(vm,ram);
				VPUSH(vm, data, ram);
				vm->registers.count += data;
				break;
			}
		case SUBC: ;{
				//increment counter by amount
				uint16_t data = VPOP(vm,ram);
				VPUSH(vm, data, ram);
				vm->registers.count -= data;
				if(!data)
					setZero(&vm->registers.flag);
				break;
			}
		case IN: ;{
				uint16_t data;
				
				printf("Enter input");
				scanf("%" SCNu16,&data);
				VPUSH(vm,data,ram);
				break;
		}
		case OUT: ;{
				uint16_t a = VPOP(vm,ram);
				VPUSH(vm, a, ram);
				printf("%u", (unsigned int)a);
				break;
		}
		case MOV: ;{
				vm->registers.count = VPOP(vm, ram);
				break;
		}
		case END: ;{

				return true;
		}
		default:
				printf("This op is not supported.");
				
				return true;
	}
	//CONTINUE EXECUTING
	return false;
}

void run(struct vMachine *vm,struct ram* ram) {
	bool halt = false;

	do{
		fetch(vm,ram); //fetch instruction into vm
		halt = execute(vm,ram);


	}while(!halt);
}

int main(int argc,char* argv) {
	//create ram and machine
	struct vMachine* vm = newVM();
	struct ram* ram = newRam();

	const char* filename = "out_code.txt";

	//assembly to hexcode type and loads it into ram->code
	bool isEmpty = loadCodeIntoRam(ram,filename);

	if(isEmpty)
		exit(1);

	//run
	run(vm,ram);

	///cleanup
	delRam(ram);
	delVM(vm);
	

	return 0;
}