#include <gtk/gtk.h>

static int counter = 0;

static void on_button_clicked(GtkWidget *widget, gpointer user_data)
{
    counter++;
    GtkLabel *label = GTK_LABEL(user_data);
    gchar *new_label_text = g_strdup_printf("You have clicked the button %d times", counter);
    gtk_label_set_text(label, new_label_text);
    g_free(new_label_text);
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GObject *label;

    builder = gtk_builder_new_from_file("window.ui");
    window = gtk_builder_get_object(builder, "window");
    button = gtk_builder_get_object(builder, "button");
    label = gtk_builder_get_object(builder, "label");

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), label);

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
