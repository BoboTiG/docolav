CC     = g++
CFLAGS = -O3 -s
LIBS   = -lm -lopencv_core -lopencv_highgui
PREFIX = /usr/bin
TOOL   = docolav
DOCDIR = /usr/share/doc/${TOOL}
MAN    = /usr/share/man/man1

all: clean
	mkdir -p bin
	${CC} ${CFLAGS} ${LIBS} src/main.cpp -o bin/${TOOL}

clean:
	rm -f bin/${TOOL}

help:
	@echo make			: build ${TOOL}
	@echo make clean	: purge the folder from previous built
	@echo make install	: install ${TOOL} and doc files
	@echo make uninstall: uninstall ${TOOL} and doc files

install:
	install -s bin/${TOOL} ${PREFIX}
	mkdir -p ${DOCDIR}
	chmod 755 ${DOCDIR}
	install -m 644 -t ${DOCDIR} CHANGELOG LICENSE README.md REQUIREMENTS
	install -m 644 -t ${MAN} ${TOOL}.1.gz

uninstall:
	rm -f ${PREFIX}/${TOOL}
	rm -rf ${DOCDIR}
	rm -f ${MAN}/${TOOL}.1.gz
