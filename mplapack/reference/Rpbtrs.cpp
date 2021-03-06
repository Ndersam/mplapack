/*
 * Copyright (c) 2008-2021
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

void Rpbtrs(const char *uplo, INTEGER const n, INTEGER const kd, INTEGER const nrhs, REAL *ab, INTEGER const ldab, REAL *b, INTEGER const ldb, INTEGER &info) {
    //
    //  -- LAPACK computational routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
    //     ..
    //     .. Array Arguments ..
    //     ..
    //
    //  =====================================================================
    //
    //     .. Local Scalars ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input parameters.
    //
    info = 0;
    bool upper = Mlsame(uplo, "U");
    if (!upper && !Mlsame(uplo, "L")) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (kd < 0) {
        info = -3;
    } else if (nrhs < 0) {
        info = -4;
    } else if (ldab < kd + 1) {
        info = -6;
    } else if (ldb < max((INTEGER)1, n)) {
        info = -8;
    }
    if (info != 0) {
        Mxerbla("Rpbtrs", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0 || nrhs == 0) {
        return;
    }
    //
    INTEGER j = 0;
    if (upper) {
        //
        //        Solve A*X = B where A = U**T *U.
        //
        for (j = 1; j <= nrhs; j = j + 1) {
            //
            //           Solve U**T *X = B, overwriting B with X.
            //
            Rtbsv("Upper", "Transpose", "Non-unit", n, kd, ab, ldab, &b[(j - 1) * ldb], 1);
            //
            //           Solve U*X = B, overwriting B with X.
            //
            Rtbsv("Upper", "No transpose", "Non-unit", n, kd, ab, ldab, &b[(j - 1) * ldb], 1);
        }
    } else {
        //
        //        Solve A*X = B where A = L*L**T.
        //
        for (j = 1; j <= nrhs; j = j + 1) {
            //
            //           Solve L*X = B, overwriting B with X.
            //
            Rtbsv("Lower", "No transpose", "Non-unit", n, kd, ab, ldab, &b[(j - 1) * ldb], 1);
            //
            //           Solve L**T *X = B, overwriting B with X.
            //
            Rtbsv("Lower", "Transpose", "Non-unit", n, kd, ab, ldab, &b[(j - 1) * ldb], 1);
        }
    }
    //
    //     End of Rpbtrs
    //
}
