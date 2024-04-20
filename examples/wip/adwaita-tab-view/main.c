#include "adw-tab-view-demo-window.h"

static void activate_cb(GtkApplication *app)
{
    AdwTabViewDemoWindow *window = adw_tab_view_demo_window_new();
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    g_autoptr (AdwApplication) app = NULL;

    app = adw_application_new("org.example.Hello", 0);

    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    return status;
}
