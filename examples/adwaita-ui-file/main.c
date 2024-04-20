#include <adwaita.h>

static void activate_cb(GtkApplication *app)
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
    g_autoptr (AdwApplication) app = NULL;

    app = adw_application_new("org.example.Hello", 0);

    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    return status;
}
