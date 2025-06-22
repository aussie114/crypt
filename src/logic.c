#include <gtk/gtk.h>
#include "main.h"
#include "sha256.h"
#include "stdlib.h"
#include "stdio.h"
#include "file.h"

gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data)
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

char * charactors = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
void generate_password(char output[], const char * service, const char * username, const char * length, const char * special, const char * keyword)
{
	// ------------------------------------------------------------------------------------------ hash inputs
	char hashes[5][65];
	sha256(service,  hashes[0]);
	sha256(username, hashes[1]);
	sha256(length,   hashes[2]);
	sha256(special,  hashes[3]);
	sha256(keyword,  hashes[4]);
	// -------------------------------------------------------- Zips 256 hashes together into a single string
	char hash_string[321] = {'\0'};
	for (int i = 0, j = 0; i < 320; i += 5, j++)
	{
		for (int k = 0; k < 5; k++)
		{
			hash_string[i+k]   = hashes[k][j];
		}
	}
	// ------------------------------------------------------------------------------ Gets initial seed value
	unsigned long long seed_value = 0;
	unsigned long long seed_value_capped = 0;
	for (int i = 0; i < 320; i++)
	{
		seed_value += hash_string[i];
	}
	// ------------------------------------------------------------------------------------------- Sets range
	unsigned int flags[4] = {0}; // lower case, upper case, numerica. special
	int cap = 70;
	if (special[0] == 'f')
	{
		cap = 62;
		flags[3] = 1;
	}
	// --------------------------------------------------------------------------------- Generates a password
	int attempt = 0;
	long long password_length = strtoll(length, NULL, 10);
	while (1)
	{
		for (int i = 0; i < 257; i++)
		{
			output[i] = '\0';
		}
		attempt += 1;
		for (int i = 0; i < password_length; i++)
		{
			seed_value += hash_string[i];
			seed_value_capped = seed_value % cap;
			flags[0] += (seed_value_capped <= 25);
			flags[1] += (seed_value_capped >= 26) && (seed_value_capped <= 51);
			flags[2] += (seed_value_capped >= 52) && (seed_value_capped <= 61);
			flags[3] += (seed_value_capped >= 62);
			output[i] = charactors[seed_value_capped];
		}
		// ----------------------------------------------------------------------- Returns after 100 attempts
		if (attempt >= 100)
		{
			return;
		}
		// ------------------------------------------------------------------------------------- Checks flags
		if ((flags[0] > 0) && (flags[1] > 0) && (flags[2] > 0) && (flags[3] > 0))
		{
			return;
		}
		// -------------------------------------------------------------------------------- Password rejected
		//g_print("Password rejected: %s flags: %d, %d, %d, %d\n", output, flags[0], flags[1], flags[2], flags[3]);
		flags[0] = 0;
		flags[1] = 0;
		flags[2] = 0;
		if (special[0] == 'f')
		{
			flags[3] = 1;
		}
		else
		{
			flags[3] = 0;
		}
	}
}

void on_generate_from_file_pressed(GtkWidget * caller, gpointer data)
{

	(void)caller;
	widget * widgets = (widget *)data;
	GtkTextBuffer * buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(OUTPUT));
	GtkTextIter end_iter;

	// Check keyword entry
	if ( gtk_entry_get_text_length( GTK_ENTRY(TOP_KEYWORD_ENTRY) ) == 0)
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(TOP_KEYWORD_ENTRY) , "Keyword required" );
		return;
	}
	else
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(TOP_KEYWORD_ENTRY) , "Keyword" );

	}

	// Check for file address
	if (file_address == NULL)
	{
		gtk_text_buffer_set_text(buffer, "No file specified", -1);
		return;
	}

	FILE * file = fopen(file_address, "r");
	if (!file)
	{
		gtk_text_buffer_set_text(buffer, "Specified file not found", -1);
		return;
	}
	char line_buffer[line_buffer_size];
	int line = 0;
	gtk_text_buffer_set_text(buffer, "", -1);
	while (fgets(line_buffer, line_buffer_size, file) != NULL)
	{
		line++;
		//  Check for empty line and strips newline
		if (line_buffer[0] == '\n')	{continue;}
		line_buffer[strcspn(line_buffer, "\n")] = '\0';
		
		// Gets fields
		char * service  = strtok(line_buffer, ",");
		char * username = strtok(NULL, ",");
		char * length   = strtok(NULL, ",");
		char * special  = strtok(NULL, ",");

		// Checks fields
		if (!service || !username || !length || !special) 
		{
			int output_buffer_size = 1 + snprintf(NULL, 0,  "Line %d is malformed, skipping.\n\n", line);
			char output_buffer[output_buffer_size];
			snprintf(output_buffer, output_buffer_size, "Line %d is malformed, skipping.\n\n", line);
			gtk_text_buffer_get_end_iter(buffer, &end_iter);
			gtk_text_buffer_insert(buffer, &end_iter, output_buffer, -1);
			continue;
		}

		const char * keyword  = gtk_editable_get_text(GTK_EDITABLE(TOP_KEYWORD_ENTRY));
		char password[257];
		generate_password(password, service, username, length, special, keyword);

		int output_buffer_size = 1 + snprintf(NULL, 0,  "/--------------------------------%s\n%s\n%s\n\n", service, username, password);
		char output_buffer[output_buffer_size];
		snprintf(output_buffer, output_buffer_size, "/--------------------------------%s\n%s\n%s\n\n", service, username, password);

		// Write to output
		gtk_text_buffer_get_end_iter(buffer, &end_iter);
		gtk_text_buffer_insert(buffer, &end_iter, output_buffer, -1);
	}
	fclose(file);
}

void on_generate_single_pressed(GtkWidget * caller, gpointer data)
{
	(void)caller;
	widget * widgets = (widget *)data;

	// Check entries
	gboolean error = false;
	if ( gtk_entry_get_text_length( GTK_ENTRY(BOTTOM_KEYWORD_ENTRY) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(BOTTOM_KEYWORD_ENTRY) , "Keyword required" );
		error = true;
	}
	if ( gtk_entry_get_text_length( GTK_ENTRY(SERVICE_ENTRY) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(SERVICE_ENTRY) , "Service required" );
		error = true;
	}
	if ( gtk_entry_get_text_length( GTK_ENTRY(USERNAME_ENTRY) ) == 0 )
	{
		gtk_entry_set_placeholder_text( GTK_ENTRY(USERNAME_ENTRY) , "Username required" );
		error = true;
	}
	if (error) {return;}

	// Get entries
	const char * service  = gtk_editable_get_text(GTK_EDITABLE(SERVICE_ENTRY));
	const char * username = gtk_editable_get_text(GTK_EDITABLE(USERNAME_ENTRY));
	const char * length   = gtk_editable_get_text(GTK_EDITABLE(LENGTH_ENTRY));
	const char * special;
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(SPECIAL_ENTRY)) == true)
	{
		special = "true";
	}
	else
	{
		special = "false";
	}
	const char * keyword = gtk_editable_get_text(GTK_EDITABLE(BOTTOM_KEYWORD_ENTRY));

	// Create password
	char password[257];
	generate_password(password, service, username, length, special, keyword);

	// Generate output
	int output_text_size = 1 + snprintf(NULL, 0,  "/--------------------------------%s\n%s\n%s", service, username, password);
	char output_text[output_text_size];
	snprintf(output_text, output_text_size, "/--------------------------------%s\n%s\n%s", service, username, password);

	// Write output
	GtkTextBuffer * buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(OUTPUT));
	gtk_text_buffer_set_text(buffer, output_text, -1);
}

void connect_signals(widget * widgets, GtkEventController * controller)
{
	g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), WINDOW);
	g_signal_connect(GENERATE_FROM_FILE_BUTTON, "clicked", G_CALLBACK(on_generate_from_file_pressed), widgets);
	g_signal_connect(TOP_KEYWORD_ENTRY, "activate", G_CALLBACK(on_generate_from_file_pressed), widgets);
	g_signal_connect(GENERATE_SINGLE_BUTTON, "clicked", G_CALLBACK(on_generate_single_pressed), widgets);
	g_signal_connect(BOTTOM_KEYWORD_ENTRY, "activate", G_CALLBACK(on_generate_single_pressed), widgets);
}
