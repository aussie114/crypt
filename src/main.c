#include <gtk/gtk.h>
#include "main.h"
#include "config.h"
#include "logic.h"
#include "file.h"

void activate(GtkApplication * app, gpointer user_data)
{
	(void)user_data;
	widget * widgets = (widget *)user_data;

	widgets[ 0] = (widget){gtk_application_window_new(app),                  0,  0,  0,  0};
	widgets[ 1] = (widget){gtk_grid_new(),                                   0,  0,  0,  0};
	widgets[ 2] = (widget){gtk_text_view_new(),                              0,  0,  0,  0};

	widgets[ 3] = (widget){gtk_entry_new(),                                  0,  0,  1,  1};
	widgets[ 4] = (widget){gtk_button_new_with_label("Generate from file"),  2,  0,  2,  1};
	
	widgets[ 5] = (widget){gtk_scrolled_window_new(),                        0,  1,  4,  1};
		
	widgets[ 6] = (widget){gtk_entry_new(),                                  0,  2,  1,  1};
	widgets[ 7] = (widget){gtk_entry_new(),                                  1,  2,  1,  1};
	widgets[ 8] = (widget){gtk_spin_button_new_with_range(8, 256, 1),        2,  2,  1,  1};
	widgets[ 9] = (widget){gtk_check_button_new_with_label("Special"),       3,  2,  1,  1};

	widgets[10] = (widget){gtk_entry_new(),                                  0,  3,  1,  1};
	widgets[11] = (widget){gtk_button_new_with_label("Generate single"),     2,  3,  2,  1};

	GtkEventController * controller = gtk_event_controller_key_new();
	
	config(widgets, controller);
	connect_signals(widgets, controller);

	gtk_window_present (         GTK_WINDOW (WINDOW));
}

int main (int argc, char ** argv)
{
	if (argc > 1)
	{
		file_address = argv[1];
		argc = 1;
	}
	get_line_buffer_size();
	GtkApplication *app;
	int status;

	widget widgets[12];

	app = gtk_application_new ("org.gtk.crypt", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), widgets);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}


