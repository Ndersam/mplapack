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

inline REAL abs1(COMPLEX cdum) { return abs(cdum.real()) + abs(cdum.imag()); }

void Chsein(const char *side, const char *eigsrc, const char *initv, bool *select, INTEGER const n, COMPLEX *h, INTEGER const ldh, COMPLEX *w, COMPLEX *vl, INTEGER const ldvl, COMPLEX *vr, INTEGER const ldvr, INTEGER const mm, INTEGER &m, COMPLEX *work, REAL *rwork, INTEGER *ifaill, INTEGER *ifailr, INTEGER &info) {
    COMPLEX cdum = 0.0;
    bool bothv = false;
    bool rightv = false;
    bool leftv = false;
    bool fromqr = false;
    bool noinit = false;
    INTEGER k = 0;
    REAL unfl = 0.0;
    REAL ulp = 0.0;
    REAL smlnum = 0.0;
    INTEGER ldwork = 0;
    INTEGER kl = 0;
    INTEGER kln = 0;
    INTEGER kr = 0;
    INTEGER ks = 0;
    INTEGER i = 0;
    const COMPLEX zero = COMPLEX(0.0, 0.0);
    REAL hnorm = 0.0;
    const REAL rzero = 0.0;
    REAL eps3 = 0.0;
    COMPLEX wk = 0.0;
    INTEGER iinfo = 0;
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
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Statement Functions ..
    //     ..
    //     .. Statement Function definitions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Decode and test the input parameters.
    //
    bothv = Mlsame(side, "B");
    rightv = Mlsame(side, "R") || bothv;
    leftv = Mlsame(side, "L") || bothv;
    //
    fromqr = Mlsame(eigsrc, "Q");
    //
    noinit = Mlsame(initv, "N");
    //
    //     Set M to the number of columns required to store the selected
    //     eigenvectors.
    //
    m = 0;
    for (k = 1; k <= n; k = k + 1) {
        if (select[k - 1]) {
            m++;
        }
    }
    //
    info = 0;
    if (!rightv && !leftv) {
        info = -1;
    } else if (!fromqr && !Mlsame(eigsrc, "N")) {
        info = -2;
    } else if (!noinit && !Mlsame(initv, "U")) {
        info = -3;
    } else if (n < 0) {
        info = -5;
    } else if (ldh < max((INTEGER)1, n)) {
        info = -7;
    } else if (ldvl < 1 || (leftv && ldvl < n)) {
        info = -10;
    } else if (ldvr < 1 || (rightv && ldvr < n)) {
        info = -12;
    } else if (mm < m) {
        info = -13;
    }
    if (info != 0) {
        Mxerbla("Chsein", -info);
        return;
    }
    //
    //     Quick return if possible.
    //
    if (n == 0) {
        return;
    }
    //
    //     Set machine-dependent constants.
    //
    unfl = Rlamch("Safe minimum");
    ulp = Rlamch("Precision");
    smlnum = unfl * (n / ulp);
    //
    ldwork = n;
    //
    kl = 1;
    kln = 0;
    if (fromqr) {
        kr = 0;
    } else {
        kr = n;
    }
    ks = 1;
    //
    for (k = 1; k <= n; k = k + 1) {
        if (select[k - 1]) {
            //
            //           Compute eigenvector(s) corresponding to W(K).
            //
            if (fromqr) {
                //
                //              If affiliation of eigenvalues is known, check whether
                //              the matrix splits.
                //
                //              Determine KL and KR such that 1 <= KL <= K <= KR <= N
                //              and H(KL,KL-1) and H(KR+1,KR) are zero (or KL = 1 or
                //              KR = N).
                //
                //              Then inverse iteration can be performed with the
                //              submatrix H(KL:N,KL:N) for a left eigenvector, and with
                //              the submatrix H(1:KR,1:KR) for a right eigenvector.
                //
                for (i = k; i >= kl + 1; i = i - 1) {
                    if (h[(i - 1) + ((i - 1) - 1) * ldh] == zero) {
                        goto statement_30;
                    }
                }
            statement_30:
                kl = i;
                if (k > kr) {
                    for (i = k; i <= n - 1; i = i + 1) {
                        if (h[((i + 1) - 1) + (i - 1) * ldh] == zero) {
                            goto statement_50;
                        }
                    }
                statement_50:
                    kr = i;
                }
            }
            //
            if (kl != kln) {
                kln = kl;
                //
                //              Compute infinity-norm of submatrix H(KL:KR,KL:KR) if it
                //              has not ben computed before.
                //
                hnorm = Clanhs("I", kr - kl + 1, &h[(kl - 1) + (kl - 1) * ldh], ldh, rwork);
                if (Risnan(hnorm)) {
                    info = -6;
                    return;
                } else if (hnorm > rzero) {
                    eps3 = hnorm * ulp;
                } else {
                    eps3 = smlnum;
                }
            }
            //
            //           Perturb eigenvalue if it is close to any previous
            //           selected eigenvalues affiliated to the submatrix
            //           H(KL:KR,KL:KR). Close roots are modified by EPS3.
            //
            wk = w[k - 1];
        statement_60:
            for (i = k - 1; i >= kl; i = i - 1) {
                if (select[i - 1] && abs1(w[i - 1] - wk) < eps3) {
                    wk += eps3;
                    goto statement_60;
                }
            }
            w[k - 1] = wk;
            //
            if (leftv) {
                //
                //              Compute left eigenvector.
                //
                Claein(false, noinit, n - kl + 1, &h[(kl - 1) + (kl - 1) * ldh], ldh, wk, &vl[(kl - 1) + (ks - 1) * ldvl], work, ldwork, rwork, eps3, smlnum, iinfo);
                if (iinfo > 0) {
                    info++;
                    ifaill[ks - 1] = k;
                } else {
                    ifaill[ks - 1] = 0;
                }
                for (i = 1; i <= kl - 1; i = i + 1) {
                    vl[(i - 1) + (ks - 1) * ldvl] = zero;
                }
            }
            if (rightv) {
                //
                //              Compute right eigenvector.
                //
                Claein(true, noinit, kr, h, ldh, wk, &vr[(ks - 1) * ldvr], work, ldwork, rwork, eps3, smlnum, iinfo);
                if (iinfo > 0) {
                    info++;
                    ifailr[ks - 1] = k;
                } else {
                    ifailr[ks - 1] = 0;
                }
                for (i = kr + 1; i <= n; i = i + 1) {
                    vr[(i - 1) + (ks - 1) * ldvr] = zero;
                }
            }
            ks++;
        }
    }
    //
    //     End of Chsein
    //
}
