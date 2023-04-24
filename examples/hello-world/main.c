#include <gtk/gtk.h>

static void on_activate(GtkApplication *app, gpointer user_data)
{
    // Create a new application window for the app
    // https://docs.gtk.org/gtk4/ctor.ApplicationWindow.new.html
    GtkWidget *window = gtk_application_window_new(app);

    // Set the title of the window to "Hello World"
    // https://docs.gtk.org/gtk4/method.Window.set_title.html
    gtk_window_set_title(GTK_WINDOW(window), "Hello World");

    // Set the default size of the window to 640x480 pixels
    // https://docs.gtk.org/gtk4/method.Window.set_default_size.html
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    // Present the window
    // https://docs.gtk.org/gtk4/method.Window.present.html
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    // Create a new GtkApplication with the specified application ID and flags
    // https://docs.gtk.org/gtk4/ctor.Application.new.html
    GtkApplication *app = gtk_application_new("com.example.hello-world", G_APPLICATION_FLAGS_NONE);

    // Connect the "activate" signal of the app to the on_activate function
    // https://docs.gtk.org/gio/signal.Application.activate.html
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Run the application and store the exit status
    // https://docs.gtk.org/gio/method.Application.run.html
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Release the reference to the application object
    // https://docs.gtk.org/gobject/method.Object.unref.html
    g_object_unref(app);

    return status;
}
