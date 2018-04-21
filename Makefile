CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Werror=vla
EXEC = RSAEncryption.exe
OBJECTS = main.o Encrypt.o Decrypt.o File_Manage.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

