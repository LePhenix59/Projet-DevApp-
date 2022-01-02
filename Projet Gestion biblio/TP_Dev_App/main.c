#include <stdio.h>
#include <stdlib.h>
#include "Arbre.h"
#include <string.h>

int main(int argc, char *argv[])
{
    int choix,val;
    Bibliotheque * arp=creerarbre();
    printf("Que voulez-vous faire?\n");
    printf("Afficher la bibliotheque(1)\n");
    printf("Quitter(2)\n");
    scanf("%d",&choix);
    if(choix==1){
        afficherbiblio(arp);
    }
    if(choix==2){
        Libererbiblio(arp);
    }
    return EXIT_SUCCESS ;
}


