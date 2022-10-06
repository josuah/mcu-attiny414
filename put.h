#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>

/* Macros to format integers into temporary strings, for use with put(). */
#define fmtb(n) fmtint((char[65]){0}, 65, n, 2)
#define fmtd(n) fmtint((char[21]){0}, 21, n, 10)
#define fmtx(n) fmtint((char[17]){0}, 17, n, 16)
#define fmtc(c) (char[2]){ c, '\0' }

#define put(...) put_(__VA_ARGS__, NULL)

void put_(char *s, ...);
char *fmtint(char *s, size_t sz, int64_t i64, uint8_t b);

#endif
