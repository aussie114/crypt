#include <gtk/gtk.h>
#include "global.h"
#include "gtk_helper_functions.h"
#include "generate_password.h"

static void on_generate_from_file_pressed(GtkWidget * caller, gpointer data)
{
	GtkWidget ** widgets = (GtkWidget **)data;
	ghf_text_view_set_text(widgets[4], "");
	gchar password[257];
	GtkTextBuffer * output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets[4]));
	GtkTextIter end_iter;
	gboolean error = false;

	// Get keyword
	gchar * keyword = ghf_entry_get_text(widgets[2]);
	if (gtk_entry_get_text_length(GTK_ENTRY(widgets[2])) == 0 )
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[2]), "Keyword required");
		error = true;
	}

	// Check for file path
	if (file_path == NULL)
	{
		ghf_text_view_set_text(widgets[4], "No file specified at run time");
		return;
	}

	// Opens file
	gchar * contents = NULL;
	gsize length = 0;
	GError * file_error = NULL;
	g_file_get_contents(file_path, &contents, &length, &file_error);
	if (file_error)
	{
		ghf_text_view_set_text(widgets[4], "Failed to open file");
		return;
	}

	if (error)
	{
		return;
	}

	// Splits file by newline
	gchar ** lines = g_strsplit(contents, "\n", -1);

	// iterates over lines
	for (gchar ** line = lines; *line != NULL; line++)
	{
		// skip on blank line
        if (g_strcmp0(*line, "") == 0)
		{
			continue;
		}

		// splits line by comma
		gchar ** fields = g_strsplit(*line, ",", -1);

		// generates and sets output
		generate_password(password, fields[0], fields[1], fields[2], fields[3], keyword);
		gchar * output = g_strdup_printf("/--------------------------------%s\n%s\n%s\n\n", fields[0], fields[1], password);

		gtk_text_buffer_get_end_iter(output_buffer, &end_iter);
		gtk_text_buffer_insert(output_buffer, &end_iter, output, -1);

		// frees memory
		g_strfreev(fields);
		g_free(output);
	}

	gtk_entry_set_placeholder_text(GTK_ENTRY(widgets[2]), "Keyword");

	g_free(contents);
	g_strfreev(lines);
}
