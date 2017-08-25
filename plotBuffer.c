#include "mange.h"

// TODO: 3 variable categorical output "plots"

// Some of the plots are created with an initial R call to "plot" and subsequent calls to "points".
// Several graphical parameters will cause an error if passed to "points".  This macro defines a set
// of conditionals used in 'if' statements to parse out those parameters.
#define DOUBLE_PASS_PARAMETER	(strncmp(argv[i],"main=",5) != 0) && \
								(strncmp(argv[i],"xlab=",5) != 0) && \
								(strncmp(argv[i],"ylab=",5) != 0)

int plotBuffer(int argc, char **argv) {
	FILE *Rscript;
	char *yVar, *xVar, *cVar;
	char plotfile[MAXLINE] = "/tmp/mangeplot.jpg\0";
	int i, has_color;
	writeFile("/tmp/mangeplot.csv");
	Rscript = fopen("/tmp/mangeplot.r","w");
	fprintf(Rscript,"attach(read.csv(\"/tmp/mangeplot.csv\"))\njpeg(\"%s\")\n",plotfile);
	if ( (strchr(argv[1],'+')) == NULL ) {	// one or two variable plot
		if ( (strchr(argv[1],'~')) == NULL) {	// one variable plot
			fprintf(Rscript,"if (is.numeric(%s)){\nhist(%s",argv[1],argv[1]);
			for (i = 2; i < argc; i++)
				fprintf(Rscript,",%s",argv[i]);
			fprintf(Rscript,")\n} else {\ncapture.output(\n"); // else table
			fprintf(Rscript,"table(%s),\nfile=\"/tmp/mangeplot.txt\")\n}\n",argv[1]);
		}
		else {	// two variable plot:
			yVar = (char *) malloc(strlen(argv[1])+1);
			strcpy(yVar,argv[1]);
			*(strchr(yVar,'~')) = '\0';
			xVar = (char *) malloc(strlen(argv[1]) - strlen(yVar) + 1);
			strcpy(xVar,strchr(argv[1],'~')+1);
			fprintf(Rscript,"if (is.numeric(%s)){\nif (is.numeric(%s)){\n",yVar,xVar);	// then scatterplot
			fprintf(Rscript,"plot(%s",argv[1]);
			for (i = 2; i < argc; i++)
				fprintf(Rscript,",%s",argv[i]);
			fprintf(Rscript,")\n} else {\ntemp=NULL\nfor(i in levels(factor(%s)))\n",xVar); // esle barplot
			fprintf(Rscript,"temp=c(temp,mean(%s[%s==i]))\nbarplot(temp",yVar,xVar);
			for (i = 2; i < argc; i++)
				fprintf(Rscript,",%s",argv[i]);
			fprintf(Rscript,")\n}\n} else {\nif(is.numeric(%s)){\nlibrary(popbio)\n",xVar); // then logistic
			fprintf(Rscript,"logi.hist.plot(%s,%s==%s[1],boxp=FALSE,type=\"hist\"",xVar,yVar,yVar);
			for (i = 2; i < argc; i++)
				fprintf(Rscript,",%s",argv[i]);
			fprintf(Rscript,")\n} else {\ncapture.output(\ntable(%s,%s)\n",yVar,xVar);	// else table
			fprintf(Rscript,",\nfile=\"/tmp/mangeplot.txt\")\n}\n}\n");
			free(yVar);
			free(xVar);
		}
	}
	else {	// three variable plot
		yVar = (char *) malloc(strlen(argv[1])+1);
		strcpy(yVar,argv[1]);
		*(strchr(yVar,'~')) = '\0';
		xVar = (char *) malloc(strlen(argv[1]) - strlen(yVar) + 1);
		strcpy(xVar,strchr(argv[1],'~')+1);
		*(strchr(xVar,'+')) = '\0';
		cVar = (char *) malloc(strlen(argv[1]) - strlen(yVar) - strlen(xVar));
		strcpy(cVar,strchr(argv[1],'+')+1);
		fprintf(Rscript,"if (is.numeric(%s)){\nif (is.numeric(%s)){\n",yVar,xVar);	// then scatterplot by color
		fprintf(Rscript,"plot(%s~%s",yVar,xVar);
		for (i = 2; i < argc; i++)
			fprintf(Rscript,",%s",argv[i]);
		fprintf(Rscript,")\ncol=rainbow(length(levels(factor(%s))))\n",cVar);
		fprintf(Rscript,"c=1\nfor(i in levels(factor(%s))){\npoints(%s[%s==i]~%s[%s==i],col=col[c]",cVar,yVar,cVar,xVar,cVar);
		for (i = 2; i < argc; i++)
			if (DOUBLE_PASS_PARAMETER)
				fprintf(Rscript,",%s",argv[i]);
		fprintf(Rscript,")\nc=c+1}\n} else {\ntemp=NULL\nfor(i in levels(factor(%s)))\n",xVar);	// barplot by color
		fprintf(Rscript,"for(j in levels(factor(%s)))\n",cVar);
		fprintf(Rscript,"temp=c(temp,%s[(%s==i) & (%s==j)])\n",yVar,xVar,cVar);
		for (i = 2; i < argc; i++)		// test if color parameters have been passed
			if (strncmp(argv[i],"col=",4) == 0)
				has_color = 1;
		if (has_color == 1) {	// color passed
			fprintf(Rscript,"barplot(temp");
		}
		else {		// no color passed
			fprintf(Rscript,"col=rep(rainbow(length(levels(factor(%s)))),length(levels(factor(%s))))\n",cVar,xVar);
			fprintf(Rscript,"barplot(temp,col=col");
		}
		for (i = 2; i < argc; i++)
			fprintf(Rscript,",%s",argv[i]);
		fprintf(Rscript,")\n}\n} else {\ncapture.output(cat(\"Three variable plots with categorical\n"); // else tabulate TODO
		fprintf(Rscript,"outcome variables are not supported\nin this version of mange.\n\"),");
		fprintf(Rscript,"file=\"/tmp/mangeplot.txt\")\n}\n");
		free(yVar);
		free(xVar);
		free(cVar);
	}
	fprintf(Rscript,"dev.off()\n");
    fclose(Rscript);
    system("R --vanilla --slave </tmp/mangeplot.r &> /dev/null");
	FILE *txt;
	if ( (txt = fopen("/tmp/mangeplot.txt","r")) != NULL) {	// for text summaries of categorical outcome data
		showText(txt);
		fclose(txt);
		system("rm /tmp/mangeplot.txt &> /dev/null");
	}
	else {
    	system(SHOW_PLOT);
	}
	return 0;
}
