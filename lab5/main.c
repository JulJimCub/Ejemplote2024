#include "double_list.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
    struct Node* head = NULL;
    nodo_inicio(&head, 2);
    nodo_inicio(&head, 1);
    nodo_final(&head, 4);
    nodo_final(&head, 5);
    printf("Lista actual con inserciones al inicio y final: ");
    imprime_lista(head);
    nodo_posicion(&head, 3, 2);
    printf("Lista actual con insercion por indice: ");
    imprime_lista(head);
    nodo_borrar(&head, 2);
    printf("Lista después de eliminar el nodo con data 2: ");
    imprime_lista(head);
    int data = 5;
    //asigna el retorno de la funcion de busqueda a un puntero con el resultado
    struct Node* busca_data = nodo_buscar(head, data);
    if (busca_data != NULL)
        printf("Elemento %d está en la lista\n", data);
    else
        printf("Elemento %d no esta en la lista\n", data);
    imprime_lista(head); 
    struct Node* tail = head;
    //revisa que la lista no este vacia y que pase al siguiente
    while (tail != NULL && tail->next != NULL)
        tail = tail->next;
    imprime_lista_alverres(tail);
    //libera la memoria utilizada
    freelist(head);
    return 0;
}
