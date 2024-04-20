#include <gtk/gtk.h>
#include <adwaita.h>

typedef struct {
    gchar *content;         // The text content of the document.
    gchar *filename;       // NULL if the document hasn't been saved.
    gboolean is_saved;     // Whether the document has been saved or not.
} Document;

// Initialize a new document.
Document* document_new(void) {
    Document *doc = g_malloc(sizeof(Document));
    doc->content = g_strdup("");  // Empty content by default.
    doc->filename = NULL;         // Not saved yet.
    doc->is_saved = FALSE;
    return doc;
}

// Set the content of the document.
void document_set_content(Document *doc, const gchar *content) {
    g_free(doc->content);
    doc->content = g_strdup(content);
    doc->is_saved = FALSE;
}

// Get the content of the document.
const gchar* document_get_content(const Document *doc) {
    return doc->content;
}

// Set the filename of the document.
void document_set_filename(Document *doc, const gchar *filename) {
    g_free(doc->filename);
    doc->filename = g_strdup(filename);
    doc->is_saved = TRUE; // Assuming we set filename after saving.
}

// Get the filename of the document.
const gchar* document_get_filename(const Document *doc) {
    return doc->filename;
}

// Free the document.
void document_free(Document *doc) {
    g_free(doc->content);
    g_free(doc->filename);
    g_free(doc);
}

// Check if the document is saved.
gboolean document_is_saved(const Document *doc) {
    return doc->is_saved;
}

// ===============================================================================================

Document *current_document;  // Global instance of our document.
GObject *window;

void update_window_title() {
    printf("UPDATING WINDOW TITLE!");
    const gchar *filename = document_get_filename(current_document);
    if (filename) {
        gchar *basename = g_path_get_basename(filename);
        gtk_window_set_title(GTK_WINDOW(window), basename);
        printf("basename: %s\n", basename);
        g_free(basename);
    } else {
        gtk_window_set_title(GTK_WINDOW(window), "Untitled");
    }
}

static void on_file_dialog_complete(GObject *gobject, GAsyncResult *result, gpointer data) {
    g_autoptr (GError)error = NULL;
    g_autoptr (GFile)file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(gobject), result, &error);
    if (error != NULL) {
        // Handle error.
    } else {
        // Set the filename in the document.
        document_set_filename(current_document, g_file_get_path(file));
        update_window_title();
    }
}

static void on_new_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    // Reset the current document.
    document_free(current_document);
    current_document = document_new();
    update_window_title();
}

static void on_save_as_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Save File...");
    gtk_file_dialog_open(dialog, NULL, NULL, on_file_dialog_complete, NULL);
}

static void on_save_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    g_print("Save menu item selected\n");
    // If the document was previously saved, save to the same file.
    // Otherwise, open a save dialog (like in on_save_as_activated).
    if (document_is_saved(current_document)) {
        // Save to the existing file.
    } else {
        on_save_as_activated(action, parameter, user_data);
    }
}

static void on_close_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    g_print("Close menu item selected\n");
    // Free and reset the current document.
    document_free(current_document);
    current_document = document_new();
}

static void on_quit_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    g_application_quit(G_APPLICATION(user_data));
}

static GActionEntry win_entries[] = {
    { .name = "new", .activate = on_new_activated },
    { .name = "save", .activate = on_save_activated },
    { .name = "save_as", .activate = on_save_as_activated },
    { .name = "close", .activate = on_close_activated },
    { .name = "quit", .activate = on_quit_activated }
};

static void activate_cb(GtkApplication *app) {
    GtkBuilder *builder;
    builder = gtk_builder_new_from_file("window.ui");
    window = gtk_builder_get_object(builder, "window");
    gtk_application_add_window(app, GTK_WINDOW(window));
    g_action_map_add_action_entries(G_ACTION_MAP(window), win_entries, G_N_ELEMENTS(win_entries), app);
    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(builder);
}

int main(int argc, char *argv[]) {
    g_autoptr (AdwApplication) app = NULL;
    app = adw_application_new("org.kestell.TextEditor", 0);
    current_document = document_new();
    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    document_free(current_document);
    return status;
}
