#ifndef INSTRUCTIONS
#define INSTRUCTIONS

enum opCode{
	READ = 1, //Push data (16bit) from specified memory position onto to of stack.sp++. s[sp]<-m[ag].
	WRTD = 2, //Pop data from top of stack to specified mem.m[ag]<-s[sp].sp--.
	ADD = 3, //pop top 2 elements and push their sum
	SUB = 4, //d
	MUL = 5, //d
	DIV = 6, 
	POP = 7, //d
	EQU = 8, //d
	GRT = 9, //d
	LST = 10, //d
	GOTO = 11, //d. JUMPS TO MM LOC SPECIFIED BY TOP OF STACK.
	GOZ = 12, //jump if zero bit set in flag.
	GONZ = 13, //jump if zero flag not set.
	END = 14,
	DUP = 15, //d
	FLIP = 16, //d
	NOP = 17, //no idea what this is.
	PUSH = 18, //d
	GON = 19, //jump if negative flag is set
	GOP = 20, //jump if parity set
	GOC = 21 //jum if carry set
};

struct instruction {  //encapsulates opcode +plus arg, every arg is 16 bit long
	int16_t code;

};

#endif
//Only PUSH takes a single 16 bit argument(equal to instruction size).
//GOTO and all jump type instructions jump to location specified by top of stack.
//Usage of READ and  WRTD -
//READ - Push memory location to be read on top of stack.READ pops it and pushes data into stack.
//WRTD - First,push memory location to be written.Second, push data to be written.
//WRTD does the rest.