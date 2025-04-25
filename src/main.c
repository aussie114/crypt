#include <gtk/gtk.h>
#include "global.h"
#include "gtk_helper_functions.h"
#include "generate_from_file.h"
#include "generate_single.h"

// ------------------------------------------------------------------------------------ function declarations
static void activate (GtkApplication* app, gpointer data);
static gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType modifiers, gpointer user_data);

// ----------------------------------------------------------------------------------------------------- Main
int main (int argc, char **argv)
{
	if (argc > 1)
	{
		file_path = argv[1];
	}

	GtkWidget * widgets[12];

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.crypt", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), widgets);
	int gtk_argc = 1;
	char * gtk_argv[] = {"crypt"};
	status = g_application_run (G_APPLICATION (app), gtk_argc, gtk_argv);
	g_object_unref (app);

	return status;
}

// -------------------------------------------------------------------------------------------------- Builder

static void activate (GtkApplication* app, gpointer data)
{
	GtkWidget **widgets = (GtkWidget **)data;

    // Create master window
    widgets[0] = ghf_create_window(app, "Crypt", 597, 902, FALSE);

	// Set up input handling
	GtkEventController * controller = gtk_event_controller_key_new();
	g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), widgets[0]);
	gtk_widget_add_controller(widgets[0], controller);

	// Create grid
	widgets[1] = ghf_create_grid(2, 2);
	ghf_widget_set_margin_all(widgets[1], 5);
	gtk_window_set_child(GTK_WINDOW(widgets[0]), widgets[1]);

	// Builder
	widgets[ 2] = ghf_create_widget(gtk_entry_new(),                        widgets[1], 0, 0, 1, 1);
	widgets[ 3] = ghf_create_widget(gtk_button_new_with_label("Generate from file"), widgets[1], 3, 0, 2, 1);

	GtkWidget * scrolled_window = gtk_scrolled_window_new();
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	widgets[ 4] = gtk_text_view_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), widgets[4]);
	gtk_grid_attach(GTK_GRID(widgets[1]), scrolled_window, 0, 1, 5, 1);

	widgets[ 5] = ghf_create_widget(gtk_entry_new(),                                 widgets[1], 0, 2, 1, 1);
	widgets[ 6] = ghf_create_widget(gtk_entry_new(),                                 widgets[1], 1, 2, 1, 1);
	widgets[ 7] = ghf_create_widget(gtk_label_new("Length"),                         widgets[1], 2, 2, 1, 1);
	widgets[ 8] = ghf_create_widget(gtk_spin_button_new_with_range(8, 256, 1),       widgets[1], 3, 2, 1, 1);
	widgets[ 9] = ghf_create_widget(gtk_check_button_new_with_label("Special"),      widgets[1], 4, 2, 1, 1);
	widgets[10] = ghf_create_widget(gtk_entry_new(),                                 widgets[1], 0, 3, 1, 1);
	widgets[11] = ghf_create_widget(gtk_button_new_with_label("Generate single"),    widgets[1], 3, 3, 2, 1);

	// configure widgets
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[2]), "Keyword");
	gtk_entry_set_visibility(GTK_ENTRY(widgets[2]), false);
	gtk_widget_set_halign(widgets[ 3], GTK_ALIGN_END);  // Right-align
	gtk_widget_set_size_request(scrolled_window, -1, 800);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(widgets[4]), true);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets[4]), false);
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[5]), "Service");
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[6]), "Username");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(widgets[9]), true);
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[10]), "Keyword");
	gtk_entry_set_visibility(GTK_ENTRY(widgets[10]), false);
	gtk_widget_set_halign(widgets[11], GTK_ALIGN_END);  // Right-align

	// Connect signal
	g_signal_connect(widgets[ 2], "activate", G_CALLBACK(on_generate_from_file_pressed), widgets);
	g_signal_connect(widgets[ 3], "clicked" , G_CALLBACK(on_generate_from_file_pressed), widgets);

	g_signal_connect(widgets[10], "activate", G_CALLBACK(on_generate_single_pressed),    widgets);
	g_signal_connect(widgets[11], "clicked" , G_CALLBACK(on_generate_single_pressed),    widgets);


	gtk_window_present (         GTK_WINDOW(widgets[0]));
}

// ------------------------------------------------------------------------------------------- Input handling
static gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType modifiers, gpointer user_data)
{
    if (keyval == GDK_KEY_Escape) 
	{
        GtkWindow * window = GTK_WINDOW(user_data);
        gtk_window_close(window);
        return TRUE;
    }
    return FALSE;
}
