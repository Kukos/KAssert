#ifndef KASSERT_PRIMITIVE_FMT_H
#define KASSERT_PRIMITIVE_FMT_H

/*
    This is a private header for kassert.
    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com

    LICENCE: GPL3
*/

#ifndef KASSERT_H
#error "Never include <kassert/kassert-primitive-fmt.h> directly, use <kassert/kassert.h> instead."
#endif

/**
 * This macro returning printf fmt for variable x
 */
#define KASSERT_PRIMTIVE_GET_FMT(x) \
    _Generic((x), \
             _Bool: "%u", \
             char: "%c", \
             signed char: "%c", \
             unsigned char: "%c", \
             short: "%hd", \
             unsigned short: "%hu", \
             int: "%d", \
             unsigned int: "%u", \
             long: "%ld", \
             unsigned long: "%lu", \
             long long: "%ll", \
             unsigned long long: "%llu", \
             float: "%f", \
             double: "%lf", \
             long double: "%Lf", \
             default: "%p" \
    )

#endif
