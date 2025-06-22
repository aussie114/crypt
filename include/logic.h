#ifndef LOGIC_H
#define LOGIC_H
gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data);
void connect_signals(widget * widgets, GtkEventController * controller);
#endif
