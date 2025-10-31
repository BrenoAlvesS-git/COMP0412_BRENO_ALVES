#include<stdio.h>
#include<time.h>

int merge(int *x, int *y,int i, int m, int f){
    int z, ix = i, iy = m+1;
    
    for(z=1; z<=f; z++){
        y[z] = x[z];
        z = i;
    }

    while (ix<=m && iy <= f){
        if(y[ix]<=y[iy]){
            x[z++]= y[ix++];
        }else{
            x[z++] = y[iy++];
        }
    }
    while (ix <= m) x[z++] = y[ix++];

    while (iy <= f) x[z++] = y[iy++];
}

int sort(int *x, int *y,int i, int f){
    if(i >= f){
        return;
    }
    int m = (i+f)/2;

    sort(x,y,i,m);
    sort(x,y,m+1,f);

    if(x[m] <= x[m+1]){
        return;
    }

    merge(x,y,i,m,f);

}


void mergesort(int *x, int n){
    int *y = malloc(sizeof(int)*n);
    sort(x, y, 0, n-1);
    free(y);
}

int main(){
    int array_P[6] = {6,5,4,3,2,1};
    int auxR;
    mergesort(array_P,6);
    for(auxR= 0;auxR<6; auxR++){
        printf ("%d ",array_P[auxR]);
        putchar('\n');
    }
    
}