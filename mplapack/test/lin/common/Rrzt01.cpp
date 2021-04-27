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

REAL Rrzt01(INTEGER const m, INTEGER const n, REAL *a, REAL *af, INTEGER const lda, REAL *tau, REAL *work, INTEGER const lwork) {
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
    //
    if (lwork < m * n + m) {
        Mxerbla("Rrzt01", 8);
        return return_value;
    }
    //
    //     Quick return if possible
    //
    if (m <= 0 || n <= 0) {
        return return_value;
    }
    //
    arr_1d<1, REAL> rwork(fill0);
    REAL norma = Rlange("One-norm", m, n, a, lda, rwork);
    //
    //     Copy upper triangle R
    //
    Rlaset("Full", m, n, zero, zero, work, m);
    INTEGER j = 0;
    INTEGER i = 0;
    for (j = 1; j <= m; j = j + 1) {
        for (i = 1; i <= j; i = i + 1) {
            work[((j - 1) * m + i) - 1] = af[(i - 1) + (j - 1) * ldaf];
        }
    }
    //
    //     R = R * P(1) * ... *P(m)
    //
    INTEGER info = 0;
    Rormrz("Right", "No tranpose", m, n, m, n - m, af, lda, tau, work, m, &work[(m * n + 1) - 1], lwork - m * n, info);
    //
    //     R = R - A
    //
    const REAL one = 1.0;
    for (i = 1; i <= n; i = i + 1) {
        Raxpy(m, -one, &a[(i - 1) * lda], 1, &work[((i - 1) * m + 1) - 1], 1);
    }
    //
    return_value = Rlange("One-norm", m, n, work, m, rwork);
    //
    return_value = return_value / (Rlamch("Epsilon") * (max(m, n)).real());
    if (norma != zero) {
        return_value = return_value / norma;
    }
    //
    return return_value;
    //
    //     End of Rrzt01
    //
}
