//public domain
#include <mpblas_double.h>
#include <mplapack_double.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define DOUBLE_FORMAT "%+20.16e"
#define DOUBLE_SHORT_FORMAT "%+20.16e"

inline void printnum(double rtmp) { printf(DOUBLE_FORMAT, rtmp); }

// Matlab/Octave format
void printvec(double *a, int len) {
    double tmp;
    printf("[ ");
    for (int i = 0; i < len; i++) {
        tmp = a[i];
        printnum(tmp);
        if (i < len - 1)
            printf(", ");
    }
    printf("]");
}

void printmat(int n, int m, double *a, int lda)
{
    double mtmp;

    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("[ ");
        for (int j = 0; j < m; j++) {
            mtmp = a[i + j * lda];
            printnum(mtmp);
            if (j < m - 1)
                printf(", ");
        }
        if (i < n - 1)
            printf("]; ");
        else
            printf("] ");
    }
    printf("]");
}
int main() {
    mplapackint n = 5;
    mplapackint m = 4;

    double *a = new double[m * n];
    double *s = new double[std::min(m, n)];
    double *u = new double[m * m];
    double *vt = new double[n * n];
    mplapackint lwork = std::max({(mplapackint)1, 3 * std::min(m, n) + std::max(m, n), 5 * std::min(m, n)});
    double *work = new double[lwork];
    mplapackint info;

    // setting A matrix
    if (n > m) {
        a[0 + 0 * m] = 0.35;        a[0 + 1 * m] = -0.1160;       a[0 + 2 * m] = -0.3886;       a[0 + 3 * m] = -0.2942;       a[0 + 4 * m] = -0.2942;
        a[1 + 0 * m] = -0.5140;     a[1 + 1 * m] = 0.1225;        a[1 + 2 * m] = 0.1004;        a[1 + 3 * m] = 0.1126;        a[1 + 4 * m] = 1.1133;
        a[2 + 0 * m] = 0.4881;      a[2 + 1 * m] = -1.6443;       a[2 + 2 * m] = -0.1357;       a[2 + 3 * m] = -0.0977;       a[2 + 4 * m] = -9.343;
        a[3 + 0 * m] = -3.0;        a[3 + 1 * m] = 9.811;         a[3 + 2 * m] = 0.4262;        a[3 + 3 * m] = 0.1632;        a[3 + 4 * m] = 0.33;
    }
    if (m > n) {
        a[0 + 0 * m] = 0.35;        a[0 + 1 * m] = -0.1160;       a[0 + 2 * m] = -0.3886;       a[0 + 3 * m] = -0.2942;
        a[1 + 0 * m] = -0.5140;     a[1 + 1 * m] = 0.1225;        a[1 + 2 * m] = 0.1004;        a[1 + 3 * m] = 0.1126;
        a[2 + 0 * m] = 0.4881;      a[2 + 1 * m] = -1.6443;       a[2 + 2 * m] = -0.1357;       a[2 + 3 * m] = -0.0977;
        a[3 + 0 * m] = -3.0;        a[3 + 1 * m] = 9.811;         a[3 + 2 * m] = 0.4262;        a[3 + 3 * m] = 0.1632;
        a[4 + 0 * m] = 1.49333;     a[4 + 1 * m] = 0.55131;       a[4 + 2 * m] = 0.6831;        a[4 + 3 * m] = 0.33333;
    }

    if (m == n) {
        a[0 + 0 * m] = 0.35;        a[0 + 1 * m] = -0.1160;       a[0 + 2 * m] = -0.3886;       a[0 + 3 * m] = -0.2942;
        a[1 + 0 * m] = -0.5140;     a[1 + 1 * m] = 0.1225;        a[1 + 2 * m] = 0.1004;        a[1 + 3 * m] = 0.1126;
        a[2 + 0 * m] = 0.4881;      a[2 + 1 * m] = -1.6443;       a[2 + 2 * m] = -0.1357;       a[2 + 3 * m] = -0.0977;
        a[3 + 0 * m] = -3.0;        a[3 + 1 * m] = 9.811;         a[3 + 2 * m] = 0.4262;        a[3 + 3 * m] = 0.1632;
    }

    printf("# octave check\n");
    printf("a ="); printmat(m, n, a, m); printf("\n");
    Rgesvd("A", "A", m, n, a, m, s, u, m, vt, n, work, lwork, info);
    printf("s="); printvec(s, std::min(m, n)); printf("\n");
    if (m < n)
        printf("padding=zeros(%d, %d-%d)\n", (int)m, (int)n, (int)m);
    if (n < m)
        printf("padding=zeros(%d-%d,%d)\n", (int)m, (int)n, (int)n);
    printf("u ="); printmat(m, m, u, m); printf("\n");
    printf("vt ="); printmat(n, n, vt, n); printf("\n");
    printf("svd(a)\n");
    if (m < n)
        printf("sigma=[diag(s) padding] \n");
    if (n < m)
        printf("sigma=[diag(s); padding] \n");
    if (n == m)
        printf("sigma=[diag(s)] \n");
    printf("sigma \n");
    printf("u * sigma  * vt\n");
    delete[] work;
    delete[] vt;
    delete[] u;
    delete[] s;
    delete[] a;
}
