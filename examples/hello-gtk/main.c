#include <gtk/gtk.h>

static void activate_cb(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK4");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    g_autoptr (GtkApplication) app = NULL;
    
    app = gtk_application_new("com.example.hello-world", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    return status;
}
