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

void Rerrge(const char *path, INTEGER const nunit) {
    //
    INTEGER nout = nunit;
    char c2[2];
    c2[0] = path[1];
    c2[1] = path[2];
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 4;
    INTEGER i = 0;
    REAL a[nmax * nmax];
    REAL af[nmax * nmax];
    REAL b[nmax];
    REAL r1[nmax];
    REAL r2[nmax];
    const INTEGER lw = 3 * nmax;
    REAL w[lw];
    REAL x[nmax];
    INTEGER ip[nmax];
    INTEGER iw[nmax];
    INTEGER lda = nmax;
    INTEGER ldaf = nmax;
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = 1.0 / castREAL(i + j);
            af[(i - 1) + (j - 1) * ldaf] = 1.0 / castREAL(i + j);
        }
        b[j - 1] = 0.0;
        r1[j - 1] = 0.0;
        r2[j - 1] = 0.0;
        w[j - 1] = 0.0;
        x[j - 1] = 0.0;
        ip[j - 1] = j;
        iw[j - 1] = j;
    }
    ok = true;
    //
    INTEGER info = 0;
    REAL anrm = 0.0;
    REAL rcond = 0.0;
    REAL ccond = 0.0;
    if (Mlsamen(2, c2, "GE")) {
        //
        //        Test error exits of the routines that use the LU decomposition
        //        of a general matrix.
        //
        //        Rgetrf
        //
        strncpy(srnamt, "Rgetrf", srnamt_len);
        infot = 1;
        Rgetrf(-1, 0, a, 1, ip, info);
        chkxer("Rgetrf", infot, nout, lerr, ok);
        infot = 2;
        Rgetrf(0, -1, a, 1, ip, info);
        chkxer("Rgetrf", infot, nout, lerr, ok);
        infot = 4;
        Rgetrf(2, 1, a, 1, ip, info);
        chkxer("Rgetrf", infot, nout, lerr, ok);
        //
        //        Rgetf2
        //
        strncpy(srnamt, "Rgetf2", srnamt_len);
        infot = 1;
        Rgetf2(-1, 0, a, 1, ip, info);
        chkxer("Rgetf2", infot, nout, lerr, ok);
        infot = 2;
        Rgetf2(0, -1, a, 1, ip, info);
        chkxer("Rgetf2", infot, nout, lerr, ok);
        infot = 4;
        Rgetf2(2, 1, a, 1, ip, info);
        chkxer("Rgetf2", infot, nout, lerr, ok);
        //
        //        Rgetri
        //
        strncpy(srnamt, "Rgetri", srnamt_len);
        infot = 1;
        Rgetri(-1, a, 1, ip, w, lw, info);
        chkxer("Rgetri", infot, nout, lerr, ok);
        infot = 3;
        Rgetri(2, a, 1, ip, w, lw, info);
        chkxer("Rgetri", infot, nout, lerr, ok);
        //
        //        Rgetrs
        //
        strncpy(srnamt, "Rgetrs", srnamt_len);
        infot = 1;
        Rgetrs("/", 0, 0, a, 1, ip, b, 1, info);
        chkxer("Rgetrs", infot, nout, lerr, ok);
        infot = 2;
        Rgetrs("N", -1, 0, a, 1, ip, b, 1, info);
        chkxer("Rgetrs", infot, nout, lerr, ok);
        infot = 3;
        Rgetrs("N", 0, -1, a, 1, ip, b, 1, info);
        chkxer("Rgetrs", infot, nout, lerr, ok);
        infot = 5;
        Rgetrs("N", 2, 1, a, 1, ip, b, 2, info);
        chkxer("Rgetrs", infot, nout, lerr, ok);
        infot = 8;
        Rgetrs("N", 2, 1, a, 2, ip, b, 1, info);
        chkxer("Rgetrs", infot, nout, lerr, ok);
        //
        //        Rgerfs
        //
        strncpy(srnamt, "Rgerfs", srnamt_len);
        infot = 1;
        Rgerfs("/", 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 2;
        Rgerfs("N", -1, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 3;
        Rgerfs("N", 0, -1, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 5;
        Rgerfs("N", 2, 1, a, 1, af, 2, ip, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 7;
        Rgerfs("N", 2, 1, a, 2, af, 1, ip, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 10;
        Rgerfs("N", 2, 1, a, 2, af, 2, ip, b, 1, x, 2, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        infot = 12;
        Rgerfs("N", 2, 1, a, 2, af, 2, ip, b, 2, x, 1, r1, r2, w, iw, info);
        chkxer("Rgerfs", infot, nout, lerr, ok);
        //
        //        Rgecon
        //
        strncpy(srnamt, "Rgecon", srnamt_len);
        infot = 1;
        Rgecon("/", 0, a, 1, anrm, rcond, w, iw, info);
        chkxer("Rgecon", infot, nout, lerr, ok);
        infot = 2;
        Rgecon("1", -1, a, 1, anrm, rcond, w, iw, info);
        chkxer("Rgecon", infot, nout, lerr, ok);
        infot = 4;
        Rgecon("1", 2, a, 1, anrm, rcond, w, iw, info);
        chkxer("Rgecon", infot, nout, lerr, ok);
        //
        //        Rgeequ
        //
        strncpy(srnamt, "Rgeequ", srnamt_len);
        infot = 1;
        Rgeequ(-1, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgeequ", infot, nout, lerr, ok);
        infot = 2;
        Rgeequ(0, -1, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgeequ", infot, nout, lerr, ok);
        infot = 4;
        Rgeequ(2, 2, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgeequ", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "GB")) {
        //
        //        Test error exits of the routines that use the LU decomposition
        //        of a general band matrix.
        //
        //        Rgbtrf
        //
        strncpy(srnamt, "Rgbtrf", srnamt_len);
        infot = 1;
        Rgbtrf(-1, 0, 0, 0, a, 1, ip, info);
        chkxer("Rgbtrf", infot, nout, lerr, ok);
        infot = 2;
        Rgbtrf(0, -1, 0, 0, a, 1, ip, info);
        chkxer("Rgbtrf", infot, nout, lerr, ok);
        infot = 3;
        Rgbtrf(1, 1, -1, 0, a, 1, ip, info);
        chkxer("Rgbtrf", infot, nout, lerr, ok);
        infot = 4;
        Rgbtrf(1, 1, 0, -1, a, 1, ip, info);
        chkxer("Rgbtrf", infot, nout, lerr, ok);
        infot = 6;
        Rgbtrf(2, 2, 1, 1, a, 3, ip, info);
        chkxer("Rgbtrf", infot, nout, lerr, ok);
        //
        //        Rgbtf2
        //
        strncpy(srnamt, "Rgbtf2", srnamt_len);
        infot = 1;
        Rgbtf2(-1, 0, 0, 0, a, 1, ip, info);
        chkxer("Rgbtf2", infot, nout, lerr, ok);
        infot = 2;
        Rgbtf2(0, -1, 0, 0, a, 1, ip, info);
        chkxer("Rgbtf2", infot, nout, lerr, ok);
        infot = 3;
        Rgbtf2(1, 1, -1, 0, a, 1, ip, info);
        chkxer("Rgbtf2", infot, nout, lerr, ok);
        infot = 4;
        Rgbtf2(1, 1, 0, -1, a, 1, ip, info);
        chkxer("Rgbtf2", infot, nout, lerr, ok);
        infot = 6;
        Rgbtf2(2, 2, 1, 1, a, 3, ip, info);
        chkxer("Rgbtf2", infot, nout, lerr, ok);
        //
        //        Rgbtrs
        //
        strncpy(srnamt, "Rgbtrs", srnamt_len);
        infot = 1;
        Rgbtrs("/", 0, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 2;
        Rgbtrs("N", -1, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 3;
        Rgbtrs("N", 1, -1, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 4;
        Rgbtrs("N", 1, 0, -1, 1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 5;
        Rgbtrs("N", 1, 0, 0, -1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 7;
        Rgbtrs("N", 2, 1, 1, 1, a, 3, ip, b, 2, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        infot = 10;
        Rgbtrs("N", 2, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Rgbtrs", infot, nout, lerr, ok);
        //
        //        Rgbrfs
        //
        strncpy(srnamt, "Rgbrfs", srnamt_len);
        infot = 1;
        Rgbrfs("/", 0, 0, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 2;
        Rgbrfs("N", -1, 0, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 3;
        Rgbrfs("N", 1, -1, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 4;
        Rgbrfs("N", 1, 0, -1, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 5;
        Rgbrfs("N", 1, 0, 0, -1, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 7;
        Rgbrfs("N", 2, 1, 1, 1, a, 2, af, 4, ip, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 9;
        Rgbrfs("N", 2, 1, 1, 1, a, 3, af, 3, ip, b, 2, x, 2, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 12;
        Rgbrfs("N", 2, 0, 0, 1, a, 1, af, 1, ip, b, 1, x, 2, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        infot = 14;
        Rgbrfs("N", 2, 0, 0, 1, a, 1, af, 1, ip, b, 2, x, 1, r1, r2, w, iw, info);
        chkxer("Rgbrfs", infot, nout, lerr, ok);
        //
        //        Rgbcon
        //
        strncpy(srnamt, "Rgbcon", srnamt_len);
        infot = 1;
        Rgbcon("/", 0, 0, 0, a, 1, ip, anrm, rcond, w, iw, info);
        chkxer("Rgbcon", infot, nout, lerr, ok);
        infot = 2;
        Rgbcon("1", -1, 0, 0, a, 1, ip, anrm, rcond, w, iw, info);
        chkxer("Rgbcon", infot, nout, lerr, ok);
        infot = 3;
        Rgbcon("1", 1, -1, 0, a, 1, ip, anrm, rcond, w, iw, info);
        chkxer("Rgbcon", infot, nout, lerr, ok);
        infot = 4;
        Rgbcon("1", 1, 0, -1, a, 1, ip, anrm, rcond, w, iw, info);
        chkxer("Rgbcon", infot, nout, lerr, ok);
        infot = 6;
        Rgbcon("1", 2, 1, 1, a, 3, ip, anrm, rcond, w, iw, info);
        chkxer("Rgbcon", infot, nout, lerr, ok);
        //
        //        Rgbequ
        //
        strncpy(srnamt, "Rgbequ", srnamt_len);
        infot = 1;
        Rgbequ(-1, 0, 0, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgbequ", infot, nout, lerr, ok);
        infot = 2;
        Rgbequ(0, -1, 0, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgbequ", infot, nout, lerr, ok);
        infot = 3;
        Rgbequ(1, 1, -1, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgbequ", infot, nout, lerr, ok);
        infot = 4;
        Rgbequ(1, 1, 0, -1, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgbequ", infot, nout, lerr, ok);
        infot = 6;
        Rgbequ(2, 2, 1, 1, a, 2, r1, r2, rcond, ccond, anrm, info);
        chkxer("Rgbequ", infot, nout, lerr, ok);
    }
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Rerrge
    //
}
