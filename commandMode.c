#include "mange.h"

int history=0;
char last_command[MAXLINE] = "\0";

int commandMode() {
	int c,i=0;
	char *line;
	char *sys;
	history = 1;
	line = (char *) msgLine(COLOR_COMMAND,MSG_LINE,":");
	history = 0;
	strcpy(last_command,line);
	if (strcmp(line,"quit") == 0)
		safeQuit();
	if (strncmp(line,"save ??",4) == 0) {
		if (strncmp(line,"saveplot ??",8) == 0) {
			sys = (char *) malloc(strlen(line) + 14);
			strcpy(sys,"cp /tmp/mangeplot.jpg ");
			strcat(sys,line + 9);
			system(sys);
			return 0;
		}
		if (strlen(line) == 4)
			writeFile(buffer_name);
		else
			writeFile(line + 5);
		return 0;
	}
	if (strncmp(line,"open ??",4) == 0) {
		// TODO copy filename to buffer name
		if (strlen(line) > 6)
			readFile(line +5);
		else
			readFile(" ");
		return 0;
	}
	if (strcmp(line,"undo") == 0) {
		undoLast();
		return 0;
	}
#ifndef __NO_PLOT__
	if (strncmp(line,"plot ??",4) == 0) {	// currently, enclosing quotes should only use ' (single-ticks) for multiple parameters
		int i=0 ,j=0 , pargc = 0;			// Also, does not check for unmatched 's, so use carefully.  Unmatched single-ticks
											//    may lead to unpredictable behavior (most likely a seg fault).
		char **pargv = (char **) malloc(sizeof(char *));
		char *tline = (char *) malloc(strlen(line) + 1);
		while (i < strlen(line)) {
			if (line[i]=='\'') {
				i++;
				while (line[i] != '\'')
					tline[j++]=line[i++];
			}
			else {
				while ((line[i] != ' ') && (line[i] != '\0'))
					tline[j++]=line[i++];
			}
			tline[j]='\0';
			if (tline[0] == '\'') {	// Strip any enclosing quotes
				int ii;
				for (ii=0; ii < strlen(tline)-1; ii++)
					tline[ii]=tline[ii+1];
				j-=2;
				tline[j]='\0';
			}
			pargv = (char **) realloc(pargv,(pargc+1) * sizeof(char *));
			pargv[pargc] = (char *) malloc(j + 1);
			strcpy(pargv[pargc++],tline);
			j = 0;
			i++;
		}
		writeFile("/tmp/mangeplot.csv");
		plotBuffer(pargc,pargv);
		for (i = 0; i < pargc; i ++)
			free(pargv[i]);
		free(pargv);
		return 0;
	}
#endif	// __NO_PLOT__
	return 1;
}
