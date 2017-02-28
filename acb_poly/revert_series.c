/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Fredrik Johansson

******************************************************************************/

#include "acb_poly.h"

void
_acb_poly_revert_series(acb_ptr Qinv,
    acb_srcptr Q, slong Qlen, slong n, slong prec)
{
    _acb_poly_revert_series_lagrange_fast(Qinv, Q, Qlen, n, prec);
}

void
acb_poly_revert_series(acb_poly_t Qinv,
                                    const acb_poly_t Q, slong n, slong prec)
{
    slong Qlen = Q->length;

    if (Qlen < 2 || !acb_is_zero(Q->coeffs)
                 || acb_contains_zero(Q->coeffs + 1))
    {
        flint_printf("Exception (acb_poly_revert_series). Input must \n"
               "have zero constant term and nonzero coefficient of x^1.\n");
        flint_abort();
    }

    if (Qinv != Q)
    {
        acb_poly_fit_length(Qinv, n);
        _acb_poly_revert_series(Qinv->coeffs, Q->coeffs, Qlen, n, prec);
    }
    else
    {
        acb_poly_t t;
        acb_poly_init2(t, n);
        _acb_poly_revert_series(t->coeffs, Q->coeffs, Qlen, n, prec);
        acb_poly_swap(Qinv, t);
        acb_poly_clear(t);
    }

    _acb_poly_set_length(Qinv, n);
    _acb_poly_normalise(Qinv);
}

