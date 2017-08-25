#include "mange.h"

#define DEFAULT_COLS	10
#define DEFAULT_ROWS	10

int readFile(char *filename) {
	FILE *fptr;
	char in_var[MAXFIELD];
	int in_count=0,var_count=0;
	int x=0,y=0,i=0,j=0;
	char c;
	if ( (strlen(buffer_name) > 3) && (saved==0) && (strncmp(filename,"/tmp/mangeundo",12)!=0) ) {
		int ret = msgLine(COLOR_QUESTION,MSG_KEY,"Save current buffer? [^Yes/^No/^Cancel]");
		switch (ret) {
			case 'Y':
			case 'y':
				// save current file
				break;
			case 'N':
			case 'n':
				break;
			default:
				return 1;
				break;
		}
	}
	if (strlen(filename) > 3) {
		if ( (fptr = fopen(filename,"r")) == NULL ) {
			if (curses_running == 1) {
				msgLine(COLOR_ERROR,MSG_START,"File read error ");
				printw("while opening \"%s",filename);
				msgLine(COLOR_ERROR,MSG_KEY,"\"");
				return 1;
			}
			else {
				fprintf(stderr,"File read error while opening %s.\n",filename);
				exit(1);
			}
		}
		if (strncmp(filename,"/tmp/mangeundo",12)!=0)
			purgeUndos();
		freeBuffer();
		cols=0;
		buffer = (char **) malloc(sizeof(char*));
		while ( (c=fgetc(fptr)) != EOF) {	//determine max cols first, then pad each row to match incase of unequal rows
			if (c == delim)
				x ++;
			if (c == '\n') {
				if (x > cols)
					cols=x;
				x=0;
			}
		}
		cols++;
		fseek(fptr,0,SEEK_SET);
		x = 0;
		while ( (c=fgetc(fptr)) != EOF) {
			if ((c == '\n') && (in_count == 0))
				continue;
			if ((c == delim) || (c == '\n')) {
				buffer = (char **) realloc(buffer,(var_count + 1) * sizeof(char*));
				x++;
				in_var[in_count] = '\0';
				buffer[var_count] = (char *) malloc(in_count+1);
				strcpy(buffer[var_count++],in_var);
				in_count = 0;
			}
			else
				in_var[in_count++] = c;
			if (c == '\n') {
				while (x < cols) {	// fill row with blanks to match length of longest row
					buffer = (char **) realloc(buffer,(var_count + 1) * sizeof(char*));
					x++;
					buffer[var_count] = (char *) malloc(2);
					strcpy(buffer[var_count++],"\0");
				}
				y++;
				x=0;
			}
		}
		rows=y;
		col_width = (int *) calloc(cols, sizeof(int));
		int tlen;
		for (j = 0; j < rows; j++) {
			for (i = 0; i < cols; i++) {
				tlen = strlen(getField(i,j));
				if (col_width[i] < tlen)
					col_width[i] = tlen;
			}
		}
		fclose(fptr);
	}
	else {
		cols=DEFAULT_COLS;
		rows=DEFAULT_ROWS;
		if (strncmp(filename,"/tmp/mangeundo",12)!=0)
			purgeUndos();
		if (buffer != NULL)
			freeBuffer();
		buffer = (char **) malloc(cols * rows * sizeof(char *));
		int i;
		for (i = 0; i < cols * rows; i ++) {
			buffer[i] = (char *) malloc(5);
			strcpy(buffer[i],".");
		}
		col_width = (int *) malloc(cols * sizeof(int));
		for (i = 0; i < cols; i ++)
			col_width[i]=3;
	}
	if (strncmp(filename,"/tmp/mangeundo",12)!=0)
		saved=1;
	return 0;
}
