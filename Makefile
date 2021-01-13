CC= gcc -o
CFLAGS= $(shell mysql_config --cflags) $(shell pkg-config --cflags gtk+-3.0)
SRC= ./src/main.c
LIBS= $(shell mysql_config --libs) $(shell pkg-config --libs gtk+-3.0)

make:
	$(CC) irma $(CFLAGS) $(SRC) $(LIBS)
