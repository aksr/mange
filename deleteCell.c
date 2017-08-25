#include "mange.h"

#define DEL_ERROR	{msgLine(COLOR_ERROR,MSG_GO,"Cannot delete last cell!"); return 1;}

int deleteCell(int di, int dj) {
	char *tptr;
	int ti,tj;
	int c = msgLine(COLOR_MODES,MSG_KEY,"[DEL] ^Column, ^Row, ^Entry?");
	switch (c) {
		case 'r':
			if (rows == 1)
				DEL_ERROR
			saved=0;
			rows--;
			for (ti = 0; ti < cols; ti++)
				free(getField(ti,dj));
			for (tj = dj; tj < rows; tj++)
				for (ti = 0; ti < cols; ti++)
					getField(ti,tj) = getField(ti,tj+1);
			buffer=realloc(buffer,(rows*cols+1) * sizeof(char *));
			break;
		case 'c':
			if (cols == 1)
				DEL_ERROR
			saved=0;
			for (tj = 0; tj < rows; tj++)
				free(getField(di,tj));
			cols--;
			for (tj = 0; tj < rows; tj ++)
				for (ti = di; ti < cols + di; ti++)
					getField(ti,tj) = getField(ti+tj+1,tj);
			buffer=realloc(buffer,(rows*cols+1) * sizeof(char *));
			for (ti = di; ti < cols; ti++)
				col_width[ti] = col_width[ti+1];
			col_width = (int *) realloc(col_width,cols * sizeof(int));
			break;
		case 'e':
			if ( (rows==1) && (cols==1) )
				DEL_ERROR
			saved=0;
/*			c = msgLine(COLOR_MODES,MSG_KEY,"[DEL] Shift ^Left, Shift ^Up, Leave ^Empty?");
			switch(c) {
				case 'L':
				case 'l':
				case KEY_LEFT:
					setField(di,dj,"");
					tptr=getField(di,dj);
					for (ti = di; ti < (cols-1); ti ++)
						getField(ti,dj) = getField(ti+1,dj);
					getField(cols-1,dj) = tptr;
					int tlen;
					for (ti = 0; ti < rows; ti ++) {
						tlen = strlen(getField(ti,dj));
							if (col_width[ti] < tlen)
								col_width[ti] = tlen;
					}
					break;
				case 'U':
				case 'u':
				case KEY_UP:
					setField(di,dj,"");
					tptr=getField(di,dj);
					for (tj = dj; tj < (rows-1); tj ++)
						getField(di,tj) = getField(di,tj+1);
					getField(di,rows-1) = tptr;
					break;
				case 'E':
				case 'e':
				case '0': */
					setField(di,dj," ");
					break;
				default:
					break;
/*			}
			break;
		default:
			break;*/
	}
	return 0;
}
