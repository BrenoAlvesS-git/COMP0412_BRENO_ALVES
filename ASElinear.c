#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   DEFINIÇÃO DOS CUSTOS (conforme especificação do projeto)
   ========================================================= */
#define GAP 2
#define MATCH 0
#define MISMATCH 1

/* =========================================================
   Função de custo entre dois caracteres
   ========================================================= */
int cost(char a, char b) {
    if (a == b)
        return MATCH;
    return MISMATCH;
}

/* =========================================================
   ESTRUTURA PARA RETORNAR O ALINHAMENTO
   a -> string alinhada de X
   b -> string alinhada de Y
   ========================================================= */
typedef struct {
    char *a;
    char *b;
} Alignment;

/* =========================================================
   PARTE A — SPACE-EFFICIENT-ALIGNMENT (FORWARD)
   Calcula os custos do início até o fim
   Retorna a última coluna f(i, n)
   Espaço: O(m)
   ========================================================= */
int* forwardAlignment(char *X, int m, char *Y, int n) {

    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));

    /* Inicialização da primeira coluna (Y vazio) */
    for (int i = 0; i <= m; i++)
        prev[i] = i * GAP;

    /* Percorre as colunas de Y */
    for (int j = 1; j <= n; j++) {

        /* Primeira linha (X vazio) */
        curr[0] = j * GAP;

        for (int i = 1; i <= m; i++) {

            int diag = prev[i - 1] + cost(X[i - 1], Y[j - 1]);
            int up   = prev[i] + GAP;        // gap em X
            int left = curr[i - 1] + GAP;    // gap em Y

            curr[i] = diag;
            if (up < curr[i])   curr[i] = up;
            if (left < curr[i]) curr[i] = left;
        }

        /* Troca prev <-> curr */
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    free(curr);
    return prev;   // última coluna
}

/* =========================================================
   PARTE A — BACKWARD-SPACE-EFFICIENT-ALIGNMENT
   Calcula os custos do fim para o início
   Retorna a última coluna g(i, 0)
   Espaço: O(m)
   ========================================================= */
int* backwardAlignment(char *X, int m, char *Y, int n) {

    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));

    /* Inicialização (sufixo de X com vazio) */
    for (int i = 0; i <= m; i++)
        prev[i] = i * GAP;

    /* Percorre Y de trás para frente */
    for (int j = 1; j <= n; j++) {

        curr[0] = j * GAP;

        for (int i = 1; i <= m; i++) {

            int diag = prev[i - 1] + cost(X[m - i], Y[n - j]);
            int up   = prev[i] + GAP;
            int left = curr[i - 1] + GAP;

            curr[i] = diag;
            if (up < curr[i])   curr[i] = up;
            if (left < curr[i]) curr[i] = left;
        }

        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    free(curr);
    return prev;
}

/* =========================================================
   CASO BASE — NEEDLEMAN-WUNSCH CLÁSSICO
   Usado quando m <= 2 ou n <= 2
   ========================================================= */
Alignment needlemanWunsch(char *X, int m, char *Y, int n) {

    int dp[m + 1][n + 1];

    /* Inicialização */
    for (int i = 0; i <= m; i++) dp[i][0] = i * GAP;
    for (int j = 0; j <= n; j++) dp[0][j] = j * GAP;

    /* Preenchimento da matriz */
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            int diag = dp[i - 1][j - 1] + cost(X[i - 1], Y[j - 1]);
            int up   = dp[i - 1][j] + GAP;
            int left = dp[i][j - 1] + GAP;

            dp[i][j] = diag;
            if (up < dp[i][j])   dp[i][j] = up;
            if (left < dp[i][j]) dp[i][j] = left;
        }
    }

    /* Backtracking */
    char *a = malloc(m + n + 1);
    char *b = malloc(m + n + 1);
    int k = 0, i = m, j = n;

    while (i > 0 || j > 0) {

        if (i > 0 && j > 0 &&
            dp[i][j] == dp[i - 1][j - 1] + cost(X[i - 1], Y[j - 1])) {
            a[k] = X[i - 1];
            b[k] = Y[j - 1];
            i--; j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + GAP) {
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

    /* Inverte as strings */
    for (int p = 0; p < k / 2; p++) {
        char t = a[p]; a[p] = a[k - p - 1]; a[k - p - 1] = t;
        t = b[p]; b[p] = b[k - p - 1]; b[k - p - 1] = t;
    }

    Alignment res = {a, b};
    return res;
}

/* =========================================================
   PARTE B — HIRSCHBERG (DIVIDE AND CONQUER)
   ========================================================= */
Alignment hirschberg(char *X, int m, char *Y, int n) {

    /* Caso base */
    if (m <= 2 || n <= 2)
        return needlemanWunsch(X, m, Y, n);

    int mid = n / 2;

    /* Parte A */
    int *f = forwardAlignment(X, m, Y, mid);
    int *g = backwardAlignment(X, m, Y + mid, n - mid);

    /* Encontra o ponto de corte ótimo */
    int q = 0;
    int best = f[0] + g[m];

    for (int i = 1; i <= m; i++) {
        int val = f[i] + g[m - i];
        if (val < best) {
            best = val;
            q = i;
        }
    }

    free(f);
    free(g);

    /* Divide e conquista */
    Alignment left  = hirschberg(X, q, Y, mid);
    Alignment right = hirschberg(X + q, m - q, Y + mid, n - mid);

    /* Concatenação dos alinhamentos */
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

/* =========================================================
   MAIN — EXEMPLO DE USO
   ========================================================= */
int main() {

    char X[] = "ACGT";
    char Y[] = "AGT";

    Alignment result = hirschberg(X, strlen(X), Y, strlen(Y));

    printf("Alinhamento X: %s\n", result.a);
    printf("Alinhamento Y: %s\n", result.b);

    free(result.a);
    free(result.b);

    return 0;
}
