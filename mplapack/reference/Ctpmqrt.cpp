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

void Ctpmqrt(const char *side, const char *trans, INTEGER const m, INTEGER const n, INTEGER const k, INTEGER const l, INTEGER const nb, COMPLEX *v, INTEGER const ldv, COMPLEX *t, INTEGER const ldt, COMPLEX *a, INTEGER const lda, COMPLEX *b, INTEGER const ldb, COMPLEX *work, INTEGER &info) {
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
    //     .. Test the input arguments ..
    //
    info = 0;
    bool left = Mlsame(side, "L");
    bool right = Mlsame(side, "R");
    bool tran = Mlsame(trans, "C");
    bool notran = Mlsame(trans, "N");
    //
    INTEGER ldvq = 0;
    INTEGER ldaq = 0;
    if (left) {
        ldvq = max((INTEGER)1, m);
        ldaq = max((INTEGER)1, k);
    } else if (right) {
        ldvq = max((INTEGER)1, n);
        ldaq = max((INTEGER)1, m);
    }
    if (!left && !right) {
        info = -1;
    } else if (!tran && !notran) {
        info = -2;
    } else if (m < 0) {
        info = -3;
    } else if (n < 0) {
        info = -4;
    } else if (k < 0) {
        info = -5;
    } else if (l < 0 || l > k) {
        info = -6;
    } else if (nb < 1 || (nb > k && k > 0)) {
        info = -7;
    } else if (ldv < ldvq) {
        info = -9;
    } else if (ldt < nb) {
        info = -11;
    } else if (lda < ldaq) {
        info = -13;
    } else if (ldb < max((INTEGER)1, m)) {
        info = -15;
    }
    //
    if (info != 0) {
        Mxerbla("Ctpmqrt", -info);
        return;
    }
    //
    //     .. Quick return if possible ..
    //
    if (m == 0 || n == 0 || k == 0) {
        return;
    }
    //
    INTEGER i = 0;
    INTEGER ib = 0;
    INTEGER mb = 0;
    INTEGER lb = 0;
    INTEGER kf = 0;
    if (left && tran) {
        //
        for (i = 1; i <= k; i = i + nb) {
            ib = min(nb, k - i + 1);
            mb = min(m - l + i + ib - 1, m);
            if (i >= l) {
                lb = 0;
            } else {
                lb = mb - m + l - i + 1;
            }
            Ctprfb("L", "C", "F", "C", mb, n, ib, lb, &v[(i - 1) * ldv], ldv, &t[(i - 1) * ldt], ldt, &a[(i - 1)], lda, b, ldb, work, ib);
        }
        //
    } else if (right && notran) {
        //
        for (i = 1; i <= k; i = i + nb) {
            ib = min(nb, k - i + 1);
            mb = min(n - l + i + ib - 1, n);
            if (i >= l) {
                lb = 0;
            } else {
                lb = mb - n + l - i + 1;
            }
            Ctprfb("R", "N", "F", "C", m, mb, ib, lb, &v[(i - 1) * ldv], ldv, &t[(i - 1) * ldt], ldt, &a[(i - 1) * lda], lda, b, ldb, work, m);
        }
        //
    } else if (left && notran) {
        //
        kf = ((k - 1) / nb) * nb + 1;
        for (i = kf; i >= 1; i = i - nb) {
            ib = min(nb, k - i + 1);
            mb = min(m - l + i + ib - 1, m);
            if (i >= l) {
                lb = 0;
            } else {
                lb = mb - m + l - i + 1;
            }
            Ctprfb("L", "N", "F", "C", mb, n, ib, lb, &v[(i - 1) * ldv], ldv, &t[(i - 1) * ldt], ldt, &a[(i - 1)], lda, b, ldb, work, ib);
        }
        //
    } else if (right && tran) {
        //
        kf = ((k - 1) / nb) * nb + 1;
        for (i = kf; i >= 1; i = i - nb) {
            ib = min(nb, k - i + 1);
            mb = min(n - l + i + ib - 1, n);
            if (i >= l) {
                lb = 0;
            } else {
                lb = mb - n + l - i + 1;
            }
            Ctprfb("R", "C", "F", "C", m, mb, ib, lb, &v[(i - 1) * ldv], ldv, &t[(i - 1) * ldt], ldt, &a[(i - 1) * lda], lda, b, ldb, work, m);
        }
        //
    }
    //
    //     End of Ctpmqrt
    //
}
