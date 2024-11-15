#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* nuevonodo(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //reserva la memoria y hace cast con la memoria dinamica
    newNode->data = data; 
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
//funciones:
//#1
void nodo_inicio(struct Node** head, int data) {
    struct Node* newNode = nuevonodo(data);
    newNode->next = *head;
    if (*head != NULL) //revisa si el nodo fue creado correctamente
        (*head)->prev = newNode;
    *head = newNode; 
}
//#2
void nodo_final(struct Node** head, int data) {
    struct Node* newNode = nuevonodo(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = newNode;
    newNode->prev = last;
}
//#3
void nodo_posicion(struct Node** head, int data, int index) {
    if (index == 0) {
        nodo_inicio(head, data); //si el indice es 0, se coloca al inicio de la lista
        return;
    }
    struct Node* newNode = nuevonodo(data);
    struct Node* current = *head;
    int i = 0; //crea uno nuevo y recorre la lista hasta encontrar el nodo que actualmente tiene ese index
    while (current != NULL && i < index - 1) {
        current = current->next;
        i++;
    }
    //si no encuentra ese valor, es porque la lista es más pequeña
    if (current == NULL) {
        printf("ñao ñao, indice no encontrado\n");
        return;
    }
    //si lo encuentra apunta el nuevo nodo a los valores prev y next del nodo anterior
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL)
        current->next->prev = newNode;
    current->next = newNode;
}
//#4
void nodo_borrar(struct Node** head, int data) {
    struct Node* current = *head;
    //revisa si la data buscada existe en la lista 
    while (current != NULL && current->data != data)
        current = current->next;
    if (current == NULL) {
        printf("No existe data en la lista\n");
        return;
    }
    //si existe, localiza el nodo, revisa que no sea el primero o el ultimo y cambia los apuntadores
    if (current->prev != NULL)
        current->prev->next = current->next;
    if (current->next != NULL)
        current->next->prev = current->prev;
    if (current == *head)
        *head = current->next;
    free(current);
}
//#5
struct Node* nodo_buscar(struct Node* head, int data) {
    struct Node* current = head;//apunta al siguiente nodo mientras no encuentre el dato buscado
    while (current != NULL && current->data != data)
        current = current->next;
    return current;
}
//borrar
//
//#6
void imprime_lista(struct Node* head) {
    printf("Lista hacia adelante: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
//#7
void imprime_lista_alverres(struct Node* tail) {
    printf("Lista al verres: "); 
    while (tail != NULL) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("\n");
}


// Función para liberar memoria alocada
void freelist(struct Node* head) {
    struct Node * current = head;
    struct Node * next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
