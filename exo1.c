//
// Created by Aurélien on 27/05/2021.
//
#include <stdio.h>
#include <stdlib.h>

void permut(int vus[], int nbVus, int nonVus[], int nbNonVus){
    /*
    Entree :
     - vus[0..nbVus-1] = sommets visites
     - nonVus[0..nbNonVus-1] = sommets non visites
    Precondition : nbVus > 0 et vus[0] = 0 (le tour commence toujours par le sommet 0)
    Postcondition : affiche tous les tours commencant par vus[0..nbVus-1] et se terminant par les sommets de nonVus[0..nbNonVus-1] (dans tous les ordres possibles)
     */
    // ECRIVEZ VOTRE CODE ICI :-)
    if(nbNonVus == 0){
        for (int i = 0; i < nbVus; i++){
            printf("%d ", vus[i]);
        }
        printf("\n");
    }
    else{
        for (int i = 0; i < nbNonVus; i++){
            vus[nbVus] = nonVus[i];

            nonVus[i] = nonVus[nbNonVus - 1];

            permut(vus,nbVus+1,nonVus,nbNonVus-1);
            nonVus[i]= vus[nbVus];

        }
    }
}

int main(){
    int nbSommets, i;
    scanf("%d",&nbSommets);
    int vus[nbSommets], nonVus[nbSommets-1];
    vus[0] = 0;
    for (i=0; i<nbSommets-1; i++)
        nonVus[i] = i+1;
    permut(vus,1,nonVus,nbSommets-1);
}

