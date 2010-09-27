//      dynset.h -- Dynamic Typed Sets (Data Structures and Algorithms)
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

# ifndef bool
# include <stdbool.h>
# endif

# ifndef malloc
# include <stdlib.h>
# endif

# ifndef printf
# include <stdio.h>
# endif

/*
 * HDYNSET(name, type)
 *
 * This macro defines all the types and function prototypes needed to
 * implement a set which elements are of a simple type (not structs).
 *
 * eg.: HDYNSET(IntSet, int)
 *
 * This defines the type IntSet, and the following function prototypes:
 *
 * void IntSet_init (IntSet *intset);
 * int IntSet_cardinality(IntSet *intset);
 * bool IntSet_isempty(IntSet *intset);
 * bool IntSet_contains(IntSet *intset, int x);
 * bool IntSet_add(IntSet *intset, int x);
 * bool IntSet_remove(IntSet *intset, int x);
 * int *IntSet_iter(IntSet *intset);
 *
 */
# define HDYNSET(name, type)                                                    \
typedef struct name##Elem {                                                     \
    type key;                                                                   \
    struct name##Elem *next;                                                    \
} *name;                                                                        \
                                                                                \
void name##_init (name *setpntr);                                               \
int name##_cardinality(name *setpntr);                                          \
bool name##_isempty(name *setpntr);                                             \
bool name##_contains(name *setpntr, type x);                                    \
bool name##_add(name *setpntr, type x);                                         \
bool name##_remove(name *setpntr, type x);                                      \
type *name##_iter(name *setpntr);

/*
 * CDYNSET(name, type, cmp)
 *
 * This macro implements all the functions which prototypes were declared by
 * HDYNSET. The aditional cmp parameter must be the name of a function
 * (or macro) which will be used to compare two elements for equality.
 *
 * Here is a brief description of what function do:
 *
 * void name_init (name *setpntr);
 * Initializes the set. You must call this after defining a set variable.
 *
 * int name_cardinality(name *setpntr);
 * Returns the number of members of the set.
 *
 * bool name_isempty(name *setpntr);
 * Return true if the set doesn't contain members.
 *
 * bool name_contains(name *setpntr, type x);
 * Returns true if the member x is in the set. cmp(type x, type y) == 0 means a
 * member y equals x; returns false otherwise.
 *
 * bool name_add(name *setpntr, type x);
 * Returns true if x is in the set after the function call, adding x to the set
 * when necessary; returns false otherwise.
 *
 * bool name_remove(name *setpntr, type x);
 * Returns true if x is not in the set after the funcion call, removing x from
 * the set when necessary; returns false otherwise.
 *
 * int *name_iter(name *setpntr);
 * Iterates through the members of the set. Each call returns a pointer to a
 * different member and NULL if there is no member left to return. Calling this
 * function passing a different set clear the previous iteration.
 */
# define CDYNSET(name, type, cmp)                                               \
void name##_init (name *setpntr){                                               \
    *setpntr = NULL;                                                            \
}                                                                               \
                                                                                \
int name##_cardinality(name *setpntr){                                          \
    name p = *setpntr;                                                          \
    int n = 0;                                                                  \
    for ( ; p != NULL; p = p->next, n++)                                        \
        ;                                                                       \
    return n;                                                                   \
}                                                                               \
                                                                                \
bool name##_isempty(name *setpntr){                                             \
    return *setpntr == NULL;                                                    \
}                                                                               \
                                                                                \
bool name##_contains(name *setpntr, type x){                                    \
    name p;                                                                     \
    for(p = *setpntr ; (p != NULL) && cmp(p->key, x); p = p->next)              \
        ;                                                                       \
    return (p != NULL);                                                         \
}                                                                               \
                                                                                \
bool name##_add(name *setpntr, type x) {                                        \
    name n = NULL;                                                              \
    if (name##_contains(setpntr, x) ||                                          \
        (n = (name) malloc(sizeof(struct name##Elem))) ) {                      \
        if (n) {                                                                \
            n->next = *setpntr;                                                 \
            n->key = x;                                                         \
            *setpntr = n;                                                       \
        }                                                                       \
        return true;                                                            \
    } else                                                                      \
        return false;                                                           \
}                                                                               \
                                                                                \
bool name##_remove(name *setpntr, type x) {                                     \
    if (name##_contains(setpntr, x)){                                           \
        name o = NULL, p = *setpntr;                                            \
        for(; cmp(p->key, x); o = p, p = p->next)                               \
            ;                                                                   \
        if (o)                                                                  \
            o->next = p->next;                                                  \
        else                                                                    \
            *setpntr = p->next;                                                 \
        free(p);                                                                \
    }                                                                           \
    return true;                                                                \
}                                                                               \
                                                                                \
type *name##_iter(name *setpntr){                                               \
    static name p, s = NULL;                                                    \
    if (s == NULL || s != *setpntr)                                             \
        p = s = *setpntr;                                                       \
    if (p != NULL){                                                             \
        type *val = &p->key;                                                    \
        p = p->next;                                                            \
        return val;                                                             \
    } else {                                                                    \
        return NULL;                                                            \
    }                                                                           \
}

/*
 * define CMP(x, y)
 *
 * Compares x and y by subtracting. Can be used with CDYNSET if suitable, but
 * note that when comparing strings and arrays you may not want to compare their
 * address.
 */
# define CMP(x, y) ((x) - (y))
