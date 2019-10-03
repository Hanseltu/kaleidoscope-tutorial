
# SOURCES = $(shell find ast kaleidoscope lexer logger parser -name '*.cpp')
# HEADERS = $(shell find ast kaleidoscope lexer logger parser -name '*.h')
#
SOURCES = chapter2-Implementing-a-Parser-and-AST.cpp
OBJ = ${SOURCES:.cpp=.o}

CC = clang++
# -stdlib=libc++ -std=c++11
CFLAGS = -g -O3
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs all`

.PHONY: main

main: chapter2-Implementing-a-Parser-and-AST.cpp
	${CC} ${CFLAGS} ${LLVMFLAGS} $< -o toy

clean:
	rm -r ${OBJ}

%.o: %.cpp
	${CC} ${CFLAGS} ${LLVMFLAGS} -c $< -o $@

