#include <adwaita.h>

static void on_hi_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_print("Hello World\n");
}

static GActionEntry win_entries[] = {
    { .name = "hi", .activate = on_hi_activated, .parameter_type = NULL, .state = NULL, .change_state = NULL, .padding = {0} }
};

static void activate_cb(GtkApplication *app)
{
    GtkBuilder *builder;
    GObject *window;

    builder = gtk_builder_new_from_file("window.ui");
    window = gtk_builder_get_object(builder, "window");

    gtk_application_add_window(app, GTK_WINDOW(window));
    g_action_map_add_action_entries(G_ACTION_MAP(window), win_entries, G_N_ELEMENTS(win_entries), NULL);

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
