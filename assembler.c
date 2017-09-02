#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isToken(char* str){
	int 
}



int main(){

	struct symbol{
		char* sym;
		uint16_t  address;
	};

	struct symbol* symtab = (struct symbol*)(malloc(1000*sizeof(struct symbol)));
	uint16_t* code = (uint16_t*)(malloc(2000*sizeof(uint16_t)));
	FILE * fp;
    char * line = NULL;
    size_t len = 20;
    ssize_t read;

    fp = fopen("test", "r");

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        if(isNotToken(line))






    }

	fclose(fp);
	if (line)
        free(line);
    exit(EXIT_SUCCESS);



	return 0;
}