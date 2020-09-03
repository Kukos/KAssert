#ifndef KASSERT_PRIV_H
#define KASSERT_PRIV_H

/*
    This is the private header for the KAssert.
    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KASSERT_H
#error "Never include <kassert/kassert-priv.h> directly, use <kassert/kassert.h> instead."
#endif

#ifndef __GNUC__
#error "Gnu extension is required to compile code with KAssert!"
#endif

/* C11 has value 201112L */
#if __STDC_VERSION__ < 201112L
#error "At least C11 is required to compile code with KAssert!"
#endif

#include "kassert-primitive-fmt.h"

#include <stdbool.h>

#ifndef TOSTRING
#define KASSERT_TOSTRING(x) #x
#define TOSTRING(x) KASSERT_TOSTRING(x)
#endif

/* Main assert function: prints all stats like format, threadID, stacktrace and calls exit(1) */
void __attribute__ ((noreturn)) __kassert_print_and_exit(bool need_free, const char* fmt, ...);

/* Returns pointer to char[] with printf format, buffer must be freed */
const char* __kassert_create_print_fmt(const char* label,
                                       const char* val1_fmt,
                                       const char* op,
                                       const char* val2_fmt);

#define KASSERT_PRIV_COND_BODY(cond) \
    do { \
        if (!(cond)) \
        { \
            __kassert_print_and_exit(false, \
                                     "%s:%d: %s: Assertion \'%s\' failed.\n", \
                                     __FILE__, \
                                     __LINE__, \
                                     __func__, \
                                     TOSTRING(cond)); \
        } \
    } while (0)

#define KASSERT_PRIV_CREATE_LABEL(val1, val2, op) \
    TOSTRING(val1) " " TOSTRING(op) " " TOSTRING(val2)

#define KASSERT_PRIV_OP(val1, val2, op) \
    do { \
        const __typeof__(val1) _kassert_val1 = (val1); \
        const __typeof__(val2) _kassert_val2 = (val2); \
        (void)(&_kassert_val1 - &_kassert_val2); \
        if (!((_kassert_val1) op (_kassert_val2))) \
        { \
            const char* const fmt = \
                __kassert_create_print_fmt(KASSERT_PRIV_CREATE_LABEL(val1, val2, op), \
                                           KASSERT_PRIMTIVE_GET_FMT(_kassert_val1), \
                                           TOSTRING(op), \
                                           KASSERT_PRIMTIVE_GET_FMT(_kassert_val2)); \
            __kassert_print_and_exit(true, \
                                     fmt, \
                                     __FILE__, \
                                     __LINE__, \
                                     __func__, \
                                     _kassert_val1, \
                                     _kassert_val2); \
        } \
    } while (0)

#define KASSERT_PRIV_EQ(val1, val2)  KASSERT_PRIV_OP(val1, val2, ==)
#define KASSERT_PRIV_NEQ(val1, val2) KASSERT_PRIV_OP(val1, val2, !=)
#define KASSERT_PRIV_LT(val1, val2)  KASSERT_PRIV_OP(val1, val2, <)
#define KASSERT_PRIV_LEQ(val1, val2) KASSERT_PRIV_OP(val1, val2, <=)
#define KASSERT_PRIV_GT(val1, val2)  KASSERT_PRIV_OP(val1, val2, >)
#define KASSERT_PRIV_GEQ(val1, val2) KASSERT_PRIV_OP(val1, val2, >=)

#define KASSERT_PRIV_COND(cond)      KASSERT_PRIV_COND_BODY(cond)

#endif
