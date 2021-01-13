# COMMANDS TO BUILD THE PROJECT

## BUILD A SINGLE-FILE PROJECT :

gcc -o irma $(mysql_config --cflags) `pkg-config --cflags gtk+-3.0` main.c $(mysql_config --libs) `pkg-config --libs gtk+-3.0`

Format is : gcc -o <executable_filename> <flags> <source_file.c> <libs>

