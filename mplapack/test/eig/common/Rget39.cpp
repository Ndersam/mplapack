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
#include <mplapack_eig.h>

#include <mplapack_debug.h>

void Rget39(REAL &rmax, INTEGER &lmax, INTEGER &ninfo, INTEGER &knt) {
    // SAVE

    INTEGER idim[] = {4, 5, 5, 5, 5, 5};
    INTEGER ival[150] = {3, 0, 0, 0, 0, 1, 1, -1, 0, 0, 3, 2, 1, 0, 0, 4, 3, 2, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 3, 3, 4, 0, 0, 4, 2, 2, 3, 0, 1, 1, 1, 1, 5, 1, 0, 0, 0, 0, 2, 4, -2, 0, 0, 3, 3, 4, 0, 0, 4, 2, 2, 3, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 1, -1, 0, 0, 9, 8, 1, 0, 0, 4, 9, 1, 2, -1, 2, 2, 2, 2, 2, 9, 0, 0, 0, 0, 6, 4, 0, 0, 0, 3, 2, 1, 1, 0, 5, 1, -1, 1, 0, 2, 2, 2, 2, 2, 4, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 4, 4, 0, 0, 2, 4, 2, 2, -1, 2, 2, 2, 2, 2};
    INTEGER ldval1 = 5;
    INTEGER ldval2 = 25;
    //
    //     Get machine parameters
    //
    REAL eps = Rlamch("P");
    REAL smlnum = Rlamch("S");
    const REAL one = 1.0;
    REAL bignum = one / smlnum;
    //
    //     Set up test case parameters
    //
    REAL vm1[5];
    vm1[1 - 1] = one;
    vm1[2 - 1] = sqrt(smlnum);
    vm1[3 - 1] = sqrt(vm1[2 - 1]);
    vm1[4 - 1] = sqrt(bignum);
    vm1[5 - 1] = sqrt(vm1[4 - 1]);
    //
    REAL vm2[5];
    vm2[1 - 1] = one;
    vm2[2 - 1] = sqrt(smlnum);
    vm2[3 - 1] = sqrt(vm2[2 - 1]);
    vm2[4 - 1] = sqrt(bignum);
    vm2[5 - 1] = sqrt(vm2[4 - 1]);
    //
    REAL vm3[5];
    vm3[1 - 1] = one;
    vm3[2 - 1] = sqrt(smlnum);
    vm3[3 - 1] = sqrt(vm3[2 - 1]);
    vm3[4 - 1] = sqrt(bignum);
    vm3[5 - 1] = sqrt(vm3[4 - 1]);
    //
    REAL vm4[5];
    vm4[1 - 1] = one;
    vm4[2 - 1] = sqrt(smlnum);
    vm4[3 - 1] = sqrt(vm4[2 - 1]);
    vm4[4 - 1] = sqrt(bignum);
    vm4[5 - 1] = sqrt(vm4[4 - 1]);
    //
    REAL vm5[3];
    vm5[1 - 1] = one;
    vm5[2 - 1] = eps;
    vm5[3 - 1] = sqrt(smlnum);
    //
    //     Initialization
    //
    knt = 0;
    const REAL zero = 0.0;
    rmax = zero;
    ninfo = 0;
    smlnum = smlnum / eps;
    //
    //     Begin test loop
    //
    INTEGER ivm5 = 0;
    INTEGER ivm4 = 0;
    INTEGER ivm3 = 0;
    INTEGER ivm2 = 0;
    INTEGER ivm1 = 0;
    INTEGER ndim = 0;
    INTEGER n = 0;
    INTEGER i = 0;
    INTEGER j = 0;
    const INTEGER ldt = 10;
    REAL t[ldt * ldt];
    REAL w = 0.0;
    REAL b[ldt];
    const INTEGER ldt2 = 2 * ldt;
    REAL d[ldt2];
    REAL work[ldt];
    REAL norm = 0.0;
    INTEGER k = 0;
    REAL normtb = 0.0;
    REAL x[ldt2];
    REAL dum[1];
    REAL dumm = 0.0;
    REAL scale = 0.0;
    INTEGER info = 0;
    REAL y[ldt2];
    REAL xnorm = 0.0;
    REAL resid = 0.0;
    REAL domin = 0.0;
    for (ivm5 = 1; ivm5 <= 3; ivm5 = ivm5 + 1) {
        for (ivm4 = 1; ivm4 <= 5; ivm4 = ivm4 + 1) {
            for (ivm3 = 1; ivm3 <= 5; ivm3 = ivm3 + 1) {
                for (ivm2 = 1; ivm2 <= 5; ivm2 = ivm2 + 1) {
                    for (ivm1 = 1; ivm1 <= 5; ivm1 = ivm1 + 1) {
                        for (ndim = 1; ndim <= 6; ndim = ndim + 1) {
                            //
                            n = idim[ndim - 1];
                            for (i = 1; i <= n; i = i + 1) {
                                for (j = 1; j <= n; j = j + 1) {
                                    t[(i - 1) + (j - 1) * ldt] = castREAL(ival[(i - 1) + (j - 1) * ldval1 + (ndim - 1) * ldval2]) * vm1[ivm1 - 1];
                                    if (i >= j) {
                                        t[(i - 1) + (j - 1) * ldt] = t[(i - 1) + (j - 1) * ldt] * vm5[ivm5 - 1];
                                    }
                                }
                            }
                            //
                            w = one * vm2[ivm2 - 1];
                            //
                            for (i = 1; i <= n; i = i + 1) {
                                b[i - 1] = cos(castREAL(i)) * vm3[ivm3 - 1];
                            }
                            //
                            for (i = 1; i <= 2 * n; i = i + 1) {
                                d[i - 1] = sin(castREAL(i)) * vm4[ivm4 - 1];
                            }
                            //
                            norm = Rlange("1", n, n, t, ldt, work);
                            k = iRamax(n, b, 1);
                            normtb = norm + abs(b[k - 1]) + abs(w);
                            //
                            Rcopy(n, d, 1, x, 1);
                            knt++;
                            Rlaqtr(false, true, n, t, ldt, dum, dumm, scale, x, work, info);
                            if (info != 0) {
                                ninfo++;
                            }
                            //
                            //                       || T*x - scale*d || /
                            //                         max(ulp*||T||*||x||,smlnum/ulp*||T||,smlnum)
                            //
                            Rcopy(n, d, 1, y, 1);
                            Rgemv("No transpose", n, n, one, t, ldt, x, 1, -scale, y, 1);
                            xnorm = Rasum(n, x, 1);
                            resid = Rasum(n, y, 1);
                            domin = max({smlnum, REAL((smlnum / eps) * norm), REAL((norm * eps) * xnorm)});
                            resid = resid / domin;
                            if (resid > rmax) {
                                rmax = resid;
                                lmax = knt;
                            }
                            //
                            Rcopy(n, d, 1, x, 1);
                            knt++;
                            Rlaqtr(true, true, n, t, ldt, dum, dumm, scale, x, work, info);
                            if (info != 0) {
                                ninfo++;
                            }
                            //
                            //                       || T*x - scale*d || /
                            //                         max(ulp*||T||*||x||,smlnum/ulp*||T||,smlnum)
                            //
                            Rcopy(n, d, 1, y, 1);
                            Rgemv("Transpose", n, n, one, t, ldt, x, 1, -scale, y, 1);
                            xnorm = Rasum(n, x, 1);
                            resid = Rasum(n, y, 1);
                            domin = max({smlnum, REAL((smlnum / eps) * norm), REAL((norm * eps) * xnorm)});
                            resid = resid / domin;
                            if (resid > rmax) {
                                rmax = resid;
                                lmax = knt;
                            }
                            //
                            Rcopy(2 * n, d, 1, x, 1);
                            knt++;
                            Rlaqtr(false, false, n, t, ldt, b, w, scale, x, work, info);
                            if (info != 0) {
                                ninfo++;
                            }
                            //
                            //                       ||(T+i*B)*(x1+i*x2) - scale*(d1+i*d2)|| /
                            //                          max(ulp*(||T||+||B||)*(||x1||+||x2||),
                            //                                  smlnum/ulp * (||T||+||B||), smlnum )
                            //
                            Rcopy(2 * n, d, 1, y, 1);
                            y[1 - 1] = Rdot(n, b, 1, &x[(1 + n) - 1], 1) + scale * y[1 - 1];
                            for (i = 2; i <= n; i = i + 1) {
                                y[i - 1] = w * x[(i + n) - 1] + scale * y[i - 1];
                            }
                            Rgemv("No transpose", n, n, one, t, ldt, x, 1, -one, y, 1);
                            //
                            y[(1 + n) - 1] = Rdot(n, b, 1, x, 1) - scale * y[(1 + n) - 1];
                            for (i = 2; i <= n; i = i + 1) {
                                y[(i + n) - 1] = w * x[i - 1] - scale * y[(i + n) - 1];
                            }
                            Rgemv("No transpose", n, n, one, t, ldt, &x[(1 + n) - 1], 1, one, &y[(1 + n) - 1], 1);
                            //
                            resid = Rasum(2 * n, y, 1);
                            domin = max({smlnum, REAL((smlnum / eps) * normtb), REAL(eps * (normtb * Rasum(2 * n, x, 1)))});
                            resid = resid / domin;
                            if (resid > rmax) {
                                rmax = resid;
                                lmax = knt;
                            }
                            //
                            Rcopy(2 * n, d, 1, x, 1);
                            knt++;
                            Rlaqtr(true, false, n, t, ldt, b, w, scale, x, work, info);
                            if (info != 0) {
                                ninfo++;
                            }
                            //
                            //                       ||(T+i*B)*(x1+i*x2) - scale*(d1+i*d2)|| /
                            //                          max(ulp*(||T||+||B||)*(||x1||+||x2||),
                            //                                  smlnum/ulp * (||T||+||B||), smlnum )
                            //
                            Rcopy(2 * n, d, 1, y, 1);
                            y[1 - 1] = b[1 - 1] * x[(1 + n) - 1] - scale * y[1 - 1];
                            for (i = 2; i <= n; i = i + 1) {
                                y[i - 1] = b[i - 1] * x[(1 + n) - 1] + w * x[(i + n) - 1] - scale * y[i - 1];
                            }
                            Rgemv("Transpose", n, n, one, t, ldt, x, 1, one, y, 1);
                            //
                            y[(1 + n) - 1] = b[1 - 1] * x[1 - 1] + scale * y[(1 + n) - 1];
                            for (i = 2; i <= n; i = i + 1) {
                                y[(i + n) - 1] = b[i - 1] * x[1 - 1] + w * x[i - 1] + scale * y[(i + n) - 1];
                            }
                            Rgemv("Transpose", n, n, one, t, ldt, &x[(1 + n) - 1], 1, -one, &y[(1 + n) - 1], 1);
                            //
                            resid = Rasum(2 * n, y, 1);
                            domin = max({smlnum, REAL((smlnum / eps) * normtb), REAL(eps * (normtb * Rasum(2 * n, x, 1)))});
                            resid = resid / domin;
                            if (resid > rmax) {
                                rmax = resid;
                                lmax = knt;
                            }
                            //
                        }
                    }
                }
            }
        }
    }
    //
    //     End of Rget39
    //
}
