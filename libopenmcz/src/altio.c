#include "altio.h"

// typedef struct FILE_BUFFER {
// 	FILE file;
// 	char *buffer;
// 	int size;
// 	int offset;
// } FILE_BUFFER;
//
// static int buffer_fputc(int c, FILE *stream)
// {
// 	FILE_BUFFER *bstream = (FILE_BUFFER*)stream;
// 	if (bstream->offset < bstream->size)
// 		bstream->buffer[bstream->offset++] = c;
// 	return (unsigned char)c;
// }
//
// static int buffer_fgetc(FILE *stream)
// {
// 	FILE_BUFFER *bstream = (FILE_BUFFER*)stream;
// 	if (bstream->offset < bstream->size)
// 		return (unsigned char)bstream->buffer[bstream->offset++];
// 	return -1;
// }

int alt_fputc(int c, FILE* stream)
{
    /* TODO: check stream->flag for write flag */
    return stream->put(c, stream);
}

int alt_fputs(const char* s, FILE* stream)
{
    int i = 0;
    while (s[i] != '\0') {
        alt_fputc(s[i], stream);
        i++;
    }
    return i;
}

int alt_putchar(int c)
{
    return alt_fputc(c, stdout);
}

int alt_puts(const char* s)
{
    int i = alt_fputs(s, stdout);
    alt_fputc('\r', stdout);
    alt_fputc('\n', stdout);
    return i + 2;
}

int alt_fgetc(FILE* stream)
{
    return stream->get(stream);
}

int alt_getchar(void)
{
    return alt_fgetc(stdin);
}

char* alt_fgets(char* str, size_t size, FILE* stream)
{
    int i = 0;
    while (i < size - 1) {
        char c = alt_fgetc(stream);
        if (c == EOF)
            break;
        str[i++] = c;
        if (c == '\n')
            break;
    }
    str[i] = '\0';
    if (i == 0)
        return NULL;
    return str;
}

char* alt_gets(char* str, size_t size)
{
    return alt_fgets(str, size, stdin);
}

int alt_printf(const char* format, ...)
{
    return 0;
}
