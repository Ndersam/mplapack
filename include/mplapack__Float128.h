/*
 * Copyright (c) 2012-2021
 *	Nakata, Maho
 * 	All rights reserved.
 *
 * $Id: mplapack_double.h,v 1.4 2010/08/07 03:15:46 nakatamaho Exp $
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

#ifndef _MPLAPACK__FLOAT128_H_
#define _MPLAPACK__FLOAT128_H_

#include "mplapack_config.h"

#if defined ___MPLAPACK_WANT_LIBQUADMATH___
#include "quadmath.h"
#endif

_Float128 Clangt(const char *norm, mplapackint const n, std::complex<_Float128> *dl, std::complex<_Float128> *d, std::complex<_Float128> *du);
_Float128 Clanhe(const char *norm, const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *work);
_Float128 Clanht(const char *norm, mplapackint const n, _Float128 *d, std::complex<_Float128> *e);
_Float128 Clansy(const char *norm, const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *work);
_Float128 RCsum1(mplapackint const n, std::complex<_Float128> *cx, mplapackint const incx);
_Float128 Rla_gerpvgrw(mplapackint const n, mplapackint const ncols, _Float128 *a, mplapackint const lda, _Float128 *af, mplapackint const ldaf);
_Float128 Rladiv2(_Float128 const &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 const &r, _Float128 const &t);
_Float128 Rladiv2(_Float128 const &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 const &r, _Float128 const &t);
_Float128 Rlamch__Float128(const char *cmach);
_Float128 Rlangt(const char *norm, mplapackint const n, _Float128 *dl, _Float128 *d, _Float128 *du);
_Float128 Rlanst(const char *norm, mplapackint const n, _Float128 *d, _Float128 *e);
_Float128 Rlansy(const char *norm, const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *work);
_Float128 Rlapy2(_Float128 const x, _Float128 const y);
_Float128 Rlapy3(_Float128 const x, _Float128 const y, _Float128 const z);
_Float128 abs1(std::complex<_Float128> ff);
_Float128 abs1(std::complex<_Float128> ff);
_Float128 abs1(std::complex<_Float128> ff);
_Float128 abssq(std::complex<_Float128> ff);
_Float128 abssq(std::complex<_Float128> ff);
bool Risnan(_Float128 const din);
bool Rlaisnan(_Float128 const din1, _Float128 const din2);
mplapackint Rlaneg(mplapackint const n, _Float128 *d, _Float128 *lld, _Float128 const sigma, _Float128 const, mplapackint const r);
mplapackint iCmax1(mplapackint const n, std::complex<_Float128> *zx, mplapackint const incx);
mplapackint iMladlc(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda);
mplapackint iMladlr(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda);
mplapackint iMlaenv__Float128(mplapackint ispec, const char *name, const char *opts, mplapackint n1, mplapackint n2, mplapackint n3, mplapackint n4);
mplapackint iMlazlc(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda);
mplapackint iMlazlr(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda);
std::complex<_Float128> Cladiv(std::complex<_Float128> const x, std::complex<_Float128> const y);
void CRrscl(mplapackint const n, _Float128 const sa, std::complex<_Float128> *sx, mplapackint const incx);
void Cgebak(const char *job, const char *side, mplapackint const n, mplapackint const ilo, mplapackint const ihi, _Float128 *scale, mplapackint const m, std::complex<_Float128> *v, mplapackint const ldv, mplapackint &info);
void Cgelq(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const tsize, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cgelqt(mplapackint const m, mplapackint const n, mplapackint const mb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint &info);
void Cgemlqt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const mb, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cgemqrt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const nb, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cgeqr(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const tsize, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cgeqrt(mplapackint const m, mplapackint const n, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint &info);
void Cgesv(mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cgetc2(mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, mplapackint *jpiv, mplapackint &info);
void Cgetf2(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Cgetrf(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Cgetrf2(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Cgetri(mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cgetrs(const char *trans, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cggbak(const char *job, const char *side, mplapackint const n, mplapackint const ilo, mplapackint const ihi, _Float128 *lscale, _Float128 *rscale, mplapackint const m, std::complex<_Float128> *v, mplapackint const ldv, mplapackint &info);
void Cgtts2(mplapackint const itrans, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *dl, std::complex<_Float128> *d, std::complex<_Float128> *du, std::complex<_Float128> *du2, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb);
void Cheev(const char *jobz, const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *w, std::complex<_Float128> *work, mplapackint const lwork, _Float128 *rwork, mplapackint &info);
void Chegst(mplapackint const itype, const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Chesv(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chesv_rook(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chetd2(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *d, _Float128 *e, std::complex<_Float128> *tau, mplapackint &info);
void Chetrd(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *d, _Float128 *e, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chetri(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint &info);
void Chetri2(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chetri_3(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chetri_rook(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint &info);
void Chetrs(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Chetrs2(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint &info);
void Chetrs_3(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Chetrs_aa(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Chetrs_rook(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Chfrk(const char *transr, const char *uplo, const char *trans, mplapackint const n, mplapackint const k, _Float128 const alpha, std::complex<_Float128> *a, mplapackint const lda, _Float128 const beta, std::complex<_Float128> *c);
void Chpsv(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *ap, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cla_wwaddw(mplapackint const n, std::complex<_Float128> *x, std::complex<_Float128> *y, std::complex<_Float128> *w);
void Clacgv(mplapackint const n, std::complex<_Float128> *x, mplapackint const incx);
void Clacp2(const char *uplo, mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb);
void Clacpy(const char *uplo, mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb);
void Clacrm(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, std::complex<_Float128> *c, mplapackint const ldc, _Float128 *rwork);
void Clacrt(mplapackint const n, std::complex<_Float128> *cx, mplapackint const incx, std::complex<_Float128> *cy, mplapackint const incy, std::complex<_Float128> const c, std::complex<_Float128> const s);
void Claesy(std::complex<_Float128> const a, std::complex<_Float128> const b, std::complex<_Float128> const c, std::complex<_Float128> &rt1, std::complex<_Float128> &rt2, std::complex<_Float128> &evscal, std::complex<_Float128> &cs1, std::complex<_Float128> &sn1);
void Claev2(std::complex<_Float128> const a, std::complex<_Float128> const b, std::complex<_Float128> const c, _Float128 &rt1, _Float128 &rt2, _Float128 &cs1, std::complex<_Float128> &sn1);
void Clagtm(const char *trans, mplapackint const n, mplapackint const nrhs, _Float128 const alpha, std::complex<_Float128> *dl, std::complex<_Float128> *d, std::complex<_Float128> *du, std::complex<_Float128> *x, mplapackint const ldx, _Float128 const beta, std::complex<_Float128> *b, mplapackint const ldb);
void Clahef(const char *uplo, mplapackint const n, mplapackint const nb, mplapackint &kb, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *w, mplapackint const ldw, mplapackint &info);
void Clapmr(bool const forwrd, mplapackint const m, mplapackint const n, std::complex<_Float128> *x, mplapackint const ldx, mplapackint *k);
void Clapmt(bool const forwrd, mplapackint const m, mplapackint const n, std::complex<_Float128> *x, mplapackint const ldx, mplapackint *k);
void Claqgb(mplapackint const m, mplapackint const n, mplapackint const kl, mplapackint const ku, std::complex<_Float128> *ab, mplapackint const ldab, _Float128 *r, _Float128 *c, _Float128 const rowcnd, _Float128 const colcnd, _Float128 const amax, char *equed);
void Claqge(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *r, _Float128 *c, _Float128 const rowcnd, _Float128 const colcnd, _Float128 const amax, char *equed);
void Claqhb(const char *uplo, mplapackint const n, mplapackint const kd, std::complex<_Float128> *ab, mplapackint const ldab, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Claqhe(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Claqhp(const char *uplo, mplapackint const n, std::complex<_Float128> *ap, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Claqsb(const char *uplo, mplapackint const n, mplapackint const kd, std::complex<_Float128> *ab, mplapackint const ldab, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Claqsp(const char *uplo, mplapackint const n, std::complex<_Float128> *ap, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Claqsy(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Clar2v(mplapackint const n, std::complex<_Float128> *x, std::complex<_Float128> *y, std::complex<_Float128> *z, mplapackint const incx, _Float128 *c, std::complex<_Float128> *s, mplapackint const incc);
void Clarf(const char *side, mplapackint const m, mplapackint const n, std::complex<_Float128> *v, mplapackint const incv, std::complex<_Float128> const tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work);
void Clarfb(const char *side, const char *trans, const char *direct, const char *storev, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint const ldwork);
void Clarfb_gett(const char *ident, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const ldwork);
void Clarfg(mplapackint const n, std::complex<_Float128> &alpha, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> &tau);
void Clarft(const char *direct, const char *storev, mplapackint const n, mplapackint const k, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *tau, std::complex<_Float128> *t, mplapackint const ldt);
void Clarfx(const char *side, mplapackint const m, mplapackint const n, std::complex<_Float128> *v, std::complex<_Float128> const tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work);
void Clarfy(const char *uplo, mplapackint const n, std::complex<_Float128> *v, mplapackint const incv, std::complex<_Float128> const tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work);
void Clarscl2(mplapackint const m, mplapackint const n, _Float128 *d, std::complex<_Float128> *x, mplapackint const ldx);
void Clartg(std::complex<_Float128> const f, std::complex<_Float128> const g, _Float128 &cs, std::complex<_Float128> &sn, std::complex<_Float128> &r);
void Clartv(mplapackint const n, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> *y, mplapackint const incy, _Float128 *c, std::complex<_Float128> *s, mplapackint const incc);
void Clarz(const char *side, mplapackint const m, mplapackint const n, mplapackint const l, std::complex<_Float128> *v, mplapackint const incv, std::complex<_Float128> const tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work);
void Clarzt(const char *direct, const char *storev, mplapackint const n, mplapackint const k, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *tau, std::complex<_Float128> *t, mplapackint const ldt);
void Clascl(const char *type, mplapackint const kl, mplapackint const ku, _Float128 const cfrom, _Float128 const cto, mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Clascl2(mplapackint const m, mplapackint const n, _Float128 *d, std::complex<_Float128> *x, mplapackint const ldx);
void Claset(const char *uplo, mplapackint const m, mplapackint const n, std::complex<_Float128> const alpha, std::complex<_Float128> const beta, std::complex<_Float128> *a, mplapackint const lda);
void Clasr(const char *side, const char *pivot, const char *direct, mplapackint const m, mplapackint const n, _Float128 *c, _Float128 *s, std::complex<_Float128> *a, mplapackint const lda);
void Classq(mplapackint const n, std::complex<_Float128> *x, mplapackint const incx, _Float128 &scale, _Float128 &sumsq);
void Claswlq(mplapackint const m, mplapackint const n, mplapackint const mb, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Claswp(mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint const k1, mplapackint const k2, mplapackint *ipiv, mplapackint const incx);
void Clasyf(const char *uplo, mplapackint const n, mplapackint const nb, mplapackint &kb, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *w, mplapackint const ldw, mplapackint &info);
void Clatrd(const char *uplo, mplapackint const n, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, _Float128 *e, std::complex<_Float128> *tau, std::complex<_Float128> *w, mplapackint const ldw);
void Clatsqr(mplapackint const m, mplapackint const n, mplapackint const mb, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Claunhr_col_getrfnp(mplapackint const m, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *d, mplapackint &info);
void Clauum(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Cpbequ(const char *uplo, mplapackint const n, mplapackint const kd, std::complex<_Float128> *ab, mplapackint const ldab, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Cpbsv(const char *uplo, mplapackint const n, mplapackint const kd, mplapackint const nrhs, std::complex<_Float128> *ab, mplapackint const ldab, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cpbtrs(const char *uplo, mplapackint const n, mplapackint const kd, mplapackint const nrhs, std::complex<_Float128> *ab, mplapackint const ldab, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cpoequ(mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Cposv(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cpotf2(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Cpotrf(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Cpotrf2(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Cpotri(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Cpotrs(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cppequ(const char *uplo, mplapackint const n, std::complex<_Float128> *ap, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Cppsv(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *ap, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cpptrs(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *ap, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cptcon(mplapackint const n, _Float128 *d, std::complex<_Float128> *e, _Float128 const anorm, _Float128 &rcond, _Float128 *rwork, mplapackint &info);
void Cptsv(mplapackint const n, mplapackint const nrhs, _Float128 *d, std::complex<_Float128> *e, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cpttrf(mplapackint const n, _Float128 *d, std::complex<_Float128> *e, mplapackint &info);
void Cpttrs(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *d, std::complex<_Float128> *e, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Cptts2(mplapackint const iuplo, mplapackint const n, mplapackint const nrhs, _Float128 *d, std::complex<_Float128> *e, std::complex<_Float128> *b, mplapackint const ldb);
void Crot(mplapackint const n, std::complex<_Float128> *cx, mplapackint const incx, std::complex<_Float128> *cy, mplapackint const incy, _Float128 const c, std::complex<_Float128> const s);
void Cspmv(const char *uplo, mplapackint const n, std::complex<_Float128> const alpha, std::complex<_Float128> *ap, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> const beta, std::complex<_Float128> *y, mplapackint const incy);
void Cspr(const char *uplo, mplapackint const n, std::complex<_Float128> const alpha, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> *ap);
void Cspsv(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *ap, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Csteqr(const char *compz, mplapackint const n, _Float128 *d, _Float128 *e, std::complex<_Float128> *z, mplapackint const ldz, _Float128 *work, mplapackint &info);
void Csyconv(const char *uplo, const char *way, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *e, mplapackint &info);
void Csyconvf(const char *uplo, const char *way, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, mplapackint &info);
void Csyconvf_rook(const char *uplo, const char *way, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, mplapackint &info);
void Csymv(const char *uplo, mplapackint const n, std::complex<_Float128> const alpha, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> const beta, std::complex<_Float128> *y, mplapackint const incy);
void Csyr(const char *uplo, mplapackint const n, std::complex<_Float128> const alpha, std::complex<_Float128> *x, mplapackint const incx, std::complex<_Float128> *a, mplapackint const lda);
void Csytri2(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Csytri_3(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Csytrs(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Csytrs2(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint &info);
void Csytrs_3(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *e, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Csytrs_aa(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Csytrs_rook(const char *uplo, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, mplapackint *ipiv, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Ctbtrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const kd, mplapackint const nrhs, std::complex<_Float128> *ab, mplapackint const ldab, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Ctgexc(bool const wantq, bool const wantz, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *q, mplapackint const ldq, std::complex<_Float128> *z, mplapackint const ldz, mplapackint const ifst, mplapackint &ilst, mplapackint &info);
void Ctplqt(mplapackint const m, mplapackint const n, mplapackint const l, mplapackint const mb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint &info);
void Ctpmlqt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, mplapackint const mb, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint &info);
void Ctpmqrt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, mplapackint const nb, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint &info);
void Ctpqrt(mplapackint const m, mplapackint const n, mplapackint const l, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint &info);
void Ctprfb(const char *side, const char *trans, const char *direct, const char *storev, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, std::complex<_Float128> *v, mplapackint const ldv, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, std::complex<_Float128> *work, mplapackint const ldwork);
void Ctptrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *ap, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Ctpttr(const char *uplo, mplapackint const n, std::complex<_Float128> *ap, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Ctrti2(const char *uplo, const char *diag, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Ctrtri(const char *uplo, const char *diag, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, mplapackint &info);
void Ctrtrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const nrhs, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *b, mplapackint const ldb, mplapackint &info);
void Ctrttp(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *ap, mplapackint &info);
void Cunbdb5(mplapackint const m1, mplapackint const m2, mplapackint const n, std::complex<_Float128> *x1, mplapackint const incx1, std::complex<_Float128> *x2, mplapackint const incx2, std::complex<_Float128> *q1, mplapackint const ldq1, std::complex<_Float128> *q2, mplapackint const ldq2, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cunbdb6(mplapackint const m1, mplapackint const m2, mplapackint const n, std::complex<_Float128> *x1, mplapackint const incx1, std::complex<_Float128> *x2, mplapackint const incx2, std::complex<_Float128> *q1, mplapackint const ldq1, std::complex<_Float128> *q2, mplapackint const ldq2, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cung2l(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint &info);
void Cung2r(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint &info);
void Cunghr(mplapackint const n, mplapackint const ilo, mplapackint const ihi, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cungl2(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint &info);
void Cungql(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cungqr(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cungr2(mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint &info);
void Cungtr(const char *uplo, mplapackint const n, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cungtsqr(mplapackint const m, mplapackint const n, mplapackint const mb, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *work, mplapackint const lwork, mplapackint &info);
void Cunhr_col(mplapackint const m, mplapackint const n, mplapackint const nb, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *t, mplapackint const ldt, std::complex<_Float128> *d, mplapackint &info);
void Cunm2l(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cunm2r(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cunml2(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cunmr2(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Cunmr3(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, std::complex<_Float128> *a, mplapackint const lda, std::complex<_Float128> *tau, std::complex<_Float128> *c, mplapackint const ldc, std::complex<_Float128> *work, mplapackint &info);
void Rbdsqr(const char *uplo, mplapackint const n, mplapackint const ncvt, mplapackint const nru, mplapackint const ncc, _Float128 *d, _Float128 *e, _Float128 *vt, mplapackint const ldvt, _Float128 *u, mplapackint const ldu, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rcombssq(_Float128 *v1, _Float128 *v2);
void Rgebak(const char *job, const char *side, mplapackint const n, mplapackint const ilo, mplapackint const ihi, _Float128 *scale, mplapackint const m, _Float128 *v, mplapackint const ldv, mplapackint &info);
void Rgebd2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, _Float128 *e, _Float128 *tauq, _Float128 *taup, _Float128 *work, mplapackint &info);
void Rgebrd(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, _Float128 *e, _Float128 *tauq, _Float128 *taup, _Float128 *work, mplapackint const lwork, int &info);
void Rgelq(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const tsize, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgelq2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint &info);
void Rgelqf(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgelqt(mplapackint const m, mplapackint const n, mplapackint const mb, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint &info);
void Rgemlqt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const mb, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rgemqrt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const nb, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rgeqr(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const tsize, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgeqr2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint &info);
void Rgeqrf(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgeqrt(mplapackint const m, mplapackint const n, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint &info);
void Rgesv(mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rgesvd(const char *jobu, const char *jobvt, mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *s, _Float128 *u, mplapackint const ldu, _Float128 *vt, mplapackint const ldvt, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgetc2(mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint *jpiv, mplapackint &info);
void Rgetf2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Rgetrf(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Rgetrf2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Rgetri(mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rgetrs(const char *trans, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rggbak(const char *job, const char *side, mplapackint const n, mplapackint const ilo, mplapackint const ihi, _Float128 *lscale, _Float128 *rscale, mplapackint const m, _Float128 *v, mplapackint const ldv, mplapackint &info);
void Rgtsv(mplapackint const n, mplapackint const nrhs, _Float128 *dl, _Float128 *d, _Float128 *du, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rgttrf(mplapackint const n, _Float128 *dl, _Float128 *d, _Float128 *du, _Float128 *du2, mplapackint *ipiv, mplapackint &info);
void Rgtts2(mplapackint const itrans, mplapackint const n, mplapackint const nrhs, _Float128 *dl, _Float128 *d, _Float128 *du, _Float128 *du2, mplapackint *ipiv, _Float128 *b, mplapackint const ldb);
void Rla_wwaddw(mplapackint const n, _Float128 *x, _Float128 *y, _Float128 *w);
void Rlabad(_Float128 &small, _Float128 &large);
void Rlabrd(mplapackint const m, mplapackint const n, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *d, _Float128 *e, _Float128 *tauq, _Float128 *taup, _Float128 *x, mplapackint const ldx, _Float128 *y, mplapackint const ldy);
void Rlacpy(const char *uplo, mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb);
void Rladiv(_Float128 const &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 &p, _Float128 &q);
void Rladiv(_Float128 const &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 &p, _Float128 &q);
void Rladiv1(_Float128 &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 &p, _Float128 &q);
void Rladiv1(_Float128 &a, _Float128 const &b, _Float128 const &c, _Float128 const &d, _Float128 &p, _Float128 &q);
void Rlae2(_Float128 const a, _Float128 const b, _Float128 const c, _Float128 &rt1, _Float128 &rt2);
void Rlaed5(mplapackint const i, _Float128 *d, _Float128 *z, _Float128 *delta, _Float128 const rho, _Float128 &dlam);
void Rlaev2(_Float128 const a, _Float128 const b, _Float128 const c, _Float128 &rt1, _Float128 &rt2, _Float128 &cs1, _Float128 &sn1);
void Rlagtf(mplapackint const n, _Float128 *a, _Float128 const lambda, _Float128 *b, _Float128 *c, _Float128 const tol, _Float128 *d, mplapackint *in, mplapackint &info);
void Rlagtm(const char *trans, mplapackint const n, mplapackint const nrhs, _Float128 const alpha, _Float128 *dl, _Float128 *d, _Float128 *du, _Float128 *x, mplapackint const ldx, _Float128 const beta, _Float128 *b, mplapackint const ldb);
void Rlaic1(mplapackint const job, mplapackint const j, _Float128 *x, _Float128 const sest, _Float128 *w, _Float128 const gamma, _Float128 &sestpr, _Float128 &s, _Float128 &c);
void Rlamrg(mplapackint const n1, mplapackint const n2, _Float128 *a, mplapackint const dtrd1, mplapackint const dtrd2, mplapackint *index);
void Rlanv2(_Float128 &a, _Float128 &b, _Float128 &c, _Float128 &d, _Float128 &rt1r, _Float128 &rt1i, _Float128 &rt2r, _Float128 &rt2i, _Float128 &cs, _Float128 &sn);
void Rlaorhr_col_getrfnp(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, mplapackint &info);
void Rlaorhr_col_getrfnp2(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, mplapackint &info);
void Rlapmr(bool const forwrd, mplapackint const m, mplapackint const n, _Float128 *x, mplapackint const ldx, mplapackint *k);
void Rlapmt(bool const forwrd, mplapackint const m, mplapackint const n, _Float128 *x, mplapackint const ldx, mplapackint *k);
void Rlaqgb(mplapackint const m, mplapackint const n, mplapackint const kl, mplapackint const ku, _Float128 *ab, mplapackint const ldab, _Float128 *r, _Float128 *c, _Float128 const rowcnd, _Float128 const colcnd, _Float128 const amax, char *equed);
void Rlaqge(mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *r, _Float128 *c, _Float128 const rowcnd, _Float128 const colcnd, _Float128 const amax, char *equed);
void Rlaqr1(mplapackint const n, _Float128 *h, mplapackint const ldh, _Float128 const sr1, _Float128 const si1, _Float128 const sr2, _Float128 const si2, _Float128 *v);
void Rlaqsb(const char *uplo, mplapackint const n, mplapackint const kd, _Float128 *ab, mplapackint const ldab, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Rlaqsp(const char *uplo, mplapackint const n, _Float128 *ap, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Rlaqsy(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *s, _Float128 const scond, _Float128 const amax, char *equed);
void Rlar1v(mplapackint const n, mplapackint const b1, mplapackint const bn, _Float128 const lambda, _Float128 *d, _Float128 *l, _Float128 *ld, _Float128 *lld, _Float128 const pivmin, _Float128 const gaptol, _Float128 *z, bool const wantnc, mplapackint &negcnt, _Float128 &ztz, _Float128 &mingma, mplapackint &r, mplapackint *isuppz, _Float128 &nrminv, _Float128 &resid, _Float128 &rqcorr, _Float128 *work);
void Rlar2v(mplapackint const n, _Float128 *x, _Float128 *y, _Float128 *z, mplapackint const incx, _Float128 *c, _Float128 *s, mplapackint const incc);
void Rlarf(const char *side, mplapackint const m, mplapackint const n, _Float128 *v, mplapackint const incv, _Float128 const tau, _Float128 *c, mplapackint const ldc, _Float128 *work);
void Rlarfb(const char *side, const char *trans, const char *direct, const char *storev, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint const ldwork);
void Rlarfb_gett(const char *ident, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *t, mplapackint const ldt, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const ldwork);
void Rlarfg(mplapackint const n, _Float128 &alpha, _Float128 *x, mplapackint const incx, _Float128 &tau);
void Rlarfgp(mplapackint const n, _Float128 &alpha, _Float128 *x, mplapackint const incx, _Float128 &tau);
void Rlarft(const char *direct, const char *storev, mplapackint const n, mplapackint const k, _Float128 *v, mplapackint const ldv, _Float128 *tau, _Float128 *t, mplapackint const ldt);
void Rlarfx(const char *side, mplapackint const m, mplapackint const n, _Float128 *v, _Float128 const tau, _Float128 *c, mplapackint const ldc, _Float128 *work);
void Rlarfy(const char *uplo, mplapackint const n, _Float128 *v, mplapackint const incv, _Float128 const tau, _Float128 *c, mplapackint const ldc, _Float128 *work);
void Rlargv(mplapackint const n, _Float128 *x, mplapackint const incx, _Float128 *y, mplapackint const incy, _Float128 *c, mplapackint const incc);
void Rlarra(mplapackint const n, _Float128 *d, _Float128 *e, _Float128 *e2, _Float128 const spltol, _Float128 const tnrm, mplapackint &nsplit, mplapackint *isplit, mplapackint &info);
void Rlarrc(const char *jobt, mplapackint const n, _Float128 const vl, _Float128 const vu, _Float128 *d, _Float128 *e, _Float128 const, mplapackint &eigcnt, mplapackint &lcnt, mplapackint &rcnt, mplapackint &info);
void Rlarrj(mplapackint const n, _Float128 *d, _Float128 *e2, mplapackint const ifirst, mplapackint const ilast, _Float128 const rtol, mplapackint const offset, _Float128 *w, _Float128 *werr, _Float128 *work, mplapackint *iwork, _Float128 const pivmin, _Float128 const spdiam, mplapackint &info);
void Rlarrr(mplapackint const n, _Float128 *d, _Float128 *e, mplapackint &info);
void Rlarscl2(mplapackint const m, mplapackint const n, _Float128 *d, _Float128 *x, mplapackint const ldx);
void Rlartg(_Float128 const f, _Float128 const g, _Float128 &cs, _Float128 &sn, _Float128 &r);
void Rlartgp(_Float128 const f, _Float128 const g, _Float128 &cs, _Float128 &sn, _Float128 &r);
void Rlartgs(_Float128 const x, _Float128 const y, _Float128 const sigma, _Float128 cs, _Float128 sn);
void Rlartv(mplapackint const n, _Float128 *x, mplapackint const incx, _Float128 *y, mplapackint const incy, _Float128 *c, _Float128 *s, mplapackint const incc);
void Rlarz(const char *side, mplapackint const m, mplapackint const n, mplapackint const l, _Float128 *v, mplapackint const incv, _Float128 const tau, _Float128 *c, mplapackint const ldc, _Float128 *work);
void Rlarzt(const char *direct, const char *storev, mplapackint const n, mplapackint const k, _Float128 *v, mplapackint const ldv, _Float128 *tau, _Float128 *t, mplapackint const ldt);
void Rlas2(_Float128 const f, _Float128 const g, _Float128 const h, _Float128 &ssmin, _Float128 &ssmax);
void Rlascl(const char *type, mplapackint const kl, mplapackint const ku, _Float128 const cfrom, _Float128 const cto, mplapackint const m, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rlascl2(mplapackint const m, mplapackint const n, _Float128 *d, _Float128 *x, mplapackint const ldx);
void Rlasd5(mplapackint const i, _Float128 *d, _Float128 *z, _Float128 *delta, _Float128 const rho, _Float128 &dsigma, _Float128 *work);
void Rlaset(const char *uplo, mplapackint const m, mplapackint const n, _Float128 const alpha, _Float128 const beta, _Float128 *a, mplapackint const lda);
void Rlasq1(mplapackint const n, _Float128 *d, _Float128 *e, _Float128 *work, mplapackint &info);
void Rlasq2(mplapackint const n, _Float128 *z, mplapackint &info);
void Rlasq3(mplapackint const i0, mplapackint &n0, _Float128 *z, mplapackint &pp, _Float128 &dmin, _Float128 &sigma, _Float128 &desig, _Float128 &qmax, mplapackint &nfail, mplapackint &iter, mplapackint &ndiv, bool const ieee, mplapackint &ttype, _Float128 const dmin1, _Float128 &dmin2, _Float128 const dn, _Float128 const dn1, _Float128 const dn2, _Float128 const g, _Float128 &tau);
void Rlasq4(mplapackint const i0, mplapackint const n0, _Float128 *z, mplapackint const pp, mplapackint const n0in, _Float128 const dmin, _Float128 const dmin1, _Float128 const dmin2, _Float128 const dn, _Float128 const dn1, _Float128 const dn2, _Float128 &tau, mplapackint &ttype, _Float128 &g);
void Rlasq6(mplapackint const i0, mplapackint const n0, _Float128 *z, mplapackint const pp, _Float128 &dmin, _Float128 &dmin1, _Float128 &dmin2, _Float128 &dn, _Float128 &dnm1, _Float128 &dnm2);
void Rlasr(const char *side, const char *pivot, const char *direct, mplapackint const m, mplapackint const n, _Float128 *c, _Float128 *s, _Float128 *a, mplapackint const lda);
void Rlasrt(const char *id, mplapackint const n, _Float128 *d, mplapackint &info);
void Rlassq(mplapackint const n, _Float128 *x, mplapackint const incx, _Float128 &scale, _Float128 &sumsq);
void Rlasv2(_Float128 const f, _Float128 const g, _Float128 const h, _Float128 &ssmin, _Float128 &ssmax, _Float128 &snr, _Float128 &csr, _Float128 &snl, _Float128 &csl);
void Rlaswlq(mplapackint const m, mplapackint const n, mplapackint const mb, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rlaswp(mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint const k1, mplapackint const k2, mplapackint *ipiv, mplapackint const incx);
void Rlasyf(const char *uplo, mplapackint const n, mplapackint const nb, mplapackint &kb, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *w, mplapackint const ldw, mplapackint &info);
void Rlasyf_aa(const char *uplo, mplapackint const j1, mplapackint const m, mplapackint const nb, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *h, mplapackint const ldh, _Float128 *work);
void Rlasyf_rk(const char *uplo, mplapackint const n, mplapackint const nb, mplapackint &kb, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, _Float128 *w, mplapackint const ldw, mplapackint &info);
void Rlasyf_rook(const char *uplo, mplapackint const n, mplapackint const nb, mplapackint &kb, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *w, mplapackint const ldw, mplapackint &info);
void Rlatrd(const char *uplo, mplapackint const n, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *e, _Float128 *tau, _Float128 *w, mplapackint const ldw);
void Rlatsqr(mplapackint const m, mplapackint const n, mplapackint const mb, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rlauu2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rlauum(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rorbdb5(mplapackint const m1, mplapackint const m2, mplapackint const n, _Float128 *x1, mplapackint const incx1, _Float128 *x2, mplapackint const incx2, _Float128 *q1, mplapackint const ldq1, _Float128 *q2, mplapackint const ldq2, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorbdb6(mplapackint const m1, mplapackint const m2, mplapackint const n, _Float128 *x1, mplapackint const incx1, _Float128 *x2, mplapackint const incx2, _Float128 *q1, mplapackint const ldq1, _Float128 *q2, mplapackint const ldq2, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorg2l(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint &info);
void Rorg2r(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint &info);
void Rorgbr(const char *vect, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorghr(mplapackint const n, mplapackint const ilo, mplapackint const ihi, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorgl2(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint &info);
void Rorglq(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorgql(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorgqr(mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorgtr(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorhr_col(mplapackint const m, mplapackint const n, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *t, mplapackint const ldt, _Float128 *d, mplapackint &info);
void Rorm2l(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rorm2l(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rorm2r(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rorm2r(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rormbr(const char *vect, const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rorml2(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint &info);
void Rormlq(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rormql(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rormqr(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, _Float128 *a, mplapackint const lda, _Float128 *tau, _Float128 *c, mplapackint const ldc, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rpbequ(const char *uplo, mplapackint const n, mplapackint const kd, _Float128 *ab, mplapackint const ldab, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Rpbsv(const char *uplo, mplapackint const n, mplapackint const kd, mplapackint const nrhs, _Float128 *ab, mplapackint const ldab, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rpbtrs(const char *uplo, mplapackint const n, mplapackint const kd, mplapackint const nrhs, _Float128 *ab, mplapackint const ldab, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rpoequ(mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Rpoequb(mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Rposv(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rposvx(const char *fact, const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *af, mplapackint const ldaf, char *equed, _Float128 *s, _Float128 *b, mplapackint const ldb, _Float128 *x, mplapackint const ldx, _Float128 &rcond, _Float128 *ferr, _Float128 *berr, _Float128 *work, mplapackint *iwork, mplapackint &info);
void Rpotf2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rpotrf(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rpotrf2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rpotri(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rpotrs(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rppequ(const char *uplo, mplapackint const n, _Float128 *ap, _Float128 *s, _Float128 &scond, _Float128 &amax, mplapackint &info);
void Rppsv(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *ap, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rpptrs(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *ap, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rptcon(mplapackint const n, _Float128 *d, _Float128 *e, _Float128 const anorm, _Float128 &rcond, _Float128 *work, mplapackint &info);
void Rptsv(mplapackint const n, mplapackint const nrhs, _Float128 *d, _Float128 *e, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rptsvx(const char *fact, mplapackint const n, mplapackint const nrhs, _Float128 *d, _Float128 *e, _Float128 *df, _Float128 *ef, _Float128 *b, mplapackint const ldb, _Float128 *x, mplapackint const ldx, _Float128 &rcond, _Float128 *ferr, _Float128 *berr, _Float128 *work, mplapackint &info);
void Rpttrf(mplapackint const n, _Float128 *d, _Float128 *e, mplapackint &info);
void Rpttrs(mplapackint const n, mplapackint const nrhs, _Float128 *d, _Float128 *e, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rptts2(mplapackint const n, mplapackint const nrhs, _Float128 *d, _Float128 *e, _Float128 *b, mplapackint const ldb);
void Rrscl(mplapackint const n, _Float128 const sa, _Float128 *sx, mplapackint const incx);
void Rsfrk(const char *transr, const char *uplo, const char *trans, mplapackint const n, mplapackint const k, _Float128 const alpha, _Float128 *a, mplapackint const lda, _Float128 const beta, _Float128 *c);
void Rspsv(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *ap, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsteqr(const char *compz, mplapackint const n, _Float128 *d, _Float128 *e, _Float128 *z, mplapackint const ldz, _Float128 *work, mplapackint &info);
void Rsterf(mplapackint const n, _Float128 *d, _Float128 *e, mplapackint &info);
void Rstev(const char *jobz, mplapackint const n, _Float128 *d, _Float128 *e, _Float128 *z, mplapackint const ldz, _Float128 *work, mplapackint &info);
void Rstevd(const char *jobz, mplapackint const n, _Float128 *d, _Float128 *e, _Float128 *z, mplapackint const ldz, _Float128 *work, mplapackint const lwork, mplapackint *iwork, mplapackint const liwork, mplapackint &info);
void Rsyconv(const char *uplo, const char *way, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *e, mplapackint &info);
void Rsyconvf(const char *uplo, const char *way, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, mplapackint &info);
void Rsyconvf_rook(const char *uplo, const char *way, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, mplapackint &info);
void Rsyequb(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *s, _Float128 &scond, _Float128 &amax, _Float128 *work, mplapackint &info);
void Rsyev(const char *jobz, const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *w, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsyevd(const char *jobz, const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *w, _Float128 *work, mplapackint const lwork, mplapackint *iwork, mplapackint const liwork, mplapackint &info);
void Rsygs2(mplapackint const itype, const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsygst(mplapackint const itype, const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsysv(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsysv_aa(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsysv_aa_2stage(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *tb, mplapackint const ltb, mplapackint *ipiv, mplapackint *ipiv2, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsysv_rk(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsysv_rook(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsysvx(const char *fact, const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *af, mplapackint const ldaf, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *x, mplapackint const ldx, _Float128 &rcond, _Float128 *ferr, _Float128 *berr, _Float128 *work, mplapackint const lwork, mplapackint *iwork, mplapackint &info);
void Rsytd2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, _Float128 *e, _Float128 *tau, mplapackint &info);
void Rsytf2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Rsytf2_rk(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, mplapackint &info);
void Rsytf2_rook(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, mplapackint &info);
void Rsytrd(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *d, _Float128 *e, _Float128 *tau, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsytri(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *work, mplapackint &info);
void Rsytri2(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsytri_3(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsytri_rook(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *work, mplapackint &info);
void Rsytrs(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsytrs2(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint &info);
void Rsytrs_3(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *e, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsytrs_aa(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rsytrs_aa_2stage(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *tb, mplapackint const ltb, mplapackint *ipiv, mplapackint *ipiv2, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rsytrs_rook(const char *uplo, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, mplapackint *ipiv, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rtbtrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const kd, mplapackint const nrhs, _Float128 *ab, mplapackint const ldab, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rtgexc(bool const wantq, bool const wantz, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *q, mplapackint const ldq, _Float128 *z, mplapackint const ldz, mplapackint &ifst, mplapackint &ilst, _Float128 *work, mplapackint const lwork, mplapackint &info);
void Rtplqt(mplapackint const m, mplapackint const n, mplapackint const l, mplapackint const mb, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint &info);
void Rtpmlqt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, mplapackint const mb, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint &info);
void Rtpmqrt(const char *side, const char *trans, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, mplapackint const nb, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint &info);
void Rtpqrt(mplapackint const m, mplapackint const n, mplapackint const l, mplapackint const nb, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *t, mplapackint const ldt, _Float128 *work, mplapackint &info);
void Rtprfb(const char *side, const char *trans, const char *direct, const char *storev, mplapackint const m, mplapackint const n, mplapackint const k, mplapackint const l, _Float128 *v, mplapackint const ldv, _Float128 *t, mplapackint const ldt, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, _Float128 *work, mplapackint const ldwork);
void Rtptrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const nrhs, _Float128 *ap, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rtpttr(const char *uplo, mplapackint const n, _Float128 *ap, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rtrexc(const char *compq, mplapackint const n, _Float128 *t, mplapackint const ldt, _Float128 *q, mplapackint const ldq, mplapackint &ifst, mplapackint &ilst, _Float128 *work, mplapackint &info);
void Rtrti2(const char *uplo, const char *diag, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rtrtri(const char *uplo, const char *diag, mplapackint const n, _Float128 *a, mplapackint const lda, mplapackint &info);
void Rtrtrs(const char *uplo, const char *trans, const char *diag, mplapackint const n, mplapackint const nrhs, _Float128 *a, mplapackint const lda, _Float128 *b, mplapackint const ldb, mplapackint &info);
void Rtrttp(const char *uplo, mplapackint const n, _Float128 *a, mplapackint const lda, _Float128 *ap, mplapackint &info);
#endif
