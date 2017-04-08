#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

struct vMachine* newVM() {

	struct vMachine* vm = (struct vMachine*)(malloc(sizeof(struct vMachine)));



	return vm;
}



int main(){
	return 0;
}