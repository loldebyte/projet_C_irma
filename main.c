#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h>
#include <string.h>

/* terminates programm and flushes all streams */
void finish_with_error();
/* creates the window and sets its position and title */
GtkWidget * generate_window(char *);
/* initializes the connexion to the DB and returns it */
MYSQL* open_database();
/* executes a DB query and returns its result as a MY_SQL_RES pointer */
MYSQL_RES * dbquery();
/* resets lock onto a GtkWidget, allowing it to be opened again */
void close_popup();
/* frees the int pointer lock */
void free_lock();
/* creates main window and related widgets */
void home();
/* closes window passed as argument and calls home() */
void transition_home();
/* closes window passed as argument */
void close_window(GtkWidget *, GtkWidget *);

void get_params(int *size_x, int *size_y, int * position, int *windowed){
    
    FILE * pf;
    char * fullscreen;
    char * get_position;
    char * get_size_x;
    char * get_size_y;
    char * cursor;
    int inter;

    cursor = malloc(sizeof(char)*255);

    pf = fopen("parameters.conf","rt");
    printf("\ndebug : file opened\n");

    if(!pf)
        return;

    fullscreen = malloc(sizeof(char)*255);
    fgets(fullscreen,255,pf);
    if (strstr(fullscreen,"NO")){
        *windowed = 1;
        printf("\ndebug : is not fullscreen\n");
    }else{
        *windowed = 0;
    }

    get_position = malloc(sizeof(char)*255);
    fgets(get_position,255,pf);
    cursor = strstr(get_position,":");
    inter =atoi(cursor+2);
    *position = inter;
    printf("\ndebug : position is %d\n", *position);

    get_size_x = malloc(sizeof(char)*255);
    fgets(get_size_x,255,pf);
    cursor = strstr(get_size_x,":");
    inter = atoi(cursor+2);
    *size_x = inter; 
    printf("\ndebug : size x is %d\n", *size_x);

    get_size_y = malloc(sizeof(char)*255);
    fgets(get_size_y,255,pf);
    cursor = strstr(get_size_y,":");
    inter = atoi(cursor+2);
    *size_y = inter; 
    printf("\ndebug : size y is %d\n", *size_y);

    free(get_size_x);
    printf("\nfree 1\n");
    free(get_size_y);
    printf("\nfree 2\n");
    free(get_position);
    printf("\nfree 3\n");
    free(fullscreen);
    printf("\nfree 4\n");
    //free(cursor);
    printf("\nfree 5\n");
    fclose(pf);
    printf("\nclosed");
}

char * get_date(char * date){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(date, "%d/%d/%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
  printf("\n debug : date is %s", date);
  return date;
}

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

GtkWidget * generate_window(char * title) {
    GtkWidget* p_window;
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    int size_x, size_y, windowed, position;

    get_params(&size_x, &size_y, &position, &windowed);
    printf("\ndebug : file closed with values:\nsize_x : %d\nsize_y : %d\nwindowed : %d\nposition : %d\n", size_x, size_y, windowed, position);

    switch(position){
        case 1 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_NONE);
                 printf("\ndebug : case is %d\n", position);
        break;
        case 2 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER);
        break;
        case 3 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_MOUSE);
        break;
        case 4 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER_ALWAYS);
        break;
        default : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_NONE);
    }

    if(windowed == 1){
        gtk_window_set_default_size(GTK_WINDOW(p_window), size_x, size_y);
    }
    if(windowed == 0){
        gtk_window_fullscreen (GTK_WINDOW(p_window));
    }

    gtk_window_set_title(GTK_WINDOW(p_window), title);

    return p_window;

};

MYSQL* open_database() { // Don't forget to close the connexion !
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) 
    {
        printf("%s\n", mysql_error(con));
        printf("\ndebug : DTB init is not open\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "developper", "project", 
            NULL, 0, NULL, 0) == NULL) 
    {
        printf("%s\n", mysql_error(con));
        printf("\ndebug : DTB connexion is not open\n");
        mysql_close(con);
        exit(1);
    }
    printf("\ndebug : Connexion to DTB Successful\n");
    return con;
}

MYSQL_RES * dbquery(MYSQL * con, char * query) {
    if (mysql_query(con, query)) 
  {
      printf("\ndebug : error during query\n");
      finish_with_error(con);
  }
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {     
      printf("\ndebug : result is NULL\n");
      finish_with_error(con);
  }
    printf("\ndebug : request correctely sent\n");
    return result;
}

void dbinsert(MYSQL * con, char * query) {
    if (mysql_query(con, query)) 
  {
      printf("\ndebug : error during query\n");
      finish_with_error(con);
  }
      printf("\ndebug : request correctely sent");
}

void close_window(GtkWidget * button, GtkWidget *principal_window) {
    gtk_window_close(GTK_WINDOW(principal_window));
}

void close_popup(GtkWidget* popup, int * lock) {
    *lock = 0;
    printf("\ndebug : lock is 0\n");
}

void free_lock(GtkWidget * window, int * lock) {
    free(lock);
    printf("lock is free");
}

void home() {
    char * title = "Menu principal";
    GtkWidget * grid, *principal_window, *_;

    principal_window = generate_window(title);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    _ = gtk_button_new_with_label("_");
    gtk_grid_attach(GTK_GRID(grid), _, 0, 0, 1, 1);
    g_signal_connect(_, "clicked", G_CALLBACK(_), principal_window);


    gtk_widget_show_all(principal_window);
}

void transition_home(GtkWidget * principal_window) {
    gtk_window_close(GTK_WINDOW(principal_window));
    home();
}

int main(int argc, char **argv)
{    
    gtk_init(&argc,&argv);
    
    char * title = "Irma";
    GtkWidget* grid, *headtitle, *principal_window, *button;

    principal_window = generate_window(title);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    headtitle = gtk_label_new("Bienvenue sur Irma");
    gtk_grid_attach(GTK_GRID(grid), headtitle, 0, 0, 3, 3);
    gtk_label_set_justify (GTK_LABEL(headtitle), GTK_JUSTIFY_CENTER);

    button = gtk_button_new_with_label("Commencer");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 3, 3);
    g_signal_connect(button, "clicked", G_CALLBACK(transition_home), principal_window);

    
    gtk_widget_show_all(principal_window);// Showing all the widget under principal_window

    gtk_main();
    
    return EXIT_SUCCESS;
}

