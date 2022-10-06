#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "put.h"
#include "attiny_usart.h"

#define PUT_WRITE(buf, sz) usart0_write(buf, sz)

/**
 * Print each string from the varargs, which all are (char *) until a NULL value is encountered.
 * This is a lightweight alternative to printf.
 */
void put_(char *s, ...)
{
    va_list va;

    va_start(va, s);
    do PUT_WRITE((uint8_t *)s, strlen(s));
    while ((s = va_arg(va, char *)));
}

static char const *fmt_digits = "0123456789ABCDEF";

/**
 * Format a signed integer i64 at the end of s of size sz using base b.
 * @return The first printable byte of `s`.
 */
char *fmtint(char *s, size_t sz, int64_t i64, uint8_t b)
{
    assert(b <= strlen(fmt_digits));
    s += sz;
    *--s = '\0';
    if (i64 == 0) {
        *--s = fmt_digits[0];
        return s;
    }
    for (uint64_t u64 = (unsigned)(i64 > 0 ? i64 : -i64); u64 > 0; u64 /= b)
        *--s = fmt_digits[u64 % b];
    if (i64 < 0)
        *--s = '-';
    return s;
}
