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

void Cerrhe(const char *path, INTEGER const nunit) {
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
    COMPLEX af[nmax * nmax];
    INTEGER lda = nmax;
    INTEGER ldaf = nmax;
    COMPLEX b[nmax];
    COMPLEX e[nmax];
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
        e[j - 1] = 0.0;
        r1[j - 1] = 0.0;
        r2[j - 1] = 0.0;
        w[j - 1] = 0.0;
        x[j - 1] = 0.0;
        ip[j - 1] = j;
    }
    REAL anrm = 1.0;
    ok = true;
    //
    INTEGER info = 0;
    REAL r[nmax];
    REAL rcond = 0.0;
    if (Mlsamen(2, c2, "HE")) {
        //
        //        Test error exits of the routines that use factorization
        //        of a Hermitian indefinite matrix with patrial
        //        (Bunch-Kaufman) diagonal pivoting method.
        //
        //        Chetrf
        //
        strncpy(srnamt, "Chetrf", srnamt_len);
        infot = 1;
        Chetrf("/", 0, a, 1, ip, w, 1, info);
        chkxer("Chetrf", infot, nout, lerr, ok);
        infot = 2;
        Chetrf("U", -1, a, 1, ip, w, 1, info);
        chkxer("Chetrf", infot, nout, lerr, ok);
        infot = 4;
        Chetrf("U", 2, a, 1, ip, w, 4, info);
        chkxer("Chetrf", infot, nout, lerr, ok);
        infot = 7;
        Chetrf("U", 0, a, 1, ip, w, 0, info);
        chkxer("Chetrf", infot, nout, lerr, ok);
        infot = 7;
        Chetrf("U", 0, a, 1, ip, w, -2, info);
        chkxer("Chetrf", infot, nout, lerr, ok);
        //
        //        Chetf2
        //
        strncpy(srnamt, "Chetf2", srnamt_len);
        infot = 1;
        Chetf2("/", 0, a, 1, ip, info);
        chkxer("Chetf2", infot, nout, lerr, ok);
        infot = 2;
        Chetf2("U", -1, a, 1, ip, info);
        chkxer("Chetf2", infot, nout, lerr, ok);
        infot = 4;
        Chetf2("U", 2, a, 1, ip, info);
        chkxer("Chetf2", infot, nout, lerr, ok);
        //
        //        Chetri
        //
        strncpy(srnamt, "Chetri", srnamt_len);
        infot = 1;
        Chetri("/", 0, a, 1, ip, w, info);
        chkxer("Chetri", infot, nout, lerr, ok);
        infot = 2;
        Chetri("U", -1, a, 1, ip, w, info);
        chkxer("Chetri", infot, nout, lerr, ok);
        infot = 4;
        Chetri("U", 2, a, 1, ip, w, info);
        chkxer("Chetri", infot, nout, lerr, ok);
        //
        //        Chetri2
        //
        strncpy(srnamt, "Chetri2", srnamt_len);
        infot = 1;
        Chetri2("/", 0, a, 1, ip, w, 1, info);
        chkxer("Chetri2", infot, nout, lerr, ok);
        infot = 2;
        Chetri2("U", -1, a, 1, ip, w, 1, info);
        chkxer("Chetri2", infot, nout, lerr, ok);
        infot = 4;
        Chetri2("U", 2, a, 1, ip, w, 1, info);
        chkxer("Chetri2", infot, nout, lerr, ok);
        //
        //        Chetri2x
        //
        strncpy(srnamt, "Chetri2x", srnamt_len);
        infot = 1;
        Chetri2x("/", 0, a, 1, ip, w, 1, info);
        chkxer("Chetri2x", infot, nout, lerr, ok);
        infot = 2;
        Chetri2x("U", -1, a, 1, ip, w, 1, info);
        chkxer("Chetri2x", infot, nout, lerr, ok);
        infot = 4;
        Chetri2x("U", 2, a, 1, ip, w, 1, info);
        chkxer("Chetri2x", infot, nout, lerr, ok);
        //
        //        Chetrs
        //
        strncpy(srnamt, "Chetrs", srnamt_len);
        infot = 1;
        Chetrs("/", 0, 0, a, 1, ip, b, 1, info);
        chkxer("Chetrs", infot, nout, lerr, ok);
        infot = 2;
        Chetrs("U", -1, 0, a, 1, ip, b, 1, info);
        chkxer("Chetrs", infot, nout, lerr, ok);
        infot = 3;
        Chetrs("U", 0, -1, a, 1, ip, b, 1, info);
        chkxer("Chetrs", infot, nout, lerr, ok);
        infot = 5;
        Chetrs("U", 2, 1, a, 1, ip, b, 2, info);
        chkxer("Chetrs", infot, nout, lerr, ok);
        infot = 8;
        Chetrs("U", 2, 1, a, 2, ip, b, 1, info);
        chkxer("Chetrs", infot, nout, lerr, ok);
        //
        //        Cherfs
        //
        strncpy(srnamt, "Cherfs", srnamt_len);
        infot = 1;
        Cherfs("/", 0, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 2;
        Cherfs("U", -1, 0, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 3;
        Cherfs("U", 0, -1, a, 1, af, 1, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 5;
        Cherfs("U", 2, 1, a, 1, af, 2, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 7;
        Cherfs("U", 2, 1, a, 2, af, 1, ip, b, 2, x, 2, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 10;
        Cherfs("U", 2, 1, a, 2, af, 2, ip, b, 1, x, 2, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        infot = 12;
        Cherfs("U", 2, 1, a, 2, af, 2, ip, b, 2, x, 1, r1, r2, w, r, info);
        chkxer("Cherfs", infot, nout, lerr, ok);
        //
        //        Checon
        //
        strncpy(srnamt, "Checon", srnamt_len);
        infot = 1;
        Checon("/", 0, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon", infot, nout, lerr, ok);
        infot = 2;
        Checon("U", -1, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon", infot, nout, lerr, ok);
        infot = 4;
        Checon("U", 2, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon", infot, nout, lerr, ok);
        infot = 6;
        Checon("U", 1, a, 1, ip, -anrm, rcond, w, info);
        chkxer("Checon", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "HR")) {
        //
        //        Test error exits of the routines that use factorization
        //        of a Hermitian indefinite matrix with rook
        //        (bounded Bunch-Kaufman) diagonal pivoting method.
        //
        //        Chetrf_rook
        //
        strncpy(srnamt, "Chetrf_rook", srnamt_len);
        infot = 1;
        Chetrf_rook("/", 0, a, 1, ip, w, 1, info);
        chkxer("Chetrf_rook", infot, nout, lerr, ok);
        infot = 2;
        Chetrf_rook("U", -1, a, 1, ip, w, 1, info);
        chkxer("Chetrf_rook", infot, nout, lerr, ok);
        infot = 4;
        Chetrf_rook("U", 2, a, 1, ip, w, 4, info);
        chkxer("Chetrf_rook", infot, nout, lerr, ok);
        infot = 7;
        Chetrf_rook("U", 0, a, 1, ip, w, 0, info);
        chkxer("Chetrf_rook", infot, nout, lerr, ok);
        infot = 7;
        Chetrf_rook("U", 0, a, 1, ip, w, -2, info);
        chkxer("Chetrf_rook", infot, nout, lerr, ok);
        //
        //        Chetf2_rook
        //
        strncpy(srnamt, "Chetf2_rook", srnamt_len);
        infot = 1;
        Chetf2_rook("/", 0, a, 1, ip, info);
        chkxer("Chetf2_rook", infot, nout, lerr, ok);
        infot = 2;
        Chetf2_rook("U", -1, a, 1, ip, info);
        chkxer("Chetf2_rook", infot, nout, lerr, ok);
        infot = 4;
        Chetf2_rook("U", 2, a, 1, ip, info);
        chkxer("Chetf2_rook", infot, nout, lerr, ok);
        //
        //        Chetri_rook
        //
        strncpy(srnamt, "Chetri_rook", srnamt_len);
        infot = 1;
        Chetri_rook("/", 0, a, 1, ip, w, info);
        chkxer("Chetri_rook", infot, nout, lerr, ok);
        infot = 2;
        Chetri_rook("U", -1, a, 1, ip, w, info);
        chkxer("Chetri_rook", infot, nout, lerr, ok);
        infot = 4;
        Chetri_rook("U", 2, a, 1, ip, w, info);
        chkxer("Chetri_rook", infot, nout, lerr, ok);
        //
        //        Chetrs_rook
        //
        strncpy(srnamt, "Chetrs_rook", srnamt_len);
        infot = 1;
        Chetrs_rook("/", 0, 0, a, 1, ip, b, 1, info);
        chkxer("Chetrs_rook", infot, nout, lerr, ok);
        infot = 2;
        Chetrs_rook("U", -1, 0, a, 1, ip, b, 1, info);
        chkxer("Chetrs_rook", infot, nout, lerr, ok);
        infot = 3;
        Chetrs_rook("U", 0, -1, a, 1, ip, b, 1, info);
        chkxer("Chetrs_rook", infot, nout, lerr, ok);
        infot = 5;
        Chetrs_rook("U", 2, 1, a, 1, ip, b, 2, info);
        chkxer("Chetrs_rook", infot, nout, lerr, ok);
        infot = 8;
        Chetrs_rook("U", 2, 1, a, 2, ip, b, 1, info);
        chkxer("Chetrs_rook", infot, nout, lerr, ok);
        //
        //        Checon_rook
        //
        strncpy(srnamt, "Checon_rook", srnamt_len);
        infot = 1;
        Checon_rook("/", 0, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon_rook", infot, nout, lerr, ok);
        infot = 2;
        Checon_rook("U", -1, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon_rook", infot, nout, lerr, ok);
        infot = 4;
        Checon_rook("U", 2, a, 1, ip, anrm, rcond, w, info);
        chkxer("Checon_rook", infot, nout, lerr, ok);
        infot = 6;
        Checon_rook("U", 1, a, 1, ip, -anrm, rcond, w, info);
        chkxer("Checon_rook", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "HK")) {
        //
        //        Test error exits of the routines that use factorization
        //        of a symmetric indefinite matrix with rook
        //        (bounded Bunch-Kaufman) pivoting with the new storage
        //        format for factors L ( or U) and D.
        //
        //        L (or U) is stored in A, diagonal of D is stored on the
        //        diagonal of A, subdiagonal of D is stored in a separate array E.
        //
        //        Chetrf_rk
        //
        strncpy(srnamt, "Chetrf_rk", srnamt_len);
        infot = 1;
        Chetrf_rk("/", 0, a, 1, e, ip, w, 1, info);
        chkxer("Chetrf_rk", infot, nout, lerr, ok);
        infot = 2;
        Chetrf_rk("U", -1, a, 1, e, ip, w, 1, info);
        chkxer("Chetrf_rk", infot, nout, lerr, ok);
        infot = 4;
        Chetrf_rk("U", 2, a, 1, e, ip, w, 4, info);
        chkxer("Chetrf_rk", infot, nout, lerr, ok);
        infot = 8;
        Chetrf_rk("U", 0, a, 1, e, ip, w, 0, info);
        chkxer("Chetrf_rk", infot, nout, lerr, ok);
        infot = 8;
        Chetrf_rk("U", 0, a, 1, e, ip, w, -2, info);
        chkxer("Chetrf_rk", infot, nout, lerr, ok);
        //
        //        Chetf2_rk
        //
        strncpy(srnamt, "Chetf2_rk", srnamt_len);
        infot = 1;
        Chetf2_rk("/", 0, a, 1, e, ip, info);
        chkxer("Chetf2_rk", infot, nout, lerr, ok);
        infot = 2;
        Chetf2_rk("U", -1, a, 1, e, ip, info);
        chkxer("Chetf2_rk", infot, nout, lerr, ok);
        infot = 4;
        Chetf2_rk("U", 2, a, 1, e, ip, info);
        chkxer("Chetf2_rk", infot, nout, lerr, ok);
        //
        //        Chetri_3
        //
        strncpy(srnamt, "Chetri_3", srnamt_len);
        infot = 1;
        Chetri_3("/", 0, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3", infot, nout, lerr, ok);
        infot = 2;
        Chetri_3("U", -1, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3", infot, nout, lerr, ok);
        infot = 4;
        Chetri_3("U", 2, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3", infot, nout, lerr, ok);
        infot = 8;
        Chetri_3("U", 0, a, 1, e, ip, w, 0, info);
        chkxer("Chetri_3", infot, nout, lerr, ok);
        infot = 8;
        Chetri_3("U", 0, a, 1, e, ip, w, -2, info);
        chkxer("Chetri_3", infot, nout, lerr, ok);
        //
        //        Chetri_3x
        //
        strncpy(srnamt, "Chetri_3x", srnamt_len);
        infot = 1;
        Chetri_3x("/", 0, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3x", infot, nout, lerr, ok);
        infot = 2;
        Chetri_3x("U", -1, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3x", infot, nout, lerr, ok);
        infot = 4;
        Chetri_3x("U", 2, a, 1, e, ip, w, 1, info);
        chkxer("Chetri_3x", infot, nout, lerr, ok);
        //
        //        Chetrs_3
        //
        strncpy(srnamt, "Chetrs_3", srnamt_len);
        infot = 1;
        Chetrs_3("/", 0, 0, a, 1, e, ip, b, 1, info);
        chkxer("Chetrs_3", infot, nout, lerr, ok);
        infot = 2;
        Chetrs_3("U", -1, 0, a, 1, e, ip, b, 1, info);
        chkxer("Chetrs_3", infot, nout, lerr, ok);
        infot = 3;
        Chetrs_3("U", 0, -1, a, 1, e, ip, b, 1, info);
        chkxer("Chetrs_3", infot, nout, lerr, ok);
        infot = 5;
        Chetrs_3("U", 2, 1, a, 1, e, ip, b, 2, info);
        chkxer("Chetrs_3", infot, nout, lerr, ok);
        infot = 9;
        Chetrs_3("U", 2, 1, a, 2, e, ip, b, 1, info);
        chkxer("Chetrs_3", infot, nout, lerr, ok);
        //
        //        Checon_3
        //
        strncpy(srnamt, "Checon_3", srnamt_len);
        infot = 1;
        Checon_3("/", 0, a, 1, e, ip, anrm, rcond, w, info);
        chkxer("Checon_3", infot, nout, lerr, ok);
        infot = 2;
        Checon_3("U", -1, a, 1, e, ip, anrm, rcond, w, info);
        chkxer("Checon_3", infot, nout, lerr, ok);
        infot = 4;
        Checon_3("U", 2, a, 1, e, ip, anrm, rcond, w, info);
        chkxer("Checon_3", infot, nout, lerr, ok);
        infot = 7;
        Checon_3("U", 1, a, 1, e, ip, -1.0, rcond, w, info);
        chkxer("Checon_3", infot, nout, lerr, ok);
        //
        //        Test error exits of the routines that use factorization
        //        of a Hermitian indefinite matrix with Aasen's algorithm.
        //
    } else if (Mlsamen(2, c2, "HA")) {
        //
        //        Chetrf_aa
        //
        strncpy(srnamt, "Chetrf_aa", srnamt_len);
        infot = 1;
        Chetrf_aa("/", 0, a, 1, ip, w, 1, info);
        chkxer("Chetrf_aa", infot, nout, lerr, ok);
        infot = 2;
        Chetrf_aa("U", -1, a, 1, ip, w, 1, info);
        chkxer("Chetrf_aa", infot, nout, lerr, ok);
        infot = 4;
        Chetrf_aa("U", 2, a, 1, ip, w, 4, info);
        chkxer("Chetrf_aa", infot, nout, lerr, ok);
        infot = 7;
        Chetrf_aa("U", 0, a, 1, ip, w, 0, info);
        chkxer("Chetrf_aa", infot, nout, lerr, ok);
        infot = 7;
        Chetrf_aa("U", 0, a, 1, ip, w, -2, info);
        chkxer("Chetrf_aa", infot, nout, lerr, ok);
        //
        //        Chetrs_aa
        //
        strncpy(srnamt, "Chetrs_aa", srnamt_len);
        infot = 1;
        Chetrs_aa("/", 0, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 2;
        Chetrs_aa("U", -1, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 3;
        Chetrs_aa("U", 0, -1, a, 1, ip, b, 1, w, 1, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 5;
        Chetrs_aa("U", 2, 1, a, 1, ip, b, 2, w, 1, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 8;
        Chetrs_aa("U", 2, 1, a, 2, ip, b, 1, w, 1, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 10;
        Chetrs_aa("U", 0, 1, a, 1, ip, b, 1, w, 0, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        infot = 10;
        Chetrs_aa("U", 0, 1, a, 1, ip, b, 1, w, -2, info);
        chkxer("Chetrs_aa", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "S2")) {
        //
        //        Test error exits of the routines that use factorization
        //        of a symmetric indefinite matrix with Aasen's algorithm.
        //
        //        Chetrf_aa_2stage
        //
        strncpy(srnamt, "Chetrf_aa_2stage", srnamt_len);
        infot = 1;
        Chetrf_aa_2stage("/", 0, a, 1, a, 1, ip, ip, w, 1, info);
        chkxer("Chetrf_aa_2stage", infot, nout, lerr, ok);
        infot = 2;
        Chetrf_aa_2stage("U", -1, a, 1, a, 1, ip, ip, w, 1, info);
        chkxer("Chetrf_aa_2stage", infot, nout, lerr, ok);
        infot = 4;
        Chetrf_aa_2stage("U", 2, a, 1, a, 2, ip, ip, w, 1, info);
        chkxer("Chetrf_aa_2stage", infot, nout, lerr, ok);
        infot = 6;
        Chetrf_aa_2stage("U", 2, a, 2, a, 1, ip, ip, w, 1, info);
        chkxer("Chetrf_aa_2stage", infot, nout, lerr, ok);
        infot = 10;
        Chetrf_aa_2stage("U", 2, a, 2, a, 8, ip, ip, w, 0, info);
        chkxer("Chetrf_aa_2stage", infot, nout, lerr, ok);
        //
        //        Chetrs_aa_2stage
        //
        strncpy(srnamt, "Chetrs_aa_2stage", srnamt_len);
        infot = 1;
        Chetrs_aa_2stage("/", 0, 0, a, 1, a, 1, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_2stage", infot, nout, lerr, ok);
        infot = 2;
        Chetrs_aa_2stage("U", -1, 0, a, 1, a, 1, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_2stage", infot, nout, lerr, ok);
        infot = 3;
        Chetrs_aa_2stage("U", 0, -1, a, 1, a, 1, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_2stage", infot, nout, lerr, ok);
        infot = 5;
        Chetrs_aa_2stage("U", 2, 1, a, 1, a, 1, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_2stage", infot, nout, lerr, ok);
        infot = 7;
        Chetrs_aa_2stage("U", 2, 1, a, 2, a, 1, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_2stage", infot, nout, lerr, ok);
        infot = 11;
        Chetrs_aa_2stage("U", 2, 1, a, 2, a, 8, ip, ip, b, 1, info);
        chkxer("Chetrs_aa_STAGE", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "HP")) {
        //
        //        Test error exits of the routines that use factorization
        //        of a Hermitian indefinite packed matrix with patrial
        //        (Bunch-Kaufman) diagonal pivoting method.
        //
        //        Chptrf
        //
        strncpy(srnamt, "Chptrf", srnamt_len);
        infot = 1;
        Chptrf("/", 0, a, ip, info);
        chkxer("Chptrf", infot, nout, lerr, ok);
        infot = 2;
        Chptrf("U", -1, a, ip, info);
        chkxer("Chptrf", infot, nout, lerr, ok);
        //
        //        Chptri
        //
        strncpy(srnamt, "Chptri", srnamt_len);
        infot = 1;
        Chptri("/", 0, a, ip, w, info);
        chkxer("Chptri", infot, nout, lerr, ok);
        infot = 2;
        Chptri("U", -1, a, ip, w, info);
        chkxer("Chptri", infot, nout, lerr, ok);
        //
        //        Chptrs
        //
        strncpy(srnamt, "Chptrs", srnamt_len);
        infot = 1;
        Chptrs("/", 0, 0, a, ip, b, 1, info);
        chkxer("Chptrs", infot, nout, lerr, ok);
        infot = 2;
        Chptrs("U", -1, 0, a, ip, b, 1, info);
        chkxer("Chptrs", infot, nout, lerr, ok);
        infot = 3;
        Chptrs("U", 0, -1, a, ip, b, 1, info);
        chkxer("Chptrs", infot, nout, lerr, ok);
        infot = 7;
        Chptrs("U", 2, 1, a, ip, b, 1, info);
        chkxer("Chptrs", infot, nout, lerr, ok);
        //
        //        Chprfs
        //
        strncpy(srnamt, "Chprfs", srnamt_len);
        infot = 1;
        Chprfs("/", 0, 0, a, af, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Chprfs", infot, nout, lerr, ok);
        infot = 2;
        Chprfs("U", -1, 0, a, af, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Chprfs", infot, nout, lerr, ok);
        infot = 3;
        Chprfs("U", 0, -1, a, af, ip, b, 1, x, 1, r1, r2, w, r, info);
        chkxer("Chprfs", infot, nout, lerr, ok);
        infot = 8;
        Chprfs("U", 2, 1, a, af, ip, b, 1, x, 2, r1, r2, w, r, info);
        chkxer("Chprfs", infot, nout, lerr, ok);
        infot = 10;
        Chprfs("U", 2, 1, a, af, ip, b, 2, x, 1, r1, r2, w, r, info);
        chkxer("Chprfs", infot, nout, lerr, ok);
        //
        //        Chpcon
        //
        strncpy(srnamt, "Chpcon", srnamt_len);
        infot = 1;
        Chpcon("/", 0, a, ip, anrm, rcond, w, info);
        chkxer("Chpcon", infot, nout, lerr, ok);
        infot = 2;
        Chpcon("U", -1, a, ip, anrm, rcond, w, info);
        chkxer("Chpcon", infot, nout, lerr, ok);
        infot = 5;
        Chpcon("U", 1, a, ip, -anrm, rcond, w, info);
        chkxer("Chpcon", infot, nout, lerr, ok);
    }
    //
    //     Print a summary line.
    //
    Alaesm(path, ok, nout);
    //
    //     End of Cerrhe
    //
}
