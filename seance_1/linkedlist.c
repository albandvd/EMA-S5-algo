#include "stdlib.h"
#include "stdio.h"

struct ListElem{
    float value;
    struct ListElem* next;
    struct ListElem* previous;
};
typedef struct ListElem ListElem ;

struct LinkedList{
    ListElem sentinel_start;
    ListElem sentinel_end;
};
typedef struct LinkedList LinkedList;


//////// FONCTIONS DEJA IMPLEMENTEES PLUS BAS
// crée une nouvelle liste
LinkedList* linked_list_new();

// affiche le contenu de la liste dans le terminal
void linked_list_print(LinkedList* list);

//////// FONCTIONS A IMPLEMENTER EX 1

// libère toute la mémoire allouée pour la liste
void linked_list_free(LinkedList* list){
    ListElem* current = list->sentinel_start.next;
    while (current != &(list->sentinel_end)){
        ListElem* next = current->next;
        free(current);
        printf("free \n");
        current=next;
    }
    free(list);
    printf("free \n");
}


// insère un element à la suite de l'élément donné
void linked_list_insert_after(ListElem* previous_elem, float toInsert){
    ListElem* new_elem = (ListElem*)malloc(sizeof(ListElem));
    printf("malloc \n");
    ListElem* next_elem = previous_elem->next;

    new_elem->value = toInsert;

    new_elem->next = previous_elem->next;
    new_elem->previous = next_elem->previous;

    previous_elem->next = new_elem;
    new_elem->previous = new_elem;
}


//////// FONCTIONS A IMPLEMENTER EX 2

// enlève l'élément suivant le noeud donné dans la liste
void list_elem_delete_after(ListElem* previous_elem){
    ListElem* elem = previous_elem->next;
    ListElem* next_elem = elem->next;

    previous_elem->next = elem->next;
    next_elem->previous = elem->previous;
    free(elem);
    printf("free \n");
}

// cherche un noeud contenant la valeur donnée
ListElem* linked_list_search(LinkedList* list, float toSearch){
    ListElem* current = list->sentinel_start.next;
    while (current != &(list->sentinel_end)){
        if (current->value == toSearch) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// ajoute un élement en fin de liste
void linked_list_insert_end(LinkedList* list, float toInsert){
    ListElem* new_elem = (ListElem*)malloc(sizeof(ListElem));
    printf("malloc \n");
    ListElem* previous_elem = list->sentinel_end.previous;

    new_elem->value = toInsert;

    new_elem->next = &(list->sentinel_end);
    new_elem->previous = previous_elem;

    previous_elem->next = new_elem;
    list->sentinel_end.previous = new_elem;
}


// affiche la liste à l'envers
void linked_list_print_reverse(LinkedList* list) {
    ListElem* elem = list->sentinel_end.previous;
    while (elem != &(list->sentinel_start)) {
        printf("%f ", elem->value);
        elem = elem->previous;
    }
    printf("\n");
}

int main() {
    LinkedList* list = linked_list_new();
    for (int i = 0; i < 4; i++) {
        linked_list_insert_end(list, (float)i);
    }
    linked_list_print(list); // Affiche 0 1 2 3
    linked_list_print_reverse(list); // Affiche 3 2 1 0

    linked_list_insert_end(list, 42.0);
    linked_list_print(list); // Affiche 0 1 2 3 42
    linked_list_print_reverse(list); // Affiche 42 3 2 1 0

    linked_list_free(list);
}

LinkedList* linked_list_new(){
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    printf("malloc \n");
    l->sentinel_start.next = &(l->sentinel_end);
    l->sentinel_start.previous = &(l->sentinel_start); // la sentinelle de début pointe vers elle même pour le précedent

    l->sentinel_end.next = &(l->sentinel_end); // la sentinelle de fin pointe vers elle même pour le suivant
    l->sentinel_start.previous = &(l->sentinel_start);
    return l;
}

void linked_list_print(LinkedList* list){
    for (ListElem* elem = list->sentinel_start.next; // on commence par le premier element
         elem->next != elem; // on ira jusqu'a la sentinelle de fin (qui pointe vers elle même)
         elem = elem->next){ // on avance d'un element a chaque iteration 
        printf("%f ", elem->value);
    }
    printf("\n");
}