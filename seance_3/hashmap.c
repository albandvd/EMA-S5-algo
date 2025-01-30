#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// un fichier qui contient son nom et son chemin complet
typedef struct {
    char* nom;
    char* chemin;
} Fichier;

// une liste de fichier
typedef struct FichierVec{
    Fichier* arr;
    int taille;
    int capacity;
} FichierVec;

// la table de hashage contient un tableau de listes de fichiers
typedef struct TableHashage{
    FichierVec* values;
    int taille_tableau;
} TableHashage;

// ****** Fonctions du vecteur de fichier
void fichier_vec_init(FichierVec* vec);

void fichier_vec_add(FichierVec* vec, char* nom, char *chemin);

void fichier_vec_free(FichierVec* vec);


// ****** Fonctions déjà implémentées
TableHashage* table_hashage_new();

// associe un nombre à une chaine de charactères
// utiliser cette fonction pour determiner la position de l'element dans le tableau
int hash(char* nom);


// ********** FONCTIONS A IMPLEMENTER

void table_hashage_add(TableHashage* table, Fichier fichier){
    int index = hash(fichier.nom) % table->taille_tableau;
    fichier_vec_add(table->values + index, fichier.nom, fichier.chemin);
}

Fichier table_hashage_search(TableHashage* table, char* nom_fichier){
    int index = hash(nom_fichier) % table->taille_tableau;
    FichierVec* vec = table->values + index;
    for (int i = 0; i < vec->taille; i++){
        if (strcmp(vec->arr[i].nom, nom_fichier) == 0){
            return vec->arr[i];
        }
    }
    Fichier f;
    f.nom = NULL;
    f.chemin = NULL;
    return f;
}

void table_hashage_free(TableHashage *table){
    for (int i = 0; i < table->taille_tableau; i++)
    {
        fichier_vec_free(table->values + i);
    }
    free(table);
}

int main() {
    // Créer une nouvelle table de hachage
    TableHashage* table = table_hashage_new(20);

    // Ajouter des fichiers à la table de hachage
    Fichier fichier1 = {"file1.txt", "/path/to/file1.txt"};
    Fichier fichier2 = {"file2.txt", "/path/to/file2.txt"};
    Fichier fichier3 = {"file3.txt", "/path/to/file3.txt"};

    table_hashage_add(table, fichier1);
    table_hashage_add(table, fichier2);
    table_hashage_add(table, fichier3);

    // Rechercher des fichiers dans la table de hachage
    Fichier result1 = table_hashage_search(table, "file1.txt");
    Fichier result2 = table_hashage_search(table, "file2.txt");
    Fichier result3 = table_hashage_search(table, "file3.txt");
    Fichier result4 = table_hashage_search(table, "file4.txt"); // Fichier non existant

    // Afficher les résultats de la recherche
    printf("Recherche de file1.txt: %s, %s\n", result1.nom, result1.chemin);
    printf("Recherche de file2.txt: %s, %s\n", result2.nom, result2.chemin);
    printf("Recherche de file3.txt: %s, %s\n", result3.nom, result3.chemin);
    if (result4.nom == NULL) {
        printf("file4.txt non trouvé\n");
    }

    // Libérer la mémoire allouée pour la table de hachage
    table_hashage_free(table);

    return 0;
}

TableHashage* table_hashage_new(int taille){
    TableHashage* table = (TableHashage*)malloc(sizeof(TableHashage));
    table->taille_tableau = taille;
    table->values = (FichierVec*)malloc(20*sizeof(FichierVec));
    for (int i = 0; i < table->taille_tableau; i++){
        fichier_vec_init(table->values + i);
    }
    return table;
}

int hash(char* nom){
    int taille = strlen(nom);
    int resultat = 17;
    for (int i = 0; i < taille; i++){
        resultat = 31 * resultat + nom[i];
    }
    return resultat;
}

void fichier_vec_init(FichierVec* vec){
    vec->arr = (Fichier*)malloc(10 * sizeof(Fichier));
    vec->capacity = 10;
    vec->taille = 0;
}

void fichier_vec_add(FichierVec* vec, char* nom, char *chemin){
    if (vec->capacity == vec->taille){
        vec->capacity *= 2;
        vec->arr = (Fichier*)realloc(vec->arr, sizeof(Fichier) * (vec->capacity));
    }
    vec->arr[vec->taille].nom = strdup(nom);
    vec->arr[vec->taille].chemin = strdup(chemin);
    vec->taille++;
}

void fichier_vec_free(FichierVec* vec){
    free(vec->arr);
    free(vec);
}
