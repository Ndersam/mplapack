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
#include <fem.hpp> // Fortran EMulation library of fable module
using namespace fem::major_types;
using fem::common;
#include <mplapack_lin.h>
#include <mplapack.h>

void Rget01(INTEGER const m, INTEGER const n, REAL *a, INTEGER const lda, REAL *afac, INTEGER const ldafac, INTEGER *ipiv, REAL *rwork, REAL &resid) {
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
    //     Quick exit if M = 0 or N = 0.
    //
    const REAL zero = 0.0;
    if (m <= 0 || n <= 0) {
        resid = zero;
        return;
    }
    //
    //     Determine EPS and the norm of A.
    //
    REAL eps = Rlamch("Epsilon");
    REAL anorm = Rlange("1", m, n, a, lda, rwork);
    //
    //     Compute the product L*U and overwrite AFAC with the result.
    //     A column at a time of the product is obtained, starting with
    //     column N.
    //
    INTEGER k = 0;
    REAL t = 0.0;
    const REAL one = 1.0;
    for (k = n; k >= 1; k = k - 1) {
        if (k > m) {
            Rtrmv("Lower", "No transpose", "Unit", m, afac, ldafac, &afac[(k - 1) * ldafac], 1);
        } else {
            //
            //           Compute elements (K+1:M,K)
            //
            t = afac[(k - 1) + (k - 1) * ldafac];
            if (k + 1 <= m) {
                Rscal(m - k, t, &afac[((k + 1) - 1) + (k - 1) * ldafac], 1);
                Rgemv("No transpose", m - k, k - 1, one, &afac[((k + 1) - 1)], ldafac, &afac[(k - 1) * ldafac], 1, one, &afac[((k + 1) - 1) + (k - 1) * ldafac], 1);
            }
            //
            //           Compute the (K,K) element
            //
            afac[(k - 1) + (k - 1) * ldafac] = t + Rdot(k - 1, &afac[(k - 1)], ldafac, &afac[(k - 1) * ldafac], 1);
            //
            //           Compute elements (1:K-1,K)
            //
            Rtrmv("Lower", "No transpose", "Unit", k - 1, afac, ldafac, &afac[(k - 1) * ldafac], 1);
        }
    }
    Rlaswp(n, afac, ldafac, 1, min(m, n), ipiv, -1);
    //
    //     Compute the difference  L*U - A  and store in AFAC.
    //
    INTEGER j = 0;
    INTEGER i = 0;
    for (j = 1; j <= n; j = j + 1) {
        for (i = 1; i <= m; i = i + 1) {
            afac[(i - 1) + (j - 1) * ldafac] = afac[(i - 1) + (j - 1) * ldafac] - a[(i - 1) + (j - 1) * lda];
        }
    }
    //
    //     Compute norm( L*U - A ) / ( N * norm(A) * EPS )
    //
    resid = Rlange("1", m, n, afac, ldafac, rwork);
    //
    if (anorm <= zero) {
        if (resid != zero) {
            resid = one / eps;
        }
    } else {
        resid = ((resid / castREAL(n)) / anorm) / eps;
    }
    //
    //     End of Rget01
    //
}
