#include "Arbre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 50

int compte(FILE *fichier)
{
	int c;
	int nLignes = 0;
	int c2 = '\0';
	while((c=fgetc(fichier)) != EOF)
	{
		if(c=='\n'){
			nLignes++;
		}
		c2 = c;
	}

	/* Ici, c2 est égal au caractère juste avant le EOF. */
	if(c2 != '\n'){
		nLignes++; /* Dernière ligne non finie */
	}
	return nLignes;
}

Bibliotheque *creernoeud(int n){
    int a=0,c;
    Bibliotheque *nouveau=(Bibliotheque*)malloc(sizeof(Bibliotheque));
    char c2[MAX_BUFFER_SIZE];
    FILE * fichier=NULL;
    FILE * f=NULL;
    f=fopen("donne.txt","r");
    if(nouveau!=NULL){
        (*nouveau).value.numerolivre=n;
        (*nouveau).Agauche=(*nouveau).Adroite=NULL;
        fgets(c2,MAX_BUFFER_SIZE,f);
        c=atoi(c2);
        while(c!=n){
            a++;
            fgets(c2,MAX_BUFFER_SIZE,f);
            c=atoi(c2);
        }
        fclose(f);
        fichier=fopen("donneeL.txt","r");
        for(int i=0;i<a*3;i++){
            fgets(c2,MAX_BUFFER_SIZE,fichier);
        }
        for(int j=0;j<3;j++){
                if(j==0){
                    fgets(c2,MAX_BUFFER_SIZE,fichier);
                    nouveau->value.pages=atoi(c2);
                }
                if(j==1){
                    fgets(nouveau->value.titre,MAX_BUFFER_SIZE,fichier);
                }
                if(j==2){
                    fgets(nouveau->value.auteur,MAX_BUFFER_SIZE,fichier);
                }
            }
    }
    fclose(f);
    fclose(fichier);
    return nouveau;


}







void Libererbiblio(Bibliotheque *arp)
{
    free(arp);



}




Bibliotheque *ajouternoeud(Bibliotheque *arp,int v)
{
    if(arp==NULL){
        return creernoeud(v);
    }
    else{
        if(v < arp->value.numerolivre){
            arp->Agauche=ajouternoeud(arp->Agauche,v);
            return arp;
        }
        if(v > arp->value.numerolivre){
            arp->Adroite=ajouternoeud(arp->Adroite,v);
            return arp;
        }
    }
    return arp;
}


Bibliotheque *creerarbre()
{
    FILE * f=NULL;
    FILE * fichier=NULL;
    int nbligne,i=0;
    int val;
    Bibliotheque *arp =(Bibliotheque*)malloc(sizeof(Bibliotheque));
    f=fopen("donne.txt","r");
    nbligne=compte(f);
    fclose(f);

    f=fopen("donne.txt","r");
    fichier=fopen("donneeL.txt","r");
    if(f==NULL && fichier==NULL){
        printf("Erreur d'ouverture");
        exit (1);
    }
    char c[MAX_BUFFER_SIZE];
    char c2[MAX_BUFFER_SIZE];
    while(fgets(c,MAX_BUFFER_SIZE,f)!= NULL){
        val= atoi(c);
        if(i==0){
            arp->value.numerolivre= atoi(c);
            for(int j=0;j<3;j++){
                if(j==0){
                    fgets(c2,MAX_BUFFER_SIZE,fichier);
                    arp->value.pages=atoi(c2);
                }
                if(j==1){
                    fgets(arp->value.titre,MAX_BUFFER_SIZE,fichier);
                }
                if(j==2){
                    fgets(arp->value.auteur,MAX_BUFFER_SIZE,fichier);
                }
            }
            arp->Agauche=NULL;
            arp->Adroite=NULL;
            fclose(fichier);
        }
        if (i!=0){
            arp=ajouternoeud(arp,val);
        }
        i++;


    }
    fclose(fichier);
    fclose(f);
    return arp;
}


void afficherbiblio(Bibliotheque *arp){
    if(arp!=NULL){
        afficherbiblio(arp->Adroite);
        printf("Numero Livre %d ::",arp->value.numerolivre);
        printf("Nombre de pages %d ::",arp->value.pages);
        printf("Auteur %s ::",arp->value.auteur);
        printf("Titre %s\n",arp->value.titre);
        afficherbiblio(arp->Agauche);
    }
}

Livre rechercherL(Bibliotheque *arp,int n){
    while(arp->value.numerolivre!=n){
        if(n<arp->value.numerolivre){
            rechercherL(arp->Agauche,n);
        }
        if(n>arp->value.numerolivre){
            rechercherL(arp->Adroite,n);
        }
    }
    return arp->value;
}

Bibliotheque supprimer(Bibliotheque *arp,int n){
    FILE * f=NULL;
    Livre L;
    L=rechercherL(arp,n);
    Libererbiblio(arp);
    f=fopen("donne.txt","r");
    modifierfich(f);
    Bibliotheque *nouveau =(Bibliotheque*)malloc(sizeof(Bibliotheque));
    nouveau=creerarbre();
    fclose(f);
}


void modifierfich(FILE *f)
{
    char mot_cle[50];
    char mot_a_modifier[50];
    char nouveau_mot[50];
    char const *ancien = "donnees.txt";
    char const *nouveau = "donnees2.txt";
    FILE *donnees2;

    donnees2 = fopen(nouveau ,"w");
    printf("entrez le mot que vous voulez changer\n");
    scanf("%s",mot_a_modifier);
    printf("entrez le nouveau mot\n");
    scanf("%s",nouveau_mot);
    printf("oui\n");
    while (fgets(mot_cle,MAX_BUFFER_SIZE,f)!=NULL){
        int b= atoi(mot_cle);
        int c=atoi(mot_a_modifier);
        if (b==c){
            printf("if\n");
            fputs(nouveau_mot,donnees2);
            fputs("\n",donnees2);
        }
        else{
            printf("else\n");
            fputs(mot_cle,donnees2);
        }
    }
    remove(nouveau);

    rename(nouveau, ancien);


}
