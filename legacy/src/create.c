#include "gtk/gtk.h"
#include "grid.h"

GtkWidget * create(GtkWidget * widget, int x, int y, int w, int h)
{
	gtk_grid_attach(GTK_GRID(grid), widget, x, y, w, h);
	return widget;
}
