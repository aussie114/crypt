#include <gtk/gtk.h>

GtkWidget * window;

static gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data)
{
	(void)controller;
	(void)keycode;
	(void)state;
	if (keyval == GDK_KEY_Escape) 
	{
		gtk_window_destroy(GTK_WINDOW(user_data));
		return TRUE;
	}
		return FALSE;
}

void create_window(GtkApplication * program)
{
	window   = gtk_application_window_new(program);
	gtk_window_set_title        ( GTK_WINDOW (window), "Window");
	gtk_window_set_resizable    ( GTK_WINDOW (window), FALSE);

	GtkEventController * controller = gtk_event_controller_key_new();
	gtk_widget_add_controller(window, controller);
	g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), window);
}

