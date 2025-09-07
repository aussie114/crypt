#include <gtk/gtk.h>
#include "window.h"

GtkWidget * grid;

void create_grid()
{
	grid = gtk_grid_new();
	gtk_window_set_child (GTK_WINDOW (window), grid);
	gtk_widget_set_margin_top           (grid,  4);
	gtk_widget_set_margin_end           (grid,  4);
	gtk_widget_set_margin_bottom        (grid,  4);
	gtk_widget_set_margin_start         (grid,  4);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
	gtk_grid_set_row_spacing(   GTK_GRID(grid), 2);

}
