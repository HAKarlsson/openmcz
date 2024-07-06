#ifndef LIBOPENMCZ_ALTIO_H
#define LIBOPENMCZ_ALTIO_H
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

int alt_fputc(int str, FILE *stream);
int alt_putchar(int c);
int alt_fputs(const char *str, FILE *stream);
int alt_puts(const char *str);

int alt_fgetc(FILE *stream);
int alt_getchar(void);
char *alt_fgets(char *str, size_t size, FILE *stream);
char *alt_gets(char *str, size_t size);

size_t alt_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t alt_fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);

int alt_printf(const char *format, ...);
int alt_fprintf(FILE *stream, const char *format, ...);
int alt_sprintf(char *str, const char *format, ...);
int alt_snprintf(char *str, size_t size, const char *restrict format, ...);

int alt_vprintf(const char *format, va_list ap);
int alt_vfprintf(FILE *stream, const char *restrict format, va_list ap);
int alt_vsprintf(char *str, const char *restrict format, va_list ap);
int alt_vsnprintf(char *str, size_t size, const char *restrict format, va_list ap);

#endif /* LIBOPENMCZ_ALTIO_H */
