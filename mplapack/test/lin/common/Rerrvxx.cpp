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

void Rerrvx(common &cmn, const char *path, INTEGER const nunit) {
    common_write write(cmn);
    // COMMON infoc
    INTEGER &infot = cmn.infot;
    INTEGER &nout = cmn.nout;
    bool &ok = cmn.ok;
    bool &lerr = cmn.lerr;
    // COMMON srnamc
    str<32> &srnamt = cmn.srnamt;
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
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    nout = nunit;
    write(nout, star);
    str<2> c2 = path[(2 - 1) + (3 - 1) * ldpath];
    //
    //     Set the variables to innocuous values.
    //
    INTEGER j = 0;
    const INTEGER nmax = 4;
    INTEGER i = 0;
    arr_2d<nmax, nmax, REAL> a(fill0);
    arr_2d<nmax, nmax, REAL> af(fill0);
    arr_1d<nmax, REAL> b(fill0);
    arr_1d<nmax, REAL> e(fill0);
    arr_1d<nmax, REAL> r1(fill0);
    arr_1d<nmax, REAL> r2(fill0);
    arr_1d<2 * nmax, REAL> w(fill0);
    arr_1d<nmax, REAL> x(fill0);
    arr_1d<nmax, REAL> c(fill0);
    arr_1d<nmax, REAL> r(fill0);
    arr_1d<nmax, int> ip(fill0);
    for (j = 1; j <= nmax; j = j + 1) {
        for (i = 1; i <= nmax; i = i + 1) {
            a[(i - 1) + (j - 1) * lda] = 1.0 / (i + j).real();
            af[(i - 1) + (j - 1) * ldaf] = 1.0 / (i + j).real();
        }
        b[j - 1] = 0.e+0;
        e[j - 1] = 0.e+0;
        r1[j - 1] = 0.e+0;
        r2[j - 1] = 0.e+0;
        w[j - 1] = 0.e+0;
        x[j - 1] = 0.e+0;
        c[j - 1] = 0.e+0;
        r[j - 1] = 0.e+0;
        ip[j - 1] = j;
    }
    char eq = " ";
    ok = true;
    //
    INTEGER info = 0;
    REAL rcond = 0.0;
    arr_1d<nmax, int> iw(fill0);
    INTEGER n_err_bnds = 0;
    INTEGER nparams = 0;
    REAL rpvgrw = 0.0;
    REAL berr = 0.0;
    arr_2d<nmax, 3, REAL> err_bnds_n(fill0);
    arr_2d<nmax, 3, REAL> err_bnds_c(fill0);
    arr_1d<1, REAL> params(fill0);
    const float one = 1.0;
    if (Mlsamen(2, c2, "GE")) {
        //
        //        Rgesv
        //
        srnamt = "Rgesv ";
        infot = 1;
        Rgesv(-1, 0, a, 1, ip, b, 1, info);
        chkxer("Rgesv ", infot, nout, lerr, ok);
        infot = 2;
        Rgesv(0, -1, a, 1, ip, b, 1, info);
        chkxer("Rgesv ", infot, nout, lerr, ok);
        infot = 4;
        Rgesv(2, 1, a, 1, ip, b, 2, info);
        chkxer("Rgesv ", infot, nout, lerr, ok);
        infot = 7;
        Rgesv(2, 1, a, 2, ip, b, 1, info);
        chkxer("Rgesv ", infot, nout, lerr, ok);
        //
        //        Rgesvx
        //
        srnamt = "Rgesvx";
        infot = 1;
        Rgesvx("/", "N", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 2;
        Rgesvx("N", "/", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 3;
        Rgesvx("N", "N", -1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 4;
        Rgesvx("N", "N", 0, -1, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 6;
        Rgesvx("N", "N", 2, 1, a, 1, af, 2, ip, eq, r, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 8;
        Rgesvx("N", "N", 2, 1, a, 2, af, 1, ip, eq, r, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 10;
        eq = "/";
        Rgesvx("F", "N", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 11;
        eq = "R";
        Rgesvx("F", "N", 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 12;
        eq = "C";
        Rgesvx("F", "N", 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 14;
        Rgesvx("N", "N", 2, 1, a, 2, af, 2, ip, eq, r, c, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        infot = 16;
        Rgesvx("N", "N", 2, 1, a, 2, af, 2, ip, eq, r, c, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgesvx", infot, nout, lerr, ok);
        //
        //        Rgesvxx
        //
        n_err_bnds = 3;
        nparams = 1;
        srnamt = "Rgesvxx";
        infot = 1;
        Rgesvxx("/", "N", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 2;
        Rgesvxx("N", "/", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 3;
        Rgesvxx("N", "N", -1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 4;
        Rgesvxx("N", "N", 0, -1, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 6;
        Rgesvxx("N", "N", 2, 1, a, 1, af, 2, ip, eq, r, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 8;
        Rgesvxx("N", "N", 2, 1, a, 2, af, 1, ip, eq, r, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 10;
        eq = "/";
        Rgesvxx("F", "N", 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 11;
        eq = "R";
        Rgesvxx("F", "N", 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 12;
        eq = "C";
        Rgesvxx("F", "N", 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 14;
        Rgesvxx("N", "N", 2, 1, a, 2, af, 2, ip, eq, r, c, b, 1, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        infot = 16;
        Rgesvxx("N", "N", 2, 1, a, 2, af, 2, ip, eq, r, c, b, 2, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgesvxx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "GB")) {
        //
        //        Rgbsv
        //
        srnamt = "Rgbsv ";
        infot = 1;
        Rgbsv(-1, 0, 0, 0, a, 1, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        infot = 2;
        Rgbsv(1, -1, 0, 0, a, 1, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        infot = 3;
        Rgbsv(1, 0, -1, 0, a, 1, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        infot = 4;
        Rgbsv(0, 0, 0, -1, a, 1, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        infot = 6;
        Rgbsv(1, 1, 1, 0, a, 3, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        infot = 9;
        Rgbsv(2, 0, 0, 0, a, 1, ip, b, 1, info);
        chkxer("Rgbsv ", infot, nout, lerr, ok);
        //
        //        Rgbsvx
        //
        srnamt = "Rgbsvx";
        infot = 1;
        Rgbsvx("/", "N", 0, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 2;
        Rgbsvx("N", "/", 0, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 3;
        Rgbsvx("N", "N", -1, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 4;
        Rgbsvx("N", "N", 1, -1, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 5;
        Rgbsvx("N", "N", 1, 0, -1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 6;
        Rgbsvx("N", "N", 0, 0, 0, -1, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 8;
        Rgbsvx("N", "N", 1, 1, 1, 0, a, 2, af, 4, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 10;
        Rgbsvx("N", "N", 1, 1, 1, 0, a, 3, af, 3, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 12;
        eq = "/";
        Rgbsvx("F", "N", 0, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 13;
        eq = "R";
        Rgbsvx("F", "N", 1, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 14;
        eq = "C";
        Rgbsvx("F", "N", 1, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 16;
        Rgbsvx("N", "N", 2, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        infot = 18;
        Rgbsvx("N", "N", 2, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgbsvx", infot, nout, lerr, ok);
        //
        //        Rgbsvxx
        //
        n_err_bnds = 3;
        nparams = 1;
        srnamt = "Rgbsvxx";
        infot = 1;
        Rgbsvxx("/", "N", 0, 0, 0, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 2;
        Rgbsvxx("N", "/", 0, 1, 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 3;
        Rgbsvxx("N", "N", -1, 1, 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 4;
        Rgbsvxx("N", "N", 2, -1, 1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 5;
        Rgbsvxx("N", "N", 2, 1, -1, 0, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 6;
        Rgbsvxx("N", "N", 0, 1, 1, -1, a, 1, af, 1, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 8;
        Rgbsvxx("N", "N", 2, 1, 1, 1, a, 2, af, 2, ip, eq, r, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 10;
        Rgbsvxx("N", "N", 2, 1, 1, 1, a, 3, af, 3, ip, eq, r, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 12;
        eq = "/";
        Rgbsvxx("F", "N", 0, 1, 1, 0, a, 3, af, 4, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 13;
        eq = "R";
        Rgbsvxx("F", "N", 1, 1, 1, 0, a, 3, af, 4, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 14;
        eq = "C";
        Rgbsvxx("F", "N", 1, 1, 1, 0, a, 3, af, 4, ip, eq, r, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 15;
        Rgbsvxx("N", "N", 2, 1, 1, 1, a, 3, af, 4, ip, eq, r, c, b, 1, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        infot = 16;
        Rgbsvxx("N", "N", 2, 1, 1, 1, a, 3, af, 4, ip, eq, r, c, b, 2, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rgbsvxx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "GT")) {
        //
        //        Rgtsv
        //
        srnamt = "Rgtsv ";
        infot = 1;
        Rgtsv(-1, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], b, 1, info);
        chkxer("Rgtsv ", infot, nout, lerr, ok);
        infot = 2;
        Rgtsv(0, -1, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], b, 1, info);
        chkxer("Rgtsv ", infot, nout, lerr, ok);
        infot = 7;
        Rgtsv(2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], b, 1, info);
        chkxer("Rgtsv ", infot, nout, lerr, ok);
        //
        //        Rgtsvx
        //
        srnamt = "Rgtsvx";
        infot = 1;
        Rgtsvx("/", "N", 0, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        infot = 2;
        Rgtsvx("N", "/", 0, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        infot = 3;
        Rgtsvx("N", "N", -1, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        infot = 4;
        Rgtsvx("N", "N", 0, -1, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        infot = 14;
        Rgtsvx("N", "N", 2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        infot = 16;
        Rgtsvx("N", "N", 2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], &a[(3 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], af[(3 - 1) * ldaf], af[(4 - 1) * ldaf], ip, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rgtsvx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "PO")) {
        //
        //        Rposv
        //
        srnamt = "Rposv ";
        infot = 1;
        Rposv("/", 0, 0, a, 1, b, 1, info);
        chkxer("Rposv ", infot, nout, lerr, ok);
        infot = 2;
        Rposv("U", -1, 0, a, 1, b, 1, info);
        chkxer("Rposv ", infot, nout, lerr, ok);
        infot = 3;
        Rposv("U", 0, -1, a, 1, b, 1, info);
        chkxer("Rposv ", infot, nout, lerr, ok);
        infot = 5;
        Rposv("U", 2, 0, a, 1, b, 2, info);
        chkxer("Rposv ", infot, nout, lerr, ok);
        infot = 7;
        Rposv("U", 2, 0, a, 2, b, 1, info);
        chkxer("Rposv ", infot, nout, lerr, ok);
        //
        //        Rposvx
        //
        srnamt = "Rposvx";
        infot = 1;
        Rposvx("/", "U", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 2;
        Rposvx("N", "/", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 3;
        Rposvx("N", "U", -1, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 4;
        Rposvx("N", "U", 0, -1, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 6;
        Rposvx("N", "U", 2, 0, a, 1, af, 2, eq, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 8;
        Rposvx("N", "U", 2, 0, a, 2, af, 1, eq, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 9;
        eq = "/";
        Rposvx("F", "U", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 10;
        eq = "Y";
        Rposvx("F", "U", 1, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 12;
        Rposvx("N", "U", 2, 0, a, 2, af, 2, eq, c, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        infot = 14;
        Rposvx("N", "U", 2, 0, a, 2, af, 2, eq, c, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rposvx", infot, nout, lerr, ok);
        //
        //        Rposvxx
        //
        n_err_bnds = 3;
        nparams = 1;
        srnamt = "Rposvxx";
        infot = 1;
        Rposvxx("/", "U", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 2;
        Rposvxx("N", "/", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 3;
        Rposvxx("N", "U", -1, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 4;
        Rposvxx("N", "U", 0, -1, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 6;
        Rposvxx("N", "U", 2, 0, a, 1, af, 2, eq, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 8;
        Rposvxx("N", "U", 2, 0, a, 2, af, 1, eq, c, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 9;
        eq = "/";
        Rposvxx("F", "U", 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 10;
        eq = "Y";
        Rposvxx("F", "U", 1, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 12;
        Rposvxx("N", "U", 2, 0, a, 2, af, 2, eq, c, b, 1, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        infot = 14;
        Rposvxx("N", "U", 2, 0, a, 2, af, 2, eq, c, b, 2, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rposvxx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "PP")) {
        //
        //        Rppsv
        //
        srnamt = "Rppsv ";
        infot = 1;
        Rppsv("/", 0, 0, a, b, 1, info);
        chkxer("Rppsv ", infot, nout, lerr, ok);
        infot = 2;
        Rppsv("U", -1, 0, a, b, 1, info);
        chkxer("Rppsv ", infot, nout, lerr, ok);
        infot = 3;
        Rppsv("U", 0, -1, a, b, 1, info);
        chkxer("Rppsv ", infot, nout, lerr, ok);
        infot = 6;
        Rppsv("U", 2, 0, a, b, 1, info);
        chkxer("Rppsv ", infot, nout, lerr, ok);
        //
        //        Rppsvx
        //
        srnamt = "Rppsvx";
        infot = 1;
        Rppsvx("/", "U", 0, 0, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 2;
        Rppsvx("N", "/", 0, 0, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 3;
        Rppsvx("N", "U", -1, 0, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 4;
        Rppsvx("N", "U", 0, -1, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 7;
        eq = "/";
        Rppsvx("F", "U", 0, 0, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 8;
        eq = "Y";
        Rppsvx("F", "U", 1, 0, a, af, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 10;
        Rppsvx("N", "U", 2, 0, a, af, eq, c, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        infot = 12;
        Rppsvx("N", "U", 2, 0, a, af, eq, c, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rppsvx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "PB")) {
        //
        //        Rpbsv
        //
        srnamt = "Rpbsv ";
        infot = 1;
        Rpbsv("/", 0, 0, 0, a, 1, b, 1, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        infot = 2;
        Rpbsv("U", -1, 0, 0, a, 1, b, 1, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        infot = 3;
        Rpbsv("U", 1, -1, 0, a, 1, b, 1, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        infot = 4;
        Rpbsv("U", 0, 0, -1, a, 1, b, 1, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        infot = 6;
        Rpbsv("U", 1, 1, 0, a, 1, b, 2, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        infot = 8;
        Rpbsv("U", 2, 0, 0, a, 1, b, 1, info);
        chkxer("Rpbsv ", infot, nout, lerr, ok);
        //
        //        Rpbsvx
        //
        srnamt = "Rpbsvx";
        infot = 1;
        Rpbsvx("/", "U", 0, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 2;
        Rpbsvx("N", "/", 0, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 3;
        Rpbsvx("N", "U", -1, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 4;
        Rpbsvx("N", "U", 1, -1, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 5;
        Rpbsvx("N", "U", 0, 0, -1, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 7;
        Rpbsvx("N", "U", 1, 1, 0, a, 1, af, 2, eq, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 9;
        Rpbsvx("N", "U", 1, 1, 0, a, 2, af, 1, eq, c, b, 2, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 10;
        eq = "/";
        Rpbsvx("F", "U", 0, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 11;
        eq = "Y";
        Rpbsvx("F", "U", 1, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 13;
        Rpbsvx("N", "U", 2, 0, 0, a, 1, af, 1, eq, c, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        infot = 15;
        Rpbsvx("N", "U", 2, 0, 0, a, 1, af, 1, eq, c, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rpbsvx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "PT")) {
        //
        //        Rptsv
        //
        srnamt = "Rptsv ";
        infot = 1;
        Rptsv(-1, 0, &a[(1 - 1)], &a[(2 - 1) * lda], b, 1, info);
        chkxer("Rptsv ", infot, nout, lerr, ok);
        infot = 2;
        Rptsv(0, -1, &a[(1 - 1)], &a[(2 - 1) * lda], b, 1, info);
        chkxer("Rptsv ", infot, nout, lerr, ok);
        infot = 6;
        Rptsv(2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], b, 1, info);
        chkxer("Rptsv ", infot, nout, lerr, ok);
        //
        //        Rptsvx
        //
        srnamt = "Rptsvx";
        infot = 1;
        Rptsvx("/", 0, 0, &a[(1 - 1)], &a[(2 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], b, 1, x, 1, rcond, r1, r2, w, info);
        chkxer("Rptsvx", infot, nout, lerr, ok);
        infot = 2;
        Rptsvx("N", -1, 0, &a[(1 - 1)], &a[(2 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], b, 1, x, 1, rcond, r1, r2, w, info);
        chkxer("Rptsvx", infot, nout, lerr, ok);
        infot = 3;
        Rptsvx("N", 0, -1, &a[(1 - 1)], &a[(2 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], b, 1, x, 1, rcond, r1, r2, w, info);
        chkxer("Rptsvx", infot, nout, lerr, ok);
        infot = 9;
        Rptsvx("N", 2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], b, 1, x, 2, rcond, r1, r2, w, info);
        chkxer("Rptsvx", infot, nout, lerr, ok);
        infot = 11;
        Rptsvx("N", 2, 0, &a[(1 - 1)], &a[(2 - 1) * lda], af[(1 - 1)], af[(2 - 1) * ldaf], b, 2, x, 1, rcond, r1, r2, w, info);
        chkxer("Rptsvx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "SY")) {
        //
        //        Rsysv
        //
        srnamt = "Rsysv ";
        infot = 1;
        Rsysv("/", 0, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        infot = 2;
        Rsysv("U", -1, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        infot = 3;
        Rsysv("U", 0, -1, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        infot = 5;
        Rsysv("U", 2, 0, a, 1, ip, b, 2, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 8;
        Rsysv("U", 2, 0, a, 2, ip, b, 1, w, 1, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        infot = 10;
        Rsysv("U", 0, 0, a, 1, ip, b, 1, w, 0, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        infot = 10;
        Rsysv("U", 0, 0, a, 1, ip, b, 1, w, -2, info);
        chkxer("Rsysv ", infot, nout, lerr, ok);
        //
        //        Rsysvx
        //
        srnamt = "Rsysvx";
        infot = 1;
        Rsysvx("/", "U", 0, 0, a, 1, af, 1, ip, b, 1, x, 1, rcond, r1, r2, w, 1, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 2;
        Rsysvx("N", "/", 0, 0, a, 1, af, 1, ip, b, 1, x, 1, rcond, r1, r2, w, 1, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 3;
        Rsysvx("N", "U", -1, 0, a, 1, af, 1, ip, b, 1, x, 1, rcond, r1, r2, w, 1, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 4;
        Rsysvx("N", "U", 0, -1, a, 1, af, 1, ip, b, 1, x, 1, rcond, r1, r2, w, 1, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 6;
        Rsysvx("N", "U", 2, 0, a, 1, af, 2, ip, b, 2, x, 2, rcond, r1, r2, w, 4, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 8;
        Rsysvx("N", "U", 2, 0, a, 2, af, 1, ip, b, 2, x, 2, rcond, r1, r2, w, 4, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 11;
        Rsysvx("N", "U", 2, 0, a, 2, af, 2, ip, b, 1, x, 2, rcond, r1, r2, w, 4, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 13;
        Rsysvx("N", "U", 2, 0, a, 2, af, 2, ip, b, 2, x, 1, rcond, r1, r2, w, 4, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        infot = 18;
        Rsysvx("N", "U", 2, 0, a, 2, af, 2, ip, b, 2, x, 2, rcond, r1, r2, w, 3, iw, info);
        chkxer("Rsysvx", infot, nout, lerr, ok);
        //
        //        Rsysvxx
        //
        n_err_bnds = 3;
        nparams = 1;
        srnamt = "Rsysvxx";
        infot = 1;
        eq = "N";
        Rsysvxx("/", "U", 0, 0, a, 1, af, 1, ip, eq, r, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 2;
        Rsysvxx("N", "/", 0, 0, a, 1, af, 1, ip, eq, r, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 3;
        Rsysvxx("N", "U", -1, 0, a, 1, af, 1, ip, eq, r, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 4;
        eq = "/";
        Rsysvxx("N", "U", 0, -1, a, 1, af, 1, ip, eq, r, b, 1, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        eq = "Y";
        infot = 6;
        Rsysvxx("N", "U", 2, 0, a, 1, af, 2, ip, eq, r, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 8;
        Rsysvxx("N", "U", 2, 0, a, 2, af, 1, ip, eq, r, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 10;
        Rsysvxx("F", "U", 2, 0, a, 2, af, 2, ip, "A", r, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 11;
        eq = "Y";
        Rsysvxx("F", "U", 2, 0, a, 2, af, 2, ip, eq, r, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 11;
        eq = "Y";
        r[1 - 1] = -one;
        Rsysvxx("F", "U", 2, 0, a, 2, af, 2, ip, eq, r, b, 2, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 13;
        eq = "N";
        Rsysvxx("N", "U", 2, 0, a, 2, af, 2, ip, eq, r, b, 1, x, 2, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        infot = 15;
        Rsysvxx("N", "U", 2, 0, a, 2, af, 2, ip, eq, r, b, 2, x, 1, rcond, rpvgrw, berr, n_err_bnds, err_bnds_n, err_bnds_c, nparams, params, w, iw, info);
        chkxer("Rsysvxx", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "SR")) {
        //
        //        Rsysv_rook
        //
        srnamt = "Rsysv_rook";
        infot = 1;
        Rsysv_rook("/", 0, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 2;
        Rsysv_rook("U", -1, 0, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 3;
        Rsysv_rook("U", 0, -1, a, 1, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 5;
        Rsysv_rook("U", 2, 0, a, 1, ip, b, 2, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 8;
        Rsysv_rook("U", 2, 0, a, 2, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 10;
        Rsysv_rook("U", 0, 0, a, 1, ip, b, 1, w, 0, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        infot = 10;
        Rsysv_rook("U", 0, 0, a, 1, ip, b, 1, w, -2, info);
        chkxer("Rsysv_rook", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "SK")) {
        //
        //        Rsysv_rk
        //
        //        Test error exits of the driver that uses factorization
        //        of a symmetric indefinite matrix with rook
        //        (bounded Bunch-Kaufman) pivoting with the new storage
        //        format for factors L ( or U) and D.
        //
        //        L (or U) is stored in A, diagonal of D is stored on the
        //        diagonal of A, subdiagonal of D is stored in a separate array E.
        //
        srnamt = "Rsysv_rk";
        infot = 1;
        Rsysv_rk("/", 0, 0, a, 1, e, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 2;
        Rsysv_rk("U", -1, 0, a, 1, e, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 3;
        Rsysv_rk("U", 0, -1, a, 1, e, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 5;
        Rsysv_rk("U", 2, 0, a, 1, e, ip, b, 2, w, 1, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 9;
        Rsysv_rk("U", 2, 0, a, 2, e, ip, b, 1, w, 1, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 11;
        Rsysv_rk("U", 0, 0, a, 1, e, ip, b, 1, w, 0, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        infot = 11;
        Rsysv_rk("U", 0, 0, a, 1, e, ip, b, 1, w, -2, info);
        chkxer("Rsysv_rk", infot, nout, lerr, ok);
        //
    } else if (Mlsamen(2, c2, "SP")) {
        //
        //        Rspsv
        //
        srnamt = "Rspsv ";
        infot = 1;
        Rspsv("/", 0, 0, a, ip, b, 1, info);
        chkxer("Rspsv ", infot, nout, lerr, ok);
        infot = 2;
        Rspsv("U", -1, 0, a, ip, b, 1, info);
        chkxer("Rspsv ", infot, nout, lerr, ok);
        infot = 3;
        Rspsv("U", 0, -1, a, ip, b, 1, info);
        chkxer("Rspsv ", infot, nout, lerr, ok);
        infot = 7;
        Rspsv("U", 2, 0, a, ip, b, 1, info);
        chkxer("Rspsv ", infot, nout, lerr, ok);
        //
        //        Rspsvx
        //
        srnamt = "Rspsvx";
        infot = 1;
        Rspsvx("/", "U", 0, 0, a, af, ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
        infot = 2;
        Rspsvx("N", "/", 0, 0, a, af, ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
        infot = 3;
        Rspsvx("N", "U", -1, 0, a, af, ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
        infot = 4;
        Rspsvx("N", "U", 0, -1, a, af, ip, b, 1, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
        infot = 9;
        Rspsvx("N", "U", 2, 0, a, af, ip, b, 1, x, 2, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
        infot = 11;
        Rspsvx("N", "U", 2, 0, a, af, ip, b, 2, x, 1, rcond, r1, r2, w, iw, info);
        chkxer("Rspsvx", infot, nout, lerr, ok);
    }
    //
    //     Print a summary line.
    //
    if (ok) {
        write(nout, "(1x,a3,' drivers passed the tests of the error exits')"), path;
    } else {
        write(nout, "(' *** ',a3,' drivers failed the tests of the error ','exits ***')"), path;
    }
    //
    //     End of Rerrvx
    //
}
