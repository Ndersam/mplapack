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

void Rlatrz(INTEGER const m, INTEGER const n, INTEGER const l, REAL *a, INTEGER const lda, REAL *tau, REAL *work) {
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
    //     .. Parameters ..
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input arguments
    //
    //     Quick return if possible
    //
    INTEGER i = 0;
    const REAL zero = 0.0;
    if (m == 0) {
        return;
    } else if (m == n) {
        for (i = 1; i <= n; i = i + 1) {
            tau[i - 1] = zero;
        }
        return;
    }
    //
    for (i = m; i >= 1; i = i - 1) {
        //
        //        Generate elementary reflector H(i) to annihilate
        //        [ A(i,i) A(i,n-l+1:n) ]
        //
        Rlarfg(l + 1, a[(i - 1) + (i - 1) * lda], &a[(i - 1) + ((n - l + 1) - 1) * lda], lda, tau[i - 1]);
        //
        //        Apply H(i) to A(1:i-1,i:n) from the right
        //
        Rlarz("Right", i - 1, n - i + 1, l, &a[(i - 1) + ((n - l + 1) - 1) * lda], lda, tau[i - 1], &a[(i - 1) * lda], lda, work);
        //
    }
    //
    //     End of Rlatrz
    //
}
