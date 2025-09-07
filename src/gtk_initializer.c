#!/bin/sh
tail -n +5 "$0" | gcc -c -xc -Wall -Wextra -std=c99 `pkg-config --cflags gtk4` - -o build/"$(basename "$0" .c).o"
exit

#include <gtk/gtk.h>
#include "global.h"

void create_generate_from_file();
void create_output();
void create_generate_single();

static gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data)
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

void activate(GtkApplication * program, gpointer user_data)
{
	(void)user_data;
	// Create main window
	widgets.window   = gtk_application_window_new(program);
	gtk_window_set_title        ( GTK_WINDOW (widgets.window), "Window");
	gtk_window_set_resizable    ( GTK_WINDOW (widgets.window), FALSE);

	// Create grid
	widgets.grid = gtk_grid_new();
	gtk_window_set_child (GTK_WINDOW (widgets.window), widgets.grid);
	gtk_widget_set_margin_top           (widgets.grid,  4);
	gtk_widget_set_margin_end           (widgets.grid,  4);
	gtk_widget_set_margin_bottom        (widgets.grid,  4);
	gtk_widget_set_margin_start         (widgets.grid,  4);
	gtk_grid_set_column_spacing(GTK_GRID(widgets.grid), 2);
	gtk_grid_set_row_spacing(   GTK_GRID(widgets.grid), 2);

	// Create input
	GtkEventController * controller = gtk_event_controller_key_new();
	gtk_widget_add_controller(widgets.window, controller);
	g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), widgets.window);

	create_generate_from_file();
	create_output();
	create_generate_single();

	gtk_window_present (GTK_WINDOW (widgets.window));
}

int create_gtk(int argc, char ** argv)
{
	if (argc > 1)
	{
		file_address = argv[1];
		argc = 1;
	}
	GtkApplication * program;
	int status;

	program = gtk_application_new (NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (program, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (program), argc, argv);
	g_object_unref (program);
	return status;
}
