#include <gtk/gtk.h>

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GObject *window;

    builder = gtk_builder_new_from_file("window.ui");
    window = gtk_builder_get_object(builder, "window");

    gtk_application_add_window(app, GTK_WINDOW(window));

    gtk_window_present(GTK_WINDOW(window));

    g_object_unref(builder);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.hello-world", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);

    return status;
}
