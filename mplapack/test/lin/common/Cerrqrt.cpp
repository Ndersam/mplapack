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

void Cerrqrt(const char *path, INTEGER const nunit) {
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 2;
    INTEGER i = 0;
    COMPLEX a[nmax * nmax];
    COMPLEX c[nmax * nmax];
    COMPLEX t[nmax * nmax];
    INTEGER lda = nmax;
    INTEGER ldc = nmax;
    INTEGER ldt = nmax;
    COMPLEX w[nmax];
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = COMPLEX(1.0 / castREAL(i + j), 0.0);
            c[(i - 1) + (j - 1) * ldc] = COMPLEX(1.0 / castREAL(i + j), 0.0);
            t[(i - 1) + (j - 1) * ldt] = COMPLEX(1.0 / castREAL(i + j), 0.0);
        }
        w[j - 1] = 0.0;
    }
    ok = true;
    //
    //     Error exits for QRT factorization
    //
    //     Cgeqrt
    //
    strncpy(srnamt, "Cgeqrt", srnamt_len);
    infot = 1;
    INTEGER info = 0;
    Cgeqrt(-1, 0, 1, a, 1, t, 1, w, info);
    chkxer("Cgeqrt", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrt(0, -1, 1, a, 1, t, 1, w, info);
    chkxer("Cgeqrt", infot, nout, lerr, ok);
    infot = 3;
    Cgeqrt(0, 0, 0, a, 1, t, 1, w, info);
    chkxer("Cgeqrt", infot, nout, lerr, ok);
    infot = 5;
    Cgeqrt(2, 1, 1, a, 1, t, 1, w, info);
    chkxer("Cgeqrt", infot, nout, lerr, ok);
    infot = 7;
    Cgeqrt(2, 2, 2, a, 2, t, 1, w, info);
    chkxer("Cgeqrt", infot, nout, lerr, ok);
    //
    //     Cgeqrt2
    //
    strncpy(srnamt, "Cgeqrt2", srnamt_len);
    infot = 1;
    Cgeqrt2(-1, 0, a, 1, t, 1, info);
    chkxer("Cgeqrt2", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrt2(0, -1, a, 1, t, 1, info);
    chkxer("Cgeqrt2", infot, nout, lerr, ok);
    infot = 4;
    Cgeqrt2(2, 1, a, 1, t, 1, info);
    chkxer("Cgeqrt2", infot, nout, lerr, ok);
    infot = 6;
    Cgeqrt2(2, 2, a, 2, t, 1, info);
    chkxer("Cgeqrt2", infot, nout, lerr, ok);
    //
    //     Cgeqrt3
    //
    strncpy(srnamt, "Cgeqrt3", srnamt_len);
    infot = 1;
    Cgeqrt3(-1, 0, a, 1, t, 1, info);
    chkxer("Cgeqrt3", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrt3(0, -1, a, 1, t, 1, info);
    chkxer("Cgeqrt3", infot, nout, lerr, ok);
    infot = 4;
    Cgeqrt3(2, 1, a, 1, t, 1, info);
    chkxer("Cgeqrt3", infot, nout, lerr, ok);
    infot = 6;
    Cgeqrt3(2, 2, a, 2, t, 1, info);
    chkxer("Cgeqrt3", infot, nout, lerr, ok);
    //
    //     Cgemqrt
    //
    strncpy(srnamt, "Cgemqrt", srnamt_len);
    infot = 1;
    Cgemqrt("/", "N", 0, 0, 0, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 2;
    Cgemqrt("L", "/", 0, 0, 0, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 3;
    Cgemqrt("L", "N", -1, 0, 0, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 4;
    Cgemqrt("L", "N", 0, -1, 0, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 5;
    Cgemqrt("L", "N", 0, 0, -1, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 5;
    Cgemqrt("R", "N", 0, 0, -1, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 6;
    Cgemqrt("L", "N", 0, 0, 0, 0, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 8;
    Cgemqrt("R", "N", 1, 2, 1, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 8;
    Cgemqrt("L", "N", 2, 1, 1, 1, a, 1, t, 1, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 10;
    Cgemqrt("R", "N", 1, 1, 1, 1, a, 1, t, 0, c, 1, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    infot = 12;
    Cgemqrt("L", "N", 1, 1, 1, 1, a, 1, t, 1, c, 0, w, info);
    chkxer("Cgemqrt", infot, nout, lerr, ok);
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Cerrqrt
    //
}
