#ifndef double_list
#define double_list

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* nuevonodo(int data); //Función inicial para crear nuevo nodo
// Funciones:
void nodo_inicio(struct Node** head, int data); //#1
void nodo_final(struct Node** head, int data); //#2
void nodo_posicion(struct Node** head, int data, int index); //#3
void nodo_borrar(struct Node** head, int data); //#4
struct Node* nodo_buscar(struct Node* head, int data); //#5
void imprime_lista(struct Node* head); //#6
void imprime_lista_alverres(struct Node* tail); //#7

void freelist(struct Node* head); //liberar la memoria utilizada

#endif
