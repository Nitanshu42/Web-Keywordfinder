#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

/* ===== BST CODE (UNCHANGED) ===== */

struct Node {
    char word[50];
    struct Node *left;
    struct Node *right;
};

struct Node* root = NULL;

struct Node* createNode(char word[]) {
    struct Node* n = malloc(sizeof(struct Node));
    strcpy(n->word, word);
    n->left = n->right = NULL;
    return n;
}

struct Node* insert(struct Node* root, char word[]) {
    if (!root) return createNode(word);

    if (strcmp(word, root->word) < 0)
        root->left = insert(root->left, word);
    else if (strcmp(word, root->word) > 0)
        root->right = insert(root->right, word);

    return root;
}

int search(struct Node* root, char word[]) {
    if (!root) return 0;
    if (strcmp(word, root->word) == 0) return 1;
    if (strcmp(word, root->word) < 0)
        return search(root->left, word);
    return search(root->right, word);
}

void inorder(struct Node* root, GtkTextBuffer *buffer) {
    if (root) {
        inorder(root->left, buffer);
        gtk_text_buffer_insert_at_cursor(buffer, root->word, -1);
        gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
        inorder(root->right, buffer);
    }
}

/* ===== GUI CALLBACKS ===== */

GtkWidget *entry;
GtkTextBuffer *text_buffer;

void on_insert_clicked(GtkWidget *widget, gpointer data) {
    const char *word = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(word) > 0) {
        root = insert(root, (char *)word);
        gtk_text_buffer_set_text(text_buffer, "Word inserted.\n", -1);
    }
}

void on_search_clicked(GtkWidget *widget, gpointer data) {
    const char *word = gtk_entry_get_text(GTK_ENTRY(entry));
    if (search(root, (char *)word))
        gtk_text_buffer_set_text(text_buffer, "Word found.\n", -1);
    else
        gtk_text_buffer_set_text(text_buffer, "Word not found.\n", -1);
}

void on_display_clicked(GtkWidget *widget, gpointer data) {
    gtk_text_buffer_set_text(text_buffer, "", -1);
    inorder(root, text_buffer);
}

/* ===== MAIN GUI ===== */

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Word Dictionary (BST)");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);

    GtkWidget *btn_insert = gtk_button_new_with_label("Insert");
    GtkWidget *btn_search = gtk_button_new_with_label("Search");
    GtkWidget *btn_display = gtk_button_new_with_label("Display Dictionary");

    gtk_box_pack_start(GTK_BOX(vbox), btn_insert, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), btn_search, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), btn_display, FALSE, FALSE, 5);

    GtkWidget *text_view = gtk_text_view_new();
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 5);

    g_signal_connect(btn_insert, "clicked", G_CALLBACK(on_insert_clicked), NULL);
    g_signal_connect(btn_search, "clicked", G_CALLBACK(on_search_clicked), NULL);
    g_signal_connect(btn_display, "clicked", G_CALLBACK(on_display_clicked), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

