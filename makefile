OUT			= mange
VERSION		= 0.1b

OBJ			= mange.o commandLine.o readFile.o writeFile.o showBuffer.o msgLine.o commandMode.o \
			plotBuffer.o startCurses.o deleteCell.o insertCell.o editCell.o getLine.o showText.o undo.o
DISTFILES	= mange-1.0b.tar.gz

PREFIX		?= /usr/local
MANPREFIX	?= ${PREFIX}/share/man

CFLAGS		:= ${CFLAGS}
LDFLAGS		:= -lncurses ${LDFLAGS}

all: ${OUT}

${OUT}: ${OBJ} mange.h
	${CC} -o $@ ${OBJ} ${LDFLAGS}

strip: ${OUT}
	strip --strip-all ${OUT}

install: mange mange.1.gz
	install -D -m755 mange ${DESTDIR}${PREFIX}/bin/mange
	install -D -m644 mange.1.gz ${DESTDIR}${MANPREFIX}/man1/mange.1.gz

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	rm -f ${DESTDIR}${PREFIX}/bin/mange
	@echo removing man page from ${DESTDIR}${PREFIX}/man1/mange.1.gz
	rm -f ${DESTDIR}/${PREFIX}/man1/mange.1.gz

clean:
	${RM} ${OUT} ${OBJ}

.PHONY: clean install uninstall
