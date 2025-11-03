#include<stdio.h>

int particiona(int a, int p, int r);
void quicksort(int a, int p, int r);


int main(){


}

void quicksort(int a, int p, int r){
    if(p<r){
    int q = particiona(a,p,r);
    quicksort(a,p,q-1);
    quicksort(a,q+1,r);
    }
    
}


int particiona(int a,int p, int r){
    int x = a[r];
    int i = p-1;
    for(int j=p; j<=r-1; j++){
        if(a[j]<= x){
            i++;
        }
        int tmp = a[i];
        a[i] = a[j];
        a[j]=tmp;
    }
    int tmp =a[i+1];
    a[i+1]=a[r];
    a[r]=tmp;

    return i+1;
}