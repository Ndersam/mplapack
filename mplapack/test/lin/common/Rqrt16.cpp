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

void Rqrt16(const char *trans, INTEGER const m, INTEGER const n, INTEGER const nrhs, REAL *a, INTEGER const lda, REAL *x, INTEGER const ldx, REAL *b, INTEGER const ldb, REAL *rwork, REAL &resid) {
    //
    //     Quick exit if M = 0 or N = 0 or NRHS = 0
    //
    const REAL zero = 0.0;
    if (m <= 0 || n <= 0 || nrhs == 0) {
        resid = zero;
        return;
    }
    //
    REAL anorm = 0.0;
    INTEGER n1 = 0;
    INTEGER n2 = 0;
    if (Mlsame(trans, "T") || Mlsame(trans, "C")) {
        anorm = Rlange("I", m, n, a, lda, rwork);
        n1 = n;
        n2 = m;
    } else {
        anorm = Rlange("1", m, n, a, lda, rwork);
        n1 = m;
        n2 = n;
    }
    //
    REAL eps = Rlamch("Epsilon");
    //
    //     Compute  B - A*X  (or  B - A'*X ) and store in B.
    //
    const REAL one = 1.0;
    Rgemm(trans, "No transpose", n1, nrhs, n2, -one, a, lda, x, ldx, one, b, ldb);
    //
    //     Compute the maximum over the number of right hand sides of
    //        norm(B - A*X) / ( max(m,n) * norm(A) * norm(X) * EPS ) .
    //
    resid = zero;
    INTEGER j = 0;
    REAL bnorm = 0.0;
    REAL xnorm = 0.0;
    for (j = 1; j <= nrhs; j = j + 1) {
        bnorm = Rasum(n1, &b[(j - 1) * ldb], 1);
        xnorm = Rasum(n2, &x[(j - 1) * ldx], 1);
        if (anorm == zero && bnorm == zero) {
            resid = zero;
        } else if (anorm <= zero || xnorm <= zero) {
            resid = one / eps;
        } else {
            resid = max(resid, REAL(((bnorm / anorm) / xnorm) / (castREAL(max(m, n)) * eps)));
        }
    }
    //
    //     End of Rqrt16
    //
}
