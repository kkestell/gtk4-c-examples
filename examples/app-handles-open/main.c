#include <gtk/gtk.h>

static void on_activate(GtkApplication *app, gpointer user_data)
{
    g_printerr("You need a filename argument.\n");
}

static void app_open (GApplication *app, GFile ** files, int n_files, char *hint)
{
    char *contents;
    gsize length;
    GError *err = NULL;

    if (g_file_load_contents (files[0], NULL, &contents, &length, NULL, &err))
    {
        g_printerr("File contents: %s\n", contents);
        g_free(contents);
    }

    return;
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("com.example.app-handles-open", G_APPLICATION_HANDLES_OPEN);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    g_signal_connect (app, "open", G_CALLBACK (app_open), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
