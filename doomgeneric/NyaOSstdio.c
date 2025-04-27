#include "NyaOSstdio.h"
#include <stdarg.h>
#include <string.h>

void debugPrint(const char *string)
{
	asm(
		"movl $69, %%eax\n"
		"movl %0, %%ebx\n"
		"int $0x80\n"
		:
		: "r"(string)
		: "%eax", "%ebx");
}

int debugPrintf(const char *restrict fmt, ...)
{
	char formatted_string[1024];

	va_list args;
	va_start(args, fmt);
	int result = vsnprintf(formatted_string, sizeof(formatted_string), fmt, args);
	va_end(args);

	if (result < 0)
	{
		return result;
	}

	debugPrint(formatted_string);
	return result;
}

int fprintf(FILE *restrict f, const char *restrict fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int result = debugPrintf(fmt, args);

	va_end(args);

	return result;
}

int printf(const char *restrict fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int result = debugPrintf(fmt, args);

	va_end(args);

	return result;
}
