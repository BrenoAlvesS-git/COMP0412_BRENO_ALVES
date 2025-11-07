/*
 * - recursão de cauda eliminada
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CUTOFF 16

static void insertion_sort(int *A, int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= p && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

static void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static int median3(int *A, int p, int r) {
    int m = (p + r) / 2;
    if (A[m] < A[p]) swap(&A[m], &A[p]);
    if (A[r] < A[p]) swap(&A[r], &A[p]);
    if (A[m] < A[r]) swap(&A[m], &A[r]);
    // pivô agora em A[r]
    return A[r];
}

static int partition(int *A, int p, int r) {
    int x = median3(A, p, r);
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

static void quicksort(int *A, int p, int r) {
    while (p < r) {
        if (r - p + 1 <= CUTOFF) {
            insertion_sort(A, p, r);
            break;
        }
        int q = partition(A, p, r);
        // recursão de cauda otimizada
        if (q - p < r - q) {
            quicksort(A, p, q - 1);
            p = q + 1;
        } else {
            quicksort(A, q + 1, r);
            r = q - 1;
        }
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int *A = (int*) malloc((size_t)n * sizeof(int));
    if (!A) return 2;

    for (int i = 0; i < n; i++)
        if (scanf("%d", &A[i]) != 1) { free(A); return 1; }

    clock_t t0 = clock();
    quicksort(A, 0, n - 1);
    clock_t t1 = clock();

    printf("%.9f\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
    free(A);
    return 0;
}
