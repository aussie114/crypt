#include <gtk/gtk.h>
#include "create.h"
#include "generate_password.h"
#include "output.h"

const char * file_address = NULL;
static GtkWidget * keyword_entry;
static GtkWidget * button;

static void on_button_pressed(GtkWidget * caller, gpointer data)
{
	(void)caller;
	(void)data;

	// Check of file address
	if (file_address == NULL)
	{
		set_output("No input file specified");
	}

	// Check for keyword
	if (gtk_entry_get_text_length(GTK_ENTRY(keyword_entry)) == 0)
	{
		gtk_entry_set_placeholder_text(GTK_ENTRY(keyword_entry), "Keyword required" );
		return;
	}
	gtk_entry_set_placeholder_text(GTK_ENTRY(keyword_entry), "Keyword" );
	const char * keyword  = gtk_editable_get_text(GTK_EDITABLE(keyword_entry));

	// Open file
    GError * error = NULL;
    GFile * file = g_file_new_for_path(file_address);
    GFileInputStream * file_stream = g_file_read(file, NULL, &error);
    if (!file_stream) 
	{
		gchar * output =  g_strdup_printf("%s", error->message);
		set_output(output);
        g_error_free(error);
        g_object_unref(file);
		g_free(output);
        return;
    }

	// Stream file
	set_output("");
    GDataInputStream * data_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
    gchar * line;
    gsize length;
    while ((line = g_data_input_stream_read_line(data_stream, &length, NULL, &error)) != NULL) 
	{
		gchar ** fields = g_strsplit(line, ",", -1);
		
		gint count = 0;
		for (gint i = 0; fields[i] != NULL; i++) 
		{
			count++;
		}
		if (count != 4) 
		{
			g_print("Skipped malformed line: %s\n", line);
			return;
		}

		char password[257];
		generate_password(password, fields[0], fields[1], fields[2], fields[3],  keyword);
		gchar * output =  g_strdup_printf("/--------------------------------%s\n%s\n%s\n\n", fields[0], fields[1], password);
		append_to_output(output);

		g_free(output);
		g_strfreev(fields);
		g_free(line);
    }

    g_object_unref(data_stream);
    g_object_unref(file_stream);
    g_object_unref(file);
}

void create_generate_from_file()
{
	keyword_entry = create(gtk_entry_new(),                          0, 0, 1, 1);
	button = create(gtk_button_new_with_label("Generate from file"), 2, 0, 2, 1);

	gtk_widget_set_size_request(keyword_entry, 100, -1);
	gtk_entry_set_placeholder_text(GTK_ENTRY(keyword_entry), "Keyword" );
	gtk_entry_set_visibility(GTK_ENTRY(keyword_entry), false);


	g_signal_connect(button, "clicked", G_CALLBACK(on_button_pressed), NULL);
	g_signal_connect(keyword_entry, "activate", G_CALLBACK(on_button_pressed), NULL);
}
