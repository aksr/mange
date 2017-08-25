#include "mange.h"

int writeFile(char *filename) {
	FILE *fptr;
	int i,j;
	if ( (fptr=fopen(filename,"w")) == NULL ) {
		msgLine(COLOR_ERROR,MSG_START,"Error opening ");
		printw("\"%s\"",filename);
		msgLine(COLOR_ERROR,MSG_GO,".  Buffer not saved.");
		return 1;
	}
	for (j = 0;j < rows;j++) {
		fprintf(fptr,"%s",getField(0,j));
		for (i = 1;i < cols;i ++)
			fprintf(fptr,",%s",getField(i,j));
		fprintf(fptr,"\n");
	}
	fclose(fptr);
	if ( (strcmp(filename,"/tmp/mangeplot.csv")==0) || (strncmp(filename,"/tmp/mangeundo",12)==0) )
		return 0;
	saved=1;
	msgLine(COLOR_INFO,MSG_START,"Wrote ");
	printw("\"%s\"",filename);
	msgLine(COLOR_INFO,MSG_GO,".  ");
	return 0;
}

int savePrompt() {
	int c;
	char *name;
	c = msgLine(COLOR_QUESTION,MSG_KEY,"Save current buffer? [^Yes / ^No / ^Cancel]");
	switch (c) {
		case 'Y':
		case 'y':
			move(MaxRows,0);
			msgLine(COLOR_QUESTION,MSG_START,"Enter file name ");
			printw("[\"%s\"",buffer_name);
			name = msgLine(COLOR_QUESTION,MSG_LINE,"]:");
			if (strlen(name) < 2) {
				writeFile(buffer_name);
				saved = 1;
			}
			else {
				writeFile(name);
			}
			break;
		case 'N':
		case 'n':
			break;
		case 'c':
		case 'C':
		default:
			return 1;
			break;
	}
	return 0;
}
