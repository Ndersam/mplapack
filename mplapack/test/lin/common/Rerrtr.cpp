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

void Rerrtr(const char *path, INTEGER const nunit) {
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
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Scalars in Common ..
    //     ..
    //     .. Common blocks ..
    //     ..
    //     .. Executable Statements ..
    //
    nout = nunit;
    char c2[2];
    c2[0] = path[1];
    c2[1] = path[2];
    const INTEGER nmax = 2;
    REAL a[nmax * nmax];
    INTEGER lda = nmax;
    a[(1 - 1) + (1 - 1) * lda] = 1.0;
    a[(1 - 1) + (2 - 1) * lda] = 2.0;
    a[(2 - 1) + (2 - 1) * lda] = 3.e0;
    a[(2 - 1)] = 4.e0;
    ok = true;
    //
    INTEGER info = 0;
    REAL x[nmax];
    REAL b[nmax];
    REAL r1[nmax];
    REAL r2[nmax];
    REAL w[nmax];
    INTEGER iw[nmax];
    REAL rcond = 0.0;
    REAL scale = 0.0;
    if (Mlsamen(2, c2, "TR")) {
        //
        //        Test error exits for the general triangular routines.
        //
        //        Rtrtri
        //
        infot = 1;
        strncpy(srnamt, "Rtrtri", srnamt_len);
        Rtrtri("/", "N", 0, a, 1, info);
        chkxer("Rtrtri", infot, nout, lerr, ok);
        infot = 2;
        Rtrtri("U", "/", 0, a, 1, info);
        chkxer("Rtrtri", infot, nout, lerr, ok);
        infot = 3;
        Rtrtri("U", "N", -1, a, 1, info);
        chkxer("Rtrtri", infot, nout, lerr, ok);
        infot = 5;
        Rtrtri("U", "N", 2, a, 1, info);
        chkxer("Rtrtri", infot, nout, lerr, ok);
        //
        //        Rtrti2
        //
        infot = 1;
        strncpy(srnamt, "Rtrti2", srnamt_len);
        Rtrti2("/", "N", 0, a, 1, info);
        chkxer("Rtrti2", infot, nout, lerr, ok);
        infot = 2;
        Rtrti2("U", "/", 0, a, 1, info);
        chkxer("Rtrti2", infot, nout, lerr, ok);
        infot = 3;
        Rtrti2("U", "N", -1, a, 1, info);
        chkxer("Rtrti2", infot, nout, lerr, ok);
        infot = 5;
        Rtrti2("U", "N", 2, a, 1, info);
        chkxer("Rtrti2", infot, nout, lerr, ok);
        //
        //        Rtrtrs
        //
        infot = 1;
        strncpy(srnamt, "Rtrtrs", srnamt_len);
        Rtrtrs("/", "N", "N", 0, 0, a, 1, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 2;
        Rtrtrs("U", "/", "N", 0, 0, a, 1, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 3;
        Rtrtrs("U", "N", "/", 0, 0, a, 1, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 4;
        Rtrtrs("U", "N", "N", -1, 0, a, 1, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 5;
        Rtrtrs("U", "N", "N", 0, -1, a, 1, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 7;
        Rtrtrs("U", "N", "N", 2, 1, a, 1, x, 2, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        infot = 9;
        Rtrtrs("U", "N", "N", 2, 1, a, 2, x, 1, info);
        chkxer("Rtrtrs", infot, nout, lerr, ok);
        //
        //        Rtrrfs
        //
        infot = 1;
        strncpy(srnamt, "Rtrrfs", srnamt_len);
        Rtrrfs("/", "N", "N", 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 2;
        Rtrrfs("U", "/", "N", 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 3;
        Rtrrfs("U", "N", "/", 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 4;
        Rtrrfs("U", "N", "N", -1, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 5;
        Rtrrfs("U", "N", "N", 0, -1, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 7;
        Rtrrfs("U", "N", "N", 2, 1, a, 1, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 9;
        Rtrrfs("U", "N", "N", 2, 1, a, 2, b, 1, x, 2, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        infot = 11;
        Rtrrfs("U", "N", "N", 2, 1, a, 2, b, 2, x, 1, r1, r2, w, iw, info);
        chkxer("Rtrrfs", infot, nout, lerr, ok);
        //
        //        Rtrcon
        //
        infot = 1;
        strncpy(srnamt, "Rtrcon", srnamt_len);
        Rtrcon("/", "U", "N", 0, a, 1, rcond, w, iw, info);
        chkxer("Rtrcon", infot, nout, lerr, ok);
        infot = 2;
        Rtrcon("1", "/", "N", 0, a, 1, rcond, w, iw, info);
        chkxer("Rtrcon", infot, nout, lerr, ok);
        infot = 3;
        Rtrcon("1", "U", "/", 0, a, 1, rcond, w, iw, info);
        chkxer("Rtrcon", infot, nout, lerr, ok);
        infot = 4;
        Rtrcon("1", "U", "N", -1, a, 1, rcond, w, iw, info);
        chkxer("Rtrcon", infot, nout, lerr, ok);
        infot = 6;
        Rtrcon("1", "U", "N", 2, a, 1, rcond, w, iw, info);
        chkxer("Rtrcon", infot, nout, lerr, ok);
        //
        //        Rlatrs
        //
        infot = 1;
        strncpy(srnamt, "Rlatrs", srnamt_len);
        Rlatrs("/", "N", "N", "N", 0, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        infot = 2;
        Rlatrs("U", "/", "N", "N", 0, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        infot = 3;
        Rlatrs("U", "N", "/", "N", 0, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        infot = 4;
        Rlatrs("U", "N", "N", "/", 0, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        infot = 5;
        Rlatrs("U", "N", "N", "N", -1, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        infot = 7;
        Rlatrs("U", "N", "N", "N", 2, a, 1, x, scale, w, info);
        chkxer("Rlatrs", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "TP")) {
        //
        //        Test error exits for the packed triangular routines.
        //
        //        Rtptri
        //
        infot = 1;
        strncpy(srnamt, "Rtptri", srnamt_len);
        Rtptri("/", "N", 0, a, info);
        chkxer("Rtptri", infot, nout, lerr, ok);
        infot = 2;
        Rtptri("U", "/", 0, a, info);
        chkxer("Rtptri", infot, nout, lerr, ok);
        infot = 3;
        Rtptri("U", "N", -1, a, info);
        chkxer("Rtptri", infot, nout, lerr, ok);
        //
        //        Rtptrs
        //
        infot = 1;
        strncpy(srnamt, "Rtptrs", srnamt_len);
        Rtptrs("/", "N", "N", 0, 0, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        infot = 2;
        Rtptrs("U", "/", "N", 0, 0, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        infot = 3;
        Rtptrs("U", "N", "/", 0, 0, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        infot = 4;
        Rtptrs("U", "N", "N", -1, 0, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        infot = 5;
        Rtptrs("U", "N", "N", 0, -1, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        infot = 8;
        Rtptrs("U", "N", "N", 2, 1, a, x, 1, info);
        chkxer("Rtptrs", infot, nout, lerr, ok);
        //
        //        Rtprfs
        //
        infot = 1;
        strncpy(srnamt, "Rtprfs", srnamt_len);
        Rtprfs("/", "N", "N", 0, 0, a, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 2;
        Rtprfs("U", "/", "N", 0, 0, a, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 3;
        Rtprfs("U", "N", "/", 0, 0, a, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 4;
        Rtprfs("U", "N", "N", -1, 0, a, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 5;
        Rtprfs("U", "N", "N", 0, -1, a, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 8;
        Rtprfs("U", "N", "N", 2, 1, a, b, 1, x, 2, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        infot = 10;
        Rtprfs("U", "N", "N", 2, 1, a, b, 2, x, 1, r1, r2, w, iw, info);
        chkxer("Rtprfs", infot, nout, lerr, ok);
        //
        //        Rtpcon
        //
        infot = 1;
        strncpy(srnamt, "Rtpcon", srnamt_len);
        Rtpcon("/", "U", "N", 0, a, rcond, w, iw, info);
        chkxer("Rtpcon", infot, nout, lerr, ok);
        infot = 2;
        Rtpcon("1", "/", "N", 0, a, rcond, w, iw, info);
        chkxer("Rtpcon", infot, nout, lerr, ok);
        infot = 3;
        Rtpcon("1", "U", "/", 0, a, rcond, w, iw, info);
        chkxer("Rtpcon", infot, nout, lerr, ok);
        infot = 4;
        Rtpcon("1", "U", "N", -1, a, rcond, w, iw, info);
        chkxer("Rtpcon", infot, nout, lerr, ok);
        //
        //        Rlatps
        //
        infot = 1;
        strncpy(srnamt, "Rlatps", srnamt_len);
        Rlatps("/", "N", "N", "N", 0, a, x, scale, w, info);
        chkxer("Rlatps", infot, nout, lerr, ok);
        infot = 2;
        Rlatps("U", "/", "N", "N", 0, a, x, scale, w, info);
        chkxer("Rlatps", infot, nout, lerr, ok);
        infot = 3;
        Rlatps("U", "N", "/", "N", 0, a, x, scale, w, info);
        chkxer("Rlatps", infot, nout, lerr, ok);
        infot = 4;
        Rlatps("U", "N", "N", "/", 0, a, x, scale, w, info);
        chkxer("Rlatps", infot, nout, lerr, ok);
        infot = 5;
        Rlatps("U", "N", "N", "N", -1, a, x, scale, w, info);
        chkxer("Rlatps", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "TB")) {
        //
        //        Test error exits for the banded triangular routines.
        //
        //        Rtbtrs
        //
        infot = 1;
        strncpy(srnamt, "Rtbtrs", srnamt_len);
        Rtbtrs("/", "N", "N", 0, 0, 0, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 2;
        Rtbtrs("U", "/", "N", 0, 0, 0, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 3;
        Rtbtrs("U", "N", "/", 0, 0, 0, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 4;
        Rtbtrs("U", "N", "N", -1, 0, 0, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 5;
        Rtbtrs("U", "N", "N", 0, -1, 0, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 6;
        Rtbtrs("U", "N", "N", 0, 0, -1, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 8;
        Rtbtrs("U", "N", "N", 2, 1, 1, a, 1, x, 2, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        infot = 10;
        Rtbtrs("U", "N", "N", 2, 0, 1, a, 1, x, 1, info);
        chkxer("Rtbtrs", infot, nout, lerr, ok);
        //
        //        Rtbrfs
        //
        infot = 1;
        strncpy(srnamt, "Rtbrfs", srnamt_len);
        Rtbrfs("/", "N", "N", 0, 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 2;
        Rtbrfs("U", "/", "N", 0, 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 3;
        Rtbrfs("U", "N", "/", 0, 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 4;
        Rtbrfs("U", "N", "N", -1, 0, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 5;
        Rtbrfs("U", "N", "N", 0, -1, 0, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 6;
        Rtbrfs("U", "N", "N", 0, 0, -1, a, 1, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 8;
        Rtbrfs("U", "N", "N", 2, 1, 1, a, 1, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 10;
        Rtbrfs("U", "N", "N", 2, 1, 1, a, 2, b, 1, x, 2, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        infot = 12;
        Rtbrfs("U", "N", "N", 2, 1, 1, a, 2, b, 2, x, 1, r1, r2, w, iw, info);
        chkxer("Rtbrfs", infot, nout, lerr, ok);
        //
        //        Rtbcon
        //
        infot = 1;
        strncpy(srnamt, "Rtbcon", srnamt_len);
        Rtbcon("/", "U", "N", 0, 0, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        infot = 2;
        Rtbcon("1", "/", "N", 0, 0, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        infot = 3;
        Rtbcon("1", "U", "/", 0, 0, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        infot = 4;
        Rtbcon("1", "U", "N", -1, 0, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        infot = 5;
        Rtbcon("1", "U", "N", 0, -1, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        infot = 7;
        Rtbcon("1", "U", "N", 2, 1, a, 1, rcond, w, iw, info);
        chkxer("Rtbcon", infot, nout, lerr, ok);
        //
        //        Rlatbs
        //
        infot = 1;
        strncpy(srnamt, "Rlatbs", srnamt_len);
        Rlatbs("/", "N", "N", "N", 0, 0, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 2;
        Rlatbs("U", "/", "N", "N", 0, 0, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 3;
        Rlatbs("U", "N", "/", "N", 0, 0, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 4;
        Rlatbs("U", "N", "N", "/", 0, 0, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 5;
        Rlatbs("U", "N", "N", "N", -1, 0, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 6;
        Rlatbs("U", "N", "N", "N", 1, -1, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
        infot = 8;
        Rlatbs("U", "N", "N", "N", 2, 1, a, 1, x, scale, w, info);
        chkxer("Rlatbs", infot, nout, lerr, ok);
    }
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Rerrtr
    //
}
