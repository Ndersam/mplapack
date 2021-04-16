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

inline REAL cabs1(COMPLEX z) { return abs(z.real()) + abs(z.imag()); }

void Csytf2_rook(const char *uplo, INTEGER const n, COMPLEX *a, INTEGER const lda, INTEGER *ipiv, INTEGER &info) {
    COMPLEX z = 0.0;
    bool upper = false;
    const REAL one = 1.0;
    const REAL sevten = 17.0e+0;
    const REAL eight = 8.0e+0;
    REAL alpha = 0.0;
    REAL sfmin = 0.0;
    INTEGER k = 0;
    INTEGER kstep = 0;
    INTEGER p = 0;
    REAL absakk = 0.0;
    INTEGER imax = 0;
    REAL colmax = 0.0;
    const REAL zero = 0.0;
    INTEGER kp = 0;
    bool done = false;
    INTEGER jmax = 0;
    REAL rowmax = 0.0;
    INTEGER itemp = 0;
    REAL dtemp = 0.0;
    COMPLEX t = 0.0;
    INTEGER kk = 0;
    const COMPLEX cone = (1.0, 0.0);
    COMPLEX d11 = 0.0;
    INTEGER ii = 0;
    COMPLEX d12 = 0.0;
    COMPLEX d22 = 0.0;
    INTEGER j = 0;
    COMPLEX wkm1 = 0.0;
    COMPLEX wk = 0.0;
    INTEGER i = 0;
    COMPLEX d21 = 0.0;
    COMPLEX wkp1 = 0.0;
    //
    //  -- LAPACK computational routine --
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
    //     .. External Functions ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Statement Functions ..
    //     ..
    //     .. Statement Function definitions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Test the input parameters.
    //
    info = 0;
    upper = Mlsame(uplo, "U");
    if (!upper && !Mlsame(uplo, "L")) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (lda < max((INTEGER)1, n)) {
        info = -4;
    }
    if (info != 0) {
        Mxerbla("Csytf2_rook", -info);
        return;
    }
    //
    //     Initialize ALPHA for use in choosing pivot block size.
    //
    alpha = (one + sqrt(sevten)) / eight;
    //
    //     Compute machine safe minimum
    //
    sfmin = Rlamch("S");
    //
    if (upper) {
        //
        //        Factorize A as U*D*U**T using the upper triangle of A
        //
        //        K is the main loop index, decreasing from N to 1 in steps of
        //        1 or 2
        //
        k = n;
    statement_10:
        //
        //        If K < 1, exit from loop
        //
        if (k < 1) {
            goto statement_70;
        }
        kstep = 1;
        p = k;
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = cabs1(a[(k - 1) + (k - 1) * lda]);
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k > 1) {
            imax = iCamax(k - 1, &a[(k - 1) * lda], 1);
            colmax = cabs1(a[(imax - 1) + (k - 1) * lda]);
        } else {
            colmax = zero;
        }
        //
        if ((max(absakk, colmax) == zero)) {
            //
            //           Column K is zero or underflow: set INFO and continue
            //
            if (info == 0) {
                info = k;
            }
            kp = k;
        } else {
            //
            //           Test for interchange
            //
            //           Equivalent to testing for (used to handle NaN and Inf)
            //           ABSAKK.GE.ALPHA*COLMAX
            //
            if (!(absakk < alpha * colmax)) {
                //
                //              no interchange,
                //              use 1-by-1 pivot block
                //
                kp = k;
            } else {
                //
                done = false;
            //
            //              Loop until pivot found
            //
            statement_12:
                //
                //                 Begin pivot search loop body
                //
                //                 JMAX is the column-index of the largest off-diagonal
                //                 element in row IMAX, and ROWMAX is its absolute value.
                //                 Determine both ROWMAX and JMAX.
                //
                if (imax != k) {
                    jmax = imax + iCamax(k - imax, &a[(imax - 1) + ((imax + 1) - 1) * lda], lda);
                    rowmax = cabs1(a[(imax - 1) + (jmax - 1) * lda]);
                } else {
                    rowmax = zero;
                }
                //
                if (imax > 1) {
                    itemp = iCamax(imax - 1, &a[(imax - 1) * lda], 1);
                    dtemp = cabs1(a[(itemp - 1) + (imax - 1) * lda]);
                    if (dtemp > rowmax) {
                        rowmax = dtemp;
                        jmax = itemp;
                    }
                }
                //
                //                 Equivalent to testing for (used to handle NaN and Inf)
                //                 CCABS1( A( IMAX, IMAX ) ).GE.ALPHA*ROWMAX
                //
                if (!(cabs1(a[(imax - 1) + (imax - 1) * lda]) < alpha * rowmax)) {
                    //
                    //                    interchange rows and columns K and IMAX,
                    //                    use 1-by-1 pivot block
                    //
                    kp = imax;
                    done = true;
                    //
                    //                 Equivalent to testing for ROWMAX .EQ. COLMAX,
                    //                 used to handle NaN and Inf
                    //
                } else if ((p == jmax) || (rowmax <= colmax)) {
                    //
                    //                    interchange rows and columns K+1 and IMAX,
                    //                    use 2-by-2 pivot block
                    //
                    kp = imax;
                    kstep = 2;
                    done = true;
                } else {
                    //
                    //                    Pivot NOT found, set variables and repeat
                    //
                    p = imax;
                    colmax = rowmax;
                    imax = jmax;
                }
                //
                //                 End pivot search loop body
                //
                if (!done) {
                    goto statement_12;
                }
                //
            }
            //
            //           Swap TWO rows and TWO columns
            //
            //           First swap
            //
            if ((kstep == 2) && (p != k)) {
                //
                //              Interchange rows and column K and P in the leading
                //              submatrix A(1:k,1:k) if we have a 2-by-2 pivot
                //
                if (p > 1) {
                    Cswap(p - 1, &a[(k - 1) * lda], 1, &a[(p - 1) * lda], 1);
                }
                if (p < (k - 1)) {
                    Cswap(k - p - 1, &a[((p + 1) - 1) + (k - 1) * lda], 1, &a[(p - 1) + ((p + 1) - 1) * lda], lda);
                }
                t = a[(k - 1) + (k - 1) * lda];
                a[(k - 1) + (k - 1) * lda] = a[(p - 1) + (p - 1) * lda];
                a[(p - 1) + (p - 1) * lda] = t;
            }
            //
            //           Second swap
            //
            kk = k - kstep + 1;
            if (kp != kk) {
                //
                //              Interchange rows and columns KK and KP in the leading
                //              submatrix A(1:k,1:k)
                //
                if (kp > 1) {
                    Cswap(kp - 1, &a[(kk - 1) * lda], 1, &a[(kp - 1) * lda], 1);
                }
                if ((kk > 1) && (kp < (kk - 1))) {
                    Cswap(kk - kp - 1, &a[((kp + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((kp + 1) - 1) * lda], lda);
                }
                t = a[(kk - 1) + (kk - 1) * lda];
                a[(kk - 1) + (kk - 1) * lda] = a[(kp - 1) + (kp - 1) * lda];
                a[(kp - 1) + (kp - 1) * lda] = t;
                if (kstep == 2) {
                    t = a[((k - 1) - 1) + (k - 1) * lda];
                    a[((k - 1) - 1) + (k - 1) * lda] = a[(kp - 1) + (k - 1) * lda];
                    a[(kp - 1) + (k - 1) * lda] = t;
                }
            }
            //
            //           Update the leading submatrix
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column k now holds
                //
                //              W(k) = U(k)*D(k)
                //
                //              where U(k) is the k-th column of U
                //
                if (k > 1) {
                    //
                    //                 Perform a rank-1 update of A(1:k-1,1:k-1) and
                    //                 store U(k) in column k
                    //
                    if (cabs1(a[(k - 1) + (k - 1) * lda]) >= sfmin) {
                        //
                        //                    Perform a rank-1 update of A(1:k-1,1:k-1) as
                        //                    A := A - U(k)*D(k)*U(k)**T
                        //                       = A - W(k)*1/D(k)*W(k)**T
                        //
                        d11 = cone / a[(k - 1) + (k - 1) * lda];
                        Csyr(uplo, k - 1, -d11, &a[(k - 1) * lda], 1, a, lda);
                        //
                        //                    Store U(k) in column k
                        //
                        Cscal(k - 1, d11, &a[(k - 1) * lda], 1);
                    } else {
                        //
                        //                    Store L(k) in column K
                        //
                        d11 = a[(k - 1) + (k - 1) * lda];
                        for (ii = 1; ii <= k - 1; ii = ii + 1) {
                            a[(ii - 1) + (k - 1) * lda] = a[(ii - 1) + (k - 1) * lda] / d11;
                        }
                        //
                        //                    Perform a rank-1 update of A(k+1:n,k+1:n) as
                        //                    A := A - U(k)*D(k)*U(k)**T
                        //                       = A - W(k)*(1/D(k))*W(k)**T
                        //                       = A - (W(k)/D(k))*(D(k))*(W(k)/D(K))**T
                        //
                        Csyr(uplo, k - 1, -d11, &a[(k - 1) * lda], 1, a, lda);
                    }
                }
                //
            } else {
                //
                //              2-by-2 pivot block D(k): columns k and k-1 now hold
                //
                //              ( W(k-1) W(k) ) = ( U(k-1) U(k) )*D(k)
                //
                //              where U(k) and U(k-1) are the k-th and (k-1)-th columns
                //              of U
                //
                //              Perform a rank-2 update of A(1:k-2,1:k-2) as
                //
                //              A := A - ( U(k-1) U(k) )*D(k)*( U(k-1) U(k) )**T
                //                 = A - ( ( A(k-1)A(k) )*inv(D(k)) ) * ( A(k-1)A(k) )**T
                //
                //              and store L(k) and L(k+1) in columns k and k+1
                //
                if (k > 2) {
                    //
                    d12 = a[((k - 1) - 1) + (k - 1) * lda];
                    d22 = a[((k - 1) - 1) + ((k - 1) - 1) * lda] / d12;
                    d11 = a[(k - 1) + (k - 1) * lda] / d12;
                    t = cone / (d11 * d22 - cone);
                    //
                    for (j = k - 2; j >= 1; j = j - 1) {
                        //
                        wkm1 = t * (d11 * a[(j - 1) + ((k - 1) - 1) * lda] - a[(j - 1) + (k - 1) * lda]);
                        wk = t * (d22 * a[(j - 1) + (k - 1) * lda] - a[(j - 1) + ((k - 1) - 1) * lda]);
                        //
                        for (i = j; i >= 1; i = i - 1) {
                            a[(i - 1) + (j - 1) * lda] = a[(i - 1) + (j - 1) * lda] - (a[(i - 1) + (k - 1) * lda] / d12) * wk - (a[(i - 1) + ((k - 1) - 1) * lda] / d12) * wkm1;
                        }
                        //
                        //                    Store U(k) and U(k-1) in cols k and k-1 for row J
                        //
                        a[(j - 1) + (k - 1) * lda] = wk / d12;
                        a[(j - 1) + ((k - 1) - 1) * lda] = wkm1 / d12;
                        //
                    }
                    //
                }
                //
            }
        }
        //
        //        Store details of the interchanges in IPIV
        //
        if (kstep == 1) {
            ipiv[k - 1] = kp;
        } else {
            ipiv[k - 1] = -p;
            ipiv[(k - 1) - 1] = -kp;
        }
        //
        //        Decrease K and return to the start of the main loop
        //
        k = k - kstep;
        goto statement_10;
        //
    } else {
        //
        //        Factorize A as L*D*L**T using the lower triangle of A
        //
        //        K is the main loop index, increasing from 1 to N in steps of
        //        1 or 2
        //
        k = 1;
    statement_40:
        //
        //        If K > N, exit from loop
        //
        if (k > n) {
            goto statement_70;
        }
        kstep = 1;
        p = k;
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = cabs1(a[(k - 1) + (k - 1) * lda]);
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k < n) {
            imax = k + iCamax(n - k, &a[((k + 1) - 1) + (k - 1) * lda], 1);
            colmax = cabs1(a[(imax - 1) + (k - 1) * lda]);
        } else {
            colmax = zero;
        }
        //
        if ((max(absakk, colmax) == zero)) {
            //
            //           Column K is zero or underflow: set INFO and continue
            //
            if (info == 0) {
                info = k;
            }
            kp = k;
        } else {
            //
            //           Test for interchange
            //
            //           Equivalent to testing for (used to handle NaN and Inf)
            //           ABSAKK.GE.ALPHA*COLMAX
            //
            if (!(absakk < alpha * colmax)) {
                //
                //              no interchange, use 1-by-1 pivot block
                //
                kp = k;
            } else {
                //
                done = false;
            //
            //              Loop until pivot found
            //
            statement_42:
                //
                //                 Begin pivot search loop body
                //
                //                 JMAX is the column-index of the largest off-diagonal
                //                 element in row IMAX, and ROWMAX is its absolute value.
                //                 Determine both ROWMAX and JMAX.
                //
                if (imax != k) {
                    jmax = k - 1 + iCamax(imax - k, &a[(imax - 1) + (k - 1) * lda], lda);
                    rowmax = cabs1(a[(imax - 1) + (jmax - 1) * lda]);
                } else {
                    rowmax = zero;
                }
                //
                if (imax < n) {
                    itemp = imax + iCamax(n - imax, &a[((imax + 1) - 1) + (imax - 1) * lda], 1);
                    dtemp = cabs1(a[(itemp - 1) + (imax - 1) * lda]);
                    if (dtemp > rowmax) {
                        rowmax = dtemp;
                        jmax = itemp;
                    }
                }
                //
                //                 Equivalent to testing for (used to handle NaN and Inf)
                //                 CCABS1( A( IMAX, IMAX ) ).GE.ALPHA*ROWMAX
                //
                if (!(cabs1(a[(imax - 1) + (imax - 1) * lda]) < alpha * rowmax)) {
                    //
                    //                    interchange rows and columns K and IMAX,
                    //                    use 1-by-1 pivot block
                    //
                    kp = imax;
                    done = true;
                    //
                    //                 Equivalent to testing for ROWMAX .EQ. COLMAX,
                    //                 used to handle NaN and Inf
                    //
                } else if ((p == jmax) || (rowmax <= colmax)) {
                    //
                    //                    interchange rows and columns K+1 and IMAX,
                    //                    use 2-by-2 pivot block
                    //
                    kp = imax;
                    kstep = 2;
                    done = true;
                } else {
                    //
                    //                    Pivot NOT found, set variables and repeat
                    //
                    p = imax;
                    colmax = rowmax;
                    imax = jmax;
                }
                //
                //                 End pivot search loop body
                //
                if (!done) {
                    goto statement_42;
                }
                //
            }
            //
            //           Swap TWO rows and TWO columns
            //
            //           First swap
            //
            if ((kstep == 2) && (p != k)) {
                //
                //              Interchange rows and column K and P in the trailing
                //              submatrix A(k:n,k:n) if we have a 2-by-2 pivot
                //
                if (p < n) {
                    Cswap(n - p, &a[((p + 1) - 1) + (k - 1) * lda], 1, &a[((p + 1) - 1) + (p - 1) * lda], 1);
                }
                if (p > (k + 1)) {
                    Cswap(p - k - 1, &a[((k + 1) - 1) + (k - 1) * lda], 1, &a[(p - 1) + ((k + 1) - 1) * lda], lda);
                }
                t = a[(k - 1) + (k - 1) * lda];
                a[(k - 1) + (k - 1) * lda] = a[(p - 1) + (p - 1) * lda];
                a[(p - 1) + (p - 1) * lda] = t;
            }
            //
            //           Second swap
            //
            kk = k + kstep - 1;
            if (kp != kk) {
                //
                //              Interchange rows and columns KK and KP in the trailing
                //              submatrix A(k:n,k:n)
                //
                if (kp < n) {
                    Cswap(n - kp, &a[((kp + 1) - 1) + (kk - 1) * lda], 1, &a[((kp + 1) - 1) + (kp - 1) * lda], 1);
                }
                if ((kk < n) && (kp > (kk + 1))) {
                    Cswap(kp - kk - 1, &a[((kk + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((kk + 1) - 1) * lda], lda);
                }
                t = a[(kk - 1) + (kk - 1) * lda];
                a[(kk - 1) + (kk - 1) * lda] = a[(kp - 1) + (kp - 1) * lda];
                a[(kp - 1) + (kp - 1) * lda] = t;
                if (kstep == 2) {
                    t = a[((k + 1) - 1) + (k - 1) * lda];
                    a[((k + 1) - 1) + (k - 1) * lda] = a[(kp - 1) + (k - 1) * lda];
                    a[(kp - 1) + (k - 1) * lda] = t;
                }
            }
            //
            //           Update the trailing submatrix
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column k now holds
                //
                //              W(k) = L(k)*D(k)
                //
                //              where L(k) is the k-th column of L
                //
                if (k < n) {
                    //
                    //              Perform a rank-1 update of A(k+1:n,k+1:n) and
                    //              store L(k) in column k
                    //
                    if (cabs1(a[(k - 1) + (k - 1) * lda]) >= sfmin) {
                        //
                        //                    Perform a rank-1 update of A(k+1:n,k+1:n) as
                        //                    A := A - L(k)*D(k)*L(k)**T
                        //                       = A - W(k)*(1/D(k))*W(k)**T
                        //
                        d11 = cone / a[(k - 1) + (k - 1) * lda];
                        Csyr(uplo, n - k, -d11, &a[((k + 1) - 1) + (k - 1) * lda], 1, &a[((k + 1) - 1) + ((k + 1) - 1) * lda], lda);
                        //
                        //                    Store L(k) in column k
                        //
                        Cscal(n - k, d11, &a[((k + 1) - 1) + (k - 1) * lda], 1);
                    } else {
                        //
                        //                    Store L(k) in column k
                        //
                        d11 = a[(k - 1) + (k - 1) * lda];
                        for (ii = k + 1; ii <= n; ii = ii + 1) {
                            a[(ii - 1) + (k - 1) * lda] = a[(ii - 1) + (k - 1) * lda] / d11;
                        }
                        //
                        //                    Perform a rank-1 update of A(k+1:n,k+1:n) as
                        //                    A := A - L(k)*D(k)*L(k)**T
                        //                       = A - W(k)*(1/D(k))*W(k)**T
                        //                       = A - (W(k)/D(k))*(D(k))*(W(k)/D(K))**T
                        //
                        Csyr(uplo, n - k, -d11, &a[((k + 1) - 1) + (k - 1) * lda], 1, &a[((k + 1) - 1) + ((k + 1) - 1) * lda], lda);
                    }
                }
                //
            } else {
                //
                //              2-by-2 pivot block D(k): columns k and k+1 now hold
                //
                //              ( W(k) W(k+1) ) = ( L(k) L(k+1) )*D(k)
                //
                //              where L(k) and L(k+1) are the k-th and (k+1)-th columns
                //              of L
                //
                //              Perform a rank-2 update of A(k+2:n,k+2:n) as
                //
                //              A := A - ( L(k) L(k+1) ) * D(k) * ( L(k) L(k+1) )**T
                //                 = A - ( ( A(k)A(k+1) )*inv(D(k) ) * ( A(k)A(k+1) )**T
                //
                //              and store L(k) and L(k+1) in columns k and k+1
                //
                if (k < n - 1) {
                    //
                    d21 = a[((k + 1) - 1) + (k - 1) * lda];
                    d11 = a[((k + 1) - 1) + ((k + 1) - 1) * lda] / d21;
                    d22 = a[(k - 1) + (k - 1) * lda] / d21;
                    t = cone / (d11 * d22 - cone);
                    //
                    for (j = k + 2; j <= n; j = j + 1) {
                        //
                        //                    Compute  D21 * ( W(k)W(k+1) ) * inv(D(k)) for row J
                        //
                        wk = t * (d11 * a[(j - 1) + (k - 1) * lda] - a[(j - 1) + ((k + 1) - 1) * lda]);
                        wkp1 = t * (d22 * a[(j - 1) + ((k + 1) - 1) * lda] - a[(j - 1) + (k - 1) * lda]);
                        //
                        //                    Perform a rank-2 update of A(k+2:n,k+2:n)
                        //
                        for (i = j; i <= n; i = i + 1) {
                            a[(i - 1) + (j - 1) * lda] = a[(i - 1) + (j - 1) * lda] - (a[(i - 1) + (k - 1) * lda] / d21) * wk - (a[(i - 1) + ((k + 1) - 1) * lda] / d21) * wkp1;
                        }
                        //
                        //                    Store L(k) and L(k+1) in cols k and k+1 for row J
                        //
                        a[(j - 1) + (k - 1) * lda] = wk / d21;
                        a[(j - 1) + ((k + 1) - 1) * lda] = wkp1 / d21;
                        //
                    }
                    //
                }
                //
            }
        }
        //
        //        Store details of the interchanges in IPIV
        //
        if (kstep == 1) {
            ipiv[k - 1] = kp;
        } else {
            ipiv[k - 1] = -p;
            ipiv[(k + 1) - 1] = -kp;
        }
        //
        //        Increase K and return to the start of the main loop
        //
        k += kstep;
        goto statement_40;
        //
    }
//
statement_70:;
    //
    //     End of Csytf2_rook
    //
}
