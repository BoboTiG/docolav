CC     = g++
CFLAGS = -O3 -s -lm -lpthread
CFLAGS += -Wall -pedantic
PREFIX = /usr/bin
TOOL   = docolav
DOCDIR = /usr/share/doc/${TOOL}
MAN    = /usr/share/man/man1

all:
	${CC} ${CFLAGS} src/${TOOL}.cc -o ${TOOL}

clean:
	rm -f ${TOOL}

help:
	@echo make			: compile ${TOOL}
	@echo make clean	: purge les fichiers de compilation
	@echo make install	: installe ${TOOL} et sa docomentation
	@echo make man    	: génère la page du manuel
	@echo make uninstall: supprime ${TOOL} et sa documentation

install:
	install -s ${TOOL} ${PREFIX}
	mkdir -p ${DOCDIR}
	chmod 755 ${DOCDIR}
	install -m 644 -t ${DOCDIR} CHANGELOG LICENSE README.md REQUIREMENTS
	install -m 644 -t ${MAN} ${TOOL}.1.gz

man:
	@rm -f docolav.1.gz
	help2man -L=utf-8 -N --name="couleur moyenne dominante d'une image" ./docolav -o docolav.1.gz


uninstall:
	rm -f ${PREFIX}/${TOOL}
	rm -rf ${DOCDIR}
	rm -f ${MAN}/${TOOL}.1.gz
