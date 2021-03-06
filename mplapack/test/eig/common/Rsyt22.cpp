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

void Rsyt22(INTEGER const itype, const char *uplo, INTEGER const n, INTEGER const m, INTEGER const kband, REAL *a, INTEGER const lda, REAL *d, REAL *e, REAL *u, INTEGER const ldu, REAL * /* v */, INTEGER const ldv, REAL * /* tau */, REAL *work, REAL *result) {
    //
    const REAL zero = 0.0;
    result[1 - 1] = zero;
    result[2 - 1] = zero;
    if (n <= 0 || m <= 0) {
        return;
    }
    //
    REAL unfl = Rlamch("Safe minimum");
    REAL ulp = Rlamch("Precision");
    //
    //     Do Test 1
    //
    //     Norm of A:
    //
    REAL anorm = max(Rlansy("1", uplo, n, a, lda, work), unfl);
    //
    //     Compute error matrix:
    //
    //     ITYPE=1: error = U**T A U - S
    //
    const REAL one = 1.0;
    Rsymm("L", uplo, n, m, one, a, lda, u, ldu, zero, work, n);
    INTEGER nn = n * n;
    INTEGER nnp1 = nn + 1;
    Rgemm("T", "N", m, m, n, one, u, ldu, work, n, zero, &work[nnp1 - 1], n);
    INTEGER j = 0;
    INTEGER jj = 0;
    for (j = 1; j <= m; j = j + 1) {
        jj = nn + (j - 1) * n + j;
        work[jj - 1] = work[jj - 1] - d[j - 1];
    }
    INTEGER jj1 = 0;
    INTEGER jj2 = 0;
    if (kband == 1 && n > 1) {
        for (j = 2; j <= m; j = j + 1) {
            jj1 = nn + (j - 1) * n + j - 1;
            jj2 = nn + (j - 2) * n + j;
            work[jj1 - 1] = work[jj1 - 1] - e[(j - 1) - 1];
            work[jj2 - 1] = work[jj2 - 1] - e[(j - 1) - 1];
        }
    }
    REAL wnorm = Rlansy("1", uplo, m, &work[nnp1 - 1], n, &work[1 - 1]);
    //
    if (anorm > wnorm) {
        result[1 - 1] = (wnorm / anorm) / (castREAL(m) * ulp);
    } else {
        if (anorm < one) {
            result[1 - 1] = (min(wnorm, REAL(castREAL(m) * anorm))) / anorm / (castREAL(m) * ulp);
        } else {
            result[1 - 1] = min(REAL(wnorm / anorm), castREAL(m)) / (castREAL(m) * ulp);
        }
    }
    //
    //     Do Test 2
    //
    //     Compute  U**T U - I
    //
    if (itype == 1) {
        Rort01("Columns", n, m, u, ldu, work, 2 * n * n, result[2 - 1]);
    }
    //
    //     End of Rsyt22
    //
}
