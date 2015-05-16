#ifndef __console_h
#define __console_h

#define CONSOLE_MAXLEN 20
#define CONSOLE_NON_BLOCKING 0
#define CONSOLE_BLOCKING 1


unsigned char console_process(unsigned char blocking, unsigned char *result, unsigned int maxlen);

#define console_BACKSPACE 8
#define console_ENTER 13
#define console_SPACE 32

#endif
