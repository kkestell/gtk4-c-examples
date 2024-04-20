#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
    // Print "Hello World" to the console
    // https://docs.gtk.org/glib/func.print.html
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);    
    gtk_window_set_title(GTK_WINDOW(window), "Signals");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    // Create a new button with the label "Click Me"
    // https://docs.gtk.org/gtk4/ctor.Button.new_with_label.html
    GtkWidget *button = gtk_button_new_with_label("Click Me");

    // Connect the "clicked" signal of the button to the print_hello function
    // https://docs.gtk.org/gtk4/signal.Button.clicked.html
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    // Set the button as the child widget of the window
    // https://docs.gtk.org/gtk4/method.Window.set_child.html
    gtk_window_set_child(GTK_WINDOW(window), button);

    // Present the window
    // https://docs.gtk.org/gtk4/method.Window.present.html
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
