#ifndef GTK_HELPER_FUNCTIONS_H
#define GTK_HELPER_FUNCTIONS_H
GtkWidget * ghf_create_window(GtkApplication * app, gchar * title, gint x, gint y, gboolean resizable);
GtkWidget * ghf_create_grid(gint x, gint y);
gchar * ghf_entry_get_text(GtkWidget * widget);
void ghf_text_view_set_text(GtkWidget * widget, gchar * text);
void ghf_text_view_append_text(GtkWidget * widget, gchar * text);
GtkWidget * ghf_create_widget(GtkWidget * widget, GtkWidget * grid, int x, int y, int w, int h);
void ghf_widget_set_margin_all(GtkWidget * widget, guint margin);
#endif
