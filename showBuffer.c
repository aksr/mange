#include "mange.h"

int oi=0, oj=0, mi=10;
int *col_width;

int setColWidth(){
	free(col_width);
	col_width = (int *) calloc(cols, sizeof(int));
    int tlen,i,j;
    for (j = 0; j < rows; j++) {
        for (i = 0; i < cols; i++) {
            tlen = strlen(getField(i,j));
            if (col_width[i] < tlen)
                col_width[i] = tlen;
        }
    }
}

int getX(int gi) {
	int i, x = 0;
	for (i=oi;i<gi;i++)
		x += (col_width[i]+2);
	return x;
}

int getY(int gj) {
	return gj-oj;
}

int getColWidth(int ci) {
	return col_width[ci];
}

int showBuffer(int *pi, int *pj) {
	clear();
	move(0,0);
	int ti,tj,i=*pi,j=*pj;
	int x,y;
	int twidth=0,tcol=0,trow=0;
	// x,y = active cell:
	if (i < 0) i = 0;
	if (i >= cols) i = cols - 1;
	if (i < oi) oi = i;
	if (i >= mi) {
		while (twidth < col_width[i])
			twidth += col_width[oi++];
	}
	twidth=2;
	if (j < 0) j = 0;
	if (j >= rows) j = rows-1;
	if (j < oj) oj = j;
	if (j > (oj + MaxRows -2)) oj = j - MaxRows + 2;
	*pi=i;
	*pj=j;
	x = oi;
	y = oj;
	if (y==0) y = 1;
	// x,y = upper left corner:
	for(ti = x; ti < cols; ti++) {
		twidth += col_width[ti] + 2;
		if (twidth > MaxCols)
			break;
	}
	tcol = ti;
	trow = rows;
	if (trow > MaxRows + y - 1)
		trow=MaxRows + y -1;
	attrset(COLOR_HEADER | A_BOLD);
	addch(' ');
	for(ti = x; ti < tcol; ti++) {
		if ((j == 0) && (ti == i))
			attrset(COLOR_HEADALT | A_BOLD);
		printw(" %*s ",col_width[ti],getField(ti,0));
		if ((j == 0) && (ti == i))
			attrset(COLOR_HEADER | A_BOLD);
	}
	printw("\n");
	attrset(COLOR_NORMAL | A_NORMAL);
	for (tj = y ; tj < trow; tj++) {
		if (tj == j)
			attrset(A_BOLD);
		else
			attrset(A_NORMAL);
		addch(' ');
		for(ti = x; ti < tcol; ti++) {
			if ((tj == j) && (ti == i))
				attrset(COLOR_NORMALT | A_BOLD);
			printw(" %*s ",col_width[ti],getField(ti,tj));
			if ((tj == j) && (ti == i))
				attrset(COLOR_NORMAL | A_BOLD);
		}
		printw("\n");
	}
	move(MaxRows,MaxCols-21);
	attrset(COLOR_HEADER | A_BOLD);
	printw("[%d/%d,%d/%d]",i,cols,j,rows);
	attrset(COLOR_NORMAL | A_NORMAL);
	refresh();
	mi = tcol;
	return 0;
}

