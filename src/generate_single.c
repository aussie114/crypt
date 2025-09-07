#!/bin/sh
tail -n +5 "$0" | gcc -c -xc -Wall -Wextra -std=c99 `pkg-config --cflags gtk4` - -o build/"$(basename "$0" .c).o"
exit

#include <gtk/gtk.h>
#include "global.h"

static void on_generate_single_button_pressed(GtkWidget * caller, gpointer data);
void generate_password(char output[257], const char * service, const char * username, const char * length, const char * special, const char * keyword);
void set_output(const char * text);

void create_generate_single()
{
	// Create widgets
	widgets.service_entry         = gtk_entry_new();
	widgets.username_entry        = gtk_entry_new();
	widgets.length_entry          = gtk_spin_button_new_with_range(8, 256, 1);
	widgets.special_entry         = gtk_check_button_new_with_label("Special");
	widgets.bottom_keyword_entry  = gtk_entry_new();
	widgets.generate_single_button= gtk_button_new_with_label("Generate single");

	// Attach to grid
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.service_entry,          0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.username_entry,         1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.length_entry,           2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.special_entry,          3, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.bottom_keyword_entry,   0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(widgets.grid), widgets.generate_single_button, 2, 3, 2, 1);

	// Set placeholders
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets.service_entry), "Service");
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets.username_entry), "Username");
	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets.bottom_keyword_entry), "Keyword" );

	gtk_entry_set_visibility(GTK_ENTRY(widgets.bottom_keyword_entry), false);

	// Set default values
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets.length_entry), 16);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(widgets.special_entry), true);

	g_signal_connect(widgets.generate_single_button,  "clicked", G_CALLBACK(on_generate_single_button_pressed), NULL);
	g_signal_connect(widgets.service_entry,          "activate", G_CALLBACK(on_generate_single_button_pressed), NULL);
	g_signal_connect(widgets.username_entry,         "activate", G_CALLBACK(on_generate_single_button_pressed), NULL);
	g_signal_connect(widgets.bottom_keyword_entry,   "activate", G_CALLBACK(on_generate_single_button_pressed), NULL);
}

int check_entry(GtkWidget * entry, const char * placeholder, const char * alt_placeholder)
{
	if ( gtk_entry_get_text_length( GTK_ENTRY(entry) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(entry) , alt_placeholder );
		return 1;
	}
	else
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(entry) , placeholder );
		return 0;
	}
}

static void on_generate_single_button_pressed(GtkWidget * caller, gpointer data)
{
	(void)caller;
	(void)data;
	// Check Entries
	int error = 0;
	error += check_entry(widgets.service_entry,        "Service",  "Service required");
	error += check_entry(widgets.username_entry,      "Username", "Username required");
	error += check_entry(widgets.bottom_keyword_entry, "Keyword",  "Keyword required");
	if (error > 1) {return;}

	// Get fields
	const char * service  = gtk_editable_get_text(GTK_EDITABLE( widgets.service_entry));
	const char * username = gtk_editable_get_text(GTK_EDITABLE(widgets.username_entry));
	const char * length   = gtk_editable_get_text(GTK_EDITABLE(  widgets.length_entry));
	const char * special;
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets.special_entry)) == true)
	{
		special = "true";
	}
	else
	{
		special = "false";
	}
	const char * keyword = gtk_editable_get_text(GTK_EDITABLE(widgets.bottom_keyword_entry));

	// Create output
	char password[257];
	generate_password(password, service, username, length, special, keyword);
	gchar * output =  g_strdup_printf("/--------------------------------%s\n%s\n%s\n\n", service, username, password);

	// Write output
	set_output(output);
	g_free(output);
	return;
}
