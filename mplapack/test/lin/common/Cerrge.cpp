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

void Cerrge(const char *path, INTEGER const nunit) {
    //
    nout = nunit;
    char c2[2];
    c2[0] = path[1];
    c2[1] = path[2];
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 4;
    INTEGER i = 0;
    COMPLEX a[nmax * nmax];
    INTEGER lda = nmax;
    COMPLEX af[nmax * nmax];
    INTEGER ldaf = nmax;
    COMPLEX b[nmax];
    REAL r1[nmax];
    REAL r2[nmax];
    COMPLEX w[2 * nmax];
    COMPLEX x[nmax];
    INTEGER ip[nmax];
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = COMPLEX(1.0 / castREAL(i + j), -1.0 / castREAL(i + j));
            af[(i - 1) + (j - 1) * ldaf] = COMPLEX(1.0 / castREAL(i + j), -1.0 / castREAL(i + j));
        }
        b[j - 1] = 0.0;
        r1[j - 1] = 0.0;
        r2[j - 1] = 0.0;
        w[j - 1] = 0.0;
        x[j - 1] = 0.0;
        ip[j - 1] = j;
    }
    ok = true;
    //
    //     Test error exits of the routines that use the LU decomposition
    //     of a general matrix.
    //
    INTEGER info = 0;
    REAL r[nmax];
    REAL anrm = 0.0;
    REAL rcond = 0.0;
    REAL ccond = 0.0;
    if (Mlsamen(2, c2, "GE")) {
        //
        //        Cgetrf
        //
        strncpy(srnamt, "Cgetrf", srnamt_len);
        infot = 1;
        Cgetrf(-1, 0, a, 1, ip, info);
        chkxer("Cgetrf", infot, nout, lerr, ok);
        infot = 2;
        Cgetrf(0, -1, a, 1, ip, info);
        chkxer("Cgetrf", infot, nout, lerr, ok);
        infot = 4;
        Cgetrf(2, 1, a, 1, ip, info);
        chkxer("Cgetrf", infot, nout, lerr, ok);
        //
        //        Cgetf2
        //
        strncpy(srnamt, "Cgetf2", srnamt_len);
        infot = 1;
        Cgetf2(-1, 0, a, 1, ip, info);
        chkxer("Cgetf2", infot, nout, lerr, ok);
        infot = 2;
        Cgetf2(0, -1, a, 1, ip, info);
        chkxer("Cgetf2", infot, nout, lerr, ok);
        infot = 4;
        Cgetf2(2, 1, a, 1, ip, info);
        chkxer("Cgetf2", infot, nout, lerr, ok);
        //
        //        Cgetri
        //
        strncpy(srnamt, "Cgetri", srnamt_len);
        infot = 1;
        Cgetri(-1, a, 1, ip, w, 1, info);
        chkxer("Cgetri", infot, nout, lerr, ok);
        infot = 3;
        Cgetri(2, a, 1, ip, w, 2, info);
        chkxer("Cgetri", infot, nout, lerr, ok);
        infot = 6;
        Cgetri(2, a, 2, ip, w, 1, info);
        chkxer("Cgetri", infot, nout, lerr, ok);
        //
        //        Cgetrs
        //
        strncpy(srnamt, "Cgetrs", srnamt_len);
        infot = 1;
        Cgetrs("/", 0, 0, a, 1, ip, b, 1, info);
        chkxer("Cgetrs", infot, nout, lerr, ok);
        infot = 2;
        Cgetrs("N", -1, 0, a, 1, ip, b, 1, info);
        chkxer("Cgetrs", infot, nout, lerr, ok);
        infot = 3;
        Cgetrs("N", 0, -1, a, 1, ip, b, 1, info);
        chkxer("Cgetrs", infot, nout, lerr, ok);
        infot = 5;
        Cgetrs("N", 2, 1, a, 1, ip, b, 2, info);
        chkxer("Cgetrs", infot, nout, lerr, ok);
        infot = 8;
        Cgetrs("N", 2, 1, a, 2, ip, b, 1, info);
        chkxer("Cgetrs", infot, nout, lerr, ok);
        //
        //        Cgerfs
        //
        strncpy(srnamt, "Cgerfs", srnamt_len);
        infot = 1;
        Cgerfs("/", 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 2;
        Cgerfs("N", -1, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 3;
        Cgerfs("N", 0, -1, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 5;
        Cgerfs("N", 2, 1, a, 1, af, 2, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 7;
        Cgerfs("N", 2, 1, a, 2, af, 1, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 10;
        Cgerfs("N", 2, 1, a, 2, af, 2, ip, b, 1, x, 2, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        infot = 12;
        Cgerfs("N", 2, 1, a, 2, af, 2, ip, b, 2, x, 1, r1, r2, w, r, info);
        chkxer("Cgerfs", infot, nout, lerr, ok);
        //
        //        Cgecon
        //
        strncpy(srnamt, "Cgecon", srnamt_len);
        infot = 1;
        Cgecon("/", 0, a, 1, anrm, rcond, w, r, info);
        chkxer("Cgecon", infot, nout, lerr, ok);
        infot = 2;
        Cgecon("1", -1, a, 1, anrm, rcond, w, r, info);
        chkxer("Cgecon", infot, nout, lerr, ok);
        infot = 4;
        Cgecon("1", 2, a, 1, anrm, rcond, w, r, info);
        chkxer("Cgecon", infot, nout, lerr, ok);
        //
        //        Cgeequ
        //
        strncpy(srnamt, "Cgeequ", srnamt_len);
        infot = 1;
        Cgeequ(-1, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgeequ", infot, nout, lerr, ok);
        infot = 2;
        Cgeequ(0, -1, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgeequ", infot, nout, lerr, ok);
        infot = 4;
        Cgeequ(2, 2, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgeequ", infot, nout, lerr, ok);
        //
        //     Test error exits of the routines that use the LU decomposition
        //     of a general band matrix.
        //
    } else if (Mlsamen(2, c2, "GB")) {
        //
        //        Cgbtrf
        //
        strncpy(srnamt, "Cgbtrf", srnamt_len);
        infot = 1;
        Cgbtrf(-1, 0, 0, 0, a, 1, ip, info);
        chkxer("Cgbtrf", infot, nout, lerr, ok);
        infot = 2;
        Cgbtrf(0, -1, 0, 0, a, 1, ip, info);
        chkxer("Cgbtrf", infot, nout, lerr, ok);
        infot = 3;
        Cgbtrf(1, 1, -1, 0, a, 1, ip, info);
        chkxer("Cgbtrf", infot, nout, lerr, ok);
        infot = 4;
        Cgbtrf(1, 1, 0, -1, a, 1, ip, info);
        chkxer("Cgbtrf", infot, nout, lerr, ok);
        infot = 6;
        Cgbtrf(2, 2, 1, 1, a, 3, ip, info);
        chkxer("Cgbtrf", infot, nout, lerr, ok);
        //
        //        Cgbtf2
        //
        strncpy(srnamt, "Cgbtf2", srnamt_len);
        infot = 1;
        Cgbtf2(-1, 0, 0, 0, a, 1, ip, info);
        chkxer("Cgbtf2", infot, nout, lerr, ok);
        infot = 2;
        Cgbtf2(0, -1, 0, 0, a, 1, ip, info);
        chkxer("Cgbtf2", infot, nout, lerr, ok);
        infot = 3;
        Cgbtf2(1, 1, -1, 0, a, 1, ip, info);
        chkxer("Cgbtf2", infot, nout, lerr, ok);
        infot = 4;
        Cgbtf2(1, 1, 0, -1, a, 1, ip, info);
        chkxer("Cgbtf2", infot, nout, lerr, ok);
        infot = 6;
        Cgbtf2(2, 2, 1, 1, a, 3, ip, info);
        chkxer("Cgbtf2", infot, nout, lerr, ok);
        //
        //        Cgbtrs
        //
        strncpy(srnamt, "Cgbtrs", srnamt_len);
        infot = 1;
        Cgbtrs("/", 0, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 2;
        Cgbtrs("N", -1, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 3;
        Cgbtrs("N", 1, -1, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 4;
        Cgbtrs("N", 1, 0, -1, 1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 5;
        Cgbtrs("N", 1, 0, 0, -1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 7;
        Cgbtrs("N", 2, 1, 1, 1, a, 3, ip, b, 2, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        infot = 10;
        Cgbtrs("N", 2, 0, 0, 1, a, 1, ip, b, 1, info);
        chkxer("Cgbtrs", infot, nout, lerr, ok);
        //
        //        Cgbrfs
        //
        strncpy(srnamt, "Cgbrfs", srnamt_len);
        infot = 1;
        Cgbrfs("/", 0, 0, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 2;
        Cgbrfs("N", -1, 0, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 3;
        Cgbrfs("N", 1, -1, 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 4;
        Cgbrfs("N", 1, 0, -1, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 5;
        Cgbrfs("N", 1, 0, 0, -1, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 7;
        Cgbrfs("N", 2, 1, 1, 1, a, 2, af, 4, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 9;
        Cgbrfs("N", 2, 1, 1, 1, a, 3, af, 3, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 12;
        Cgbrfs("N", 2, 0, 0, 1, a, 1, af, 1, ip, b, 1, x, 2, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        infot = 14;
        Cgbrfs("N", 2, 0, 0, 1, a, 1, af, 1, ip, b, 2, x, 1, r1, r2, w, r, info);
        chkxer("Cgbrfs", infot, nout, lerr, ok);
        //
        //        Cgbcon
        //
        strncpy(srnamt, "Cgbcon", srnamt_len);
        infot = 1;
        Cgbcon("/", 0, 0, 0, a, 1, ip, anrm, rcond, w, r, info);
        chkxer("Cgbcon", infot, nout, lerr, ok);
        infot = 2;
        Cgbcon("1", -1, 0, 0, a, 1, ip, anrm, rcond, w, r, info);
        chkxer("Cgbcon", infot, nout, lerr, ok);
        infot = 3;
        Cgbcon("1", 1, -1, 0, a, 1, ip, anrm, rcond, w, r, info);
        chkxer("Cgbcon", infot, nout, lerr, ok);
        infot = 4;
        Cgbcon("1", 1, 0, -1, a, 1, ip, anrm, rcond, w, r, info);
        chkxer("Cgbcon", infot, nout, lerr, ok);
        infot = 6;
        Cgbcon("1", 2, 1, 1, a, 3, ip, anrm, rcond, w, r, info);
        chkxer("Cgbcon", infot, nout, lerr, ok);
        //
        //        Cgbequ
        //
        strncpy(srnamt, "Cgbequ", srnamt_len);
        infot = 1;
        Cgbequ(-1, 0, 0, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgbequ", infot, nout, lerr, ok);
        infot = 2;
        Cgbequ(0, -1, 0, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgbequ", infot, nout, lerr, ok);
        infot = 3;
        Cgbequ(1, 1, -1, 0, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgbequ", infot, nout, lerr, ok);
        infot = 4;
        Cgbequ(1, 1, 0, -1, a, 1, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgbequ", infot, nout, lerr, ok);
        infot = 6;
        Cgbequ(2, 2, 1, 1, a, 2, r1, r2, rcond, ccond, anrm, info);
        chkxer("Cgbequ", infot, nout, lerr, ok);
    }
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Cerrge
    //
}
