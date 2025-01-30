#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
    char value;
    struct Node* noeud_gauche;
    struct Node* noeud_droit;
} Node;


Node* create_node(Node* noeud_gauche, char value, Node* noeud_droit){
    Node* n = (Node*)malloc(sizeof(Node));
    n->noeud_gauche = noeud_gauche;
    n->noeud_droit = noeud_droit;
    n->value = value;
    return n;
}

// ******** FONCTION A IMPLEMENTER 

// affiche les valeurs des noeuds en utilisant un parcours en profondeur
void affiche_profondeur(Node* n){
    // parcours en profondeur récursif
    if (n == NULL){
        printf("\n");
        return; 
    }

    printf("%c", n->value);
    affiche_profondeur(n->noeud_gauche);
    affiche_profondeur(n->noeud_droit);
}

// affiche les valeurs des noeuds en utilisant un parcours en largeur
void affiche_largeur(Node* n){
    // parcours en largeur
    Node* file[100];
    int debut = 0;
    int fin = 0;
    file[fin] = n;
    fin++;
    while (debut != fin){
        Node* current = file[debut];
        debut++;
        printf("%c", current->value);
        if (current->noeud_gauche != NULL){
            file[fin] = current->noeud_gauche;
            fin++;
        }
        if (current->noeud_droit != NULL){
            file[fin] = current->noeud_droit;
            fin++;
        }
    }
    printf("\n");
}

// calcule le resultat de l'expression enregistrée dans l'arbre
int calcule_resultat(Node* n){
    if (n->value == '+'){
        return calcule_resultat(n->noeud_gauche) + calcule_resultat(n->noeud_droit);
    }
    if (n->value == '-'){
        return calcule_resultat(n->noeud_gauche) - calcule_resultat(n->noeud_droit);
    }
    if (n->value == '*'){
        return calcule_resultat(n->noeud_gauche) * calcule_resultat(n->noeud_droit);
    }
    if (n->value == '/'){
        return calcule_resultat(n->noeud_gauche) / calcule_resultat(n->noeud_droit);
    }
    return n->value - '0';
}

void free_arbre(Node* n){
    if (n == NULL){
        printf("\n");
        return; 
    }

    affiche_profondeur(n->noeud_gauche);
    affiche_profondeur(n->noeud_droit);
    free(n);
}

int main(){
    Node* cinq = create_node(NULL, '5', NULL);
    Node* six = create_node(NULL, '6', NULL);
    Node* sept = create_node(NULL, '7', NULL);
    Node* a = create_node(create_node(sept, '-', cinq), '+', six);
    Node* b = create_node( cinq, '*',a);
    Node* c = create_node( b, '*',a);
    affiche_largeur(c);
    affiche_profondeur(c);
    printf("%d\n", calcule_resultat(c));
    free_arbre(c);
}
