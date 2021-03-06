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

REAL Rla_gbrpvgrw(INTEGER const n, INTEGER const kl, INTEGER const ku, INTEGER const ncols, REAL *ab, INTEGER const ldab, REAL *afb, INTEGER const ldafb) {
    REAL return_value = 0.0;
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
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    REAL rpvgrw = 1.0;
    //
    INTEGER kd = ku + 1;
    INTEGER j = 0;
    REAL amax = 0.0;
    REAL umax = 0.0;
    INTEGER i = 0;
    for (j = 1; j <= ncols; j = j + 1) {
        amax = 0.0;
        umax = 0.0;
        for (i = max(j - ku, (INTEGER)1); i <= min(j + kl, n); i = i + 1) {
            amax = max(REAL(abs(ab[((kd + i - j) - 1) + (j - 1) * ldab])), amax);
        }
        for (i = max(j - ku, (INTEGER)1); i <= j; i = i + 1) {
            umax = max(REAL(abs(afb[((kd + i - j) - 1) + (j - 1) * ldafb])), umax);
        }
        if (umax != 0.0) {
            rpvgrw = min(REAL(amax / umax), rpvgrw);
        }
    }
    return_value = rpvgrw;
    return return_value;
}
