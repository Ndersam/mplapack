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

#include <fem.hpp> // Fortran EMulation library of fable module
using namespace fem::major_types;
using fem::common;

#include <mplapack_matgen.h>
#include <mplapack_lin.h>

REAL Rqrt14(const char *trans, INTEGER const m, INTEGER const n, INTEGER const nrhs, REAL *a, INTEGER const lda, REAL *x, INTEGER const ldx, REAL *work, INTEGER const lwork) {
    REAL return_value = 0.0;
    //
    //  -- LAPACK test routine --
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
    //     .. Parameters ..
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. Local Arrays ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    const REAL zero = 0.0;
    return_value = zero;
    INTEGER ldwork = 0;
    bool tpsd = false;
    if (Mlsame(trans, "N")) {
        ldwork = m + nrhs;
        tpsd = false;
        if (lwork < (m + nrhs) * (n + 2)) {
            Mxerbla("Rqrt14", 10);
            return return_value;
        } else if (n <= 0 || nrhs <= 0) {
            return return_value;
        }
    } else if (Mlsame(trans, "T")) {
        ldwork = m;
        tpsd = true;
        if (lwork < (n + nrhs) * (m + 2)) {
            Mxerbla("Rqrt14", 10);
            return return_value;
        } else if (m <= 0 || nrhs <= 0) {
            return return_value;
        }
    } else {
        Mxerbla("Rqrt14", 1);
        return return_value;
    }
    //
    //     Copy and scale A
    //
    Rlacpy("All", m, n, a, lda, work, ldwork);
    REAL rwork[1];
    REAL anrm = Rlange("M", m, n, work, ldwork, rwork);
    const REAL one = 1.0;
    INTEGER info = 0;
    if (anrm != zero) {
        Rlascl("G", 0, 0, anrm, one, m, n, work, ldwork, info);
    }
    //
    //     Copy X or X' into the right place and scale it
    //
    REAL xnrm = 0.0;
    REAL err = 0.0;
    INTEGER j = 0;
    INTEGER i = 0;
    if (tpsd) {
        //
        //        Copy X into columns n+1:n+nrhs of work
        //
        Rlacpy("All", m, nrhs, x, ldx, &work[(n * ldwork + 1) - 1], ldwork);
        xnrm = Rlange("M", m, nrhs, &work[(n * ldwork + 1) - 1], ldwork, rwork);
        if (xnrm != zero) {
            Rlascl("G", 0, 0, xnrm, one, m, nrhs, &work[(n * ldwork + 1) - 1], ldwork, info);
        }
        anrm = Rlange("One-norm", m, n + nrhs, work, ldwork, rwork);
        //
        //        Compute QR factorization of X
        //
        Rgeqr2(m, n + nrhs, work, ldwork, &work[(ldwork * (n + nrhs) + 1) - 1], &work[(ldwork * (n + nrhs) + min(m, n + nrhs) + 1) - 1], info);
        //
        //        Compute largest entry in upper triangle of
        //        work(n+1:m,n+1:n+nrhs)
        //
        err = zero;
        for (j = n + 1; j <= n + nrhs; j = j + 1) {
            for (i = n + 1; i <= min(m, j); i = i + 1) {
                err = max(err, REAL(abs(work[(i + (j - 1) * m) - 1])));
            }
        }
        //
    } else {
        //
        //        Copy X' into rows m+1:m+nrhs of work
        //
        for (i = 1; i <= n; i = i + 1) {
            for (j = 1; j <= nrhs; j = j + 1) {
                work[(m + j + (i - 1) * ldwork) - 1] = x[(i - 1) + (j - 1) * ldx];
            }
        }
        //
        xnrm = Rlange("M", nrhs, n, &work[(m + 1) - 1], ldwork, rwork);
        if (xnrm != zero) {
            Rlascl("G", 0, 0, xnrm, one, nrhs, n, &work[(m + 1) - 1], ldwork, info);
        }
        //
        //        Compute LQ factorization of work
        //
        Rgelq2(ldwork, n, work, ldwork, &work[(ldwork * n + 1) - 1], &work[(ldwork * (n + 1) + 1) - 1], info);
        //
        //        Compute largest entry in lower triangle in
        //        work(m+1:m+nrhs,m+1:n)
        //
        err = zero;
        for (j = m + 1; j <= n; j = j + 1) {
            for (i = j; i <= ldwork; i = i + 1) {
                err = max(err, REAL(abs(work[(i + (j - 1) * ldwork) - 1])));
            }
        }
        //
    }
    //
    return_value = err / (castREAL(max({m, n, nrhs})) * Rlamch("Epsilon"));
    //
    return return_value;
    //
    //     End of Rqrt14
    //
}
