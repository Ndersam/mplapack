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

void Rlasyf_rk(const char *uplo, INTEGER const n, INTEGER const nb, INTEGER &kb, REAL *a, INTEGER const lda, REAL *e, INTEGER *ipiv, REAL *w, INTEGER const ldw, INTEGER &info) {
    const REAL one = 1.0;
    const REAL sevten = 17.0e+0;
    const REAL eight = 8.0e+0;
    REAL alpha = 0.0;
    REAL sfmin = 0.0;
    const REAL zero = 0.0;
    INTEGER k = 0;
    INTEGER kw = 0;
    INTEGER kstep = 0;
    INTEGER p = 0;
    REAL absakk = 0.0;
    INTEGER imax = 0;
    REAL colmax = 0.0;
    INTEGER kp = 0;
    bool done = false;
    INTEGER jmax = 0;
    REAL rowmax = 0.0;
    INTEGER itemp = 0;
    REAL dtemp = 0.0;
    INTEGER kk = 0;
    INTEGER kkw = 0;
    REAL r1 = 0.0;
    INTEGER ii = 0;
    REAL d12 = 0.0;
    REAL d11 = 0.0;
    REAL d22 = 0.0;
    REAL t = 0.0;
    INTEGER j = 0;
    INTEGER jb = 0;
    INTEGER jj = 0;
    REAL d21 = 0.0;
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
    //     .. Executable Statements ..
    //
    info = 0;
    //
    //     Initialize ALPHA for use in choosing pivot block size.
    //
    alpha = (one + sqrt(sevten)) / eight;
    //
    //     Compute machine safe minimum
    //
    sfmin = Rlamch("S");
    //
    if (Mlsame(uplo, "U")) {
        //
        //        Factorize the trailing columns of A using the upper triangle
        //        of A and working backwards, and compute the matrix W = U12*D
        //        for use in updating A11
        //
        //        Initialize the first entry of array E, where superdiagonal
        //        elements of D are stored
        //
        e[1 - 1] = zero;
        //
        //        K is the main loop index, decreasing from N in steps of 1 or 2
        //
        k = n;
    statement_10:
        //
        //        KW is the column of W which corresponds to column K of A
        //
        kw = nb + k - n;
        //
        //        Exit from loop
        //
        if ((k <= n - nb + 1 && nb < n) || k < 1) {
            goto statement_30;
        }
        //
        kstep = 1;
        p = k;
        //
        //        Copy column K of A to column KW of W and update it
        //
        Rcopy(k, &a[(k - 1) * lda], 1, &w[(kw - 1) * ldw], 1);
        if (k < n) {
            Rgemv("No transpose", k, n - k, -one, &a[((k + 1) - 1) * lda], lda, &w[(k - 1) + ((kw + 1) - 1) * ldw], ldw, one, &w[(kw - 1) * ldw], 1);
        }
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = abs(w[(k - 1) + (kw - 1) * ldw]);
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k > 1) {
            imax = iRamax(k - 1, &w[(kw - 1) * ldw], 1);
            colmax = abs(w[(imax - 1) + (kw - 1) * ldw]);
        } else {
            colmax = zero;
        }
        //
        if (max(absakk, colmax) == zero) {
            //
            //           Column K is zero or underflow: set INFO and continue
            //
            if (info == 0) {
                info = k;
            }
            kp = k;
            Rcopy(k, &w[(kw - 1) * ldw], 1, &a[(k - 1) * lda], 1);
            //
            //           Set E( K ) to zero
            //
            if (k > 1) {
                e[k - 1] = zero;
            }
            //
        } else {
            //
            //           ============================================================
            //
            //           Test for interchange
            //
            //           Equivalent to testing for ABSAKK.GE.ALPHA*COLMAX
            //           (used to handle NaN and Inf)
            //
            if (!(absakk < alpha * colmax)) {
                //
                //              no interchange, use 1-by-1 pivot block
                //
                kp = k;
                //
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
                //                 Copy column IMAX to column KW-1 of W and update it
                //
                Rcopy(imax, &a[(imax - 1) * lda], 1, &w[((kw - 1) - 1) * ldw], 1);
                Rcopy(k - imax, &a[(imax - 1) + ((imax + 1) - 1) * lda], lda, &w[((imax + 1) - 1) + ((kw - 1) - 1) * ldw], 1);
                //
                if (k < n) {
                    Rgemv("No transpose", k, n - k, -one, &a[((k + 1) - 1) * lda], lda, &w[(imax - 1) + ((kw + 1) - 1) * ldw], ldw, one, &w[((kw - 1) - 1) * ldw], 1);
                }
                //
                //                 JMAX is the column-index of the largest off-diagonal
                //                 element in row IMAX, and ROWMAX is its absolute value.
                //                 Determine both ROWMAX and JMAX.
                //
                if (imax != k) {
                    jmax = imax + iRamax(k - imax, &w[((imax + 1) - 1) + ((kw - 1) - 1) * ldw], 1);
                    rowmax = abs(w[(jmax - 1) + ((kw - 1) - 1) * ldw]);
                } else {
                    rowmax = zero;
                }
                //
                if (imax > 1) {
                    itemp = iRamax(imax - 1, &w[((kw - 1) - 1) * ldw], 1);
                    dtemp = abs(w[(itemp - 1) + ((kw - 1) - 1) * ldw]);
                    if (dtemp > rowmax) {
                        rowmax = dtemp;
                        jmax = itemp;
                    }
                }
                //
                //                 Equivalent to testing for
                //                 ABS( W( IMAX, KW-1 ) ).GE.ALPHA*ROWMAX
                //                 (used to handle NaN and Inf)
                //
                if (!(abs(w[(imax - 1) + ((kw - 1) - 1) * ldw]) < alpha * rowmax)) {
                    //
                    //                    interchange rows and columns K and IMAX,
                    //                    use 1-by-1 pivot block
                    //
                    kp = imax;
                    //
                    //                    copy column KW-1 of W to column KW of W
                    //
                    Rcopy(k, &w[((kw - 1) - 1) * ldw], 1, &w[(kw - 1) * ldw], 1);
                    //
                    done = true;
                    //
                    //                 Equivalent to testing for ROWMAX.EQ.COLMAX,
                    //                 (used to handle NaN and Inf)
                    //
                } else if ((p == jmax) || (rowmax <= colmax)) {
                    //
                    //                    interchange rows and columns K-1 and IMAX,
                    //                    use 2-by-2 pivot block
                    //
                    kp = imax;
                    kstep = 2;
                    done = true;
                } else {
                    //
                    //                    Pivot not found: set params and repeat
                    //
                    p = imax;
                    colmax = rowmax;
                    imax = jmax;
                    //
                    //                    Copy updated JMAXth (next IMAXth) column to Kth of W
                    //
                    Rcopy(k, &w[((kw - 1) - 1) * ldw], 1, &w[(kw - 1) * ldw], 1);
                    //
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
            //           ============================================================
            //
            kk = k - kstep + 1;
            //
            //           KKW is the column of W which corresponds to column KK of A
            //
            kkw = nb + kk - n;
            //
            if ((kstep == 2) && (p != k)) {
                //
                //              Copy non-updated column K to column P
                //
                Rcopy(k - p, &a[((p + 1) - 1) + (k - 1) * lda], 1, &a[(p - 1) + ((p + 1) - 1) * lda], lda);
                Rcopy(p, &a[(k - 1) * lda], 1, &a[(p - 1) * lda], 1);
                //
                //              Interchange rows K and P in last N-K+1 columns of A
                //              and last N-K+2 columns of W
                //
                Rswap(n - k + 1, &a[(k - 1) + (k - 1) * lda], lda, &a[(p - 1) + (k - 1) * lda], lda);
                Rswap(n - kk + 1, &w[(k - 1) + (kkw - 1) * ldw], ldw, &w[(p - 1) + (kkw - 1) * ldw], ldw);
            }
            //
            //           Updated column KP is already stored in column KKW of W
            //
            if (kp != kk) {
                //
                //              Copy non-updated column KK to column KP
                //
                a[(kp - 1) + (k - 1) * lda] = a[(kk - 1) + (k - 1) * lda];
                Rcopy(k - 1 - kp, &a[((kp + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((kp + 1) - 1) * lda], lda);
                Rcopy(kp, &a[(kk - 1) * lda], 1, &a[(kp - 1) * lda], 1);
                //
                //              Interchange rows KK and KP in last N-KK+1 columns
                //              of A and W
                //
                Rswap(n - kk + 1, &a[(kk - 1) + (kk - 1) * lda], lda, &a[(kp - 1) + (kk - 1) * lda], lda);
                Rswap(n - kk + 1, &w[(kk - 1) + (kkw - 1) * ldw], ldw, &w[(kp - 1) + (kkw - 1) * ldw], ldw);
            }
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column KW of W now holds
                //
                //              W(k) = U(k)*D(k)
                //
                //              where U(k) is the k-th column of U
                //
                //              Store U(k) in column k of A
                //
                Rcopy(k, &w[(kw - 1) * ldw], 1, &a[(k - 1) * lda], 1);
                if (k > 1) {
                    if (abs(a[(k - 1) + (k - 1) * lda]) >= sfmin) {
                        r1 = one / a[(k - 1) + (k - 1) * lda];
                        Rscal(k - 1, r1, &a[(k - 1) * lda], 1);
                    } else if (a[(k - 1) + (k - 1) * lda] != zero) {
                        for (ii = 1; ii <= k - 1; ii = ii + 1) {
                            a[(ii - 1) + (k - 1) * lda] = a[(ii - 1) + (k - 1) * lda] / a[(k - 1) + (k - 1) * lda];
                        }
                    }
                    //
                    //                 Store the superdiagonal element of D in array E
                    //
                    e[k - 1] = zero;
                    //
                }
                //
            } else {
                //
                //              2-by-2 pivot block D(k): columns KW and KW-1 of W now
                //              hold
                //
                //              ( W(k-1) W(k) ) = ( U(k-1) U(k) )*D(k)
                //
                //              where U(k) and U(k-1) are the k-th and (k-1)-th columns
                //              of U
                //
                if (k > 2) {
                    //
                    //                 Store U(k) and U(k-1) in columns k and k-1 of A
                    //
                    d12 = w[((k - 1) - 1) + (kw - 1) * ldw];
                    d11 = w[(k - 1) + (kw - 1) * ldw] / d12;
                    d22 = w[((k - 1) - 1) + ((kw - 1) - 1) * ldw] / d12;
                    t = one / (d11 * d22 - one);
                    for (j = 1; j <= k - 2; j = j + 1) {
                        a[(j - 1) + ((k - 1) - 1) * lda] = t * ((d11 * w[(j - 1) + ((kw - 1) - 1) * ldw] - w[(j - 1) + (kw - 1) * ldw]) / d12);
                        a[(j - 1) + (k - 1) * lda] = t * ((d22 * w[(j - 1) + (kw - 1) * ldw] - w[(j - 1) + ((kw - 1) - 1) * ldw]) / d12);
                    }
                }
                //
                //              Copy diagonal elements of D(K) to A,
                //              copy superdiagonal element of D(K) to E(K) and
                //              ZERO out superdiagonal entry of A
                //
                a[((k - 1) - 1) + ((k - 1) - 1) * lda] = w[((k - 1) - 1) + ((kw - 1) - 1) * ldw];
                a[((k - 1) - 1) + (k - 1) * lda] = zero;
                a[(k - 1) + (k - 1) * lda] = w[(k - 1) + (kw - 1) * ldw];
                e[k - 1] = w[((k - 1) - 1) + (kw - 1) * ldw];
                e[(k - 1) - 1] = zero;
                //
            }
            //
            //           End column K is nonsingular
            //
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
    statement_30:
        //
        //        Update the upper triangle of A11 (= A(1:k,1:k)) as
        //
        //        A11 := A11 - U12*D*U12**T = A11 - U12*W**T
        //
        //        computing blocks of NB columns at a time
        //
        for (j = ((k - 1) / nb) * nb + 1; j >= 1; j = j - nb) {
            jb = min(nb, k - j + 1);
            //
            //           Update the upper triangle of the diagonal block
            //
            for (jj = j; jj <= j + jb - 1; jj = jj + 1) {
                Rgemv("No transpose", jj - j + 1, n - k, -one, &a[(j - 1) + ((k + 1) - 1) * lda], lda, &w[(jj - 1) + ((kw + 1) - 1) * ldw], ldw, one, &a[(j - 1) + (jj - 1) * lda], 1);
            }
            //
            //           Update the rectangular superdiagonal block
            //
            if (j >= 2) {
                Rgemm("No transpose", "Transpose", j - 1, jb, n - k, -one, &a[((k + 1) - 1) * lda], lda, &w[(j - 1) + ((kw + 1) - 1) * ldw], ldw, one, &a[(j - 1) * lda], lda);
            }
        }
        //
        //        Set KB to the number of columns factorized
        //
        kb = n - k;
        //
    } else {
        //
        //        Factorize the leading columns of A using the lower triangle
        //        of A and working forwards, and compute the matrix W = L21*D
        //        for use in updating A22
        //
        //        Initialize the unused last entry of the subdiagonal array E.
        //
        e[n - 1] = zero;
        //
        //        K is the main loop index, increasing from 1 in steps of 1 or 2
        //
        k = 1;
    statement_70:
        //
        //        Exit from loop
        //
        if ((k >= nb && nb < n) || k > n) {
            goto statement_90;
        }
        //
        kstep = 1;
        p = k;
        //
        //        Copy column K of A to column K of W and update it
        //
        Rcopy(n - k + 1, &a[(k - 1) + (k - 1) * lda], 1, &w[(k - 1) + (k - 1) * ldw], 1);
        if (k > 1) {
            Rgemv("No transpose", n - k + 1, k - 1, -one, &a[(k - 1)], lda, &w[(k - 1)], ldw, one, &w[(k - 1) + (k - 1) * ldw], 1);
        }
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = abs(w[(k - 1) + (k - 1) * ldw]);
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k < n) {
            imax = k + iRamax(n - k, &w[((k + 1) - 1) + (k - 1) * ldw], 1);
            colmax = abs(w[(imax - 1) + (k - 1) * ldw]);
        } else {
            colmax = zero;
        }
        //
        if (max(absakk, colmax) == zero) {
            //
            //           Column K is zero or underflow: set INFO and continue
            //
            if (info == 0) {
                info = k;
            }
            kp = k;
            Rcopy(n - k + 1, &w[(k - 1) + (k - 1) * ldw], 1, &a[(k - 1) + (k - 1) * lda], 1);
            //
            //           Set E( K ) to zero
            //
            if (k < n) {
                e[k - 1] = zero;
            }
            //
        } else {
            //
            //           ============================================================
            //
            //           Test for interchange
            //
            //           Equivalent to testing for ABSAKK.GE.ALPHA*COLMAX
            //           (used to handle NaN and Inf)
            //
            if (!(absakk < alpha * colmax)) {
                //
                //              no interchange, use 1-by-1 pivot block
                //
                kp = k;
                //
            } else {
                //
                done = false;
            //
            //              Loop until pivot found
            //
            statement_72:
                //
                //                 Begin pivot search loop body
                //
                //                 Copy column IMAX to column K+1 of W and update it
                //
                Rcopy(imax - k, &a[(imax - 1) + (k - 1) * lda], lda, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                Rcopy(n - imax + 1, &a[(imax - 1) + (imax - 1) * lda], 1, &w[(imax - 1) + ((k + 1) - 1) * ldw], 1);
                if (k > 1) {
                    Rgemv("No transpose", n - k + 1, k - 1, -one, &a[(k - 1)], lda, &w[(imax - 1)], ldw, one, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                }
                //
                //                 JMAX is the column-index of the largest off-diagonal
                //                 element in row IMAX, and ROWMAX is its absolute value.
                //                 Determine both ROWMAX and JMAX.
                //
                if (imax != k) {
                    jmax = k - 1 + iRamax(imax - k, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                    rowmax = abs(w[(jmax - 1) + ((k + 1) - 1) * ldw]);
                } else {
                    rowmax = zero;
                }
                //
                if (imax < n) {
                    itemp = imax + iRamax(n - imax, &w[((imax + 1) - 1) + ((k + 1) - 1) * ldw], 1);
                    dtemp = abs(w[(itemp - 1) + ((k + 1) - 1) * ldw]);
                    if (dtemp > rowmax) {
                        rowmax = dtemp;
                        jmax = itemp;
                    }
                }
                //
                //                 Equivalent to testing for
                //                 ABS( W( IMAX, K+1 ) ).GE.ALPHA*ROWMAX
                //                 (used to handle NaN and Inf)
                //
                if (!(abs(w[(imax - 1) + ((k + 1) - 1) * ldw]) < alpha * rowmax)) {
                    //
                    //                    interchange rows and columns K and IMAX,
                    //                    use 1-by-1 pivot block
                    //
                    kp = imax;
                    //
                    //                    copy column K+1 of W to column K of W
                    //
                    Rcopy(n - k + 1, &w[(k - 1) + ((k + 1) - 1) * ldw], 1, &w[(k - 1) + (k - 1) * ldw], 1);
                    //
                    done = true;
                    //
                    //                 Equivalent to testing for ROWMAX.EQ.COLMAX,
                    //                 (used to handle NaN and Inf)
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
                    //                    Pivot not found: set params and repeat
                    //
                    p = imax;
                    colmax = rowmax;
                    imax = jmax;
                    //
                    //                    Copy updated JMAXth (next IMAXth) column to Kth of W
                    //
                    Rcopy(n - k + 1, &w[(k - 1) + ((k + 1) - 1) * ldw], 1, &w[(k - 1) + (k - 1) * ldw], 1);
                    //
                }
                //
                //                 End pivot search loop body
                //
                if (!done) {
                    goto statement_72;
                }
                //
            }
            //
            //           ============================================================
            //
            kk = k + kstep - 1;
            //
            if ((kstep == 2) && (p != k)) {
                //
                //              Copy non-updated column K to column P
                //
                Rcopy(p - k, &a[(k - 1) + (k - 1) * lda], 1, &a[(p - 1) + (k - 1) * lda], lda);
                Rcopy(n - p + 1, &a[(p - 1) + (k - 1) * lda], 1, &a[(p - 1) + (p - 1) * lda], 1);
                //
                //              Interchange rows K and P in first K columns of A
                //              and first K+1 columns of W
                //
                Rswap(k, &a[(k - 1)], lda, &a[(p - 1)], lda);
                Rswap(kk, &w[(k - 1)], ldw, &w[(p - 1)], ldw);
            }
            //
            //           Updated column KP is already stored in column KK of W
            //
            if (kp != kk) {
                //
                //              Copy non-updated column KK to column KP
                //
                a[(kp - 1) + (k - 1) * lda] = a[(kk - 1) + (k - 1) * lda];
                Rcopy(kp - k - 1, &a[((k + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((k + 1) - 1) * lda], lda);
                Rcopy(n - kp + 1, &a[(kp - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + (kp - 1) * lda], 1);
                //
                //              Interchange rows KK and KP in first KK columns of A and W
                //
                Rswap(kk, &a[(kk - 1)], lda, &a[(kp - 1)], lda);
                Rswap(kk, &w[(kk - 1)], ldw, &w[(kp - 1)], ldw);
            }
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column k of W now holds
                //
                //              W(k) = L(k)*D(k)
                //
                //              where L(k) is the k-th column of L
                //
                //              Store L(k) in column k of A
                //
                Rcopy(n - k + 1, &w[(k - 1) + (k - 1) * ldw], 1, &a[(k - 1) + (k - 1) * lda], 1);
                if (k < n) {
                    if (abs(a[(k - 1) + (k - 1) * lda]) >= sfmin) {
                        r1 = one / a[(k - 1) + (k - 1) * lda];
                        Rscal(n - k, r1, &a[((k + 1) - 1) + (k - 1) * lda], 1);
                    } else if (a[(k - 1) + (k - 1) * lda] != zero) {
                        for (ii = k + 1; ii <= n; ii = ii + 1) {
                            a[(ii - 1) + (k - 1) * lda] = a[(ii - 1) + (k - 1) * lda] / a[(k - 1) + (k - 1) * lda];
                        }
                    }
                    //
                    //                 Store the subdiagonal element of D in array E
                    //
                    e[k - 1] = zero;
                    //
                }
                //
            } else {
                //
                //              2-by-2 pivot block D(k): columns k and k+1 of W now hold
                //
                //              ( W(k) W(k+1) ) = ( L(k) L(k+1) )*D(k)
                //
                //              where L(k) and L(k+1) are the k-th and (k+1)-th columns
                //              of L
                //
                if (k < n - 1) {
                    //
                    //                 Store L(k) and L(k+1) in columns k and k+1 of A
                    //
                    d21 = w[((k + 1) - 1) + (k - 1) * ldw];
                    d11 = w[((k + 1) - 1) + ((k + 1) - 1) * ldw] / d21;
                    d22 = w[(k - 1) + (k - 1) * ldw] / d21;
                    t = one / (d11 * d22 - one);
                    for (j = k + 2; j <= n; j = j + 1) {
                        a[(j - 1) + (k - 1) * lda] = t * ((d11 * w[(j - 1) + (k - 1) * ldw] - w[(j - 1) + ((k + 1) - 1) * ldw]) / d21);
                        a[(j - 1) + ((k + 1) - 1) * lda] = t * ((d22 * w[(j - 1) + ((k + 1) - 1) * ldw] - w[(j - 1) + (k - 1) * ldw]) / d21);
                    }
                }
                //
                //              Copy diagonal elements of D(K) to A,
                //              copy subdiagonal element of D(K) to E(K) and
                //              ZERO out subdiagonal entry of A
                //
                a[(k - 1) + (k - 1) * lda] = w[(k - 1) + (k - 1) * ldw];
                a[((k + 1) - 1) + (k - 1) * lda] = zero;
                a[((k + 1) - 1) + ((k + 1) - 1) * lda] = w[((k + 1) - 1) + ((k + 1) - 1) * ldw];
                e[k - 1] = w[((k + 1) - 1) + (k - 1) * ldw];
                e[(k + 1) - 1] = zero;
                //
            }
            //
            //           End column K is nonsingular
            //
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
        goto statement_70;
    //
    statement_90:
        //
        //        Update the lower triangle of A22 (= A(k:n,k:n)) as
        //
        //        A22 := A22 - L21*D*L21**T = A22 - L21*W**T
        //
        //        computing blocks of NB columns at a time
        //
        for (j = k; j <= n; j = j + nb) {
            jb = min(nb, n - j + 1);
            //
            //           Update the lower triangle of the diagonal block
            //
            for (jj = j; jj <= j + jb - 1; jj = jj + 1) {
                Rgemv("No transpose", j + jb - jj, k - 1, -one, &a[(jj - 1)], lda, &w[(jj - 1)], ldw, one, &a[(jj - 1) + (jj - 1) * lda], 1);
            }
            //
            //           Update the rectangular subdiagonal block
            //
            if (j + jb <= n) {
                Rgemm("No transpose", "Transpose", n - j - jb + 1, jb, k - 1, -one, &a[((j + jb) - 1)], lda, &w[(j - 1)], ldw, one, &a[((j + jb) - 1) + (j - 1) * lda], lda);
            }
        }
        //
        //        Set KB to the number of columns factorized
        //
        kb = k - 1;
        //
    }
    //
    //     End of Rlasyf_rk
    //
}
