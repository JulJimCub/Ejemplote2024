#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <gtk/gtk.h>

// Estructura de tarea
typedef struct {
    char descripcion[100];
    char subtareas[10][100];
 
   int numSubtareas;
} Tarea;

// lista de funciones
void verTareas(GtkWidget *widget, gpointer label);
void agregarTarea(GtkWidget *widget, gpointer entry);
void borrarTarea(GtkWidget *widget, gpointer data);
void agregarEliminarSubTareas(GtkWidget *widget, gpointer data);
void inicializarDB(sqlite3 **db);
void guardarTarea(sqlite3 *db, Tarea tarea);
void cargarTareas(sqlite3 *db, Tarea tareas[], int *numTareas);
void on_task_selected(GtkComboBox *combo_box, gpointer combo_subtasks);

// Variables globales
sqlite3 *db;
Tarea tareas[10];
int numTareas = 0;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Inicializar la base de datos
    inicializarDB(&db);
    cargarTareas(db, tareas, &numTareas);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "To-Do List");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Botones
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *entry = gtk_entry_new();
    GtkWidget *add_button = gtk_button_new_with_label("Agregar Tarea");
    GtkWidget *view_button = gtk_button_new_with_label("Ver Tareas");
    GtkWidget *delete_button = gtk_button_new_with_label("Borrar Tarea");
    GtkWidget *edit_button = gtk_button_new_with_label("Agregar/Eliminar Sub-tareas");
    GtkWidget *label = gtk_label_new("");

    //Widgets
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), add_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), delete_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), edit_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
   
    //Conectar la interfaz a las funciones
    g_signal_connect(add_button, "clicked", G_CALLBACK(agregarTarea), entry);
    g_signal_connect(view_button, "clicked", G_CALLBACK(verTareas), label);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(borrarTarea), label);
    g_signal_connect(edit_button, "clicked", G_CALLBACK(agregarEliminarSubTareas), label);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();
    sqlite3_close(db);
    return 0;
}


// Función para agregar tarea
void agregarTarea(GtkWidget *widget, gpointer entry) {
    const char *texto = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(texto) > 0 && numTareas < 10) {
        strcpy(tareas[numTareas].descripcion, texto);
        tareas[numTareas].numSubtareas = 0;
        guardarTarea(db, tareas[numTareas]);
        numTareas++;
        gtk_entry_set_text(GTK_ENTRY(entry), "");
        g_print("Tarea agregada: %s\n", texto);
    }
}


// Función para ver  tareas
void verTareas(GtkWidget *widget, gpointer label) {
    char buffer[2048] = ""; // Espacio suficiente para incluir todas las tareas y subtareas
    for (int i = 0; i < numTareas; i++) {
        sprintf(buffer + strlen(buffer), "%d. %s\n", i + 1, tareas[i].descripcion);
        for (int j = 0; j < tareas[i].numSubtareas; j++) {
            sprintf(buffer + strlen(buffer), "   * %s\n", tareas[i].subtareas[j]);
        }
    }
    gtk_label_set_text(GTK_LABEL(label), buffer);
}


// Función para borrar tarea
void borrarTarea(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Borrar Tarea", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_DIALOG_MODAL, "Cancelar", GTK_RESPONSE_CANCEL, "Borrar", GTK_RESPONSE_ACCEPT, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *combo = gtk_combo_box_text_new();
    for (int i = 0; i < numTareas; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), tareas[i].descripcion);
    }
    gtk_box_pack_start(GTK_BOX(content_area), combo, FALSE, FALSE, 0);
    gtk_widget_show_all(dialog);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        int index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
        if (index >= 0 && index < numTareas) {
            char *sql = "DELETE FROM Tareas WHERE descripcion = ?";
            sqlite3_stmt *stmt;
            sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, tareas[index].descripcion, -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_DONE) {
                fprintf(stderr, "Error al borrar tarea: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_finalize(stmt);

            for (int i = index; i < numTareas - 1; i++) {
                tareas[i] = tareas[i + 1];
            }
            numTareas--;
        }
    }
    gtk_widget_destroy(dialog);
}


// Función para agregar/eliminar sub-tareas
void agregarEliminarSubTareas(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Agregar/Eliminar Subtareas", GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_DIALOG_MODAL, "Cancelar", GTK_RESPONSE_CANCEL, "Guardar", GTK_RESPONSE_ACCEPT, NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *combo = gtk_combo_box_text_new(); // Combo para seleccionar tarea principal
    for (int i = 0; i < numTareas; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), tareas[i].descripcion);
    }
    GtkWidget *radio_add = gtk_radio_button_new_with_label(NULL, "Agregar Subtarea");
    GtkWidget *radio_delete = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_add), "Eliminar Subtarea");
    GtkWidget *entry = gtk_entry_new(); // Entrada para agregar subtarea
    GtkWidget *combo_sub = gtk_combo_box_text_new(); // Combo para seleccionar subtarea a eliminar
    gtk_box_pack_start(GTK_BOX(content_area), combo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), radio_add, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), radio_delete, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), gtk_label_new("Nueva subtarea:"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), gtk_label_new("Eliminar subtarea:"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), combo_sub, FALSE, FALSE, 0);
    g_signal_connect(combo, "changed", G_CALLBACK(on_task_selected), combo_sub);    gtk_widget_show_all(dialog);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        int task_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
        if (task_index >= 0 && task_index < numTareas) {
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_add))) {
                const char *subtarea = gtk_entry_get_text(GTK_ENTRY(entry));
                if (strlen(subtarea) > 0 && tareas[task_index].numSubtareas < 10) {
                    strcpy(tareas[task_index].subtareas[tareas[task_index].numSubtareas], subtarea);
                    tareas[task_index].numSubtareas++;
                    guardarTarea(db, tareas[task_index]);
                    g_print("Subtarea agregada: %s\n", subtarea);
                }
            } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_delete))) {
                int sub_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_sub));
                if (sub_index >= 0 && sub_index < tareas[task_index].numSubtareas) {
                    for (int i = sub_index; i < tareas[task_index].numSubtareas - 1; i++) {
                        strcpy(tareas[task_index].subtareas[i], tareas[task_index].subtareas[i + 1]);
                    }
                    tareas[task_index].numSubtareas--;
                    guardarTarea(db, tareas[task_index]);
                    g_print("Subtarea eliminada.\n");
                }
            }
        }
    }

    gtk_widget_destroy(dialog);
}


// Callback subtareas
void on_task_selected(GtkComboBox *combo_box, gpointer combo_subtasks) {
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_subtasks));

    int task_index = gtk_combo_box_get_active(combo_box);
    if (task_index >= 0 && task_index < numTareas) {
        for (int i = 0; i < tareas[task_index].numSubtareas; i++) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_subtasks), tareas[task_index].subtareas[i]);
        }
    }
}


// Función para inicializar la base de datos
void inicializarDB(sqlite3 **db) {
    if (sqlite3_open("tareas.db", db)) {
        fprintf(stderr, "Error database: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS Tareas (descripcion TEXT, subtarea TEXT)";
    char *errmsg;
    if (sqlite3_exec(*db, sql, 0, 0, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "Error tabla: %s\n", errmsg);
        sqlite3_free(errmsg);
        exit(1);
    }
}


// Función de SQlite
void guardarTarea(sqlite3 *db, Tarea tarea) {
    char *errmsg;
    const char *sql_delete = "DELETE FROM Tareas WHERE descripcion = ?";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql_delete, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, tarea.descripcion, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    const char *sql_insert = "INSERT INTO Tareas (descripcion, subtarea) VALUES (?, ?)";
    for (int i = 0; i < tarea.numSubtareas; i++) {
        sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, tarea.descripcion, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, tarea.subtareas[i], -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Error database2: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }
}


// Función para cargar tareas cuando se cierra el programa
void cargarTareas(sqlite3 *db, Tarea tareas[], int *numTareas) {
    const char *sql = "SELECT descripcion, subtarea FROM Tareas";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error abrir: %s\n", sqlite3_errmsg(db));
        return;
    }
    char last_descripcion[100] = "";
    int current_index = -1;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *descripcion = (const char *)sqlite3_column_text(stmt, 0);
        const char *subtarea = (const char *)sqlite3_column_text(stmt, 1);
        if (strcmp(last_descripcion, descripcion) != 0) {
            strcpy(last_descripcion, descripcion);
            current_index++;
            strcpy(tareas[current_index].descripcion, descripcion);
            tareas[current_index].numSubtareas = 0;
        }
        if (subtarea) {
            strcpy(tareas[current_index].subtareas[tareas[current_index].numSubtareas], subtarea);
            tareas[current_index].numSubtareas++;
        }
    }
    *numTareas = current_index + 1;
    sqlite3_finalize(stmt);
}
