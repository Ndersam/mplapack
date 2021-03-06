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

inline REAL cabs1(COMPLEX z) { return (abs(z.real()) + abs(z.imag())); }

void Clahef(const char *uplo, INTEGER const n, INTEGER const nb, INTEGER &kb, COMPLEX *a, INTEGER const lda, INTEGER *ipiv, COMPLEX *w, INTEGER const ldw, INTEGER &info) {
    COMPLEX z = 0.0;
    const REAL one = 1.0;
    const REAL sevten = 17.0e+0;
    const REAL eight = 8.0e+0;
    REAL alpha = 0.0;
    INTEGER k = 0;
    INTEGER kw = 0;
    INTEGER kstep = 0;
    const COMPLEX cone = COMPLEX(1.0, 0.0);
    REAL absakk = 0.0;
    INTEGER imax = 0;
    REAL colmax = 0.0;
    const REAL zero = 0.0;
    INTEGER kp = 0;
    INTEGER jmax = 0;
    REAL rowmax = 0.0;
    INTEGER kk = 0;
    INTEGER kkw = 0;
    REAL r1 = 0.0;
    COMPLEX d21 = 0.0;
    COMPLEX d11 = 0.0;
    COMPLEX d22 = 0.0;
    REAL t = 0.0;
    INTEGER j = 0;
    INTEGER jb = 0;
    INTEGER jj = 0;
    INTEGER jp = 0;
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
    //     .. Executable Statements ..
    //
    info = 0;
    //
    //     Initialize ALPHA for use in choosing pivot block size.
    //
    alpha = (one + sqrt(sevten)) / eight;
    //
    if (Mlsame(uplo, "U")) {
        //
        //        Factorize the trailing columns of A using the upper triangle
        //        of A and working backwards, and compute the matrix W = U12*D
        //        for use in updating A11 (note that conj(W) is actually stored)
        //
        //        K is the main loop index, decreasing from N in steps of 1 or 2
        //
        //        KW is the column of W which corresponds to column K of A
        //
        k = n;
    statement_10:
        kw = nb + k - n;
        //
        //        Exit from loop
        //
        if ((k <= n - nb + 1 && nb < n) || k < 1) {
            goto statement_30;
        }
        //
        kstep = 1;
        //
        //        Copy column K of A to column KW of W and update it
        //
        Ccopy(k - 1, &a[(k - 1) * lda], 1, &w[(kw - 1) * ldw], 1);
        w[(k - 1) + (kw - 1) * ldw] = a[(k - 1) + (k - 1) * lda].real();
        if (k < n) {
            Cgemv("No transpose", k, n - k, -cone, &a[((k + 1) - 1) * lda], lda, &w[(k - 1) + ((kw + 1) - 1) * ldw], ldw, cone, &w[(kw - 1) * ldw], 1);
            w[(k - 1) + (kw - 1) * ldw] = w[(k - 1) + (kw - 1) * ldw].real();
        }
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = abs(w[(k - 1) + (kw - 1) * ldw].real());
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k > 1) {
            imax = iCamax(k - 1, &w[(kw - 1) * ldw], 1);
            colmax = cabs1(w[(imax - 1) + (kw - 1) * ldw]);
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
            a[(k - 1) + (k - 1) * lda] = a[(k - 1) + (k - 1) * lda].real();
        } else {
            //
            //           ============================================================
            //
            //           BEGIN pivot search
            //
            //           Case(1)
            if (absakk >= alpha * colmax) {
                //
                //              no interchange, use 1-by-1 pivot block
                //
                kp = k;
            } else {
                //
                //              BEGIN pivot search along IMAX row
                //
                //              Copy column IMAX to column KW-1 of W and update it
                //
                Ccopy(imax - 1, &a[(imax - 1) * lda], 1, &w[((kw - 1) - 1) * ldw], 1);
                w[(imax - 1) + ((kw - 1) - 1) * ldw] = a[(imax - 1) + (imax - 1) * lda].real();
                Ccopy(k - imax, &a[(imax - 1) + ((imax + 1) - 1) * lda], lda, &w[((imax + 1) - 1) + ((kw - 1) - 1) * ldw], 1);
                Clacgv(k - imax, &w[((imax + 1) - 1) + ((kw - 1) - 1) * ldw], 1);
                if (k < n) {
                    Cgemv("No transpose", k, n - k, -cone, &a[((k + 1) - 1) * lda], lda, &w[(imax - 1) + ((kw + 1) - 1) * ldw], ldw, cone, &w[((kw - 1) - 1) * ldw], 1);
                    w[(imax - 1) + ((kw - 1) - 1) * ldw] = w[(imax - 1) + ((kw - 1) - 1) * ldw].real();
                }
                //
                //              JMAX is the column-index of the largest off-diagonal
                //              element in row IMAX, and ROWMAX is its absolute value.
                //              Determine only ROWMAX.
                //
                jmax = imax + iCamax(k - imax, &w[((imax + 1) - 1) + ((kw - 1) - 1) * ldw], 1);
                rowmax = cabs1(w[(jmax - 1) + ((kw - 1) - 1) * ldw]);
                if (imax > 1) {
                    jmax = iCamax(imax - 1, &w[((kw - 1) - 1) * ldw], 1);
                    rowmax = max(rowmax, cabs1(w[(jmax - 1) + ((kw - 1) - 1) * ldw]));
                }
                //
                //              Case(2)
                if (absakk >= alpha * colmax * (colmax / rowmax)) {
                    //
                    //                 no interchange, use 1-by-1 pivot block
                    //
                    kp = k;
                    //
                    //              Case(3)
                } else if (abs(w[(imax - 1) + ((kw - 1) - 1) * ldw].real()) >= alpha * rowmax) {
                    //
                    //                 interchange rows and columns K and IMAX, use 1-by-1
                    //                 pivot block
                    //
                    kp = imax;
                    //
                    //                 copy column KW-1 of W to column KW of W
                    //
                    Ccopy(k, &w[((kw - 1) - 1) * ldw], 1, &w[(kw - 1) * ldw], 1);
                    //
                    //              Case(4)
                } else {
                    //
                    //                 interchange rows and columns K-1 and IMAX, use 2-by-2
                    //                 pivot block
                    //
                    kp = imax;
                    kstep = 2;
                }
                //
                //              END pivot search along IMAX row
                //
            }
            //
            //           END pivot search
            //
            //           ============================================================
            //
            //           KK is the column of A where pivoting step stopped
            //
            kk = k - kstep + 1;
            //
            //           KKW is the column of W which corresponds to column KK of A
            //
            kkw = nb + kk - n;
            //
            //           Interchange rows and columns KP and KK.
            //           Updated column KP is already stored in column KKW of W.
            //
            if (kp != kk) {
                //
                //              Copy non-updated column KK to column KP of submatrix A
                //              at step K. No need to copy element into column K
                //              (or K and K-1 for 2-by-2 pivot) of A, since these columns
                //              will be later overwritten.
                //
                a[(kp - 1) + (kp - 1) * lda] = a[(kk - 1) + (kk - 1) * lda].real();
                Ccopy(kk - 1 - kp, &a[((kp + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((kp + 1) - 1) * lda], lda);
                Clacgv(kk - 1 - kp, &a[(kp - 1) + ((kp + 1) - 1) * lda], lda);
                if (kp > 1) {
                    Ccopy(kp - 1, &a[(kk - 1) * lda], 1, &a[(kp - 1) * lda], 1);
                }
                //
                //              Interchange rows KK and KP in last K+1 to N columns of A
                //              (columns K (or K and K-1 for 2-by-2 pivot) of A will be
                //              later overwritten). Interchange rows KK and KP
                //              in last KKW to NB columns of W.
                //
                if (k < n) {
                    Cswap(n - k, &a[(kk - 1) + ((k + 1) - 1) * lda], lda, &a[(kp - 1) + ((k + 1) - 1) * lda], lda);
                }
                Cswap(n - kk + 1, &w[(kk - 1) + (kkw - 1) * ldw], ldw, &w[(kp - 1) + (kkw - 1) * ldw], ldw);
            }
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column kw of W now holds
                //
                //              W(kw) = U(k)*D(k),
                //
                //              where U(k) is the k-th column of U
                //
                //              (1) Store subdiag. elements of column U(k)
                //              and 1-by-1 block D(k) in column k of A.
                //              (NOTE: Diagonal element U(k,k) is a UNIT element
                //              and not stored)
                //                 A(k,k) := D(k,k) = W(k,kw)
                //                 A(1:k-1,k) := U(1:k-1,k) = W(1:k-1,kw)/D(k,k)
                //
                //              (NOTE: No need to use for Hermitian matrix
                //              A( K, K ) = DBLE( W( K, K) ) to separately copy diagonal
                //              element D(k,k) from W (potentially saves only one load))
                Ccopy(k, &w[(kw - 1) * ldw], 1, &a[(k - 1) * lda], 1);
                if (k > 1) {
                    //
                    //                 (NOTE: No need to check if A(k,k) is NOT ZERO,
                    //                  since that was ensured earlier in pivot search:
                    //                  case A(k,k) = 0 falls into 2x2 pivot case(4))
                    //
                    r1 = one / a[(k - 1) + (k - 1) * lda].real();
                    CRscal(k - 1, r1, &a[(k - 1) * lda], 1);
                    //
                    //                 (2) Conjugate column W(kw)
                    //
                    Clacgv(k - 1, &w[(kw - 1) * ldw], 1);
                }
                //
            } else {
                //
                //              2-by-2 pivot block D(k): columns kw and kw-1 of W now hold
                //
                //              ( W(kw-1) W(kw) ) = ( U(k-1) U(k) )*D(k)
                //
                //              where U(k) and U(k-1) are the k-th and (k-1)-th columns
                //              of U
                //
                //              (1) Store U(1:k-2,k-1) and U(1:k-2,k) and 2-by-2
                //              block D(k-1:k,k-1:k) in columns k-1 and k of A.
                //              (NOTE: 2-by-2 diagonal block U(k-1:k,k-1:k) is a UNIT
                //              block and not stored)
                //                 A(k-1:k,k-1:k) := D(k-1:k,k-1:k) = W(k-1:k,kw-1:kw)
                //                 A(1:k-2,k-1:k) := U(1:k-2,k:k-1:k) =
                //                 = W(1:k-2,kw-1:kw) * ( D(k-1:k,k-1:k)**(-1) )
                //
                if (k > 2) {
                    //
                    //                 Factor out the columns of the inverse of 2-by-2 pivot
                    //                 block D, so that each column contains 1, to reduce the
                    //                 number of FLOPS when we multiply panel
                    //                 ( W(kw-1) W(kw) ) by this inverse, i.e. by D**(-1).
                    //
                    //                 D**(-1) = ( d11 cj(d21) )**(-1) =
                    //                           ( d21    d22 )
                    //
                    //                 = 1/(d11*d22-|d21|**2) * ( ( d22) (-cj(d21) ) ) =
                    //                                          ( (-d21) (     d11 ) )
                    //
                    //                 = 1/(|d21|**2) * 1/((d11/cj(d21))*(d22/d21)-1) *
                    //
                    //                   * ( d21*( d22/d21 ) conj(d21)*(           - 1 ) ) =
                    //                     (     (      -1 )           ( d11/conj(d21) ) )
                    //
                    //                 = 1/(|d21|**2) * 1/(D22*D11-1) *
                    //
                    //                   * ( d21*( D11 ) conj(d21)*(  -1 ) ) =
                    //                     (     (  -1 )           ( D22 ) )
                    //
                    //                 = (1/|d21|**2) * T * ( d21*( D11 ) conj(d21)*(  -1 ) ) =
                    //                                      (     (  -1 )           ( D22 ) )
                    //
                    //                 = ( (T/conj(d21))*( D11 ) (T/d21)*(  -1 ) ) =
                    //                   (               (  -1 )         ( D22 ) )
                    //
                    //                 = ( conj(D21)*( D11 ) D21*(  -1 ) )
                    //                   (           (  -1 )     ( D22 ) ),
                    //
                    //                 where D11 = d22/d21,
                    //                       D22 = d11/conj(d21),
                    //                       D21 = T/d21,
                    //                       T = 1/(D22*D11-1).
                    //
                    //                 (NOTE: No need to check for division by ZERO,
                    //                  since that was ensured earlier in pivot search:
                    //                  (a) d21 != 0, since in 2x2 pivot case(4)
                    //                      |d21| should be larger than |d11| and |d22|;
                    //                  (b) (D22*D11 - 1) != 0, since from (a),
                    //                      both |D11| < 1, |D22| < 1, hence |D22*D11| << 1.)
                    //
                    d21 = w[((k - 1) - 1) + (kw - 1) * ldw];
                    d11 = w[(k - 1) + (kw - 1) * ldw] / conj(d21);
                    d22 = w[((k - 1) - 1) + ((kw - 1) - 1) * ldw] / d21;
                    t = one / ((d11 * d22).real() - one);
                    d21 = t / d21;
                    //
                    //                 Update elements in columns A(k-1) and A(k) as
                    //                 dot products of rows of ( W(kw-1) W(kw) ) and columns
                    //                 of D**(-1)
                    //
                    for (j = 1; j <= k - 2; j = j + 1) {
                        a[(j - 1) + ((k - 1) - 1) * lda] = d21 * (d11 * w[(j - 1) + ((kw - 1) - 1) * ldw] - w[(j - 1) + (kw - 1) * ldw]);
                        a[(j - 1) + (k - 1) * lda] = conj(d21) * (d22 * w[(j - 1) + (kw - 1) * ldw] - w[(j - 1) + ((kw - 1) - 1) * ldw]);
                    }
                }
                //
                //              Copy D(k) to A
                //
                a[((k - 1) - 1) + ((k - 1) - 1) * lda] = w[((k - 1) - 1) + ((kw - 1) - 1) * ldw];
                a[((k - 1) - 1) + (k - 1) * lda] = w[((k - 1) - 1) + (kw - 1) * ldw];
                a[(k - 1) + (k - 1) * lda] = w[(k - 1) + (kw - 1) * ldw];
                //
                //              (2) Conjugate columns W(kw) and W(kw-1)
                //
                Clacgv(k - 1, &w[(kw - 1) * ldw], 1);
                Clacgv(k - 2, &w[((kw - 1) - 1) * ldw], 1);
                //
            }
            //
        }
        //
        //        Store details of the interchanges in IPIV
        //
        if (kstep == 1) {
            ipiv[k - 1] = kp;
        } else {
            ipiv[k - 1] = -kp;
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
        //        A11 := A11 - U12*D*U12**H = A11 - U12*W**H
        //
        //        computing blocks of NB columns at a time (note that conj(W) is
        //        actually stored)
        //
        for (j = ((k - 1) / nb) * nb + 1; j >= 1; j = j - nb) {
            jb = min(nb, k - j + 1);
            //
            //           Update the upper triangle of the diagonal block
            //
            for (jj = j; jj <= j + jb - 1; jj = jj + 1) {
                a[(jj - 1) + (jj - 1) * lda] = a[(jj - 1) + (jj - 1) * lda].real();
                Cgemv("No transpose", jj - j + 1, n - k, -cone, &a[(j - 1) + ((k + 1) - 1) * lda], lda, &w[(jj - 1) + ((kw + 1) - 1) * ldw], ldw, cone, &a[(j - 1) + (jj - 1) * lda], 1);
                a[(jj - 1) + (jj - 1) * lda] = a[(jj - 1) + (jj - 1) * lda].real();
            }
            //
            //           Update the rectangular superdiagonal block
            //
            Cgemm("No transpose", "Transpose", j - 1, jb, n - k, -cone, &a[((k + 1) - 1) * lda], lda, &w[(j - 1) + ((kw + 1) - 1) * ldw], ldw, cone, &a[(j - 1) * lda], lda);
        }
        //
        //        Put U12 in standard form by partially undoing the interchanges
        //        in columns k+1:n looping backwards from k+1 to n
        //
        j = k + 1;
    statement_60:
        //
        //           Undo the interchanges (if any) of rows JJ and JP at each
        //           step J
        //
        //           (Here, J is a diagonal index)
        jj = j;
        jp = ipiv[j - 1];
        if (jp < 0) {
            jp = -jp;
            //              (Here, J is a diagonal index)
            j++;
        }
        //           (NOTE: Here, J is used to determine row length. Length N-J+1
        //           of the rows to swap back doesn't include diagonal element)
        j++;
        if (jp != jj && j <= n) {
            Cswap(n - j + 1, &a[(jp - 1) + (j - 1) * lda], lda, &a[(jj - 1) + (j - 1) * lda], lda);
        }
        if (j < n) {
            goto statement_60;
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
        //        for use in updating A22 (note that conj(W) is actually stored)
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
        //
        //        Copy column K of A to column K of W and update it
        //
        w[(k - 1) + (k - 1) * ldw] = a[(k - 1) + (k - 1) * lda].real();
        if (k < n) {
            Ccopy(n - k, &a[((k + 1) - 1) + (k - 1) * lda], 1, &w[((k + 1) - 1) + (k - 1) * ldw], 1);
        }
        Cgemv("No transpose", n - k + 1, k - 1, -cone, &a[(k - 1)], lda, &w[(k - 1)], ldw, cone, &w[(k - 1) + (k - 1) * ldw], 1);
        w[(k - 1) + (k - 1) * ldw] = w[(k - 1) + (k - 1) * ldw].real();
        //
        //        Determine rows and columns to be interchanged and whether
        //        a 1-by-1 or 2-by-2 pivot block will be used
        //
        absakk = abs(w[(k - 1) + (k - 1) * ldw].real());
        //
        //        IMAX is the row-index of the largest off-diagonal element in
        //        column K, and COLMAX is its absolute value.
        //        Determine both COLMAX and IMAX.
        //
        if (k < n) {
            imax = k + iCamax(n - k, &w[((k + 1) - 1) + (k - 1) * ldw], 1);
            colmax = cabs1(w[(imax - 1) + (k - 1) * ldw]);
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
            a[(k - 1) + (k - 1) * lda] = a[(k - 1) + (k - 1) * lda].real();
        } else {
            //
            //           ============================================================
            //
            //           BEGIN pivot search
            //
            //           Case(1)
            if (absakk >= alpha * colmax) {
                //
                //              no interchange, use 1-by-1 pivot block
                //
                kp = k;
            } else {
                //
                //              BEGIN pivot search along IMAX row
                //
                //              Copy column IMAX to column K+1 of W and update it
                //
                Ccopy(imax - k, &a[(imax - 1) + (k - 1) * lda], lda, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                Clacgv(imax - k, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                w[(imax - 1) + ((k + 1) - 1) * ldw] = a[(imax - 1) + (imax - 1) * lda].real();
                if (imax < n) {
                    Ccopy(n - imax, &a[((imax + 1) - 1) + (imax - 1) * lda], 1, &w[((imax + 1) - 1) + ((k + 1) - 1) * ldw], 1);
                }
                Cgemv("No transpose", n - k + 1, k - 1, -cone, &a[(k - 1)], lda, &w[(imax - 1)], ldw, cone, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                w[(imax - 1) + ((k + 1) - 1) * ldw] = w[(imax - 1) + ((k + 1) - 1) * ldw].real();
                //
                //              JMAX is the column-index of the largest off-diagonal
                //              element in row IMAX, and ROWMAX is its absolute value.
                //              Determine only ROWMAX.
                //
                jmax = k - 1 + iCamax(imax - k, &w[(k - 1) + ((k + 1) - 1) * ldw], 1);
                rowmax = cabs1(w[(jmax - 1) + ((k + 1) - 1) * ldw]);
                if (imax < n) {
                    jmax = imax + iCamax(n - imax, &w[((imax + 1) - 1) + ((k + 1) - 1) * ldw], 1);
                    rowmax = max(rowmax, cabs1(w[(jmax - 1) + ((k + 1) - 1) * ldw]));
                }
                //
                //              Case(2)
                if (absakk >= alpha * colmax * (colmax / rowmax)) {
                    //
                    //                 no interchange, use 1-by-1 pivot block
                    //
                    kp = k;
                    //
                    //              Case(3)
                } else if (abs(w[(imax - 1) + ((k + 1) - 1) * ldw].real()) >= alpha * rowmax) {
                    //
                    //                 interchange rows and columns K and IMAX, use 1-by-1
                    //                 pivot block
                    //
                    kp = imax;
                    //
                    //                 copy column K+1 of W to column K of W
                    //
                    Ccopy(n - k + 1, &w[(k - 1) + ((k + 1) - 1) * ldw], 1, &w[(k - 1) + (k - 1) * ldw], 1);
                    //
                    //              Case(4)
                } else {
                    //
                    //                 interchange rows and columns K+1 and IMAX, use 2-by-2
                    //                 pivot block
                    //
                    kp = imax;
                    kstep = 2;
                }
                //
                //              END pivot search along IMAX row
                //
            }
            //
            //           END pivot search
            //
            //           ============================================================
            //
            //           KK is the column of A where pivoting step stopped
            //
            kk = k + kstep - 1;
            //
            //           Interchange rows and columns KP and KK.
            //           Updated column KP is already stored in column KK of W.
            //
            if (kp != kk) {
                //
                //              Copy non-updated column KK to column KP of submatrix A
                //              at step K. No need to copy element into column K
                //              (or K and K+1 for 2-by-2 pivot) of A, since these columns
                //              will be later overwritten.
                //
                a[(kp - 1) + (kp - 1) * lda] = a[(kk - 1) + (kk - 1) * lda].real();
                Ccopy(kp - kk - 1, &a[((kk + 1) - 1) + (kk - 1) * lda], 1, &a[(kp - 1) + ((kk + 1) - 1) * lda], lda);
                Clacgv(kp - kk - 1, &a[(kp - 1) + ((kk + 1) - 1) * lda], lda);
                if (kp < n) {
                    Ccopy(n - kp, &a[((kp + 1) - 1) + (kk - 1) * lda], 1, &a[((kp + 1) - 1) + (kp - 1) * lda], 1);
                }
                //
                //              Interchange rows KK and KP in first K-1 columns of A
                //              (columns K (or K and K+1 for 2-by-2 pivot) of A will be
                //              later overwritten). Interchange rows KK and KP
                //              in first KK columns of W.
                //
                if (k > 1) {
                    Cswap(k - 1, &a[(kk - 1)], lda, &a[(kp - 1)], lda);
                }
                Cswap(kk, &w[(kk - 1)], ldw, &w[(kp - 1)], ldw);
            }
            //
            if (kstep == 1) {
                //
                //              1-by-1 pivot block D(k): column k of W now holds
                //
                //              W(k) = L(k)*D(k),
                //
                //              where L(k) is the k-th column of L
                //
                //              (1) Store subdiag. elements of column L(k)
                //              and 1-by-1 block D(k) in column k of A.
                //              (NOTE: Diagonal element L(k,k) is a UNIT element
                //              and not stored)
                //                 A(k,k) := D(k,k) = W(k,k)
                //                 A(k+1:N,k) := L(k+1:N,k) = W(k+1:N,k)/D(k,k)
                //
                //              (NOTE: No need to use for Hermitian matrix
                //              A( K, K ) = DBLE( W( K, K) ) to separately copy diagonal
                //              element D(k,k) from W (potentially saves only one load))
                Ccopy(n - k + 1, &w[(k - 1) + (k - 1) * ldw], 1, &a[(k - 1) + (k - 1) * lda], 1);
                if (k < n) {
                    //
                    //                 (NOTE: No need to check if A(k,k) is NOT ZERO,
                    //                  since that was ensured earlier in pivot search:
                    //                  case A(k,k) = 0 falls into 2x2 pivot case(4))
                    //
                    r1 = one / a[(k - 1) + (k - 1) * lda].real();
                    CRscal(n - k, r1, &a[((k + 1) - 1) + (k - 1) * lda], 1);
                    //
                    //                 (2) Conjugate column W(k)
                    //
                    Clacgv(n - k, &w[((k + 1) - 1) + (k - 1) * ldw], 1);
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
                //              (1) Store L(k+2:N,k) and L(k+2:N,k+1) and 2-by-2
                //              block D(k:k+1,k:k+1) in columns k and k+1 of A.
                //              (NOTE: 2-by-2 diagonal block L(k:k+1,k:k+1) is a UNIT
                //              block and not stored)
                //                 A(k:k+1,k:k+1) := D(k:k+1,k:k+1) = W(k:k+1,k:k+1)
                //                 A(k+2:N,k:k+1) := L(k+2:N,k:k+1) =
                //                 = W(k+2:N,k:k+1) * ( D(k:k+1,k:k+1)**(-1) )
                //
                if (k < n - 1) {
                    //
                    //                 Factor out the columns of the inverse of 2-by-2 pivot
                    //                 block D, so that each column contains 1, to reduce the
                    //                 number of FLOPS when we multiply panel
                    //                 ( W(kw-1) W(kw) ) by this inverse, i.e. by D**(-1).
                    //
                    //                 D**(-1) = ( d11 cj(d21) )**(-1) =
                    //                           ( d21    d22 )
                    //
                    //                 = 1/(d11*d22-|d21|**2) * ( ( d22) (-cj(d21) ) ) =
                    //                                          ( (-d21) (     d11 ) )
                    //
                    //                 = 1/(|d21|**2) * 1/((d11/cj(d21))*(d22/d21)-1) *
                    //
                    //                   * ( d21*( d22/d21 ) conj(d21)*(           - 1 ) ) =
                    //                     (     (      -1 )           ( d11/conj(d21) ) )
                    //
                    //                 = 1/(|d21|**2) * 1/(D22*D11-1) *
                    //
                    //                   * ( d21*( D11 ) conj(d21)*(  -1 ) ) =
                    //                     (     (  -1 )           ( D22 ) )
                    //
                    //                 = (1/|d21|**2) * T * ( d21*( D11 ) conj(d21)*(  -1 ) ) =
                    //                                      (     (  -1 )           ( D22 ) )
                    //
                    //                 = ( (T/conj(d21))*( D11 ) (T/d21)*(  -1 ) ) =
                    //                   (               (  -1 )         ( D22 ) )
                    //
                    //                 = ( conj(D21)*( D11 ) D21*(  -1 ) )
                    //                   (           (  -1 )     ( D22 ) ),
                    //
                    //                 where D11 = d22/d21,
                    //                       D22 = d11/conj(d21),
                    //                       D21 = T/d21,
                    //                       T = 1/(D22*D11-1).
                    //
                    //                 (NOTE: No need to check for division by ZERO,
                    //                  since that was ensured earlier in pivot search:
                    //                  (a) d21 != 0, since in 2x2 pivot case(4)
                    //                      |d21| should be larger than |d11| and |d22|;
                    //                  (b) (D22*D11 - 1) != 0, since from (a),
                    //                      both |D11| < 1, |D22| < 1, hence |D22*D11| << 1.)
                    //
                    d21 = w[((k + 1) - 1) + (k - 1) * ldw];
                    d11 = w[((k + 1) - 1) + ((k + 1) - 1) * ldw] / d21;
                    d22 = w[(k - 1) + (k - 1) * ldw] / conj(d21);
                    t = one / ((d11 * d22).real() - one);
                    d21 = t / d21;
                    //
                    //                 Update elements in columns A(k) and A(k+1) as
                    //                 dot products of rows of ( W(k) W(k+1) ) and columns
                    //                 of D**(-1)
                    //
                    for (j = k + 2; j <= n; j = j + 1) {
                        a[(j - 1) + (k - 1) * lda] = conj(d21) * (d11 * w[(j - 1) + (k - 1) * ldw] - w[(j - 1) + ((k + 1) - 1) * ldw]);
                        a[(j - 1) + ((k + 1) - 1) * lda] = d21 * (d22 * w[(j - 1) + ((k + 1) - 1) * ldw] - w[(j - 1) + (k - 1) * ldw]);
                    }
                }
                //
                //              Copy D(k) to A
                //
                a[(k - 1) + (k - 1) * lda] = w[(k - 1) + (k - 1) * ldw];
                a[((k + 1) - 1) + (k - 1) * lda] = w[((k + 1) - 1) + (k - 1) * ldw];
                a[((k + 1) - 1) + ((k + 1) - 1) * lda] = w[((k + 1) - 1) + ((k + 1) - 1) * ldw];
                //
                //              (2) Conjugate columns W(k) and W(k+1)
                //
                Clacgv(n - k, &w[((k + 1) - 1) + (k - 1) * ldw], 1);
                Clacgv(n - k - 1, &w[((k + 2) - 1) + ((k + 1) - 1) * ldw], 1);
                //
            }
            //
        }
        //
        //        Store details of the interchanges in IPIV
        //
        if (kstep == 1) {
            ipiv[k - 1] = kp;
        } else {
            ipiv[k - 1] = -kp;
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
        //        A22 := A22 - L21*D*L21**H = A22 - L21*W**H
        //
        //        computing blocks of NB columns at a time (note that conj(W) is
        //        actually stored)
        //
        for (j = k; j <= n; j = j + nb) {
            jb = min(nb, n - j + 1);
            //
            //           Update the lower triangle of the diagonal block
            //
            for (jj = j; jj <= j + jb - 1; jj = jj + 1) {
                a[(jj - 1) + (jj - 1) * lda] = a[(jj - 1) + (jj - 1) * lda].real();
                Cgemv("No transpose", j + jb - jj, k - 1, -cone, &a[(jj - 1)], lda, &w[(jj - 1)], ldw, cone, &a[(jj - 1) + (jj - 1) * lda], 1);
                a[(jj - 1) + (jj - 1) * lda] = a[(jj - 1) + (jj - 1) * lda].real();
            }
            //
            //           Update the rectangular subdiagonal block
            //
            if (j + jb <= n) {
                Cgemm("No transpose", "Transpose", n - j - jb + 1, jb, k - 1, -cone, &a[((j + jb) - 1)], lda, &w[(j - 1)], ldw, cone, &a[((j + jb) - 1) + (j - 1) * lda], lda);
            }
        }
        //
        //        Put L21 in standard form by partially undoing the interchanges
        //        of rows in columns 1:k-1 looping backwards from k-1 to 1
        //
        j = k - 1;
    statement_120:
        //
        //           Undo the interchanges (if any) of rows JJ and JP at each
        //           step J
        //
        //           (Here, J is a diagonal index)
        jj = j;
        jp = ipiv[j - 1];
        if (jp < 0) {
            jp = -jp;
            //              (Here, J is a diagonal index)
            j = j - 1;
        }
        //           (NOTE: Here, J is used to determine row length. Length J
        //           of the rows to swap back doesn't include diagonal element)
        j = j - 1;
        if (jp != jj && j >= 1) {
            Cswap(j, &a[(jp - 1)], lda, &a[(jj - 1)], lda);
        }
        if (j > 1) {
            goto statement_120;
        }
        //
        //        Set KB to the number of columns factorized
        //
        kb = k - 1;
        //
    }
    //
    //     End of Clahef
    //
}
