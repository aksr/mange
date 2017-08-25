#include "mange.h"

#define MAXUNDOS	20

int firstundo = 0;
int undolevel = 0;
char undostring[MAXLINE];

int undoLast() {
	if (undolevel > firstundo) {
		sprintf(undostring,"/tmp/mangeundo%d",--undolevel);
		readFile(undostring);
	}
	return 0;
}

int setUndo() {
	sprintf(undostring,"/tmp/mangeundo%d",undolevel++);
	writeFile(undostring);
	if (undolevel - firstundo > MAXUNDOS) {
		sprintf(undostring,"cd /tmp; rm mangeundo%d &> /dev/null",firstundo++);
		system(undostring);
	}
	return 0;
}

int purgeUndos() {
	system("cd /tmp; rm mangeundo* &> /dev/null");
	firstundo = 0;
	undolevel = 0;
	return 0;
}
