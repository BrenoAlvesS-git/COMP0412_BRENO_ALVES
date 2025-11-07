#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

void maxheapify(int *A, int m, int i){
    int maior, aux;
    int e = 2*i +1;
    int d = 2*i+2;
    if(e<= m && A[e]>A[i]){
        maior = e;
    }else{
        maior = i;
    }
    if(d <= m && A[d]> A[maior]){
        maior = d;
    }
    if(maior != i){
        aux = A[i];
        A[i] = A[maior];
        A[maior] = aux;
        maxheapify(A,m,maior);
    }
}


void build_Max_heap(int *A, int n){
    for(int i = floor(n/2);i>=0;i-- ){
        maxheapify(A, n,i);
    }
}
void heapsort(int *A, int n){
    int m,aux;
    build_Max_heap(A,n);
    m=n-1;
    for(int i = n-1;i>= 1;i--){
        aux = A[0];
        A[0]= A[i];
        A[i]= aux;
        m--;
        maxheapify(A,m,0);
    }
}

int* geravalorDecrescente(int n){
    int *a = malloc(sizeof(int)*n);
    for (int i = 0; i <n;i++){
        a[i]= n-1;
    }
    return a;
}

int main(){
    int reps = 15;
    int ini = 100000;
    int fim = 1000000;
    int passo = 10000;
    int i;
    for (i= ini; i<=fim; i+= passo*10){
        int *a = geravalorDecrescente(i);
        for (int j = 0; j< reps; j++){
            clock_t iniClock = clock();
            heapsort(a,i);
            clock_t fimClock = clock();
            double tempo = (double)(fimClock-iniClock)/CLOCKS_PER_SEC;
            printf("%d\t%d\t%lf\n", (j+1),i, tempo);
        }
        free(a);
    }
    return 0;
}