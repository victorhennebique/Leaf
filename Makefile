CC=gcc

CFLAGS=-Wall -Wextra -Werror \
       -fsanitize=address \
       -fsanitize=undefined

CPPFLAGS=-I./src \
         -I./include \
         -I./external/utf8proc \

EXEC=./bin/leaf

UTF8PROC_DIR=./external/utf8proc
UTF8PROC_OBJ=./build/utf8proc.o

SRC=./src/main.c \
    ./src/scanner/scanner.c


all: $(EXEC)


# Compilation du programme final
$(EXEC): $(SRC) $(UTF8PROC_OBJ)
	mkdir -p ./bin
	$(CC) $(CPPFLAGS) $(CFLAGS) \
		$(SRC) \
		$(UTF8PROC_OBJ) \
		-o $(EXEC)


# Construit utf8proc uniquement si nécessaire
$(UTF8PROC_OBJ):
	$(MAKE) -C $(UTF8PROC_DIR)
	mkdir -p ./build
	cp $(UTF8PROC_DIR)/utf8proc.o $(UTF8PROC_OBJ)


clean:
	rm -rf ./bin/*

.PHONY: all clean
