/*
 * Copyright (c) 2008-2010
 *	Nakata, Maho
 * 	All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#include <mpblas.h>
#include <blas.h>
#include <mplapack_compare_debug.h>

#if defined VERBOSE_TEST
#include <iostream>
#endif

#define MIN_INCX -2
#define MAX_INCX 8
#define MIN_INCY -2
#define MAX_INCY 8
#define MIN_N -2
#define MAX_N 8
#define MAX_LDA 10
#define MAX_ITER 2

REAL_REF maxdiff = 0.0;

void Rsyr2_test2(const char *uplo) {
    int errorflag = FALSE;
    int mplapack_errno1, mplapack_errno2;
    for (int n = MIN_N; n < MAX_N; n++) {
        for (int lda = max(n, 1); lda < MAX_LDA; lda++) {
            for (int incx = MIN_INCX; incx <= MAX_INCX; incx++) {
                for (int incy = MIN_INCY; incy < MAX_INCY; incy++) {
#if defined VERBOSE_TEST
                    printf("#n is %d, incx is %d, uplo is %s lda is %d.\n", n, incx, uplo, lda);
#endif
                    REAL_REF alpha_ref;
                    REAL_REF *x_ref;
                    REAL_REF *y_ref;
                    REAL_REF *A_ref;
                    REAL alpha;
                    REAL *x;
                    REAL *y;
                    REAL *A;

                    x_ref = new REAL_REF[veclen(n, incx)];
                    y_ref = new REAL_REF[veclen(n, incy)];
                    A_ref = new REAL_REF[matlen(lda, n)];
                    x = new REAL[veclen(n, incx)];
                    y = new REAL[veclen(n, incy)];
                    A = new REAL[matlen(lda, n)];

                    for (int i = 0; i < MAX_ITER; i++) {
                        set_random_vector(A_ref, A, matlen(lda, n));
                        set_random_vector(x_ref, x, veclen(n, incx));
                        set_random_vector(y_ref, y, veclen(n, incy));
                        set_random_number(alpha_ref, alpha);

                        mplapack_errno = 0;
                        blas_errno = 0;
#if defined ___MPLAPACK_BUILD_WITH_MPFR___
                        dsyr2_f77(uplo, &n, &alpha_ref, x_ref, &incx, y_ref, &incy, A_ref, &lda);
                        mplapack_errno1 = blas_errno;
#else
                        Rsyr2(uplo, n, alpha_ref, x_ref, incx, y_ref, incy, A_ref, lda);
                        mplapack_errno1 = mplapack_errno;
#endif
                        Rsyr2(uplo, n, alpha, x, incx, y, incy, A, lda);
                        mplapack_errno2 = mplapack_errno;
#if defined VERBOSE_TEST
                        printf("errno: mplapack %d, ref %d\n", mplapack_errno1, mplapack_errno2);
#endif
                        if (mplapack_errno1 != mplapack_errno2) {
#if defined VERBOSE_TEST
                            printf("error in Mxerbla!!\n");
#endif
                            errorflag = TRUE;
                        }
                        REAL_REF diff = infnorm(A_ref, A, matlen(lda, n), 1);
                        if (diff > EPSILON) {
#if defined VERBOSE_TEST
                            printf("error: ");
                            printnum(diff);
                            printf("\n");
#endif
                            errorflag = TRUE;
                        }
                        if (maxdiff < diff)
                            maxdiff = diff;
                    }
                    delete[] A_ref;
                    delete[] x_ref;
                    delete[] y_ref;
                    delete[] A;
                    delete[] x;
                    delete[] y;
                }
            }
        }
    }
    if (errorflag == TRUE) {
        printf("error: ");
        printnum(maxdiff);
        printf("\n");
        printf("*** Testing Rsyr2 failed ***\n");
        exit(1);
    } else {
        printf("maxerror: ");
        printnum(maxdiff);
        printf("\n");
    }
}

void Rsyr2_test() {
    Rsyr2_test2("U");
    Rsyr2_test2("L");
}

int main(int argc, char *argv[]) {
    printf("*** Testing Rsyr2 start ***\n");
    Rsyr2_test();
    printf("*** Testing Rsyr2 successful ***\n");
    return (0);
}
