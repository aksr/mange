#include "mange.h"

int continuation = 0;
char inLine[MAXLINE];

int msgLine(int color, int mode, const char *format) {
	int i,count=2;
	if (continuation == 0) {
		move(MaxRows,0);
		attrset(color);
    	printw("_%*s",MaxCols-2," ");
		move(MaxRows,0);
		refresh();
	}
	continuation = 0;
	i = 0;
	while (i < strlen(format)) {
		if (format[i] == '^') {
			attrset(color | A_BOLD);
			addch(format[++i]);
			i++;
			attrset(color);
		}
		else {
			count++;
			addch(format[i++]);
		}
	}
	if (mode == MSG_START) {
		continuation = 1;
		return 0;
	}
	refresh();
	if (mode == MSG_GO) {
		getchar();
		return 0;
	}
	if (mode == MSG_KEY)
		return getchar();
	if (mode == MSG_LINE) {
		int tj,ti;
		inLine[0] = '\0';
		getyx(stdscr,tj,ti);
		getLine(inLine,ti,MaxRows);
		return (int) inLine;
	}
}
