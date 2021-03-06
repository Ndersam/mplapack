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

void Rlaic1(INTEGER const job, INTEGER const j, REAL *x, REAL const sest, REAL *w, REAL const gamma, REAL &sestpr, REAL &s, REAL &c) {
    //
    //  -- LAPACK auxiliary routine --
    //  -- LAPACK is a software package provided by Univ. of Tennessee,    --
    //  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
    //
    //     .. Scalar Arguments ..
    //     ..
    //     .. Array Arguments ..
    //     ..
    //
    //  =====================================================================
    //
    //     .. Parameters ..
    //     ..
    //     .. Local Scalars ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. Executable Statements ..
    //
    REAL eps = Rlamch("Epsilon");
    REAL alpha = Rdot(j, x, 1, w, 1);
    //
    REAL absalp = abs(alpha);
    REAL absgam = abs(gamma);
    REAL absest = abs(sest);
    //
    const REAL zero = 0.0;
    REAL s1 = 0.0;
    const REAL one = 1.0;
    REAL tmp = 0.0;
    REAL s2 = 0.0;
    REAL zeta1 = 0.0;
    REAL zeta2 = 0.0;
    const REAL half = 0.5e0;
    REAL b = 0.0;
    REAL t = 0.0;
    REAL sine = 0.0;
    REAL cosine = 0.0;
    REAL norma = 0.0;
    const REAL two = 2.0;
    REAL test = 0.0;
    const REAL four = 4.0;
    if (job == 1) {
        //
        //        Estimating largest singular value
        //
        //        special cases
        //
        if (sest == zero) {
            s1 = max(absgam, absalp);
            if (s1 == zero) {
                s = zero;
                c = one;
                sestpr = zero;
            } else {
                s = alpha / s1;
                c = gamma / s1;
                tmp = sqrt(s * s + c * c);
                s = s / tmp;
                c = c / tmp;
                sestpr = s1 * tmp;
            }
            return;
        } else if (absgam <= eps * absest) {
            s = one;
            c = zero;
            tmp = max(absest, absalp);
            s1 = absest / tmp;
            s2 = absalp / tmp;
            sestpr = tmp * sqrt(s1 * s1 + s2 * s2);
            return;
        } else if (absalp <= eps * absest) {
            s1 = absgam;
            s2 = absest;
            if (s1 <= s2) {
                s = one;
                c = zero;
                sestpr = s2;
            } else {
                s = zero;
                c = one;
                sestpr = s1;
            }
            return;
        } else if (absest <= eps * absalp || absest <= eps * absgam) {
            s1 = absgam;
            s2 = absalp;
            if (s1 <= s2) {
                tmp = s1 / s2;
                s = sqrt(one + tmp * tmp);
                sestpr = s2 * s;
                c = (gamma / s2) / s;
                s = sign(one, alpha) / s;
            } else {
                tmp = s2 / s1;
                c = sqrt(one + tmp * tmp);
                sestpr = s1 * c;
                s = (alpha / s1) / c;
                c = sign(one, gamma) / c;
            }
            return;
        } else {
            //
            //           normal case
            //
            zeta1 = alpha / absest;
            zeta2 = gamma / absest;
            //
            b = (one - zeta1 * zeta1 - zeta2 * zeta2) * half;
            c = zeta1 * zeta1;
            if (b > zero) {
                t = c / (b + sqrt(b * b + c));
            } else {
                t = sqrt(b * b + c) - b;
            }
            //
            sine = -zeta1 / t;
            cosine = -zeta2 / (one + t);
            tmp = sqrt(sine * sine + cosine * cosine);
            s = sine / tmp;
            c = cosine / tmp;
            sestpr = sqrt(t + one) * absest;
            return;
        }
        //
    } else if (job == 2) {
        //
        //        Estimating smallest singular value
        //
        //        special cases
        //
        if (sest == zero) {
            sestpr = zero;
            if (max(absgam, absalp) == zero) {
                sine = one;
                cosine = zero;
            } else {
                sine = -gamma;
                cosine = alpha;
            }
            s1 = max(abs(sine), abs(cosine));
            s = sine / s1;
            c = cosine / s1;
            tmp = sqrt(s * s + c * c);
            s = s / tmp;
            c = c / tmp;
            return;
        } else if (absgam <= eps * absest) {
            s = zero;
            c = one;
            sestpr = absgam;
            return;
        } else if (absalp <= eps * absest) {
            s1 = absgam;
            s2 = absest;
            if (s1 <= s2) {
                s = zero;
                c = one;
                sestpr = s1;
            } else {
                s = one;
                c = zero;
                sestpr = s2;
            }
            return;
        } else if (absest <= eps * absalp || absest <= eps * absgam) {
            s1 = absgam;
            s2 = absalp;
            if (s1 <= s2) {
                tmp = s1 / s2;
                c = sqrt(one + tmp * tmp);
                sestpr = absest * (tmp / c);
                s = -(gamma / s2) / c;
                c = sign(one, alpha) / c;
            } else {
                tmp = s2 / s1;
                s = sqrt(one + tmp * tmp);
                sestpr = absest / s;
                c = (alpha / s1) / s;
                s = -sign(one, gamma) / s;
            }
            return;
        } else {
            //
            //           normal case
            //
            zeta1 = alpha / absest;
            zeta2 = gamma / absest;
            //
            norma = max(REAL(one + zeta1 * zeta1 + abs(zeta1 * zeta2)), REAL(abs(zeta1 * zeta2) + zeta2 * zeta2));
            //
            //           See if root is closer to zero or to ONE
            //
            test = one + two * (zeta1 - zeta2) * (zeta1 + zeta2);
            if (test >= zero) {
                //
                //              root is close to zero, compute directly
                //
                b = (zeta1 * zeta1 + zeta2 * zeta2 + one) * half;
                c = zeta2 * zeta2;
                t = c / (b + sqrt(abs(b * b - c)));
                sine = zeta1 / (one - t);
                cosine = -zeta2 / t;
                sestpr = sqrt(t + four * eps * eps * norma) * absest;
            } else {
                //
                //              root is closer to ONE, shift by that amount
                //
                b = (zeta2 * zeta2 + zeta1 * zeta1 - one) * half;
                c = zeta1 * zeta1;
                if (b >= zero) {
                    t = -c / (b + sqrt(b * b + c));
                } else {
                    t = b - sqrt(b * b + c);
                }
                sine = -zeta1 / t;
                cosine = -zeta2 / (one + t);
                sestpr = sqrt(one + t + four * eps * eps * norma) * absest;
            }
            tmp = sqrt(sine * sine + cosine * cosine);
            s = sine / tmp;
            c = cosine / tmp;
            return;
            //
        }
    }
    //
    //     End of Rlaic1
    //
}
