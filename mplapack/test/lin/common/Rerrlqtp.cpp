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

#include <mplapack_debug.h>

void Rerrlqtp(const char *path, INTEGER const nunit) {
    common cmn;
    common_write write(cmn);
    //
    //
    //  -- LAPACK test routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
    //     ..
    //
    //  =====================================================================
    //
    //     .. Parameters ..
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. Local Arrays ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Scalars in Common ..
    //     ..
    //     .. Common blocks ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    nout = nunit;
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 2;
    INTEGER i = 0;
    REAL a[nmax * nmax];
    REAL c[nmax * nmax];
    REAL t[nmax * nmax];
    INTEGER lda = nmax;
    INTEGER ldc = nmax;
    INTEGER ldt = nmax;
    REAL w[nmax];
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = 1.0 / castREAL(i + j);
            c[(i - 1) + (j - 1) * ldc] = 1.0 / castREAL(i + j);
            t[(i - 1) + (j - 1) * ldt] = 1.0 / castREAL(i + j);
        }
        w[j - 1] = 0.0f;
    }
    ok = true;
    //
    //     Error exits for TPLQT factorization
    //
    //     Rtplqt
    //
    infot = 1;
    REAL b[nmax * nmax];
    INTEGER info = 0;
    strncpy(srnamt, "Rtplqt", srnamt_len);
    Rtplqt(-1, 1, 0, 1, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 2;
    Rtplqt(1, -1, 0, 1, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 3;
    Rtplqt(0, 1, -1, 1, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 3;
    Rtplqt(0, 1, 1, 1, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 4;
    Rtplqt(0, 1, 0, 0, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 4;
    Rtplqt(1, 1, 0, 2, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 6;
    Rtplqt(2, 1, 0, 2, a, 1, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 8;
    Rtplqt(2, 1, 0, 1, a, 2, b, 1, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    infot = 10;
    Rtplqt(2, 2, 1, 2, a, 2, b, 2, t, 1, w, info);
    chkxer("Rtplqt", infot, nout, lerr, ok);
    //
    //     Rtplqt2
    //
    infot = 1;
    strncpy(srnamt, "Rtplqt2", srnamt_len);
    Rtplqt2(-1, 0, 0, a, 1, b, 1, t, 1, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    infot = 2;
    Rtplqt2(0, -1, 0, a, 1, b, 1, t, 1, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    infot = 3;
    Rtplqt2(0, 0, -1, a, 1, b, 1, t, 1, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    infot = 5;
    Rtplqt2(2, 2, 0, a, 1, b, 2, t, 2, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    infot = 7;
    Rtplqt2(2, 2, 0, a, 2, b, 1, t, 2, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    infot = 9;
    Rtplqt2(2, 2, 0, a, 2, b, 2, t, 1, info);
    chkxer("Rtplqt2", infot, nout, lerr, ok);
    //
    //     Rtpmlqt
    //
    infot = 1;
    strncpy(srnamt, "Rtpmlqt", srnamt_len);
    Rtpmlqt("/", "N", 0, 0, 0, 0, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 2;
    Rtpmlqt("L", "/", 0, 0, 0, 0, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 3;
    Rtpmlqt("L", "N", -1, 0, 0, 0, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 4;
    Rtpmlqt("L", "N", 0, -1, 0, 0, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 5;
    Rtpmlqt("L", "N", 0, 0, -1, 0, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    infot = 6;
    Rtpmlqt("L", "N", 0, 0, 0, -1, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 7;
    Rtpmlqt("L", "N", 0, 0, 0, 0, 0, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 9;
    Rtpmlqt("R", "N", 2, 2, 2, 1, 1, a, 1, t, 1, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 11;
    Rtpmlqt("R", "N", 1, 1, 1, 1, 1, a, 1, t, 0, b, 1, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 13;
    Rtpmlqt("L", "N", 1, 1, 1, 1, 1, a, 1, t, 1, b, 0, c, 1, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    infot = 15;
    Rtpmlqt("L", "N", 1, 1, 1, 1, 1, a, 1, t, 1, b, 1, c, 0, w, info);
    chkxer("Rtpmlqt", infot, nout, lerr, ok);
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Rerrlqt
    //
}
