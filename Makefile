CC= gcc -o
CFLAGS= $(shell mysql_config --cflags) $(shell pkg-config --cflags gtk+-3.0)
SRC= ./src/main.c
LIBS= $(shell mysql_config --libs) $(shell pkg-config --libs gtk+-3.0)
GTK_OPTION= -DGDK_DISABLE_DEPRECATION_WARNINGS

make:
	$(CC) irma $(CFLAGS) $(GTK_OPTION) $(SRC) $(LIBS)
