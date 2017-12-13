objects=main.o decision_tree.o

LIBS=

INCLUDE=-I ./ -I /usr/local/include -I /usr/include

DEFINE=

LDFLAGS=-g 

BIN=decision_tree

${BIN}:${objects}
	g++ ${LDFLAGS} -o ${BIN} ${objects} ${LIBS} ${INCLUDE} ${DEFINE}

main.o:main.cpp decision_tree.h
	g++ ${LDFLAGS} -c main.cpp

decision_tree.o:decision_tree.cpp decision_tree.h
	g++ ${LDFLAGS} -c decision_tree.cpp

clean:
	rm -f ${BIN} ${objects} core
