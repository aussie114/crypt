#include <gtk/gtk.h>
#include "gtk_helper_functions.h"
#include "generate_password.h"

static void on_generate_single_pressed(GtkWidget * caller, gpointer data)
{
	GtkWidget ** widgets = (GtkWidget **)data;

	// Check inputs
	gboolean error = false;

	if ( gtk_entry_get_text_length(GTK_ENTRY(widgets[5])) == 0 )
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[5]), "Service required");
		error = true;
	}
	if ( gtk_entry_get_text_length(GTK_ENTRY(widgets[6])) == 0 )
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[6]), "Username required");
		error = true;
	}
	if ( gtk_entry_get_text_length(GTK_ENTRY(widgets[10])) == 0 )
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[10]), "Keyword required");
		error = true;
	}

	if (error)
	{
		return;
	}

	// Get inputs
	gchar * service  = (gchar *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widgets[ 5])));
	gchar * username = (gchar *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widgets[ 6])));
	gchar * length   = g_strdup_printf("%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgets[8])));
	gchar * special;
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets[9])))
	{
		special = "true";
	}
	else
	{
		special = "false";
	}
	gchar * keyword  = (gchar *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widgets[10])));


	// Generate and set output
	gchar password[257];
	generate_password(password, service, username, length, special, keyword);
	gchar * output = g_strdup_printf("/--------------------------------%s\n%s\n%s\n\n", service, username, password);

	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets[4])), output, -1);

	// Resets place holders
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[5]), "Service");
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[6]), "Username");
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[10]), "Keyword");

	// Free memory
	g_free(length);
	g_free(output);
}
