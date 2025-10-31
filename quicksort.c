#include<stdio.h>

int particiona(int *a, int p, int r);
int quicksort(int *a, int p, int r);


int main(){


}

int quicksort(int *a, int p, int r){
    
}


int particiona(int *a,int p, int r){
    int x = a[r];
    int i = p-1;
    for(int j=0; j<=r-1; j++){
        if(a[j]<= x){
            i = i+1;
        }
        a[i] = a[j];
        a[i+1] = a[r];
    }
    if(p<r){
        int q = particiona(*a,p,r);
        quicksort(*a,p,q-1);
        quicksort(*a,q+1,r);
    }
}