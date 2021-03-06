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

void Cgemv(const char *trans, INTEGER const m, INTEGER const n, COMPLEX const alpha, COMPLEX *a, INTEGER const lda, COMPLEX *x, INTEGER const incx, COMPLEX const beta, COMPLEX *y, INTEGER const incy) {
    //
    //  -- Reference BLAS level2 routine --
    //  -- Reference BLAS is a software package provided by Univ. of Tennessee,    --
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
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //
    //     Test the input parameters.
    //
    INTEGER info = 0;
    if (!Mlsame(trans, "N") && !Mlsame(trans, "T") && !Mlsame(trans, "C")) {
        info = 1;
    } else if (m < 0) {
        info = 2;
    } else if (n < 0) {
        info = 3;
    } else if (lda < max((INTEGER)1, m)) {
        info = 6;
    } else if (incx == 0) {
        info = 8;
    } else if (incy == 0) {
        info = 11;
    }
    if (info != 0) {
        Mxerbla("Cgemv ", info);
        return;
    }
    //
    //     Quick return if possible.
    //
    const COMPLEX zero = COMPLEX(0.0, 0.0);
    const COMPLEX one = COMPLEX(1.0, 0.0);
    if ((m == 0) || (n == 0) || ((alpha == zero) && (beta == one))) {
        return;
    }
    //
    bool noconj = Mlsame(trans, "T");
    //
    //     Set  LENX  and  LENY, the lengths of the vectors x and y, and set
    //     up the start points in  X  and  Y.
    //
    INTEGER lenx = 0;
    INTEGER leny = 0;
    if (Mlsame(trans, "N")) {
        lenx = n;
        leny = m;
    } else {
        lenx = m;
        leny = n;
    }
    INTEGER kx = 0;
    if (incx > 0) {
        kx = 1;
    } else {
        kx = 1 - (lenx - 1) * incx;
    }
    INTEGER ky = 0;
    if (incy > 0) {
        ky = 1;
    } else {
        ky = 1 - (leny - 1) * incy;
    }
    //
    //     Start the operations. In this version the elements of A are
    //     accessed sequentially with one pass through A.
    //
    //     First form  y := beta*y.
    //
    INTEGER i = 0;
    INTEGER iy = 0;
    if (beta != one) {
        if (incy == 1) {
            if (beta == zero) {
                for (i = 1; i <= leny; i = i + 1) {
                    y[i - 1] = zero;
                }
            } else {
                for (i = 1; i <= leny; i = i + 1) {
                    y[i - 1] = beta * y[i - 1];
                }
            }
        } else {
            iy = ky;
            if (beta == zero) {
                for (i = 1; i <= leny; i = i + 1) {
                    y[iy - 1] = zero;
                    iy += incy;
                }
            } else {
                for (i = 1; i <= leny; i = i + 1) {
                    y[iy - 1] = beta * y[iy - 1];
                    iy += incy;
                }
            }
        }
    }
    if (alpha == zero) {
        return;
    }
    INTEGER jx = 0;
    INTEGER j = 0;
    COMPLEX temp = 0.0;
    INTEGER jy = 0;
    INTEGER ix = 0;
    if (Mlsame(trans, "N")) {
        //
        //        Form  y := alpha*A*x + y.
        //
        jx = kx;
        if (incy == 1) {
            for (j = 1; j <= n; j = j + 1) {
                temp = alpha * x[jx - 1];
                for (i = 1; i <= m; i = i + 1) {
                    y[i - 1] += temp * a[(i - 1) + (j - 1) * lda];
                }
                jx += incx;
            }
        } else {
            for (j = 1; j <= n; j = j + 1) {
                temp = alpha * x[jx - 1];
                iy = ky;
                for (i = 1; i <= m; i = i + 1) {
                    y[iy - 1] += temp * a[(i - 1) + (j - 1) * lda];
                    iy += incy;
                }
                jx += incx;
            }
        }
    } else {
        //
        //        Form  y := alpha*A**T*x + y  or  y := alpha*A**H*x + y.
        //
        jy = ky;
        if (incx == 1) {
            for (j = 1; j <= n; j = j + 1) {
                temp = zero;
                if (noconj) {
                    for (i = 1; i <= m; i = i + 1) {
                        temp += a[(i - 1) + (j - 1) * lda] * x[i - 1];
                    }
                } else {
                    for (i = 1; i <= m; i = i + 1) {
                        temp += conj(a[(i - 1) + (j - 1) * lda]) * x[i - 1];
                    }
                }
                y[jy - 1] += alpha * temp;
                jy += incy;
            }
        } else {
            for (j = 1; j <= n; j = j + 1) {
                temp = zero;
                ix = kx;
                if (noconj) {
                    for (i = 1; i <= m; i = i + 1) {
                        temp += a[(i - 1) + (j - 1) * lda] * x[ix - 1];
                        ix += incx;
                    }
                } else {
                    for (i = 1; i <= m; i = i + 1) {
                        temp += conj(a[(i - 1) + (j - 1) * lda]) * x[ix - 1];
                        ix += incx;
                    }
                }
                y[jy - 1] += alpha * temp;
                jy += incy;
            }
        }
    }
    //
    //     End of Cgemv .
    //
}
