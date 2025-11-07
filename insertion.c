/*Preciso fazer os 3 algoritmos de ordenação e inserção usando C, ver o tempo de execução de cada um
fazer o grafico de cada com quantidade de entradas vs tempo de execução usando python, gravar um video
de mais ou menos 5 minutos detalhando o código e explicando os graficos, posso usar qualquer biblioteca

tamanho da instancia vs tempo de execução
10                                ?
100                               ?
1000                              ?
10000                             ?
100000                            ?
1000000                           ?
Rodar varias vezes pra cada tamanho de instancia pela minha cabeça um bom número é 12 vezes pra cada
tamanho de instância, tirar média se for conveniente desvio padrão.
Executar todos os algoritmos de forma mais justa possivel, ou seja, com as mesmas coisas abertas,
se possivel tudo fechado para maior constância nos dados


*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//lembrando da invariante, o algoritmo já está ordenado do indice 0 até x-1
static void insertion(int *A, int n){
    for(int x = 1; x<n; x++){//entra num loop a partir do segundo elemento pois em teoria o primeiro já tá prdenado
        int lista = A[x];       //armazena o valor atual de A[posição x] 
        int i = x-1;    //cria um outro indice na possição anterior a x pra podermos ordenar

        while(i>=0 && A[i]> lista){//segundo loop para cumprir as duas condições que é o indice não ser invalido 
            A[i+1] = A[i];          //copia os valores para a proxima posição
            i=i-1;                  //move o indice para esquerda
        }
        A[i+1] = lista;             //insere o valor na posição correta
    }
}

int main(void){
    int n;
    if (scanf("%d", &n) != 1){
        return 1;
    }
    int *A = (int*) malloc((size_t)n * sizeof(int));
    if (!A) {
        return 2;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1) { free(A);
             return 1;
            }
    }

    clock_t t0 = clock();
    insertion(A, n);
    clock_t t1 = clock();

    double tempo = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("%.9f\n", tempo);

    free(A);
    return 0;

}
