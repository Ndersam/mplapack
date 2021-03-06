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

void Cgemqr(const char *side, const char *trans, INTEGER const m, INTEGER const n, INTEGER const k, COMPLEX *a, INTEGER const lda, COMPLEX *t, INTEGER const tsize, COMPLEX *c, INTEGER const ldc, COMPLEX *work, INTEGER const lwork, INTEGER &info) {
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
    // =====================================================================
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
    //     Test the input arguments
    //
    bool lquery = lwork == -1;
    bool notran = Mlsame(trans, "N");
    bool tran = Mlsame(trans, "C");
    bool left = Mlsame(side, "L");
    bool right = Mlsame(side, "R");
    //
    INTEGER mb = castINTEGER(t[2 - 1].real());
    INTEGER nb = castINTEGER(t[3 - 1].real());
    INTEGER lw = 0;
    INTEGER mn = 0;
    if (left) {
        lw = n * nb;
        mn = m;
    } else {
        lw = mb * nb;
        mn = n;
    }
    //
    INTEGER nblcks = 0;
    if ((mb > k) && (mn > k)) {
        if (mod(mn - k, mb - k) == 0) {
            nblcks = (mn - k) / (mb - k);
        } else {
            nblcks = (mn - k) / (mb - k) + 1;
        }
    } else {
        nblcks = 1;
    }
    //
    info = 0;
    if (!left && !right) {
        info = -1;
    } else if (!tran && !notran) {
        info = -2;
    } else if (m < 0) {
        info = -3;
    } else if (n < 0) {
        info = -4;
    } else if (k < 0 || k > mn) {
        info = -5;
    } else if (lda < max((INTEGER)1, mn)) {
        info = -7;
    } else if (tsize < 5) {
        info = -9;
    } else if (ldc < max((INTEGER)1, m)) {
        info = -11;
    } else if ((lwork < max((INTEGER)1, lw)) && (!lquery)) {
        info = -13;
    }
    //
    if (info == 0) {
        work[1 - 1] = lw;
    }
    //
    if (info != 0) {
        Mxerbla("Cgemqr", -info);
        return;
    } else if (lquery) {
        return;
    }
    //
    //     Quick return if possible
    //
    if (min({m, n, k}) == 0) {
        return;
    }
    //
    if ((left && m <= k) || (right && n <= k) || (mb <= k) || (mb >= max({m, n, k}))) {
        Cgemqrt(side, trans, m, n, k, nb, a, lda, &t[6 - 1], nb, c, ldc, work, info);
    } else {
        Clamtsqr(side, trans, m, n, k, mb, nb, a, lda, &t[6 - 1], nb, c, ldc, work, lwork, info);
    }
    //
    work[1 - 1] = lw;
    //
    //     End of Cgemqr
    //
}
