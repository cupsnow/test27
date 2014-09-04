#include <moss/util.h>

int moss_vprintf(const char *fmt, va_list ap)
{
	int r;

	if (!fmt) return 0;

	r = vprintf(fmt, ap);
	if (r < 0) r = 0;
	return r;
}

int moss_printf(const char *fmt, ...)
{
	int r;
	va_list ap;

	va_start(ap, fmt);
	r = moss_vprintf(fmt, ap);
	va_end(ap);
	return r;
}

int moss_vsnprintf(char *o, size_t n, const char *fmt, va_list ap)
{
	int r;

	if (!o || n < 1) return 0;

	r = vsnprintf(o, n, fmt, ap);
	if (r < 0) r = 0;
	else if (r >= n) r = n - 1;
	o[r] = '\0';
	return r;
}

int moss_snprintf(char *o, size_t n, const char *fmt, ...)
{
	int r;
	va_list ap;

	va_start(ap, fmt);
	r = moss_vsnprintf(o, n, fmt, ap);
	va_end(ap);
	return r;
}

int moss_log_out(int level, const char *func, long line,
		const char *fmt, ...)
{
	const int len = 1024;
	int idx = 0;
	char msg[len];
	va_list ap;

	if (level == 1) {
		idx += moss_snprintf(msg + idx, len - idx, "ERROR %s #%ld ", func, line);
	} else if (level == 2) {
		idx += moss_snprintf(msg + idx, len - idx, "INFO %s #%ld ", func, line);
	} else if (level == 4) {
		idx += moss_snprintf(msg + idx, len - idx, "verbose %s #%ld ", func, line);
	} else {
		idx += moss_snprintf(msg + idx, len - idx, "Debug %s #%ld ", func, line);
	}
	if (idx >= len) goto finally;

	va_start(ap, fmt);
	idx += moss_vsnprintf(msg + idx, len - idx, fmt, ap);
	va_end(ap);
	if (idx >= len) goto finally;
finally:
	moss_printf("%s", msg);
	return idx;
}

int moss_showhex(const unsigned char *s, size_t n, unsigned long a)
{
#define SHOWHEX_ASCII 1
#define SHOWHEX_ADDR_WIDTH 8 /* sizeof(char*) * 2 */
#define SHOWHEX_ADDR_FMT "%08lX"
#define SHOWHEX_ADDR_SP "        "

/*                   1         2         3         4                   1
 * 12345678 12345678901234567890123456789012345678901234567   1234567890123456
 *
 * 00007FFF 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | 0123456789abcdef
 *          ----------------------------------------------- | ----------------
 * FFFFDDBE                                           1f 20 |               .
 * FFFFDDC0 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f 30 | !"#$%&'()*+,-./0
 */
	char ascii_sp[16]  = "----------------";
	int i, l;

	moss_printf(SHOWHEX_ADDR_FMT " 00 01 02 03 04 05 06 07 08 09"
			" 0A 0B 0C 0D 0E 0F", a >> 32);
	a = (a << 32) >> 32;

	if (SHOWHEX_ASCII) moss_printf(" | 0123456789ABCDEF");
	moss_printf("\n" SHOWHEX_ADDR_SP " -----------------------------"
			"------------------");

	for (i = l = 0; i < n; l++) {
		if ((l & 0x0f) == 0) {
			ascii_sp[0x10] = '\0';
			if (SHOWHEX_ASCII) moss_printf(" | %s", ascii_sp);
			moss_printf("\n" SHOWHEX_ADDR_FMT, (unsigned long)(a + i));
		}
		if ((l & 0x0f) != ((unsigned long)(a + i) & 0x0f)) {
			moss_printf("   ");
			if (SHOWHEX_ASCII) ascii_sp[l % 0x10] = ' ';
		} else {
			moss_printf(" %02x", s[i]);
			if (SHOWHEX_ASCII) {
				ascii_sp[l % 0x10] = (isprint(s[i]) ? s[i] : '.');
			}
			i++;
		}
	}

	if (SHOWHEX_ASCII && ((l & 0x0f) != 0)) {
		for (; ; l++) {
			if ((l & 0x0f) == 0) {
				ascii_sp[l % 0x11] = '\0';
				moss_printf(" | %s\n", ascii_sp);
				break;
			}
			moss_printf("   ");
			ascii_sp[l % 0x10] = ' ';
		}
	}

	moss_printf("\n");

	return 0;
}
