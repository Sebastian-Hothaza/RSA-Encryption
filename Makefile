CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Werror=vla
EXEC = prog
OBJECTS = main.o burger.o baseburg.o topping.o decorator.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

