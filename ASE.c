#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAP 2
#define MATCH 0
#define MISMATCH 1
#define INF 1000000000

int cost(char a, char b) {
    return (a == b) ? MATCH : MISMATCH;
}

typedef struct {
    char *a;
    char *b;
} Alignment;



int* forwardAlignment(char *X, int m, char *Y, int n) {
    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));

    for (int i = 0; i <= m; i++)
        prev[i] = i * GAP;

    for (int j = 1; j <= n; j++) {
        curr[0] = j * GAP;

        for (int i = 1; i <= m; i++) {
            int diag = prev[i - 1] + cost(X[i - 1], Y[j - 1]);
            int up   = prev[i] + GAP;
            int left = curr[i - 1] + GAP;

            curr[i] = diag;
            if (up < curr[i]) curr[i] = up;
            if (left < curr[i]) curr[i] = left;
        }

        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    free(curr);
    return prev;
}

int* backwardAlignment(char *X, int m, char *Y, int n) {
    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));

    for (int i = 0; i <= m; i++)
        prev[i] = i * GAP;

    for (int j = 1; j <= n; j++) {
        curr[0] = j * GAP;

        for (int i = 1; i <= m; i++) {
            int diag = prev[i - 1] + cost(X[m - i], Y[n - j]);
            int up   = prev[i] + GAP;
            int left = curr[i - 1] + GAP;

            curr[i] = diag;
            if (up < curr[i]) curr[i] = up;
            if (left < curr[i]) curr[i] = left;
        }

        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    free(curr);
    return prev;
}



Alignment needlemanWunsch(char *X, int m, char *Y, int n) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = i * GAP;
    for (int j = 0; j <= n; j++) dp[0][j] = j * GAP;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int diag = dp[i - 1][j - 1] + cost(X[i - 1], Y[j - 1]);
            int up   = dp[i - 1][j] + GAP;
            int left = dp[i][j - 1] + GAP;

            dp[i][j] = diag;
            if (up < dp[i][j]) dp[i][j] = up;
            if (left < dp[i][j]) dp[i][j] = left;
        }
    }

    char *a = malloc(m + n + 1);
    char *b = malloc(m + n + 1);
    int i = m, j = n, k = 0;

    while (i > 0 || j > 0) {
        int diagCost = (i > 0 && j > 0) ? dp[i - 1][j - 1] + cost(X[i - 1], Y[j - 1]) : INF;
        int upCost   = (i > 0) ? dp[i - 1][j] + GAP : INF;
        int leftCost = (j > 0) ? dp[i][j - 1] + GAP : INF;

        if (diagCost <= upCost && diagCost <= leftCost) {
            a[k] = (i > 0) ? X[i - 1] : '-';
            b[k] = (j > 0) ? Y[j - 1] : '-';
            i--; j--;
        }
        else if (upCost <= leftCost) {
            a[k] = X[i - 1];
            b[k] = '-';
            i--;
        }
        else {
            a[k] = '-';
            b[k] = Y[j - 1];
            j--;
        }
        k++;
    }

    a[k] = b[k] = '\0';

    for (int p = 0; p < k / 2; p++) {
        char t = a[p]; a[p] = a[k - p - 1]; a[k - p - 1] = t;
        t = b[p]; b[p] = b[k - p - 1]; b[k - p - 1] = t;
    }

    Alignment res = {a, b};
    return res;
}

/* ===================== HIRSCHBERG ===================== */

Alignment hirschberg(char *X, int m, char *Y, int n) {
    if (m <= 1 || n <= 1)
        return needlemanWunsch(X, m, Y, n);

    int mid = n / 2;

    int *f = forwardAlignment(X, m, Y, mid);
    int *g = backwardAlignment(X, m, Y + mid, n - mid);

    int q = 0;
    int best = INF;

    for (int i = 0; i <= m; i++) {
        int val = f[i] + g[m - i];
        if (val < best) {
            best = val;
            q = i;
        }
    }


    free(f);
    free(g);

    Alignment left  = hirschberg(X, q, Y, mid);
    Alignment right = hirschberg(X + q, m - q, Y + mid, n - mid);

    int len = strlen(left.a) + strlen(right.a);

    char *A = malloc(len + 1);
    char *B = malloc(len + 1);

    sprintf(A, "%s%s", left.a, right.a);
    sprintf(B, "%s%s", left.b, right.b);

    free(left.a);  free(left.b);
    free(right.a); free(right.b);

    Alignment res = {A, B};
    return res;
}



int main() {
    char X[10005], Y[10005];

    scanf("%s", X);
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    Alignment result = hirschberg(X, m, Y, n);

    int score = 0;
    for (int i = 0; result.a[i]; i++) {
        if (result.a[i] == '-' || result.b[i] == '-')
            score += GAP;
        else
            score += cost(result.a[i], result.b[i]);
    }

    printf("%d\n", score);
    printf("%s\n", result.a);
    printf("%s\n", result.b);

    free(result.a);
    free(result.b);

    return 0;
}

/*. Explique por que a função Backward é necessária para encontrar o ponto de
corte ótimo q na coluna central.


2. Discuta a complexidade de espaço. Por que a versão recursiva (Parte B)
é considerada O(m + n) mesmo fazendo chamadas recursivas? Baseie sua
resposta na reutilização de memória descrita em aula.

*/

