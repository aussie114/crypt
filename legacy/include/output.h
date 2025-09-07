#ifndef OUTPUT_H
#define OUTPUT_H
typedef struct
{
	GtkWidget * viewer;
	GtkWidget * scrolled_window;
	GtkTextBuffer * buffer;
	GtkTextIter iter;
} text_view;
void set_output(const char * text);
void append_to_output(const char * text);
void create_output();
#endif
