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

void Rptrfs(INTEGER const n, INTEGER const nrhs, REAL *d, REAL *e, REAL *df, REAL *ef, REAL *b, INTEGER const ldb, REAL *x, INTEGER const ldx, REAL *ferr, REAL *berr, REAL *work, INTEGER &info) {
    INTEGER j = 0;
    const REAL zero = 0.0;
    INTEGER nz = 0;
    REAL eps = 0.0;
    REAL safmin = 0.0;
    REAL safe1 = 0.0;
    REAL safe2 = 0.0;
    INTEGER count = 0;
    const REAL three = 3.0e+0;
    REAL lstres = 0.0;
    REAL bi = 0.0;
    REAL dx = 0.0;
    REAL ex = 0.0;
    INTEGER i = 0;
    REAL cx = 0.0;
    REAL s = 0.0;
    const REAL two = 2.0e+0;
    const INTEGER itmax = 5;
    const REAL one = 1.0;
    INTEGER ix = 0;
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
    //     .. External Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input parameters.
    //
    info = 0;
    if (n < 0) {
        info = -1;
    } else if (nrhs < 0) {
        info = -2;
    } else if (ldb < max((INTEGER)1, n)) {
        info = -8;
    } else if (ldx < max((INTEGER)1, n)) {
        info = -10;
    }
    if (info != 0) {
        Mxerbla("Rptrfs", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0 || nrhs == 0) {
        for (j = 1; j <= nrhs; j = j + 1) {
            ferr[j - 1] = zero;
            berr[j - 1] = zero;
        }
        return;
    }
    //
    //     NZ = maximum number of nonzero elements in each row of A, plus 1
    //
    nz = 4;
    eps = Rlamch("Epsilon");
    safmin = Rlamch("Safe minimum");
    safe1 = nz * safmin;
    safe2 = safe1 / eps;
    //
    //     Do for each right hand side
    //
    for (j = 1; j <= nrhs; j = j + 1) {
        //
        count = 1;
        lstres = three;
    statement_20:
        //
        //        Loop until stopping criterion is satisfied.
        //
        //        Compute residual R = B - A * X.  Also compute
        //        abs(A)*abs(x) + abs(b) for use in the backward error bound.
        //
        if (n == 1) {
            bi = b[(j - 1) * ldb];
            dx = d[1 - 1] * x[(j - 1) * ldx];
            work[(n + 1) - 1] = bi - dx;
            work[1 - 1] = abs(bi) + abs(dx);
        } else {
            bi = b[(j - 1) * ldb];
            dx = d[1 - 1] * x[(j - 1) * ldx];
            ex = e[1 - 1] * x[(2 - 1) + (j - 1) * ldx];
            work[(n + 1) - 1] = bi - dx - ex;
            work[1 - 1] = abs(bi) + abs(dx) + abs(ex);
            for (i = 2; i <= n - 1; i = i + 1) {
                bi = b[(i - 1) + (j - 1) * ldb];
                cx = e[(i - 1) - 1] * x[((i - 1) - 1) + (j - 1) * ldx];
                dx = d[i - 1] * x[(i - 1) + (j - 1) * ldx];
                ex = e[i - 1] * x[((i + 1) - 1) + (j - 1) * ldx];
                work[(n + i) - 1] = bi - cx - dx - ex;
                work[i - 1] = abs(bi) + abs(cx) + abs(dx) + abs(ex);
            }
            bi = b[(n - 1) + (j - 1) * ldb];
            cx = e[(n - 1) - 1] * x[((n - 1) - 1) + (j - 1) * ldx];
            dx = d[n - 1] * x[(n - 1) + (j - 1) * ldx];
            work[(n + n) - 1] = bi - cx - dx;
            work[n - 1] = abs(bi) + abs(cx) + abs(dx);
        }
        //
        //        Compute componentwise relative backward error from formula
        //
        //        max(i) ( abs(R(i)) / ( abs(A)*abs(X) + abs(B) )(i) )
        //
        //        where abs(Z) is the componentwise absolute value of the matrix
        //        or vector Z.  If the i-th component of the denominator is less
        //        than SAFE2, then SAFE1 is added to the i-th components of the
        //        numerator and denominator before dividing.
        //
        s = zero;
        for (i = 1; i <= n; i = i + 1) {
            if (work[i - 1] > safe2) {
                s = max(s, REAL(abs(work[(n + i) - 1]) / work[i - 1]));
            } else {
                s = max(s, REAL((abs(work[(n + i) - 1]) + safe1) / (work[i - 1] + safe1)));
            }
        }
        berr[j - 1] = s;
        //
        //        Test stopping criterion. Continue iterating if
        //           1) The residual BERR(J) is larger than machine epsilon, and
        //           2) BERR(J) decreased by at least a factor of 2 during the
        //              last iteration, and
        //           3) At most ITMAX iterations tried.
        //
        if (berr[j - 1] > eps && two * berr[j - 1] <= lstres && count <= itmax) {
            //
            //           Update solution and try again.
            //
            Rpttrs(n, 1, df, ef, &work[(n + 1) - 1], n, info);
            Raxpy(n, one, &work[(n + 1) - 1], 1, &x[(j - 1) * ldx], 1);
            lstres = berr[j - 1];
            count++;
            goto statement_20;
        }
        //
        //        Bound error from formula
        //
        //        norm(X - XTRUE) / norm(X) .le. FERR =
        //        norm( abs(inv(A))*
        //           ( abs(R) + NZ*EPS*( abs(A)*abs(X)+abs(B) ))) / norm(X)
        //
        //        where
        //          norm(Z) is the magnitude of the largest component of Z
        //          inv(A) is the inverse of A
        //          abs(Z) is the componentwise absolute value of the matrix or
        //             vector Z
        //          NZ is the maximum number of nonzeros in any row of A, plus 1
        //          EPS is machine epsilon
        //
        //        The i-th component of abs(R)+NZ*EPS*(abs(A)*abs(X)+abs(B))
        //        is incremented by SAFE1 if the i-th component of
        //        abs(A)*abs(X) + abs(B) is less than SAFE2.
        //
        for (i = 1; i <= n; i = i + 1) {
            if (work[i - 1] > safe2) {
                work[i - 1] = abs(work[(n + i) - 1]) + nz * eps * work[i - 1];
            } else {
                work[i - 1] = abs(work[(n + i) - 1]) + nz * eps * work[i - 1] + safe1;
            }
        }
        ix = iRamax(n, work, 1);
        ferr[j - 1] = work[ix - 1];
        //
        //        Estimate the norm of inv(A).
        //
        //        Solve M(A) * x = e, where M(A) = (m(i,j)) is given by
        //
        //           m(i,j) =  abs(A(i,j)), i = j,
        //           m(i,j) = -abs(A(i,j)), i .ne. j,
        //
        //        and e = [ 1, 1, ..., 1 ]**T.  Note M(A) = M(L)*D*M(L)**T.
        //
        //        Solve M(L) * x = e.
        //
        work[1 - 1] = one;
        for (i = 2; i <= n; i = i + 1) {
            work[i - 1] = one + work[(i - 1) - 1] * abs(ef[(i - 1) - 1]);
        }
        //
        //        Solve D * M(L)**T * x = b.
        //
        work[n - 1] = work[n - 1] / df[n - 1];
        for (i = n - 1; i >= 1; i = i - 1) {
            work[i - 1] = work[i - 1] / df[i - 1] + work[(i + 1) - 1] * abs(ef[i - 1]);
        }
        //
        //        Compute norm(inv(A)) = max(x(i)), 1<=i<=n.
        //
        ix = iRamax(n, work, 1);
        ferr[j - 1] = ferr[j - 1] * abs(work[ix - 1]);
        //
        //        Normalize error.
        //
        lstres = zero;
        for (i = 1; i <= n; i = i + 1) {
            lstres = max(lstres, REAL(abs(x[(i - 1) + (j - 1) * ldx])));
        }
        if (lstres != zero) {
            ferr[j - 1] = ferr[j - 1] / lstres;
        }
        //
    }
    //
    //     End of Rptrfs
    //
}
