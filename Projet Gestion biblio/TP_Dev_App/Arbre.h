#ifndef ARBRE__
#define ARBRE__
#define Max 100
#include <stdio.h>
typedef struct Livre{
    int numerolivre;
    int pages;
    char titre[Max];
    char auteur[Max];
}Livre;

typedef struct Bibliotheque{
    struct Bibliotheque *Agauche;
    struct Bibliotheque *Adroite;
    Livre value;
}Bibliotheque;



Bibliotheque *creerarbre();
Bibliotheque *ajouternoeud(Bibliotheque *arp, int v);
void Libererbiblio(Bibliotheque *arp);
int compte(FILE *fichier);
Bibliotheque *creernoeud(int n);
void afficherbiblio(Bibliotheque *arp);

#endif ARBRE__
