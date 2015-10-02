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

    Copyright (C) 2012, 2013 Fredrik Johansson

******************************************************************************/

#include "acb.h"

static const char *testdata[5] = {
    "-0.2487544770337842625472529935761139760973697136685351169998556396906930329999105060928584336658420889 +/- 1e-90",
    "-0.9189385332046727417803297364056176398613974736377834128171515404827656959272603976947432986359541976 +/- 1e-90",
    "-0.5772156649015328606065120900824024310421593359399235988057672348848677267776646709369470632917467495 +/- 1e-90",
    "1.644934066848226436472415166646025189218949901206798437735558229370007470403200873833628900619758705 +/- 1e-90",
    "-2.404113806319188570799476323022899981529972584680997763584543110683676411572626180372911747218670516 +/- 1e-90",
};

int main()
{
    long iter;
    flint_rand_t state;

    printf("polygamma....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 1000; iter++)
    {
        acb_t a, s, b, c;
        long prec1, prec2;

        prec1 = 2 + n_randint(state, 500);
        prec2 = prec1 + 30;

        acb_init(a);
        acb_init(s);
        acb_init(b);
        acb_init(c);

        if (iter < 200)
        {
            long i = n_randint(state, 5);

            acb_set_si(s, -2 + i);
            acb_one(a);

            acb_randtest(c, state, 1 + n_randint(state, 500), 3);
            acb_add(s, s, c, prec2);
            acb_sub(s, s, c, prec2);

            acb_polygamma(b, s, a, prec1);
            acb_zero(c);
            arb_set_str(acb_realref(c), testdata[i], prec2);
        }
        else
        {
            acb_randtest(a, state, 1 + n_randint(state, 500), 3);
            acb_randtest(s, state, 1 + n_randint(state, 500), 3);

            acb_polygamma(b, s, a, prec1);

            acb_randtest(c, state, 1 + n_randint(state, 500), 3);
            acb_add(s, s, c, prec2);
            acb_sub(s, s, c, prec2);

            acb_polygamma(c, s, a, prec2);
        }

        if (!acb_overlaps(b, c))
        {
            printf("FAIL: overlap\n\n");
            printf("a = "); acb_print(a); printf("\n\n");
            printf("s = "); acb_print(s); printf("\n\n");
            printf("b = "); acb_print(b); printf("\n\n");
            printf("c = "); acb_print(c); printf("\n\n");
            abort();
        }

        acb_clear(a);
        acb_clear(s);
        acb_clear(b);
        acb_clear(c);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
