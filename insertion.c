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

void insertion(int *A, int n);

int main(){
    int arrayP[] = {6,5,4,3,2,1};//array pro pior caso
    int arrayM[] = {1,2,3,4,5,6};//array pro melhor caso(percebi que pra essa quantidade de elementos é irrelevante pior ou melhor caso :p)
    int tamanho = 6;

    insertion(arrayP,tamanho);
    printf("Array ordenado:\n");
    for(int i =0; i<tamanho;i++){
        printf("%d ", arrayP[i]);
    }

}
//lembrando da invariante, o algoritmo já está ordenado do indice 0 até x-1
void insertion(int *A, int n){
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