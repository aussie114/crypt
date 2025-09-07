#include <gtk/gtk.h>
#include "create.h"
#include "generate_password.h"
#include "output.h"

static GtkWidget * service_entry;
static GtkWidget * username_entry;
static GtkWidget * length_entry;
static GtkWidget * special_entry;
static GtkWidget * keyword_entry;
static GtkWidget * button;

static void on_button_pressed(GtkWidget * caller, gpointer data)
{
	(void)caller;
	(void)data;
	// Check entries
	gboolean error = false;
	// Keyword
	if ( gtk_entry_get_text_length( GTK_ENTRY(keyword_entry) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(keyword_entry) , "Keyword required" );
		error = true;
	}
	else
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(keyword_entry) , "Keyword" );
	}
	// Service
	if ( gtk_entry_get_text_length( GTK_ENTRY(service_entry) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(service_entry) , "Service required" );
		error = true;
	}
	else
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(service_entry) , "Service" );
	}
	// Username
	if ( gtk_entry_get_text_length( GTK_ENTRY(username_entry) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(username_entry) , "Username required" );
		error = true;
	}
	else
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(username_entry) , "Username" );
	}
	if (error) {return;}
	// Get fields
	const char * service  = gtk_editable_get_text(GTK_EDITABLE(service_entry));
	const char * username = gtk_editable_get_text(GTK_EDITABLE(username_entry));
	const char * length   = gtk_editable_get_text(GTK_EDITABLE(length_entry));
	const char * special;
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(special_entry)) == true)
	{
		special = "true";
	}
	else
	{
		special = "false";
	}
	const char * keyword = gtk_editable_get_text(GTK_EDITABLE(keyword_entry));

	// Create output
	char password[257];
	generate_password(password, service, username, length, special, keyword);
	gchar * output =  g_strdup_printf("/--------------------------------%s\n%s\n%s\n\n", service, username, password);

	// Write output
	set_output("");
	append_to_output(output);
	g_free(output);
}

void create_generate_single()
{
	service_entry  = create(gtk_entry_new(),                                  0,  2,  1,  1);
	username_entry = create(gtk_entry_new(),                                  1,  2,  1,  1);
	length_entry   = create(gtk_spin_button_new_with_range(8, 256, 1),        2,  2,  1,  1);
	special_entry  = create(gtk_check_button_new_with_label("Special"),       3,  2,  1,  1);
	keyword_entry  = create(gtk_entry_new(),                                  0,  3,  1,  1);
	button         = create(gtk_button_new_with_label("Generate single"),     2,  3,  2,  1);

	// Set placeholders
	gtk_entry_set_placeholder_text(GTK_ENTRY(service_entry), "Service");
	gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
	gtk_entry_set_placeholder_text(GTK_ENTRY(keyword_entry), "Keyword" );

	gtk_entry_set_visibility(GTK_ENTRY(keyword_entry), false);

	// Set default values
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(length_entry), 16);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(special_entry), true);

	g_signal_connect(button, "clicked", G_CALLBACK(on_button_pressed), NULL);
	g_signal_connect(service_entry,  "activate", G_CALLBACK(on_button_pressed), NULL);
	g_signal_connect(username_entry, "activate", G_CALLBACK(on_button_pressed), NULL);
	g_signal_connect(keyword_entry,  "activate", G_CALLBACK(on_button_pressed), NULL);
}
