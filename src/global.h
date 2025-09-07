#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>

typedef struct {
    GtkWidget *viewer;
    GtkWidget *scrolled_window;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
} text_viewer;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *top_keyword_entry;
    GtkWidget *generate_from_file_button;

    text_viewer output;

    GtkWidget *service_entry;
    GtkWidget *username_entry;
    GtkWidget *length_entry;
    GtkWidget *special_entry;
    GtkWidget *bottom_keyword_entry;
    GtkWidget *generate_single_button;
} Widgets;

extern Widgets widgets;
extern char * file_address;

#endif
