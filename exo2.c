//
// Created by Aurélien on 27/05/2021.
//
#include <stdio.h>
#include <stdlib.h>

int** cout;
int pcc = 100000; //plus court chemin
int dMin = 100000; //arc le plus court
int nextRand(int iseed){
    // Postcondition : retourne le prochain entier selon une suite pseudo-aleatoire avec la graine iseed
    int i = 16807 * (iseed % 127773) - 2836 * (iseed / 127773);
    if (i > 0) iseed = i;
    else iseed = 2147483647 + i;
    return iseed;
}

int** creeCout1(int n){
    // retourne une matrice cout telle que pour tout i,j appartenant à [0,n-1], cout[i][j] = cout de l'arc (i,j)
    int** cout;
    int coutMax = 1000;
    int iseed = 1;
    cout = (int**) malloc(n*sizeof(int*));
    for (int i=0; i<n; i++){
        cout[i] = (int*) malloc(n*sizeof(int));
        for (int j=0; j<n; j++){
            if (i == j) cout[i][j] = coutMax+1;
            else {
                iseed = nextRand(iseed);
                cout[i][j] = 1 + iseed % coutMax;
            }
        }
    }
    return cout;
}
int** creeCout(int n){
    // retourne une matrice cout telle que pour tout i,j appartenant à [0,n-1], cout[i][j] = cout de l'arc (i,j)
    int** cout;
    int coutMax = 1000;
    int iseed = 1;
    cout = (int**) malloc(n*sizeof(int*));
    for (int i=0; i<n; i++){
        cout[i] = (int*) malloc(n*sizeof(int));
        for (int j=0; j<n; j++){
            if (i == j) cout[i][j] = coutMax+1;
            else {
                iseed = nextRand(iseed);
                cout[i][j] = 1 + iseed % coutMax;
                if(cout[i][j]<dMin)
                    dMin = cout[i][j];
            }
        }
    }
    return cout;
}


int bound(int nbNonVus){
    return (nbNonVus + 1)*dMin;
}

int bound2(int last, const int nonVus[], int nbNonVus){

    int l = 100000;
    int res = 0;
    for (int i = 0; i < nbNonVus; i++){
        int current = nonVus[i];
        int currentL = cout[last][current];
        if(currentL < l){
            l = currentL;
        }
        int li = cout[current][0];
        //calcul de li
        for(int j = 0; j < nbNonVus; j++){
            if(j == i){
                continue;
            }
            int next = nonVus[j];
            int currentLi = cout[current][next];
            if(currentLi < li){
                li = currentLi;
            }
        }
        res += li;
    }
    res += l;
    return res;
}

int * order(int last, const int * nonVus, int nbNonVus){
    int * res = (int *) malloc(nbNonVus * sizeof(int));
    //copy nonVus to res
    for(int i =0; i < nbNonVus; i++){
        res[i] = nonVus[i];
    }
    for (int i = 0; i < nbNonVus-1; i++){
        for (int j = 0 ; j < nbNonVus-i-1; j++){
            if (cout[last][res[j]] > cout[last][res[j+1]]){
                int tmp = res[j];
                res[j] = res[j+1];
                res[j+1] = tmp;

            }
        }
    }

    return res;

}
void permut(int vus[], int nbVus, int nonVus[], int nbNonVus, int longueur){
    /*
     Variable globale :
     - pour tout couple de sommets (i,j), cout[i][j] = cout pour aller de i vers j
     Entree :
     - nonVus[0..nbNonVus-1] = sommets non visites
     - vus[0..nbVus-1] = sommets visites
     Precondition :
     - nbVus > 0 et Vus[0] = 0 (on commence toujours par le sommet 0)
     - longueur = somme des couts des arcs du chemin <vus[0], vus[1], ..., vus[nbVus-1]>
     Postcondition : affiche les longueurs de tous les circuits commençant par vus[0..nbVus-1] et se terminant par les sommets de nonVus[0..nbNonVus-1] (dans tous les ordres possibles), suivis de 0
     */
    // ECRIVEZ VOTRE CODE ICI :-)
    if(nbNonVus == 0){
        int last = vus[nbVus-1];
        int first = vus[0];
        int currentDistance = longueur + cout[last][first]; //do not forget return to 0
        if (currentDistance < pcc){
            pcc = currentDistance;
        }
        //printf("%d ", currentDistance);
        /*
        for (int i = 0; i < nbVus; i++){
            printf("%d ", vus[i]);
        }
        printf("\n");
         */
    }else{
        //int heuristic = longueur + bound(nbNonVus);
        int heuristic = longueur + bound2(vus[nbVus-1], nonVus, nbNonVus);
        if (heuristic < pcc) {
            nonVus = order(vus[nbVus-1], nonVus, nbNonVus);
            for (int k = 0; k < nbNonVus; k++) {
                vus[nbVus] = nonVus[k]; //add to vus
                nonVus[k] = nonVus[nbNonVus - 1];   //remove from nonVus

                int i = vus[nbVus - 1];
                int j = vus[nbVus];

                permut(vus, nbVus + 1, nonVus, nbNonVus - 1, longueur + cout[i][j]);

                nonVus[k] = vus[nbVus]; //Undo

            }
        }
    }
}

int main(){
    int nbSommets;
    scanf("%d",&nbSommets);
    cout = creeCout(nbSommets);
    int vus[nbSommets];
    int nonVus[nbSommets-1];
    for (int i=0; i<nbSommets-1; i++) nonVus[i] = i+1;
    vus[0] = 0;
    permut(vus,1,nonVus,nbSommets-1,0);
    printf("Pcc for n = %d : %d", nbSommets, pcc);
}


