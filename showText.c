#include "mange.h"

int showText(FILE *stream) {
	int count = 0, width = 0, i;
	char line[MAXLINE];
	// count lines and columns of file
	while ( fscanf(stream,"%[^\n]\n",line) != EOF ) {
		if (strlen(line) > width)
			width=strlen(line);
		count++;
	}
	width++;
	fseek(stream,0,SEEK_SET);
	// draw a text box
	move((MaxRows-count)/2 -2,(MaxCols-width)/2 -2);
	attrset(COLOR_PAIR(9) | A_BOLD);
	addch(ACS_ULCORNER);
	for (i = 0; i < width; i ++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for (i = 0; i < count; i ++){
		move((MaxRows-count)/2 -1 + i,(MaxCols-width)/2 -2);
		addch(ACS_VLINE);
		move((MaxRows-count)/2 -1 + i,(MaxCols-width)/2 + width - 1);
		addch(ACS_VLINE);
	}
	move((MaxRows-count)/2 -1 + count,(MaxCols-width)/2 -2);
	addch(ACS_LLCORNER);
	for (i = 0; i < width; i ++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
	move((MaxRows-count)/2-1,(MaxCols-width)/2-1);
	attrset(COLOR_PAIR(9));
	// print the file
	i = 0;
	while ( fscanf(stream,"%[^\n]\n",line) != EOF ) {
		printw("%s%*s",line,width-strlen(line)," ");
		move((MaxRows-count)/2+(i++),(MaxCols-width)/2-1);
	}
	getch();
	return 0;
}
