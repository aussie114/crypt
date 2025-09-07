#include <gtk/gtk.h>
#include "grid.h"
#include "output.h"

static text_view output;

void set_output(const char * text)
{
	gtk_text_buffer_set_text(output.buffer, text, -1);
}

void append_to_output(const char * text)
{
	gtk_text_buffer_get_end_iter(output.buffer, &output.iter);
	gtk_text_buffer_insert(output.buffer, &output.iter, text, -1);
}

void create_output()
{
	output.viewer = gtk_text_view_new();
	output.scrolled_window = gtk_scrolled_window_new();
	output.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output.viewer));
	gtk_widget_set_size_request(output.scrolled_window, -1, 600);
	gtk_scrolled_window_set_child( GTK_SCROLLED_WINDOW(output.scrolled_window), output.viewer);

	// Set font
	gtk_text_view_set_editable(GTK_TEXT_VIEW(output.viewer), false);
	gtk_widget_add_css_class(output.viewer, "monospace");
	GtkCssProvider * provider = gtk_css_provider_new();
	gtk_css_provider_load_from_string(provider,	".monospace { font-family: monospace; font-size: 10pt; }");
	gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	g_object_unref(provider);

	gtk_grid_attach (GTK_GRID(grid), output.scrolled_window, 0, 1, 4, 1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(output.viewer), false);
}
