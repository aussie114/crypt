#include <gtk/gtk.h>
#include "main.h"
#include "window.h"
#include "grid.h"
#include "generate_from_file.h"
#include "output.h"
#include "generate_single.h"

void activate(GtkApplication * app, gpointer user_data)
{
	(void)user_data;
	create_window(app);
	create_grid();
	create_generate_from_file();
	create_output();
	create_generate_single();
	gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char ** argv)
{
	if (argc > 1)
	{
		file_address = argv[1];
		argc = 1;
	}
	GtkApplication * program;
	int status;

	program = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (program, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (program), argc, argv);
	g_object_unref (program);
	return status;
}


