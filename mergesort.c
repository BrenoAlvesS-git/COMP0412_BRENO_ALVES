#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static void merge(int *x, int *aux,int i, int m, int f){
    for(int k = i; k<=f;k++){
        aux[k] = x[k];
    }
    int ix=i;
    int iy=m+1;
    int k =i;

    while (ix<=m && iy <= f){
        if(aux[ix]<=aux[iy]){
            x[k++]= aux[ix++];
        }else{
            x[k++] = aux[iy++];
        }
    }
    while (ix <= m) x[k++] = aux[ix++];
    while (iy <= f) x[k++] = aux[iy++];
}

static void sort(int *x, int *aux,int i, int f){
    if(i >= f){
        return;
    }
    int m = i+(f-i)/2;

    sort(x,aux,i,m);
    sort(x,aux,m+1,f);

    if(x[m] <= x[m+1]){
        return;
    }

    merge(x,aux,i,m,f);

}


void mergesort(int *x, int n){
    int *y = malloc(sizeof(int)*n);
    if (!y) return;
    sort(x, y, 0, n-1);
    free(y);
}

int main(void){
int n;
    if (scanf("%d", &n) != 1){
        return 1;
    }
    int *A = (int*) malloc((size_t)n * sizeof(int));
    if (!A){
        free(A);
        return 2;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1){
            free(A);
            
            return 1;
        }
    }
    clock_t t0 = clock();
    mergesort(A,n);
    clock_t t1 = clock();

    double tempo = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("%.9f\n", tempo);

    free(A);

    return 0;
    
}