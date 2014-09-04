#ifndef _H_MOSS_UTIL
#define _H_MOSS_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define log_out(level, ...) do { \
	moss_log_out(level, __func__, __LINE__, __VA_ARGS__); \
} while(0)
#define log_error(...) log_out(1, __VA_ARGS__)
#define log_info(...) log_out(2, __VA_ARGS__)
#define log_debug(...) log_out(3, __VA_ARGS__)
#define log_verbose(...) log_out(4, __VA_ARGS__)

#define MOSS_STRINGIFY(_s) # _s
#define MOSS_STRINGIFY2(_s) MOSS_STRINGIFY(_s)

#ifdef __cplusplus
extern "C" {
#endif

int moss_vprintf(const char *fmt, va_list ap) __attribute__((format(printf, 1, 0)));

int moss_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
int moss_vsnprintf(char *o, size_t n,
		const char *fmt, va_list ap) __attribute__((format(printf, 3, 0)));
int moss_snprintf(char *o, size_t n,
		const char *fmt, ...) __attribute__((format(printf, 3, 4)));
int moss_log_out(int level, const char *func, long line,
		const char *fmt, ...) __attribute__((format(printf, 4, 5)));

/** @brief show memory in HEX/ASCII
 *
 * 00007FFF 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | 0123456789abcdef
 *          ----------------------------------------------- | ----------------
 * FFFFDDBE                                           1f 20 |               .
 * FFFFDDC0 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f 30 | !"#$%&'()*+,-./0
 */
int moss_showhex(const unsigned char *s, size_t n, unsigned long a);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _H_MOSS_UTIL */
