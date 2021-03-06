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

void icopy(INTEGER const &n, INTEGER *sx, INTEGER const &incx, INTEGER *sy, INTEGER const &incy) {
    INTEGER ix = 0;
    INTEGER iy = 0;
    INTEGER i = 0;
    INTEGER m = 0;
    INTEGER mp1 = 0;
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
    //     .. Local Scalars ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    if (n <= 0) {
        return;
    }
    if (incx == 1 && incy == 1) {
        goto statement_20;
    }
    //
    //     Code for unequal increments or equal increments not equal to 1
    //
    ix = 1;
    iy = 1;
    if (incx < 0) {
        ix = (-n + 1) * incx + 1;
    }
    if (incy < 0) {
        iy = (-n + 1) * incy + 1;
    }
    for (i = 1; i <= n; i = i + 1) {
        sy[iy - 1] = sx[ix - 1];
        ix += incx;
        iy += incy;
    }
    return;
//
//     Code for both increments equal to 1
//
//     Clean-up loop
//
statement_20:
    m = mod(n, 7);
    if (m == 0) {
        goto statement_40;
    }
    for (i = 1; i <= m; i = i + 1) {
        sy[i - 1] = sx[i - 1];
    }
    if (n < 7) {
        return;
    }
statement_40:
    mp1 = m + 1;
    for (i = mp1; i <= n; i = i + 7) {
        sy[i - 1] = sx[i - 1];
        sy[(i + 1) - 1] = sx[(i + 1) - 1];
        sy[(i + 2) - 1] = sx[(i + 2) - 1];
        sy[(i + 3) - 1] = sx[(i + 3) - 1];
        sy[(i + 4) - 1] = sx[(i + 4) - 1];
        sy[(i + 5) - 1] = sx[(i + 5) - 1];
        sy[(i + 6) - 1] = sx[(i + 6) - 1];
    }
    //
    //     End of ICOPY
    //
}
