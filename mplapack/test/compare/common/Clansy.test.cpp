/*
 * Copyright (c) 2008-2010
 *	Nakata, Maho
 * 	All rights reserved.
 *
 * $Id: Clansy.debug.cpp,v 1.5 2010/08/07 05:50:10 nakatamaho Exp $
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
#include <mplapack.h>
#include <mplapack_compare_debug.h>

#include <blas.h>
#include <lapack.h>

#if defined VERBOSE_TEST
#include <iostream>
#endif

#define MIN_N 0
#define MAX_N 30
#define MAX_LDA 32
#define MAX_ITER 2

REAL_REF maxdiff = 0.0;

void Clansy_test2(const char *norm, const char *uplo) {
    int errorflag = FALSE;
    int j = 0;
    REAL_REF zlansy_ret;
    REAL Clansy_ret;

    for (int n = MIN_N; n < MAX_N; n++) {
        for (int lda = max(n, 1); lda < MAX_LDA; lda++) {
#if defined VERBOSE_TEST
            printf("n:%d lda %d, uplo %s, norm %s\n", n, lda, uplo, norm);
#endif
            COMPLEX_REF *A_ref = new COMPLEX_REF[matlen(lda, n)];
            REAL_REF *work_ref = new REAL_REF[max(1, n)];
            COMPLEX *A = new COMPLEX[matlen(lda, n)];
            REAL *work = new REAL[max(1, n)];
            j = 0;
            while (j < MAX_ITER) {
                set_random_vector(A_ref, A, matlen(lda, n));
#if defined ___MPLAPACK_BUILD_WITH_MPFR___
                zlansy_ret = zlansy_f77(norm, uplo, &n, A_ref, &lda, work_ref);
#else
                zlansy_ret = Clansy(norm, uplo, n, A_ref, lda, work_ref);
#endif
                Clansy_ret = Clansy(norm, uplo, n, A, lda, work);

                REAL_REF diff = abs(zlansy_ret - Clansy_ret);

                if (diff > EPSILON) {
                    printf("n:%d lda %d, uplo %s, norm %s\n", n, lda, uplo, norm);
                    printf("error: ");
                    printnum(diff);
                    printf("\n");
                    errorflag = TRUE;
                }
                if (maxdiff < diff)
                    maxdiff = diff;
#if defined VERBOSE_TEST
                printf("max error: ");
                printnum(maxdiff);
                printf("\n");
#endif
                j++;
            }
            delete[] A;
            delete[] A_ref;
            delete[] work;
            delete[] work_ref;
        }
        if (errorflag == TRUE) {
            printf("*** Testing Clansy failed ***\n");
            exit(1);
        }
    }
}

void Clansy_test(void) {
    Clansy_test2("M", "U");
    Clansy_test2("m", "U");
    Clansy_test2("1", "U");
    Clansy_test2("O", "U");
    Clansy_test2("o", "U");
    Clansy_test2("I", "U");
    Clansy_test2("i", "U");
    Clansy_test2("F", "U");
    Clansy_test2("f", "U");
    Clansy_test2("E", "U");
    Clansy_test2("e", "U");

    Clansy_test2("M", "L");
    Clansy_test2("m", "L");
    Clansy_test2("1", "L");
    Clansy_test2("O", "L");
    Clansy_test2("o", "L");
    Clansy_test2("I", "L");
    Clansy_test2("i", "L");
    Clansy_test2("F", "L");
    Clansy_test2("f", "L");
    Clansy_test2("E", "L");
    Clansy_test2("e", "L");
}

int main(int argc, char *argv[]) {
    printf("*** Testing Clansy start ***\n");
    Clansy_test();
    printf("*** Testing Clansy successful ***\n");
    return (0);
}
