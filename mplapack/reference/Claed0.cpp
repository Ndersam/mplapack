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

void Claed0(INTEGER const qsiz, INTEGER const n, REAL *d, REAL *e, COMPLEX *q, INTEGER const ldq, COMPLEX *qstore, INTEGER const ldqs, REAL *rwork, INTEGER *iwork, INTEGER &info) {
    INTEGER smlsiz = 0;
    INTEGER subpbs = 0;
    INTEGER tlvls = 0;
    INTEGER j = 0;
    INTEGER spm1 = 0;
    INTEGER i = 0;
    INTEGER submat = 0;
    INTEGER smm1 = 0;
    INTEGER indxq = 0;
    const REAL two = 2.e+0;
    REAL temp = 0.0;
    INTEGER lgn = 0;
    INTEGER iprmpt = 0;
    INTEGER iperm = 0;
    INTEGER iqptr = 0;
    INTEGER igivpt = 0;
    INTEGER igivcl = 0;
    INTEGER igivnm = 0;
    INTEGER iq = 0;
    INTEGER iwrem = 0;
    INTEGER curr = 0;
    INTEGER matsiz = 0;
    INTEGER ll = 0;
    INTEGER k = 0;
    INTEGER curlvl = 0;
    INTEGER spm2 = 0;
    INTEGER msd2 = 0;
    INTEGER curprb = 0;
    INTEGER ldqstore = ldqs;
    //
    //     Test the input parameters.
    //
    info = 0;
    //
    //     IF( ICOMPQ .LT. 0 .OR. ICOMPQ .GT. 2 ) THEN
    //        INFO = -1
    //     ELSE IF( ( ICOMPQ .EQ. 1 ) .AND. ( QSIZ .LT. MAX( 0, N ) ) )
    //    $        THEN
    if (qsiz < max((INTEGER)0, n)) {
        info = -1;
    } else if (n < 0) {
        info = -2;
    } else if (ldq < max((INTEGER)1, n)) {
        info = -6;
    } else if (ldqs < max((INTEGER)1, n)) {
        info = -8;
    }
    if (info != 0) {
        Mxerbla("Claed0", -info);
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0) {
        return;
    }
    //
    smlsiz = iMlaenv(9, "Claed0", " ", 0, 0, 0, 0);
    //
    //     Determine the size and placement of the submatrices, and save in
    //     the leading elements of IWORK.
    //
    iwork[1 - 1] = n;
    subpbs = 1;
    tlvls = 0;
statement_10:
    if (iwork[subpbs - 1] > smlsiz) {
        for (j = subpbs; j >= 1; j = j - 1) {
            iwork[(2 * j) - 1] = (iwork[j - 1] + 1) / 2;
            iwork[(2 * j - 1) - 1] = iwork[j - 1] / 2;
        }
        tlvls++;
        subpbs = 2 * subpbs;
        goto statement_10;
    }
    for (j = 2; j <= subpbs; j = j + 1) {
        iwork[j - 1] += iwork[(j - 1) - 1];
    }
    //
    //     Divide the matrix into SUBPBS submatrices of size at most SMLSIZ+1
    //     using rank-1 modifications (cuts).
    //
    spm1 = subpbs - 1;
    for (i = 1; i <= spm1; i = i + 1) {
        submat = iwork[i - 1] + 1;
        smm1 = submat - 1;
        d[smm1 - 1] = d[smm1 - 1] - abs(e[smm1 - 1]);
        d[submat - 1] = d[submat - 1] - abs(e[smm1 - 1]);
    }
    //
    indxq = 4 * n + 3;
    //
    //     Set up workspaces for eigenvalues only/accumulate new vectors
    //     routine
    //
    temp = log(castREAL(n)) / log(two);
    lgn = castINTEGER(temp);
    if (pow((double)2, (double)lgn) < n) {
        lgn++;
    }
    if (pow((double)2, (double)lgn) < n) {
        lgn++;
    }
    iprmpt = indxq + n + 1;
    iperm = iprmpt + n * lgn;
    iqptr = iperm + n * lgn;
    igivpt = iqptr + n + 2;
    igivcl = igivpt + n * lgn;
    //
    igivnm = 1;
    iq = igivnm + 2 * n * lgn;
    iwrem = iq + n * n + 1;
    //     Initialize pointers
    for (i = 0; i <= subpbs; i = i + 1) {
        iwork[(iprmpt + i) - 1] = 1;
        iwork[(igivpt + i) - 1] = 1;
    }
    iwork[iqptr - 1] = 1;
    //
    //     Solve each submatrix eigenproblem at the bottom of the divide and
    //     conquer tree.
    //
    curr = 0;
    for (i = 0; i <= spm1; i = i + 1) {
        if (i == 0) {
            submat = 1;
            matsiz = iwork[1 - 1];
        } else {
            submat = iwork[i - 1] + 1;
            matsiz = iwork[(i + 1) - 1] - iwork[i - 1];
        }
        ll = iq - 1 + iwork[(iqptr + curr) - 1];
        Rsteqr("I", matsiz, &d[submat - 1], &e[submat - 1], &rwork[ll - 1], matsiz, rwork, info);
        Clacrm(qsiz, matsiz, &q[(submat - 1) * ldq], ldq, &rwork[ll - 1], matsiz, &qstore[(submat - 1) * ldqstore], ldqs, &rwork[iwrem - 1]);
        iwork[(iqptr + curr + 1) - 1] = iwork[(iqptr + curr) - 1] + matsiz * matsiz;
        curr++;
        if (info > 0) {
            info = submat * (n + 1) + submat + matsiz - 1;
            return;
        }
        k = 1;
        for (j = submat; j <= iwork[(i + 1) - 1]; j = j + 1) {
            iwork[(indxq + j) - 1] = k;
            k++;
        }
    }
    //
    //     Successively merge eigensystems of adjacent submatrices
    //     into eigensystem for the corresponding larger matrix.
    //
    //     while ( SUBPBS > 1 )
    //
    curlvl = 1;
statement_80:
    if (subpbs > 1) {
        spm2 = subpbs - 2;
        for (i = 0; i <= spm2; i = i + 2) {
            if (i == 0) {
                submat = 1;
                matsiz = iwork[2 - 1];
                msd2 = iwork[1 - 1];
                curprb = 0;
            } else {
                submat = iwork[i - 1] + 1;
                matsiz = iwork[(i + 2) - 1] - iwork[i - 1];
                msd2 = matsiz / 2;
                curprb++;
            }
            //
            //     Merge lower order eigensystems (of size MSD2 and MATSIZ - MSD2)
            //     into an eigensystem of size MATSIZ.  Claed7 handles the case
            //     when the eigenvectors of a full or band Hermitian matrix (which
            //     was reduced to tridiagonal form) are desired.
            //
            //     I am free to use Q as a valuable working space until Loop 150.
            //
            Claed7(matsiz, msd2, qsiz, tlvls, curlvl, curprb, &d[submat - 1], &qstore[(submat - 1) * ldqstore], ldqs, e[(submat + msd2 - 1) - 1], &iwork[(indxq + submat) - 1], &rwork[iq - 1], &iwork[iqptr - 1], &iwork[iprmpt - 1], &iwork[iperm - 1], &iwork[igivpt - 1], &iwork[igivcl - 1], &rwork[igivnm - 1], &q[(submat - 1) * ldq], &rwork[iwrem - 1], &iwork[(subpbs + 1) - 1], info);
            if (info > 0) {
                info = submat * (n + 1) + submat + matsiz - 1;
                return;
            }
            iwork[(i / 2 + 1) - 1] = iwork[(i + 2) - 1];
        }
        subpbs = subpbs / 2;
        curlvl++;
        goto statement_80;
    }
    //
    //     end while
    //
    //     Re-merge the eigenvalues/vectors which were deflated at the final
    //     merge step.
    //
    for (i = 1; i <= n; i = i + 1) {
        j = iwork[(indxq + i) - 1];
        rwork[i - 1] = d[j - 1];
        Ccopy(qsiz, &qstore[(j - 1) * ldqstore], 1, &q[(i - 1) * ldq], 1);
    }
    Rcopy(n, rwork, 1, d, 1);
    //
    //     End of Claed0
    //
}
