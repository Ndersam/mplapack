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

inline REAL abs1(COMPLEX zdum) { return abs(zdum.real()) + abs(zdum.imag()); }

void Cpbt01(const char *uplo, INTEGER const n, INTEGER const kd, COMPLEX *a, INTEGER const lda, COMPLEX *afac, INTEGER const ldafac, REAL *rwork, REAL &resid) {
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
    //     Quick exit if N = 0.
    //
    const REAL zero = 0.0;
    if (n <= 0) {
        resid = zero;
        return;
    }
    //
    //     Exit with RESID = 1/EPS if ANORM = 0.
    //
    REAL eps = Rlamch("Epsilon");
    REAL anorm = Clanhb("1", uplo, n, kd, a, lda, rwork);
    const REAL one = 1.0;
    if (anorm <= zero) {
        resid = one / eps;
        return;
    }
    //
    //     Check the imaginary parts of the diagonal elements and return with
    //     an error code if any are nonzero.
    //
    INTEGER j = 0;
    if (Mlsame(uplo, "U")) {
        for (j = 1; j <= n; j = j + 1) {
            if (afac[((kd + 1) - 1) + (j - 1) * ldafac].imag() != zero) {
                resid = one / eps;
                return;
            }
        }
    } else {
        for (j = 1; j <= n; j = j + 1) {
            if (afac[(j - 1) * ldafac].imag() != zero) {
                resid = one / eps;
                return;
            }
        }
    }
    //
    //     Compute the product U'*U, overwriting U.
    //
    INTEGER k = 0;
    INTEGER kc = 0;
    INTEGER klen = 0;
    REAL akk = 0.0;
    if (Mlsame(uplo, "U")) {
        for (k = n; k >= 1; k = k - 1) {
            kc = max((INTEGER)1, kd + 2 - k);
            klen = kd + 1 - kc;
            //
            //           Compute the (K,K) element of the result.
            //
            akk = Cdotc(klen + 1, &afac[(kc - 1) + (k - 1) * ldafac], 1, &afac[(kc - 1) + (k - 1) * ldafac], 1).real();
            afac[((kd + 1) - 1) + (k - 1) * ldafac] = akk;
            //
            //           Compute the rest of column K.
            //
            if (klen > 0) {
                Ctrmv("Upper", "Conjugate", "Non-unit", klen, &afac[((kd + 1) - 1) + ((k - klen) - 1) * ldafac], ldafac - 1, &afac[(kc - 1) + (k - 1) * ldafac], 1);
            }
            //
        }
        //
        //     UPLO = 'L':  Compute the product L*L', overwriting L.
        //
    } else {
        for (k = n; k >= 1; k = k - 1) {
            klen = min(kd, n - k);
            //
            //           Add a multiple of column K of the factor L to each of
            //           columns K+1 through N.
            //
            if (klen > 0) {
                Cher("Lower", klen, one, &afac[(2 - 1) + (k - 1) * ldafac], 1, &afac[((k + 1) - 1) * ldafac], ldafac - 1);
            }
            //
            //           Scale column K by the diagonal element.
            //
            akk = afac[(k - 1) * ldafac].real();
            CRscal(klen + 1, akk, &afac[(k - 1) * ldafac], 1);
            //
        }
    }
    //
    //     Compute the difference  L*L' - A  or  U'*U - A.
    //
    INTEGER mu = 0;
    INTEGER i = 0;
    INTEGER ml = 0;
    if (Mlsame(uplo, "U")) {
        for (j = 1; j <= n; j = j + 1) {
            mu = max((INTEGER)1, kd + 2 - j);
            for (i = mu; i <= kd + 1; i = i + 1) {
                afac[(i - 1) + (j - 1) * ldafac] = afac[(i - 1) + (j - 1) * ldafac] - a[(i - 1) + (j - 1) * lda];
            }
        }
    } else {
        for (j = 1; j <= n; j = j + 1) {
            ml = min(kd + 1, n - j + 1);
            for (i = 1; i <= ml; i = i + 1) {
                afac[(i - 1) + (j - 1) * ldafac] = afac[(i - 1) + (j - 1) * ldafac] - a[(i - 1) + (j - 1) * lda];
            }
        }
    }
    //
    //     Compute norm( L*L' - A ) / ( N * norm(A) * EPS )
    //
    resid = Clanhb("1", uplo, n, kd, afac, ldafac, rwork);
    //
    resid = ((resid / castREAL(n)) / anorm) / eps;
    //
    //     End of Cpbt01
    //
}
