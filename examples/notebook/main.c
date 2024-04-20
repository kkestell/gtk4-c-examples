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

    // Create a new notebook
    // https://docs.gtk.org/gtk4/ctor.Notebook.new.html
    GtkWidget *notebook = gtk_notebook_new();
    
    for (int i = 1; i <= 3; ++i)
    {
        // Create a new label and content for the tab
        // https://docs.gtk.org/gtk4/ctor.Label.new.html
        GtkWidget *label = gtk_label_new(g_strdup_printf("Tab %d", i));
        GtkWidget *content = gtk_label_new(g_strdup_printf("Content of Tab %d", i));

        // Append the content to the notebook
        // https://docs.gtk.org/gtk4/method.Notebook.append_page.html
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), content, label);
    }

    // Add the notebook to the window
    // https://docs.gtk.org/gtk4/method.Window.set_child.html
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // Present the window
    // https://docs.gtk.org/gtk4/method.Window.present.html
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    // Create a new GtkApplication with the specified application ID and flags
    // https://docs.gtk.org/gtk4/ctor.Application.new.html
    GtkApplication *app = gtk_application_new("com.example.hello-world", G_APPLICATION_DEFAULT_FLAGS);

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
