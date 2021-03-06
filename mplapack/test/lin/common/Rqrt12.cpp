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

REAL Rqrt12(INTEGER const m, INTEGER const n, REAL *a, INTEGER const lda, REAL *s, REAL *work, INTEGER const lwork) {
    REAL return_value = 0.0;
    //
    const REAL zero = 0.0;
    return_value = zero;
    //
    //     Test that enough workspace is supplied
    //
    if (lwork < max({m * n + 4 * min(m, n) + max(m, n), m * n + 2 * min(m, n) + 4 * n})) {
        Mxerbla("Rqrt12", 7);
        return return_value;
    }
    //
    //     Quick return if possible
    //
    INTEGER mn = min(m, n);
    if (mn <= zero) {
        return return_value;
    }
    //
    REAL nrmsvl = Rnrm2(mn, s, 1);
    //
    //     Copy upper triangle of A into work
    //
    Rlaset("Full", m, n, zero, zero, work, m);
    INTEGER j = 0;
    INTEGER i = 0;
    for (j = 1; j <= n; j = j + 1) {
        for (i = 1; i <= min(j, m); i = i + 1) {
            work[((j - 1) * m + i) - 1] = a[(i - 1) + (j - 1) * lda];
        }
    }
    //
    //     Get machine parameters
    //
    REAL smlnum = Rlamch("S") / Rlamch("P");
    const REAL one = 1.0;
    REAL bignum = one / smlnum;
    //
    //     Scale work if max entry outside range [SMLNUM,BIGNUM]
    //
    REAL dummy[1];
    REAL anrm = Rlange("M", m, n, work, m, dummy);
    INTEGER iscl = 0;
    INTEGER info = 0;
    if (anrm > zero && anrm < smlnum) {
        //
        //        Scale matrix norm up to SMLNUM
        //
        Rlascl("G", 0, 0, anrm, smlnum, m, n, work, m, info);
        iscl = 1;
    } else if (anrm > bignum) {
        //
        //        Scale matrix norm down to BIGNUM
        //
        Rlascl("G", 0, 0, anrm, bignum, m, n, work, m, info);
        iscl = 1;
    }
    //
    if (anrm != zero) {
        //
        //        Compute SVD of work
        //
        Rgebd2(m, n, work, m, &work[(m * n + 1) - 1], &work[(m * n + mn + 1) - 1], &work[(m * n + 2 * mn + 1) - 1], &work[(m * n + 3 * mn + 1) - 1], &work[(m * n + 4 * mn + 1) - 1], info);
        Rbdsqr("Upper", mn, 0, 0, 0, &work[(m * n + 1) - 1], &work[(m * n + mn + 1) - 1], dummy, mn, dummy, 1, dummy, mn, &work[(m * n + 2 * mn + 1) - 1], info);
        //
        if (iscl == 1) {
            if (anrm > bignum) {
                Rlascl("G", 0, 0, bignum, anrm, mn, 1, &work[(m * n + 1) - 1], mn, info);
            }
            if (anrm < smlnum) {
                Rlascl("G", 0, 0, smlnum, anrm, mn, 1, &work[(m * n + 1) - 1], mn, info);
            }
        }
        //
    } else {
        //
        for (i = 1; i <= mn; i = i + 1) {
            work[(m * n + i) - 1] = zero;
        }
    }
    //
    //     Compare s and singular values of work
    //
    Raxpy(mn, -one, s, 1, &work[(m * n + 1) - 1], 1);
    return_value = Rasum(mn, &work[(m * n + 1) - 1], 1) / (Rlamch("Epsilon") * castREAL(max(m, n)));
    if (nrmsvl != zero) {
        return_value = return_value / nrmsvl;
    }
    //
    return return_value;
    //
    //     End of Rqrt12
    //
}
