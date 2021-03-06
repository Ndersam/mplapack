/*
 * Copyright (c) 2021
 *      Nakata, Maho
 *      All rights reserved.
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

void Chesv_rk(const char *uplo, INTEGER const n, INTEGER const nrhs, COMPLEX *a, INTEGER const lda, COMPLEX *e, INTEGER *ipiv, COMPLEX *b, INTEGER const ldb, COMPLEX *work, INTEGER const lwork, INTEGER &info) {
    //
    //     Test the input parameters.
    //
    info = 0;
    bool lquery = (lwork == -1);
    if (!Mlsame(uplo, "U") && !Mlsame(uplo, "L")) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (nrhs < 0) {
        info = -3;
    } else if (lda < max((INTEGER)1, n)) {
        info = -5;
    } else if (ldb < max((INTEGER)1, n)) {
        info = -9;
    } else if (lwork < 1 && !lquery) {
        info = -11;
    }
    //
    INTEGER lwkopt = 0;
    if (info == 0) {
        if (n == 0) {
            lwkopt = 1;
        } else {
            Chetrf_rk(uplo, n, a, lda, e, ipiv, work, -1, info);
            lwkopt = castINTEGER(work[1 - 1].real());
        }
        work[1 - 1] = castREAL(lwkopt);
    }
    //
    if (info != 0) {
        Mxerbla("Chesv_rk", -info);
        return;
    } else if (lquery) {
        return;
    }
    //
    //     Compute the factorization A = P*U*D*(U**H)*(P**T) or
    //     A = P*U*D*(U**H)*(P**T).
    //
    Chetrf_rk(uplo, n, a, lda, e, ipiv, work, lwork, info);
    //
    if (info == 0) {
        //
        //        Solve the system A*X = B with BLAS3 solver, overwriting B with X.
        //
        Chetrs_3(uplo, n, nrhs, a, lda, e, ipiv, b, ldb, info);
        //
    }
    //
    work[1 - 1] = castREAL(lwkopt);
    //
    //     End of Chesv_rk
    //
}
