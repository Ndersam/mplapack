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

void Cerrlq(const char *path, INTEGER const nunit) {
    common cmn;
    common_write write(cmn);
    //
    nout = nunit;
    write(nout, star);
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 2;
    INTEGER i = 0;
    COMPLEX a[nmax * nmax];
    COMPLEX af[nmax * nmax];
    INTEGER lda = nmax;
    INTEGER ldaf = nmax;
    COMPLEX b[nmax];
    COMPLEX w[nmax];
    COMPLEX x[nmax];
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
    //     Error exits for LQ factorization
    //
    //     Cgelqf
    //
    strncpy(srnamt, "Cgelqf", srnamt_len);
    infot = 1;
    INTEGER info = 0;
    Cgelqf(-1, 0, a, 1, b, w, 1, info);
    chkxer("Cgelqf", infot, nout, lerr, ok);
    infot = 2;
    Cgelqf(0, -1, a, 1, b, w, 1, info);
    chkxer("Cgelqf", infot, nout, lerr, ok);
    infot = 4;
    Cgelqf(2, 1, a, 1, b, w, 2, info);
    chkxer("Cgelqf", infot, nout, lerr, ok);
    infot = 7;
    Cgelqf(2, 1, a, 2, b, w, 1, info);
    chkxer("Cgelqf", infot, nout, lerr, ok);
    //
    //     Cgelq2
    //
    strncpy(srnamt, "Cgelq2", srnamt_len);
    infot = 1;
    Cgelq2(-1, 0, a, 1, b, w, info);
    chkxer("Cgelq2", infot, nout, lerr, ok);
    infot = 2;
    Cgelq2(0, -1, a, 1, b, w, info);
    chkxer("Cgelq2", infot, nout, lerr, ok);
    infot = 4;
    Cgelq2(2, 1, a, 1, b, w, info);
    chkxer("Cgelq2", infot, nout, lerr, ok);
    //
    //     Cgelqs
    //
    strncpy(srnamt, "Cgelqs", srnamt_len);
    infot = 1;
    Cgelqs(-1, 0, 0, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 2;
    Cgelqs(0, -1, 0, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 2;
    Cgelqs(2, 1, 0, a, 2, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 3;
    Cgelqs(0, 0, -1, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 5;
    Cgelqs(2, 2, 0, a, 1, x, b, 2, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 8;
    Cgelqs(1, 2, 0, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    infot = 10;
    Cgelqs(1, 1, 2, a, 1, x, b, 1, w, 1, info);
    chkxer("Cgelqs", infot, nout, lerr, ok);
    //
    //     Cunglq
    //
    strncpy(srnamt, "Cunglq", srnamt_len);
    infot = 1;
    Cunglq(-1, 0, 0, a, 1, x, w, 1, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 2;
    Cunglq(0, -1, 0, a, 1, x, w, 1, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 2;
    Cunglq(2, 1, 0, a, 2, x, w, 2, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 3;
    Cunglq(0, 0, -1, a, 1, x, w, 1, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 3;
    Cunglq(1, 1, 2, a, 1, x, w, 1, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 5;
    Cunglq(2, 2, 0, a, 1, x, w, 2, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    infot = 8;
    Cunglq(2, 2, 0, a, 2, x, w, 1, info);
    chkxer("Cunglq", infot, nout, lerr, ok);
    //
    //     Cungl2
    //
    strncpy(srnamt, "Cungl2", srnamt_len);
    infot = 1;
    Cungl2(-1, 0, 0, a, 1, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    infot = 2;
    Cungl2(0, -1, 0, a, 1, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    infot = 2;
    Cungl2(2, 1, 0, a, 2, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    infot = 3;
    Cungl2(0, 0, -1, a, 1, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    infot = 3;
    Cungl2(1, 1, 2, a, 1, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    infot = 5;
    Cungl2(2, 2, 0, a, 1, x, w, info);
    chkxer("Cungl2", infot, nout, lerr, ok);
    //
    //     Cunmlq
    //
    strncpy(srnamt, "Cunmlq", srnamt_len);
    infot = 1;
    Cunmlq("/", "N", 0, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 2;
    Cunmlq("L", "/", 0, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 3;
    Cunmlq("L", "N", -1, 0, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 4;
    Cunmlq("L", "N", 0, -1, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 5;
    Cunmlq("L", "N", 0, 0, -1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 5;
    Cunmlq("L", "N", 0, 1, 1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 5;
    Cunmlq("R", "N", 1, 0, 1, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 7;
    Cunmlq("L", "N", 2, 0, 2, a, 1, x, af, 2, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 7;
    Cunmlq("R", "N", 0, 2, 2, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 10;
    Cunmlq("L", "N", 2, 1, 0, a, 2, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 12;
    Cunmlq("L", "N", 1, 2, 0, a, 1, x, af, 1, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    infot = 12;
    Cunmlq("R", "N", 2, 1, 0, a, 1, x, af, 2, w, 1, info);
    chkxer("Cunmlq", infot, nout, lerr, ok);
    //
    //     Cunml2
    //
    strncpy(srnamt, "Cunml2", srnamt_len);
    infot = 1;
    Cunml2("/", "N", 0, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 2;
    Cunml2("L", "/", 0, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 3;
    Cunml2("L", "N", -1, 0, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 4;
    Cunml2("L", "N", 0, -1, 0, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 5;
    Cunml2("L", "N", 0, 0, -1, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 5;
    Cunml2("L", "N", 0, 1, 1, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 5;
    Cunml2("R", "N", 1, 0, 1, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 7;
    Cunml2("L", "N", 2, 1, 2, a, 1, x, af, 2, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 7;
    Cunml2("R", "N", 1, 2, 2, a, 1, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    infot = 10;
    Cunml2("L", "N", 2, 1, 0, a, 2, x, af, 1, w, info);
    chkxer("Cunml2", infot, nout, lerr, ok);
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Cerrlq
    //
}
