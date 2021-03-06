//public domain
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>

#include <mpblas_qd.h>
#include <mplapack_qd.h>

#define QD_PRECISION_SHORT 16

inline void printnum(qd_real rtmp) {
    std::cout.precision(QD_PRECISION_SHORT);
    if (rtmp >= 0.0) {
        std::cout << "+" << rtmp;
    } else {
        std::cout << rtmp;
    }
    return;
}

//Matlab/Octave format
void printvec(qd_real *a, int len) {
    qd_real tmp;
    printf("[ ");
    for (int i = 0; i < len; i++) {
        tmp = a[i];
        printnum(tmp);
        if (i < len - 1)
            printf(", ");
    }
    printf("]");
}

void printmat(int n, int m, qd_real * a, int lda)
{
    qd_real mtmp;
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

    qd_real *a = new qd_real[m * n];
    qd_real *s = new qd_real[std::min(m, n)];
    qd_real *u = new qd_real[m * m];
    qd_real *vt = new qd_real[n * n];
    mplapackint lwork = std::max({(mplapackint)1, 3 * std::min(m, n) + std::max(m, n), 5 * std::min(m, n)});
    qd_real *work = new qd_real[lwork];
    mplapackint info;

    // setting A matrix
    a[0 + 0 * m] = 1.0; a[0 + 1 * m] = 0.0; a[0 + 2 * m] = 0.0;  a[0 + 3 * m] = 0.0;  a[0 + 4 * m] = 2.0;
    a[1 + 0 * m] = 0.0; a[1 + 1 * m] = 0.0; a[1 + 2 * m] = 3.0;  a[1 + 3 * m] = 0.0;  a[1 + 4 * m] = 0.0;
    a[2 + 0 * m] = 0.0; a[2 + 1 * m] = 0.0; a[2 + 2 * m] = 0.0;  a[2 + 3 * m] = 0.0;  a[2 + 4 * m] = 0.0;
    a[3 + 0 * m] = 0.0; a[3 + 1 * m] = 2.0; a[3 + 2 * m] = 0.0;  a[3 + 3 * m] = 0.0;  a[3 + 4 * m] = 0.0;

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
