CFLAGS	:=	-O -DNDEBUG
LDFLAGS	:=	-static
all: basic.exe

basic.exe: basic_LM_example.cpp
	g++ ${CFLAGS} ${LDFLAGS} -o basic.exe -Ieigen-3.4.0 -static basic_LM_example.cpp

basic_split.exe: basic_split/main.o basic_split/solver.o
	g++ ${LDFLAGS} -o basic_split.exe -static basic_split/main.o basic_split/solver.o

basic_split/main.o: basic_split/main.cpp
	g++ ${CFLAGS} -Ieigen-3.4.0 -o basic_split/main.o -c basic_split/main.cpp

basic_split/solver.o: basic_split/solver.cpp
	g++ ${CFLAGS} -Ieigen-3.4.0 -o basic_split/solver.o -c basic_split/solver.cpp

clean: 
	rm -f basic.exe basic_split.exe basic_split/main.o basic_split/solver.o

.PHONY: clean