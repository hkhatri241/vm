#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ram.h"

//allocacte a new ram struct.
struct ram* newRam(){

	struct ram* ram = (struct ram*)(malloc(sizeof(struct ram)));
	ram->stack = (uint16_t*)(malloc(STACK_SIZE*sizeof(uint16_t)));
	ram->code = (uint16_t*)(malloc(CODE_MEMORY_SIZE*sizeof(uint16_t)));
	return ram;
}

uint16_t loadMem(struct ram* ram,uint16_t addr){

	if(!(addr < CODE_MEMORY_SIZE))
		printf("Invalid Memory access. Raise Hell from loadmem");
	return ram->code[addr];

}

uint16_t loadStack(struct ram* ram,int16_t addr){

	if(!(addr < STACK_SIZE))
		printf("Invalid Stack access. Raise Hell from load stack");
	return ram->stack[addr];	
}

void storeStack(struct ram* ram,int16_t addr,uint16_t data){

	if(!(addr < STACK_SIZE))
		printf("Invalid Stack access. Raise Hell storestack");

	ram->stack[addr] = data;	

}
void loadCodeIntoRam(struct ram* ram,char* filename){
	char* opcode = NULL;
	if(file == NULL){
		printf("No file name. Exit");
		exit(1);
	}

	while()
}

void storeMem(struct ram* ram,uint16_t addr,uint16_t data){

	if(!(addr < CODE_MEMORY_SIZE))
		printf("Invalid Memory access. Raise Hell from storemem");
	ram->code[addr] = data;

}


void delRam(struct ram* ram){
	free(ram->code);
	free(ram->stack);
}


