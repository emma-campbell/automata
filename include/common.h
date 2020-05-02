#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define INT2CHAR(i) (char)(uintptr_t)(i)

#define CHAR2VOIDP(i) (void*)(char)(i)
#define VOID2CHAR(i) (char)(void*)(i)

#define INT2VOIDP(i) (void*)(uintptr_t)(i)
#define VOIDP2INT(i) (uintptr_t)(void*)(i)

#endif // _COMMON_H
