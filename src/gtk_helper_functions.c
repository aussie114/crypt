#include <gtk/gtk.h>

// Create master window
GtkWidget * ghf_create_window(GtkApplication * app, gchar * title, gint x, gint y, gboolean resizable)
{
	GtkWidget * window = gtk_application_window_new(app);
	gtk_window_set_title(        GTK_WINDOW(window), title);
	gtk_window_set_default_size( GTK_WINDOW(window), x, y);
	gtk_window_set_resizable(    GTK_WINDOW(window), resizable);
	return window;
}

// Create grid
GtkWidget * ghf_create_grid(gint x, gint y)
{
	GtkWidget * grid = gtk_grid_new();
	gtk_grid_set_column_spacing(GTK_GRID(grid), x);
	gtk_grid_set_row_spacing(GTK_GRID(grid),    y);
	return grid;
}

// Text setters and getters
gchar * ghf_entry_get_text(GtkWidget * widget)
{
	GtkEntryBuffer * text_buffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
	return (gchar *)gtk_entry_buffer_get_text(text_buffer);
}

void ghf_text_view_set_text(GtkWidget * widget, gchar * text)
{
	GtkTextBuffer * text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	gtk_text_buffer_set_text(text_buffer, text, -1);
}

void ghf_text_view_append_text(GtkWidget * widget, gchar * text)
{
	GtkTextBuffer * output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	GtkTextIter end_iter;
	gtk_text_buffer_get_end_iter(output_buffer, &end_iter);
	gtk_text_buffer_insert(output_buffer, &end_iter, text, -1);
	gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(widget), &end_iter, 0.0, FALSE, 0.0, 0.0);
}

// Creates and attaches a widget to a grid
GtkWidget * ghf_create_widget(GtkWidget * widget, GtkWidget * grid, int x, int y, int w, int h)
{
	gtk_grid_attach(GTK_GRID(grid), widget, x, y, w, h);
	return widget;
}

// Set's a margin for all of a widgets properties
void ghf_widget_set_margin_all(GtkWidget * widget, guint margin)
{
	gtk_widget_set_margin_top(   widget, margin);
	gtk_widget_set_margin_bottom(widget, margin);
	gtk_widget_set_margin_start( widget, margin);
	gtk_widget_set_margin_end(   widget, margin);
}
