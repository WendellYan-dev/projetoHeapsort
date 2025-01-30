#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int indice;
    int tamanho;
    char *dadosPacote;
}Pacote;


// A empresa de telecomunicações **Poxim Tech** está construindo um sistema de comunicação baseado no **protocolo de datagrama do usuário (UDP)** para transferência de pacotes em redes **TCP/IP**.  

// #### **Características do Sistema**  
// - Os dados são organizados em **sequências de bytes de tamanho variável**, com um limite máximo de **512 bytes** por pacote.  
// - Devido às características de roteamento das redes **TCP/IP**, os pacotes podem **chegar fora de ordem**, tornando necessária a **reordenação** antes do processamento.  
// - Para permitir o acesso rápido aos dados, o sistema pode **processar as informações parcialmente ordenadas**, desde que os pacotes iniciais já estejam disponíveis.  
// - Esse processamento é acionado quando uma **quantidade específica de pacotes** for recebida.  

// ---

// ### **Formato do Arquivo de Entrada**  
// O arquivo de entrada contém os seguintes dados:  

// 1. **Primeira linha:**  
//    ```
//    [número total de pacotes] [quantidade de pacotes para processamento]
//    ```
// 2. **Linhas seguintes:** Para cada pacote recebido, são fornecidos os seguintes valores:  
//    ```
//    [número do pacote] [tamanho do pacote] [B1] [B2] ... [Bm]
//    ```
//    Onde:  
//    - **Número do pacote**: Identificador único do pacote.  
//    - **Tamanho do pacote**: Número de bytes contidos no pacote.  
//    - **B1 ... Bm**: Sequência de bytes do pacote.  

// **Exemplo de entrada:**  
// 6 2
// 0 3 01 02 03
// 1 2 04 05
// 2 4 06 07 08 09
// 4 2 0F 10
// 3 5 0A 0B 0C 0D 0E
// 5 6 11 12 13 14 15 16


// ### **Formato do Arquivo de Saída**  
// Sempre que a quantidade definida de pacotes for recebida, os pacotes disponíveis são **parcialmente ordenados**.  
// - Se for possível formar a sequência inicial completa, os **dados desses pacotes são exibidos**.  

// A saída contém os bytes ordenados na sequência correta conforme os pacotes forem sendo organizados.  
// |01,02,03|04,05|
// |06,07,08,09|
// |0A,0B,0C,0D,0E|0F,10|11,12,13,14,15,16|





void criarHeap(Pacote *pacote,int inicio,int fim){
    //aux será relativamente o pai
    Pacote aux = pacote[inicio];
    //calculamos o primeiro filho(j)
    int j=inicio*2+1;
    while(j<= fim){
        if(j<fim){
            //verificação para saber qual dos filhos é menor,caso o filho(j) for o menor,incrementamos a posição na lista e vamos atrás do outro filho
            //caso contrário,continumaos no (j)
            if(pacote[j].indice<pacote[j+1].indice){
                j++;
            }
        }
        //verificação para saber se a posição do pai é maior do que o do filho,por que a posição do pai deve sempre ser maior do que a dos filhos
        //caso essa verificação retorne que "isso é falso",e trocamos a posição do pai pela posição do 
        //processo se repete
        if(aux.indice<pacote[j].indice){
            pacote[inicio] = pacote[j];
            inicio=j;
            j= 2*inicio+1;
        } else {
            j= fim+1;
        }
    }
    //antigo pai ocupa o lugar do último filho analisado
    pacote[inicio] = aux;
}

//todo elemento pai da árvore possui 2 filhos,o pai tem como posição(i) e os filhos(2*i+1) e (2*i+2)
void heapsort(Pacote *pacote,int fim){
    int i;
    Pacote aux;
    //for para percorrer/preencher o vetor da metade do vetor para o início
    for(i= (fim-1)/2;i>=0;i--){
        criarHeap(pacote,i,fim-1);
    }
    //pegamos o maior elemento da heap(topo) e colocar ele na posição i(última posição do vetor) ordenando-o
    for(i =fim-1;i>=1;i--){
        aux = pacote[0];
        pacote[0] = pacote[i];
        pacote[i]= aux;
        criarHeap(pacote,0,i-1);
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

    int totalPacotes,pularPacotes;
    
    fscanf(arquivo, "%d%d", &totalPacotes,&pularPacotes);
    Pacote *pacote = (Pacote *)malloc(totalPacotes * sizeof(Pacote));
    if (pacote == NULL) {
        printf("ERRO\n");
    }

    for (int i = 0; i < totalPacotes; i++) {

        fscanf(arquivo, "%d%d",&pacote[i].indice, &pacote[i].tamanho);
        pacote[i].dadosPacote = (char *)malloc(pacote[i].tamanho *sizeof(char));
        if (pacote[i].dadosPacote == NULL) {
            printf("ERRO\n");
        }    

        for (int j = 0; j < pacote[i].tamanho; j++) {
            fscanf(arquivo, "%2hhx", &pacote[i].dadosPacote[j]);
        }
    }

    int indiceAtual = 0;
    int lidos = 0;

    while(indiceAtual<totalPacotes) {
        int k = 0;
        int limite = indiceAtual + pularPacotes;
        if(limite>totalPacotes) {
            limite = totalPacotes;
        }

        heapsort(pacote+lidos,limite-lidos);

    
        for (int i = lidos; i < limite; i++) {
            if (pacote[i].indice == lidos) {
                fprintf(saida, "|");
                k =1;
                for (int j = 0; j < pacote[i].tamanho; j++) {
                    fprintf(saida, "%02X", (unsigned char)pacote[i].dadosPacote[j]);
                    if (j < pacote[i].tamanho - 1) {
                        fprintf(saida, ",");
                    }
                }
                lidos++;
            } 
        }
        if(k==1){
            fprintf(saida, "|");
            fprintf(saida, "\n");
        }
        
        indiceAtual = limite;
    }
    
    //apaguei o for de free q limpa de todos

    free(pacote);
    fclose(arquivo);
    fclose(saida);

    return 0;
}