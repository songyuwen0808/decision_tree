objects=main.o decision_tree.o tools.o info_ent.o

LIBS=

INCLUDE=-I ./ -I /usr/local/include -I /usr/include

DEFINE=

LDFLAGS=-g 

BIN=decision_tree

${BIN}:${objects}
	g++ ${LDFLAGS} -o ${BIN} ${objects} ${LIBS} ${INCLUDE} ${DEFINE}
	cp -f ${BIN} ../bin/

main.o:main.cpp decision_tree.h tools.h
	g++ ${LDFLAGS} -c main.cpp

decision_tree.o:decision_tree.cpp decision_tree.h
	g++ ${LDFLAGS} -c decision_tree.cpp

info_ent.o:info_ent.cpp info_ent.h
	g++ ${LDFLAGS} -c info_ent.cpp

tools.o:tools.cpp tools.h
	g++ ${LDFLAGS} -c tools.cpp

clean:
	rm -f ${BIN} ${objects} core

