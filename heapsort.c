#include <stdio.h>
#include <stdlib.h>




void criarHeap(int *lista,int inicio,int fim){
    //aux será relativamente o pai
    int aux = lista[inicio];
    //calculamos o primeiro filho(j)
    int j=inicio*2+1;
    while(j<= fim){
        if(j<fim){
            //verificação para saber qual dos filhos é menor,caso o filho(j) for o menor,incrementamos a posição na lista e vamos atrás do outro filho
            //caso contrário,continumaos no (j)
            if(lista[j]<lista[j+1]){
                j++;
            }
        }
        //verificação para saber se a posição do pai é maior do que o do filho,por que a posição do pai deve sempre ser maior do que a dos filhos
        //caso essa verificação retorne que "isso é falso",e trocamos a posição do pai pela posição do 
        //processo se repete
        if(aux<lista[j]){
            lista[inicio] = lista[j];
            inicio=j;
            j= 2*inicio+1;
        } else {
            j= fim+1;
        }
    }
    //antigo pai ocupa o lugar do último filho analisado
    lista[inicio] = aux;
}

//todo elemento pai da árvore possui 2 filhos,o pai tem como posição(i) e os filhos(2*i+1) e (2*i+2)
void heapsort(int *lista,int fim){
    int i,aux;
    //for para percorrer/preencher o vetor da metade do vetor para o início
    for(i= (fim-1)/2;i>=0;i--){
        criarHeap(lista,i,fim-1);
    }
    //pegamos o maior elemento da heap(topo) e colocar ele na posição i(última posição do vetor) ordenando-o
    for(i =fim-1;i>=1;i--){
        aux = lista[0];
        lista[0] = lista[i];
        lista[i]= aux;
        criarHeap(lista,0,i-1);
    }
}



int main(int argc, char *argv[]) {
    FILE* arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("ERRO\n");
        return 0;
    }
    FILE* saida = fopen(argv[2], "w");
    if (saida == NULL) {
        printf("ERRO\n");
        return 0;
    }


    fclose(arquivo);
    fclose(saida);

    return 0;
}