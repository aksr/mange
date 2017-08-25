#include "mange.h"

int editCell(int ei, int ej) {
	char line[MAXLINE];
	strcpy(line,getField(ei,ej));
	// need to set attribs here
	move(getY(ej),getX(ei));
	attrset(COLOR_EDIT);
	printw(" %*s ",getColWidth(ei)," ");
	int c = getLine(line,getX(ei),getY(ej));
	attrset(COLOR_NORMAL);
	if (strcmp(line,getField(ei,ej)) != 0) {	// changed value
		// TODO: save undo file
		saved=0;
		if (strlen(line) > strlen(getField(ei,ej))) {	// longer value
			getField(ei,ej) = (char *) realloc(getField(ei,ej),strlen(line) + 1);
			if (strlen(line) + 2 > col_width[ei])
				col_width[ei] = strlen(line);
		}
		setField(ei,ej,line);
		return c;
	}
	return 0;
}
