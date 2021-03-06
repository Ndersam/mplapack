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

void Cgehd2(INTEGER const n, INTEGER const ilo, INTEGER const ihi, COMPLEX *a, INTEGER const lda, COMPLEX *tau, COMPLEX *work, INTEGER &info) {
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
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input parameters
    //
    info = 0;
    if (n < 0) {
        info = -1;
    } else if (ilo < 1 || ilo > max((INTEGER)1, n)) {
        info = -2;
    } else if (ihi < min(ilo, n) || ihi > n) {
        info = -3;
    } else if (lda < max((INTEGER)1, n)) {
        info = -5;
    }
    if (info != 0) {
        Mxerbla("Cgehd2", -info);
        return;
    }
    //
    INTEGER i = 0;
    COMPLEX alpha = 0.0;
    const COMPLEX one = COMPLEX(1.0, 0.0);
    for (i = ilo; i <= ihi - 1; i = i + 1) {
        //
        //        Compute elementary reflector H(i) to annihilate A(i+2:ihi,i)
        //
        alpha = a[((i + 1) - 1) + (i - 1) * lda];
        Clarfg(ihi - i, alpha, &a[(min(i + 2, n) - 1) + (i - 1) * lda], 1, tau[i - 1]);
        a[((i + 1) - 1) + (i - 1) * lda] = one;
        //
        //        Apply H(i) to A(1:ihi,i+1:ihi) from the right
        //
        Clarf("Right", ihi, ihi - i, &a[((i + 1) - 1) + (i - 1) * lda], 1, tau[i - 1], &a[((i + 1) - 1) * lda], lda, work);
        //
        //        Apply H(i)**H to A(i+1:ihi,i+1:n) from the left
        //
        Clarf("Left", ihi - i, n - i, &a[((i + 1) - 1) + (i - 1) * lda], 1, conj(tau[i - 1]), &a[((i + 1) - 1) + ((i + 1) - 1) * lda], lda, work);
        //
        a[((i + 1) - 1) + (i - 1) * lda] = alpha;
    }
    //
    //     End of Cgehd2
    //
}
