#ifndef RAM_H
#define RAM_H

#define STACK_SIZE 32768   //sp is 16  bits
#define CODE_MEMORY_SIZE 65535

struct ram{
	uint16_t* stack;
	uint16_t* code;
};

struct ram* newRam();

uint16_t loadMem(struct ram* ram,uint16_t addr);

uint16_t loadStack(struct ram* ram,int16_t addr);

void storeStack(struct ram* ram,int16_t addr,uint16_t data);

void storeMem(struct ram* ram,uint16_t addr,uint16_t data);

void loadCodeIntoRam(struct ram* ram, char* filename);

void delRam(struct ram* ram);

#endif