CC=gcc

APP_CFLAGS=-Wall -Wextra -Werror \
	-fsanitize=address \
	-fsanitize=undefined

UTF8PROC_CFLAGS=-w

CPPFLAGS=-I./external/utf8proc

EXEC=./bin/main

SRC=./src/main.c

UTF8PROC_SRC= \
	./external/utf8proc/utf8proc.c \
	./external/utf8proc/utf8proc_data.c


all: $(EXEC)

$(EXEC):
	mkdir -p ./bin
	$(CC) $(CPPFLAGS) \
		$(APP_CFLAGS) \
		$(UTF8PROC_CFLAGS) \
		$(SRC) $(UTF8PROC_SRC) \
		-o $(EXEC)

clean:
	rm -rf ./bin/*
