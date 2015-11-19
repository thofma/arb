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

#include "acb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("coth....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 1000; iter++)
    {
        acb_t x, y, a, b, c, d;
        slong prec1, prec2;

        prec1 = 2 + n_randint(state, 200);
        prec2 = prec1 + 30;

        acb_init(x);
        acb_init(y);
        acb_init(a);
        acb_init(b);
        acb_init(c);
        acb_init(d);

        acb_randtest(x, state, 1 + n_randint(state, 200), 2 + n_randint(state, 100));
        acb_randtest(y, state, 1 + n_randint(state, 200), 2 + n_randint(state, 100));

        acb_coth(a, x, prec1);
        acb_coth(b, x, prec2);

        /* check consistency */
        if (!acb_overlaps(a, b))
        {
            flint_printf("FAIL: overlap\n\n");
            flint_printf("x = "); acb_print(x); flint_printf("\n\n");
            flint_printf("a = "); acb_print(a); flint_printf("\n\n");
            flint_printf("b = "); acb_print(b); flint_printf("\n\n");
            abort();
        }

        /* check coth(x+y) = (1 + coth(x) coth(y)) / (coth(x) + coth(y)) */
        acb_add(b, x, y, prec1);
        acb_coth(b, b, prec1);

        acb_coth(c, y, prec1);
        acb_add(d, a, c, prec1);
        acb_mul(c, a, c, prec1);
        acb_add_ui(c, c, 1, prec1);
        acb_div(d, c, d, prec1);

        if (!acb_overlaps(b, d))
        {
            flint_printf("FAIL: functional equation\n\n");
            flint_printf("x = "); acb_print(x); flint_printf("\n\n");
            flint_printf("y = "); acb_print(y); flint_printf("\n\n");
            flint_printf("b = "); acb_print(b); flint_printf("\n\n");
            flint_printf("d = "); acb_print(d); flint_printf("\n\n");
            abort();
        }

        acb_coth(x, x, prec1);

        if (!acb_overlaps(a, x))
        {
            flint_printf("FAIL: aliasing\n\n");
            flint_printf("a = "); acb_print(a); flint_printf("\n\n");
            flint_printf("x = "); acb_print(x); flint_printf("\n\n");
            abort();
        }

        acb_clear(x);
        acb_clear(y);
        acb_clear(a);
        acb_clear(b);
        acb_clear(c);
        acb_clear(d);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

