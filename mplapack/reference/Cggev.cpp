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

inline REAL abs1(COMPLEX x) { return abs(x.real()) + abs(x.imag()); }

void Cggev(const char *jobvl, const char *jobvr, INTEGER const n, COMPLEX *a, INTEGER const lda, COMPLEX *b, INTEGER const ldb, COMPLEX *alpha, COMPLEX *beta, COMPLEX *vl, INTEGER const ldvl, COMPLEX *vr, INTEGER const ldvr, COMPLEX *work, INTEGER const lwork, REAL *rwork, INTEGER &info) {
    COMPLEX x = 0.0;
    INTEGER ijobvl = 0;
    bool ilvl = false;
    INTEGER ijobvr = 0;
    bool ilvr = false;
    bool ilv = false;
    bool lquery = false;
    INTEGER lwkmin = 0;
    INTEGER lwkopt = 0;
    REAL eps = 0.0;
    REAL smlnum = 0.0;
    const REAL one = 1.0;
    REAL bignum = 0.0;
    REAL anrm = 0.0;
    bool ilascl = false;
    const REAL zero = 0.0;
    REAL anrmto = 0.0;
    INTEGER ierr = 0;
    REAL bnrm = 0.0;
    bool ilbscl = false;
    REAL bnrmto = 0.0;
    INTEGER ileft = 0;
    INTEGER iright = 0;
    INTEGER irwrk = 0;
    INTEGER ilo = 0;
    INTEGER ihi = 0;
    INTEGER irows = 0;
    INTEGER icols = 0;
    INTEGER itau = 0;
    INTEGER iwrk = 0;
    const COMPLEX czero = COMPLEX(0.0, 0.0);
    const COMPLEX cone = COMPLEX(1.0, 0.0);
    char chtemp;
    bool ldumma[1];
    INTEGER in = 0;
    INTEGER jc = 0;
    REAL temp = 0.0;
    INTEGER jr = 0;
    //
    //  -- LAPACK driver routine --
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
    //     .. Local Arrays ..
    //     ..
    //     .. External Subroutines ..
    //     ..
    //     .. External Functions ..
    //     ..
    //     .. Intrinsic Functions ..
    //     ..
    //     .. Statement Functions ..
    //     ..
    //     .. Statement Function definitions ..
    //     ..
    //     .. Executable Statements ..
    //
    //     Decode the input arguments
    //
    if (Mlsame(jobvl, "N")) {
        ijobvl = 1;
        ilvl = false;
    } else if (Mlsame(jobvl, "V")) {
        ijobvl = 2;
        ilvl = true;
    } else {
        ijobvl = -1;
        ilvl = false;
    }
    //
    if (Mlsame(jobvr, "N")) {
        ijobvr = 1;
        ilvr = false;
    } else if (Mlsame(jobvr, "V")) {
        ijobvr = 2;
        ilvr = true;
    } else {
        ijobvr = -1;
        ilvr = false;
    }
    ilv = ilvl || ilvr;
    //
    //     Test the input arguments
    //
    info = 0;
    lquery = (lwork == -1);
    if (ijobvl <= 0) {
        info = -1;
    } else if (ijobvr <= 0) {
        info = -2;
    } else if (n < 0) {
        info = -3;
    } else if (lda < max((INTEGER)1, n)) {
        info = -5;
    } else if (ldb < max((INTEGER)1, n)) {
        info = -7;
    } else if (ldvl < 1 || (ilvl && ldvl < n)) {
        info = -11;
    } else if (ldvr < 1 || (ilvr && ldvr < n)) {
        info = -13;
    }
    //
    //     Compute workspace
    //      (Note: Comments in the code beginning "Workspace:" describe the
    //       minimal amount of workspace needed at that point in the code,
    //       as well as the preferred amount for good performance.
    //       NB refers to the optimal block size for the immediately
    //       following subroutine, as returned by iMlaenv. The workspace is
    //       computed assuming ILO = 1 and IHI = N, the worst case.)
    //
    if (info == 0) {
        lwkmin = max((INTEGER)1, 2 * n);
        lwkopt = max({(INTEGER)1, n + n * iMlaenv(1, "Cgeqrf", " ", n, 1, n, 0)});
        lwkopt = max({lwkopt, n + n * iMlaenv(1, "Cunmqr", " ", n, 1, n, 0)});
        if (ilvl) {
            lwkopt = max({lwkopt, n + n * iMlaenv(1, "Cungqr", " ", n, 1, n, -1)});
        }
        work[1 - 1] = lwkopt;
        //
        if (lwork < lwkmin && !lquery) {
            info = -15;
        }
    }
    //
    if (info != 0) {
        Mxerbla("Cggev", -info);
        return;
    } else if (lquery) {
        return;
    }
    //
    //     Quick return if possible
    //
    if (n == 0) {
        return;
    }
    //
    //     Get machine constants
    //
    eps = Rlamch("E") * Rlamch("B");
    smlnum = Rlamch("S");
    bignum = one / smlnum;
    smlnum = sqrt(smlnum) / eps;
    bignum = one / smlnum;
    //
    //     Scale A if max element outside range [SMLNUM,BIGNUM]
    //
    anrm = Clange("M", n, n, a, lda, rwork);
    ilascl = false;
    if (anrm > zero && anrm < smlnum) {
        anrmto = smlnum;
        ilascl = true;
    } else if (anrm > bignum) {
        anrmto = bignum;
        ilascl = true;
    }
    if (ilascl) {
        Clascl("G", 0, 0, anrm, anrmto, n, n, a, lda, ierr);
    }
    //
    //     Scale B if max element outside range [SMLNUM,BIGNUM]
    //
    bnrm = Clange("M", n, n, b, ldb, rwork);
    ilbscl = false;
    if (bnrm > zero && bnrm < smlnum) {
        bnrmto = smlnum;
        ilbscl = true;
    } else if (bnrm > bignum) {
        bnrmto = bignum;
        ilbscl = true;
    }
    if (ilbscl) {
        Clascl("G", 0, 0, bnrm, bnrmto, n, n, b, ldb, ierr);
    }
    //
    //     Permute the matrices A, B to isolate eigenvalues if possible
    //     (Real Workspace: need 6*N)
    //
    ileft = 1;
    iright = n + 1;
    irwrk = iright + n;
    Cggbal("P", n, a, lda, b, ldb, ilo, ihi, &rwork[ileft - 1], &rwork[iright - 1], &rwork[irwrk - 1], ierr);
    //
    //     Reduce B to triangular form (QR decomposition of B)
    //     (Complex Workspace: need N, prefer N*NB)
    //
    irows = ihi + 1 - ilo;
    if (ilv) {
        icols = n + 1 - ilo;
    } else {
        icols = irows;
    }
    itau = 1;
    iwrk = itau + irows;
    Cgeqrf(irows, icols, &b[(ilo - 1) + (ilo - 1) * ldb], ldb, &work[itau - 1], &work[iwrk - 1], lwork + 1 - iwrk, ierr);
    //
    //     Apply the orthogonal transformation to matrix A
    //     (Complex Workspace: need N, prefer N*NB)
    //
    Cunmqr("L", "C", irows, icols, irows, &b[(ilo - 1) + (ilo - 1) * ldb], ldb, &work[itau - 1], &a[(ilo - 1) + (ilo - 1) * lda], lda, &work[iwrk - 1], lwork + 1 - iwrk, ierr);
    //
    //     Initialize VL
    //     (Complex Workspace: need N, prefer N*NB)
    //
    if (ilvl) {
        Claset("Full", n, n, czero, cone, vl, ldvl);
        if (irows > 1) {
            Clacpy("L", irows - 1, irows - 1, &b[((ilo + 1) - 1) + (ilo - 1) * ldb], ldb, &vl[((ilo + 1) - 1) + (ilo - 1) * ldvl], ldvl);
        }
        Cungqr(irows, irows, irows, &vl[(ilo - 1) + (ilo - 1) * ldvl], ldvl, &work[itau - 1], &work[iwrk - 1], lwork + 1 - iwrk, ierr);
    }
    //
    //     Initialize VR
    //
    if (ilvr) {
        Claset("Full", n, n, czero, cone, vr, ldvr);
    }
    //
    //     Reduce to generalized Hessenberg form
    //
    if (ilv) {
        //
        //        Eigenvectors requested -- work on whole matrix.
        //
        Cgghrd(jobvl, jobvr, n, ilo, ihi, a, lda, b, ldb, vl, ldvl, vr, ldvr, ierr);
    } else {
        Cgghrd("N", "N", irows, 1, irows, &a[(ilo - 1) + (ilo - 1) * lda], lda, &b[(ilo - 1) + (ilo - 1) * ldb], ldb, vl, ldvl, vr, ldvr, ierr);
    }
    //
    //     Perform QZ algorithm (Compute eigenvalues, and optionally, the
    //     Schur form and Schur vectors)
    //     (Complex Workspace: need N)
    //     (Real Workspace: need N)
    //
    iwrk = itau;
    if (ilv) {
        chtemp = 'S';
    } else {
        chtemp = 'E';
    }
    Chgeqz(&chtemp, jobvl, jobvr, n, ilo, ihi, a, lda, b, ldb, alpha, beta, vl, ldvl, vr, ldvr, &work[iwrk - 1], lwork + 1 - iwrk, &rwork[irwrk - 1], ierr);
    if (ierr != 0) {
        if (ierr > 0 && ierr <= n) {
            info = ierr;
        } else if (ierr > n && ierr <= 2 * n) {
            info = ierr - n;
        } else {
            info = n + 1;
        }
        goto statement_70;
    }
    //
    //     Compute Eigenvectors
    //     (Real Workspace: need 2*N)
    //     (Complex Workspace: need 2*N)
    //
    if (ilv) {
        if (ilvl) {
            if (ilvr) {
                chtemp = 'B';
            } else {
                chtemp = 'L';
            }
        } else {
            chtemp = 'R';
        }
        //
        Ctgevc(&chtemp, "B", ldumma, n, a, lda, b, ldb, vl, ldvl, vr, ldvr, n, in, &work[iwrk - 1], &rwork[irwrk - 1], ierr);
        if (ierr != 0) {
            info = n + 2;
            goto statement_70;
        }
        //
        //        Undo balancing on VL and VR and normalization
        //        (Workspace: none needed)
        //
        if (ilvl) {
            Cggbak("P", "L", n, ilo, ihi, &rwork[ileft - 1], &rwork[iright - 1], n, vl, ldvl, ierr);
            for (jc = 1; jc <= n; jc = jc + 1) {
                temp = zero;
                for (jr = 1; jr <= n; jr = jr + 1) {
                    temp = max(temp, abs1(vl[(jr - 1) + (jc - 1) * ldvl]));
                }
                if (temp < smlnum) {
                    goto statement_30;
                }
                temp = one / temp;
                for (jr = 1; jr <= n; jr = jr + 1) {
                    vl[(jr - 1) + (jc - 1) * ldvl] = vl[(jr - 1) + (jc - 1) * ldvl] * temp;
                }
            statement_30:;
            }
        }
        if (ilvr) {
            Cggbak("P", "R", n, ilo, ihi, &rwork[ileft - 1], &rwork[iright - 1], n, vr, ldvr, ierr);
            for (jc = 1; jc <= n; jc = jc + 1) {
                temp = zero;
                for (jr = 1; jr <= n; jr = jr + 1) {
                    temp = max(temp, abs1(vr[(jr - 1) + (jc - 1) * ldvr]));
                }
                if (temp < smlnum) {
                    goto statement_60;
                }
                temp = one / temp;
                for (jr = 1; jr <= n; jr = jr + 1) {
                    vr[(jr - 1) + (jc - 1) * ldvr] = vr[(jr - 1) + (jc - 1) * ldvr] * temp;
                }
            statement_60:;
            }
        }
    }
//
//     Undo scaling if necessary
//
statement_70:
    //
    if (ilascl) {
        Clascl("G", 0, 0, anrmto, anrm, n, 1, alpha, n, ierr);
    }
    //
    if (ilbscl) {
        Clascl("G", 0, 0, bnrmto, bnrm, n, 1, beta, n, ierr);
    }
    //
    work[1 - 1] = lwkopt;
    //
    //     End of Cggev
    //
}
