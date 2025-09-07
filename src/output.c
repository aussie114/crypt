#!/bin/sh
tail -n +5 "$0" | gcc -c -xc -Wall -Wextra -std=c99 `pkg-config --cflags gtk4` - -o build/"$(basename "$0" .c).o"
exit

#include <gtk/gtk.h>
#include "global.h"

void create_output()
{
	widgets.output.viewer = gtk_text_view_new();
	widgets.output.scrolled_window = gtk_scrolled_window_new();
	widgets.output.buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets.output.viewer));
	gtk_widget_set_size_request(widgets.output.scrolled_window, -1, 600);
	gtk_scrolled_window_set_child( GTK_SCROLLED_WINDOW(widgets.output.scrolled_window), widgets.output.viewer);

	// Set font
	gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets.output.viewer), false);
	gtk_widget_add_css_class(widgets.output.viewer, "monospace");
	GtkCssProvider * provider = gtk_css_provider_new();
	gtk_css_provider_load_from_string(provider,	".monospace { font-family: monospace; font-size: 10pt; }");
	gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	g_object_unref(provider);

	gtk_grid_attach (GTK_GRID(widgets.grid), widgets.output.scrolled_window, 0, 1, 4, 1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets.output.viewer), false);
}

void set_output(const char * text)
{
	gtk_text_buffer_set_text(widgets.output.buffer, text, -1);
}

void append_to_output(const char * text)
{
	gtk_text_buffer_get_end_iter(widgets.output.buffer, &widgets.output.iter);
	gtk_text_buffer_insert(widgets.output.buffer, &widgets.output.iter, text, -1);
}
