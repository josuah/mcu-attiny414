#ifndef UTIL_H
#define UTIL_H
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define PUT_WRITE(buf, sz) usart0_write(buf, sz)

/* Macros to format integers into temporary strings, for use with put(). */
#define fmtb(n) fmtint((char[65]){0}, 65, n, 2)
#define fmtd(n) fmtint((char[21]){0}, 21, n, 10)
#define fmtx(n) fmtint((char[17]){0}, 17, n, 16)
#define fmtc(c) (char[2]){ c, '\0' }

#define put(...) put_(__VA_ARGS__, NULL)

/* equivalent to fputs(stdout, s); */
static void put_(char *s, ...)
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
static char *fmtint(char *s, size_t sz, int16_t i64, uint8_t b)
{
    assert(b <= strlen(fmt_digits));
    s += sz;
    *--s = '\0';
    if (i64 == 0) {
        *--s = fmt_digits[0];
        return s;
    }
    for (uint16_t u64 = i64 > 0 ? i64 : -i64; u64 > 0; u64 /= b)
        *--s = fmt_digits[u64 % b];
    if (i64 < 0)
        *--s = '-';
    return s;
}

#endif
