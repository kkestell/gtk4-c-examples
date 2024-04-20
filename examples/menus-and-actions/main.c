#include <gtk/gtk.h>

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_application_quit(G_APPLICATION(user_data));
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Menus and Actions");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

    gtk_window_present(GTK_WINDOW(window));
}

static void on_startup(GApplication *application, gpointer user_data)
{
    GtkApplication *app = GTK_APPLICATION(application);

    GSimpleAction *act_quit = g_simple_action_new("quit", NULL);
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_quit));
    g_signal_connect(act_quit, "activate", G_CALLBACK(quit_activated), application);

    const gchar *quit_accels[2] = {"<Ctrl>Q", NULL};
    gtk_application_set_accels_for_action(app, "app.quit", quit_accels);

    GMenu *menubar = g_menu_new();
    GMenu *menu = g_menu_new();

    // Create and append the "Quit" menu item
    GMenuItem *menu_item_quit = g_menu_item_new("Quit", "app.quit");
    g_menu_append_item(menu, menu_item_quit);
    g_object_unref(menu_item_quit);

    // Create the "File" menu and append it to the menubar
    GMenuItem *menu_item_file = g_menu_item_new("File", NULL);
    g_menu_item_set_submenu(menu_item_file, G_MENU_MODEL(menu));
    g_menu_append_item(menubar, menu_item_file);
    g_object_unref(menu);
    g_object_unref(menu_item_file);

    // Set the application's menubar
    gtk_application_set_menubar(app, G_MENU_MODEL(menubar));
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("org.kestell.gtk-examples.menus-and-actions", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "startup", G_CALLBACK(on_startup), NULL);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
