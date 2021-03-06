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

void Cerrqr(const char *path, INTEGER const nunit) {
    nout = nunit;
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 2;
    INTEGER i = 0;
    COMPLEX a[nmax * nmax];
    COMPLEX af[nmax * nmax];
    COMPLEX b[nmax];
    COMPLEX w[nmax];
    COMPLEX x[nmax];
    INTEGER lda = nmax;
    INTEGER ldaf = nmax;
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = COMPLEX(1.0 / castREAL(i + j), -1.0 / castREAL(i + j));
            af[(i - 1) + (j - 1) * ldaf] = COMPLEX(1.0 / castREAL(i + j), -1.0 / castREAL(i + j));
        }
        b[j - 1] = 0.0;
        w[j - 1] = 0.0;
        x[j - 1] = 0.0;
    }
    ok = true;
    //
    //     Error exits for QR factorization
    //
    //     Cgeqrf
    //
    strncpy(srnamt, "Cgeqrf", srnamt_len);
    infot = 1;
    INTEGER info = 0;
    Cgeqrf(-1, 0, a, 1, b, w, 1, info);
    chkxer("Cgeqrf", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrf(0, -1, a, 1, b, w, 1, info);
    chkxer("Cgeqrf", infot, nout, lerr, ok);
    infot = 4;
    Cgeqrf(2, 1, a, 1, b, w, 1, info);
    chkxer("Cgeqrf", infot, nout, lerr, ok);
    infot = 7;
    Cgeqrf(1, 2, a, 1, b, w, 1, info);
    chkxer("Cgeqrf", infot, nout, lerr, ok);
    //
    //     Cgeqrfp
    //
    strncpy(srnamt, "Cgeqrfp", srnamt_len);
    infot = 1;
    Cgeqrfp(-1, 0, a, 1, b, w, 1, info);
    chkxer("Cgeqrfp", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrfp(0, -1, a, 1, b, w, 1, info);
    chkxer("Cgeqrfp", infot, nout, lerr, ok);
    infot = 4;
    Cgeqrfp(2, 1, a, 1, b, w, 1, info);
    chkxer("Cgeqrfp", infot, nout, lerr, ok);
    infot = 7;
    Cgeqrfp(1, 2, a, 1, b, w, 1, info);
    chkxer("Cgeqrfp", infot, nout, lerr, ok);
    //
    //     Cgeqr2
    //
    strncpy(srnamt, "Cgeqr2", srnamt_len);
    infot = 1;
    Cgeqr2(-1, 0, a, 1, b, w, info);
    chkxer("Cgeqr2", infot, nout, lerr, ok);
    infot = 2;
    Cgeqr2(0, -1, a, 1, b, w, info);
    chkxer("Cgeqr2", infot, nout, lerr, ok);
    infot = 4;
    Cgeqr2(2, 1, a, 1, b, w, info);
    chkxer("Cgeqr2", infot, nout, lerr, ok);
    //
    //     Cgeqr2p
    //
    strncpy(srnamt, "Cgeqr2p", srnamt_len);
    infot = 1;
    Cgeqr2p(-1, 0, a, 1, b, w, info);
    chkxer("Cgeqr2p", infot, nout, lerr, ok);
    infot = 2;
    Cgeqr2p(0, -1, a, 1, b, w, info);
    chkxer("Cgeqr2p", infot, nout, lerr, ok);
    infot = 4;
    Cgeqr2p(2, 1, a, 1, b, w, info);
    chkxer("Cgeqr2p", infot, nout, lerr, ok);
    //
    //     Cgeqrs
    //
    strncpy(srnamt, "Cgeqrs", srnamt_len);
    infot = 1;
    Cgeqrs(-1, 0, 0, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrs(0, -1, 0, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 2;
    Cgeqrs(1, 2, 0, a, 2, x, b, 2, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 3;
    Cgeqrs(0, 0, -1, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 5;
    Cgeqrs(2, 1, 0, a, 1, x, b, 2, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 8;
    Cgeqrs(2, 1, 0, a, 2, x, b, 1, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    infot = 10;
    Cgeqrs(1, 1, 2, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgeqrs", infot, nout, lerr, ok);
    //
    //     Cungqr
    //
    strncpy(srnamt, "Cungqr", srnamt_len);
    infot = 1;
    Cungqr(-1, 0, 0, a, 1, x, w, 1, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 2;
    Cungqr(0, -1, 0, a, 1, x, w, 1, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 2;
    Cungqr(1, 2, 0, a, 1, x, w, 2, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 3;
    Cungqr(0, 0, -1, a, 1, x, w, 1, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 3;
    Cungqr(1, 1, 2, a, 1, x, w, 1, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 5;
    Cungqr(2, 2, 0, a, 1, x, w, 2, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    infot = 8;
    Cungqr(2, 2, 0, a, 2, x, w, 1, info);
    chkxer("Cungqr", infot, nout, lerr, ok);
    //
    //     Cung2r
    //
    strncpy(srnamt, "Cung2r", srnamt_len);
    infot = 1;
    Cung2r(-1, 0, 0, a, 1, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    infot = 2;
    Cung2r(0, -1, 0, a, 1, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    infot = 2;
    Cung2r(1, 2, 0, a, 1, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    infot = 3;
    Cung2r(0, 0, -1, a, 1, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    infot = 3;
    Cung2r(2, 1, 2, a, 2, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    infot = 5;
    Cung2r(2, 1, 0, a, 1, x, w, info);
    chkxer("Cung2r", infot, nout, lerr, ok);
    //
    //     Cunmqr
    //
    strncpy(srnamt, "Cunmqr", srnamt_len);
    infot = 1;
    Cunmqr("/", "N", 0, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 2;
    Cunmqr("L", "/", 0, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 3;
    Cunmqr("L", "N", -1, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 4;
    Cunmqr("L", "N", 0, -1, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 5;
    Cunmqr("L", "N", 0, 0, -1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 5;
    Cunmqr("L", "N", 0, 1, 1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 5;
    Cunmqr("R", "N", 1, 0, 1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 7;
    Cunmqr("L", "N", 2, 1, 0, a, 1, x, af, 2, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 7;
    Cunmqr("R", "N", 1, 2, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 10;
    Cunmqr("L", "N", 2, 1, 0, a, 2, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 12;
    Cunmqr("L", "N", 1, 2, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    infot = 12;
    Cunmqr("R", "N", 2, 1, 0, a, 1, x, af, 2, w, 1, info);
    chkxer("Cunmqr", infot, nout, lerr, ok);
    //
    //     Cunm2r
    //
    strncpy(srnamt, "Cunm2r", srnamt_len);
    infot = 1;
    Cunm2r("/", "N", 0, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 2;
    Cunm2r("L", "/", 0, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 3;
    Cunm2r("L", "N", -1, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 4;
    Cunm2r("L", "N", 0, -1, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 5;
    Cunm2r("L", "N", 0, 0, -1, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 5;
    Cunm2r("L", "N", 0, 1, 1, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 5;
    Cunm2r("R", "N", 1, 0, 1, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 7;
    Cunm2r("L", "N", 2, 1, 0, a, 1, x, af, 2, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 7;
    Cunm2r("R", "N", 1, 2, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    infot = 10;
    Cunm2r("L", "N", 2, 1, 0, a, 2, x, af, 1, w, info);
    chkxer("Cunm2r", infot, nout, lerr, ok);
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Cerrqr
    //
}
