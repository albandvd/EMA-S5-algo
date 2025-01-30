#include "stdlib.h"
#include "stdio.h"


// Pile à base de tableau
// s'inspirer de l'exercice "Vecteur" du TP 4 du cours C
struct Pile{
    char* valeurs; // les valeurs
    int taille; // la position de la derniere valeur
    int capacite; // la quantitie de memoire allouee
};
typedef struct Pile Pile ;

Pile* pile_creer(){
    Pile* new_pile = malloc(sizeof(Pile));
    new_pile->valeurs = malloc(10*sizeof(char));

    new_pile->taille = 0;
    new_pile->capacite = 10;    
}

void pile_free(Pile* p){
    free(p->valeurs);
    free(p);
}

char depiler(Pile* p){
    char valeurs = p->valeurs[p->taille];
    p->taille--;
    return valeurs;
}

void empiler(Pile* p, char valeur){
    if (p->taille == p->capacite){
        p->capacite *= 2;
        p->valeurs = realloc(p->valeurs, p->capacite*sizeof(char));
    }
    p->taille++;
    p->valeurs[p->taille] = valeur;
}

void print_pile(Pile* p){
    for(int i = p->taille; i >=0; i--){
        printf("%c", p->valeurs[i]);
    }
    printf("\n");
}


// File à base de liste chaînée
// Réutiliser la liste doublement chaînée du TP 1 d'algo 
struct ListElem{
    char value;
    struct ListElem* next;
    struct ListElem* previous;
};
typedef struct ListElem ListElem ;

struct File{
    ListElem sentinel_start;
    ListElem sentinel_end;
};
typedef struct File File;

File* file_creer() {
    File* f = (File*)malloc(sizeof(File));
    f->sentinel_start.next = &(f->sentinel_end);
    f->sentinel_end.previous = &(f->sentinel_start);
    f->sentinel_end.next = &(f->sentinel_end);
    f->sentinel_start.previous = &(f->sentinel_start);
    return f;
}

void file_free(File* f){
    ListElem* current = f->sentinel_start.next;
    while (current != &(f->sentinel_end)){
        ListElem* next = current->next;
        free(current);
        current=next;
    }
    free(f);
}

char defiler(File* f) {
    ListElem* temp = f->sentinel_start.next;
    char value = temp->value;
    f->sentinel_start.next = temp->next;
    temp->next->previous = &(f->sentinel_start);
    free(temp);
    return value;
}

void enfiler(File* f, char value) {
    ListElem* newElem = (ListElem*)malloc(sizeof(ListElem));
    newElem->value = value;
    newElem->next = &(f->sentinel_end);
    newElem->previous = f->sentinel_end.previous;
    f->sentinel_end.previous->next = newElem;
    f->sentinel_end.previous = newElem;
}

void print_file(File* f){
    for (ListElem* elem = f->sentinel_start.next; elem->next != elem; elem = elem->next){
        printf("%c", elem->value);
    }
    printf("\n");
}

int main() {
    Pile* p = pile_creer();
    empiler(p, 'a');
    empiler(p, 'b');
    empiler(p, 'c');
    print_pile(p);
    printf("Depile: %c\n", depiler(p));
    print_pile(p);
    pile_free(p);

    File* f = file_creer();
    enfiler(f, 'a');
    enfiler(f, 'b');
    enfiler(f, 'c');
    print_file(f);
    printf("Defile: %c\n", defiler(f));
    print_file(f);
    file_free(f);

    return 0;
}