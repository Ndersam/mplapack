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
#include <mplapack_eig.h>

#include <mplapack_debug.h>

void Rstt21(INTEGER const n, INTEGER const kband, REAL *ad, REAL *ae, REAL *sd, REAL *se, REAL *u, INTEGER const ldu, REAL *work, REAL *result) {
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
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     1)      Constants
    //
    const REAL zero = 0.0;
    result[1 - 1] = zero;
    result[2 - 1] = zero;
    if (n <= 0) {
        return;
    }
    //
    REAL unfl = Rlamch("Safe minimum");
    REAL ulp = Rlamch("Precision");
    //
    //     Do Test 1
    //
    //     Copy A & Compute its 1-Norm:
    //
    Rlaset("Full", n, n, zero, zero, work, n);
    //
    REAL anorm = zero;
    REAL temp1 = zero;
    //
    INTEGER j = 0;
    REAL temp2 = 0.0;
    for (j = 1; j <= n - 1; j = j + 1) {
        work[((n + 1) * (j - 1) + 1) - 1] = ad[j - 1];
        work[((n + 1) * (j - 1) + 2) - 1] = ae[j - 1];
        temp2 = abs(ae[j - 1]);
        anorm = max(anorm, REAL(abs(ad[j - 1]) + temp1 + temp2));
        temp1 = temp2;
    }
    //
    work[n * n - 1] = ad[n - 1];
    anorm = max({anorm, REAL(abs(ad[n - 1]) + temp1), unfl});
    //
    //     Norm of A - USU'
    //
    for (j = 1; j <= n; j = j + 1) {
        Rsyr("L", n, -sd[j - 1], &u[(j - 1) * ldu], 1, work, n);
    }
    //
    if (n > 1 && kband == 1) {
        for (j = 1; j <= n - 1; j = j + 1) {
            Rsyr2("L", n, -se[j - 1], &u[(j - 1) * ldu], 1, &u[((j + 1) - 1) * ldu], 1, work, n);
        }
    }
    //
    REAL wnorm = Rlansy("1", "L", n, work, n, &work[(n * n + 1) - 1]);
    //
    const REAL one = 1.0;
    if (anorm > wnorm) {
        result[1 - 1] = (wnorm / anorm) / (n * ulp);
    } else {
        if (anorm < one) {
            result[1 - 1] = (min(wnorm, REAL(castREAL(n) * anorm)) / anorm) / (castREAL(n) * ulp);
        } else {
            result[1 - 1] = min(REAL(wnorm / anorm), castREAL(n)) / (castREAL(n) * ulp);
        }
    }
    //
    //     Do Test 2
    //
    //     Compute  UU' - I
    //
    Rgemm("N", "C", n, n, n, one, u, ldu, u, ldu, zero, work, n);
    //
    for (j = 1; j <= n; j = j + 1) {
        work[((n + 1) * (j - 1) + 1) - 1] = work[((n + 1) * (j - 1) + 1) - 1] - one;
    }
    //
    result[2 - 1] = min(castREAL(n), Rlange("1", n, n, work, n, &work[(n * n + 1) - 1])) / (n * ulp);
    //
    //     End of Rstt21
    //
}
