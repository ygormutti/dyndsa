//      dynset.c
//
//      Copyright 2010 Ygor Mutti <ygormutti@dcc.ufba.br>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "dynset.h"

int datecmp(date x, date y){
    if (x.year == y.year){
        if (x.month == y.month) {
            if (x.day == y.day) {
                return 0;
            } else {
                return x.day - y.day;
            }
        } else {
            return x.month - y.month;
        }
    } else {
        return x.year - y.year;
    }
}

CDYNSET(DoubleSet, double, CMP)
CDYNSET(IntSet, int, CMP)
CDYNSET(DateSet, date, datecmp)



void IntSet_print(IntSet *setpntr){
    int *i;
    printf("{ ");
    while ((i = IntSet_iter(setpntr)) != NULL)
        printf("%d ", *i);
    putchar('}');
}

void DoubleSet_print(DoubleSet *setpntr){
    double *i;
    printf("{ ");
    while ((i = DoubleSet_iter(setpntr)) != NULL)
        printf("%f ", *i);
    putchar('}');
}

void DateSet_print(DateSet *setpntr){
    date *i;
    printf("{ ");
    while ((i = DateSet_iter(setpntr)) != NULL)
        printf("%d/%d/%d ", i->year, i->month, i->day);
    putchar('}');
}

int main() {
    IntSet intset;
    DoubleSet doubleset;
    DateSet dateset;

    IntSet_init(&intset);
    IntSet_print(&intset);
    printf("\nConjunto inicializado\n");
    IntSet_add(&intset, 1);
    IntSet_add(&intset, 1);
    IntSet_add(&intset, 2);
    IntSet_add(&intset, 3);
    IntSet_add(&intset, 19);
    IntSet_print(&intset);
    printf("\nElementos inseridos\nCardinalidade: %d\n", IntSet_cardinality(&intset));
    IntSet_remove(&intset, 19);
    IntSet_remove(&intset, 19);
    IntSet_remove(&intset, 1);
    IntSet_remove(&intset, 2);
    IntSet_remove(&intset, 3);
    IntSet_print(&intset);
    printf("\nElementos removidos\nCardinalidade: %d\n", IntSet_cardinality(&intset));

    DoubleSet_init(&doubleset);
    DoubleSet_print(&doubleset);
    printf("\nConjunto inicializado\n");
    DoubleSet_add(&doubleset, 1);
    DoubleSet_add(&doubleset, 1);
    DoubleSet_add(&doubleset, 2);
    DoubleSet_add(&doubleset, 3);
    DoubleSet_add(&doubleset, 19);
    DoubleSet_print(&doubleset);
    printf("\nElementos inseridos\nCardinalidade: %d\n", DoubleSet_cardinality(&doubleset));
    DoubleSet_remove(&doubleset, 19);
    DoubleSet_remove(&doubleset, 19);
    DoubleSet_remove(&doubleset, 1);
    DoubleSet_remove(&doubleset, 2);
    DoubleSet_remove(&doubleset, 3);
    DoubleSet_print(&doubleset);
    printf("\nElementos removidos\nCardinalidade: %d\n", DoubleSet_cardinality(&doubleset));

    date a = {1991, 8, 2}, b = {1991,9,22}, wtc = {2001,9,11};
    DateSet_init(&dateset);
    DateSet_print(&dateset);
    printf("\nConjunto inicializado\n");
    DateSet_add(&dateset, a);
    DateSet_add(&dateset, a);
    DateSet_add(&dateset, b);
    DateSet_add(&dateset, wtc);
    DateSet_print(&dateset);
    printf("\nElementos inseridos\nCardinalidade: %d\n", DateSet_cardinality(&dateset));
    DateSet_remove(&dateset, wtc);
    DateSet_remove(&dateset, wtc);
    DateSet_remove(&dateset, a);
    DateSet_remove(&dateset, b);
    DateSet_print(&dateset);
    printf("\nElementos removidos\nCardinalidade: %d\n", DateSet_cardinality(&dateset));

    return 0;
}
