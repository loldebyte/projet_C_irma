#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <io.h>
#include <stdbool.h>
//  RAPPEL : CF format_du_fichier_settings.md POUR LE FORMAT EN LECTURE/ECRITURE

/* creates a settings.txt with default values */
void create_default_settings_file(void);
/* returns a stream to the settings.txt config file */
FILE * open_config(const char *);
/* returns 1 if conf file has correct size, else returns 0 */
int8_t conf_file_is_valid(void);
/* change font size with the inputed size*/
void font_size_change(const uint8_t);
/* returns a settings struct with fields initialized to current settings */
settings get_current_settings(void);

typedef Struct settings {
    uint8_t taille_police;
    char carte[10];
    char fond[10];
}settings;

void create_default_settings_file(void) {
}

settings get_current_settings(void) {
}

int8_t conf_file_is_valid(void) {
}
