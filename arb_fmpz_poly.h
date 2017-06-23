/*
    Copyright (C) 2017 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef ARB_FMPZ_POLY_H
#define ARB_FMPZ_POLY_H

#ifdef ARB_FMPZ_POLY_INLINES_C
#define ARB_FMPZ_POLY_INLINE
#else
#define ARB_FMPZ_POLY_INLINE static __inline__
#endif

#include "flint/ulong_extras.h"
#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"
#include "arb.h"
#include "acb.h"
#include "arb_poly.h"
#include "acb_poly.h"

void _arb_fmpz_poly_evaluate_acb_horner(acb_t res, const fmpz * f, slong len, const acb_t x, slong prec);
void arb_fmpz_poly_evaluate_acb_horner(acb_t res, const fmpz_poly_t f, const acb_t a, slong prec);
void _arb_fmpz_poly_evaluate_acb_rectangular(acb_t res, const fmpz * f, slong len, const acb_t x, slong prec);
void arb_fmpz_poly_evaluate_acb_rectangular(acb_t res, const fmpz_poly_t f, const acb_t a, slong prec);
void _arb_fmpz_poly_evaluate_acb(acb_t res, const fmpz * f, slong len, const acb_t x, slong prec);
void arb_fmpz_poly_evaluate_acb(acb_t res, const fmpz_poly_t f, const acb_t a, slong prec);

void _arb_fmpz_poly_evaluate_arb_horner(arb_t res, const fmpz * f, slong len, const arb_t x, slong prec);
void arb_fmpz_poly_evaluate_arb_horner(arb_t res, const fmpz_poly_t f, const arb_t a, slong prec);
void _arb_fmpz_poly_evaluate_arb_rectangular(arb_t res, const fmpz * f, slong len, const arb_t x, slong prec);
void arb_fmpz_poly_evaluate_arb_rectangular(arb_t res, const fmpz_poly_t f, const arb_t a, slong prec);
void _arb_fmpz_poly_evaluate_arb(arb_t res, const fmpz * f, slong len, const arb_t x, slong prec);
void arb_fmpz_poly_evaluate_arb(arb_t res, const fmpz_poly_t f, const arb_t a, slong prec);

void arb_fmpz_poly_gauss_period_minpoly(fmpz_poly_t res, ulong q, ulong n);

#endif
