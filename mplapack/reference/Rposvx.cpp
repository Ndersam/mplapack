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

void Rposvx(const char *fact, const char *uplo, INTEGER const n, INTEGER const nrhs, REAL *a, INTEGER const lda, REAL *af, INTEGER const ldaf, char *equed, REAL *s, REAL *b, INTEGER const ldb, REAL *x, INTEGER const ldx, REAL &rcond, REAL *ferr, REAL *berr, REAL *work, INTEGER *iwork, INTEGER &info) {
    //
    info = 0;
    bool nofact = Mlsame(fact, "N");
    bool equil = Mlsame(fact, "E");
    bool rcequ = false;
    REAL smlnum = 0.0;
    const REAL one = 1.0;
    REAL bignum = 0.0;
    if (nofact || equil) {
        *equed = 'N';
        rcequ = false;
    } else {
        rcequ = Mlsame(equed, "Y");
        smlnum = Rlamch("Safe minimum");
        bignum = one / smlnum;
    }
    //
    //     Test the input parameters.
    //
    REAL smin = 0.0;
    const REAL zero = 0.0;
    REAL smax = 0.0;
    INTEGER j = 0;
    REAL scond = 0.0;
    if (!nofact && !equil && !Mlsame(fact, "F")) {
        info = -1;
    } else if (!Mlsame(uplo, "U") && !Mlsame(uplo, "L")) {
        info = -2;
    } else if (n < 0) {
        info = -3;
    } else if (nrhs < 0) {
        info = -4;
    } else if (lda < max((INTEGER)1, n)) {
        info = -6;
    } else if (ldaf < max((INTEGER)1, n)) {
        info = -8;
    } else if (Mlsame(fact, "F") && !(rcequ || Mlsame(equed, "N"))) {
        info = -9;
    } else {
        if (rcequ) {
            smin = bignum;
            smax = zero;
            for (j = 1; j <= n; j = j + 1) {
                smin = min(smin, s[j - 1]);
                smax = max(smax, s[j - 1]);
            }
            if (smin <= zero) {
                info = -10;
            } else if (n > 0) {
                scond = max(smin, smlnum) / min(smax, bignum);
            } else {
                scond = one;
            }
        }
        if (info == 0) {
            if (ldb < max((INTEGER)1, n)) {
                info = -12;
            } else if (ldx < max((INTEGER)1, n)) {
                info = -14;
            }
        }
    }
    //
    if (info != 0) {
        Mxerbla("Rposvx", -info);
        return;
    }
    //
    REAL amax = 0.0;
    INTEGER infequ = 0;
    if (equil) {
        //
        //        Compute row and column scalings to equilibrate the matrix A.
        //
        Rpoequ(n, a, lda, s, scond, amax, infequ);
        if (infequ == 0) {
            //
            //           Equilibrate the matrix.
            //
            Rlaqsy(uplo, n, a, lda, s, scond, amax, equed);
            rcequ = Mlsame(equed, "Y");
        }
    }
    //
    //     Scale the right hand side.
    //
    INTEGER i = 0;
    if (rcequ) {
        for (j = 1; j <= nrhs; j = j + 1) {
            for (i = 1; i <= n; i = i + 1) {
                b[(i - 1) + (j - 1) * ldb] = s[i - 1] * b[(i - 1) + (j - 1) * ldb];
            }
        }
    }
    //
    if (nofact || equil) {
        //
        //        Compute the Cholesky factorization A = U**T *U or A = L*L**T.
        //
        Rlacpy(uplo, n, n, a, lda, af, ldaf);
        Rpotrf(uplo, n, af, ldaf, info);
        //
        //        Return if INFO is non-zero.
        //
        if (info > 0) {
            rcond = zero;
            return;
        }
    }
    //
    //     Compute the norm of the matrix A.
    //
    REAL anorm = Rlansy("1", uplo, n, a, lda, work);
    //
    //     Compute the reciprocal of the condition number of A.
    //
    Rpocon(uplo, n, af, ldaf, anorm, rcond, work, iwork, info);
    //
    //     Compute the solution matrix X.
    //
    Rlacpy("Full", n, nrhs, b, ldb, x, ldx);
    Rpotrs(uplo, n, nrhs, af, ldaf, x, ldx, info);
    //
    //     Use iterative refinement to improve the computed solution and
    //     compute error bounds and backward error estimates for it.
    //
    Rporfs(uplo, n, nrhs, a, lda, af, ldaf, b, ldb, x, ldx, ferr, berr, work, iwork, info);
    //
    //     Transform the solution matrix X to a solution of the original
    //     system.
    //
    if (rcequ) {
        for (j = 1; j <= nrhs; j = j + 1) {
            for (i = 1; i <= n; i = i + 1) {
                x[(i - 1) + (j - 1) * ldx] = s[i - 1] * x[(i - 1) + (j - 1) * ldx];
            }
        }
        for (j = 1; j <= nrhs; j = j + 1) {
            ferr[j - 1] = ferr[j - 1] / scond;
        }
    }
    //
    //     Set INFO = N+1 if the matrix is singular to working precision.
    //
    if (rcond < Rlamch("Epsilon")) {
        info = n + 1;
    }
    //
    //     End of Rposvx
    //
}
