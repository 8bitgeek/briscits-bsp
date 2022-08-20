/******************************************************************************
 ________  ________  ___  ________  ________  ___  _________  ________      
|\   __  \|\   __  \|\  \|\   ____\|\   ____\|\  \|\___   ___\\   ____\     
\ \  \|\ /\ \  \|\  \ \  \ \  \___|\ \  \___|\ \  \|___ \  \_\ \  \___|_    
 \ \   __  \ \   _  _\ \  \ \_____  \ \  \    \ \  \   \ \  \ \ \_____  \   
  \ \  \|\  \ \  \\  \\ \  \|____|\  \ \  \____\ \  \   \ \  \ \|____|\  \  
   \ \_______\ \__\\ _\\ \__\____\_\  \ \_______\ \__\   \ \__\  ____\_\  \ 
    \|_______|\|__|\|__|\|__|\_________\|_______|\|__|    \|__| |\_________\
                            \|_________|                        \|_________|
                            
MIT License

Copyright (c) 2021 Mike Sharkey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/
#ifndef BRISCITS_STRING_H
#define BRISCITS_STRING_H

#include <stdint.h>
#include <stddef.h>
#include <brisc_thread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define caribou_isupper(c) ((c)>='A'&&(c)<='Z')
#define caribou_islower(c) ((c)>='a'&&(c)<='z')
#define caribou_toupper(c) (caribou_islower(c)?(c)-0x20:(c))
#define caribou_tolower(c) (caribou_isupper(c)?(c)+0x20:(c))
#define caribou_isalpha(c) (caribou_isupper(c)||caribou_islower(c))

/**
 ** @brief The  memcpy()  function  copies n bytes from memory area src to memory area dest. The memory areas should not overlap.
 ** @return void
 */
extern void* memcpy(void* dest, const void *src, register size_t n);

/**
 ** @brief The  memmove() method copies n bytes from memory area src to memory area dest.  The memory areas may overlap.
 ** @return The memmove() function returns a pointer to dest.
 */
extern void* memmove(void *dest, const void *src, register size_t n);

/**
 ** @brief The memset() function fills the first n bytes of the memory area pointed to by dest with the constant byte c.
 ** @return The memset() function returns a pointer to the memory area dest.
 */
extern void* memset(void* dest, register int c, register size_t n);

/**
 ** @brief The memcmp() function compares the first n bytes of the memory areas s1 and s2.  It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 ** @return The memcmp() function returns an integer less than, equal to, or greater than zero if the  first  n  bytes  of  s1  is  found, respectively, to be less than, to match, or be greater than the first n bytes of s2.
 */
extern int memcmp(const void *s1, const void *s2, size_t n);

/**
 ** The  strcpy()  function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to
 ** by dest.  The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 ** @return The strcpy() and strncpy() functions return a pointer to the destination string dest.
 */
extern char* strcpy(register char *dest, register const char *src);

/**
 ** The  strcpy()  function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to
 ** by dest.  The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 ** @return The strcpy() and strncpy() functions return a pointer to the destination string dest.
 */
extern char* strncpy( register char *dest, register const char *src, size_t len );

/**
 ** @brief The  strcmp()  function  compares  the  two  strings s1 and s2.
 ** @return It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
extern int strcmp(register const char *s1, register const char *s2);

/**
 ** @brief The  strcasecmp()  function  performs case insensitive compare  the  two  strings s1 and s2.
 ** @return It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
extern int strcasecmp(register const char *s1, register const char *s2);

/**
 ** @brief The  strcmp()  function  compares  the  two  strings s1 and s2.
 ** @return It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
extern int strncmp(register const char* s1, register const char* s2, size_t n);

/**
 ** @brief The  strcmp()  function  compares  the  two  strings s1 and s2.
 ** @return It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
extern int strncasecmp(register const char* s1, register const char* s2, size_t n);

/**
 ** @brief The strlen() function calculates the length of the string s, not including the terminating '\0' character.
 ** @return The strlen() function returns the number of characters in s.
 */
extern size_t strlen(const char* s);

/**
 ** @return The strchr() functions return a pointer to the matched character or NULL if the character is not found.
 */
extern char *strchr(const char *s, int c);

/**
 ** @brief The strcat() function appends the src string to the dest string, overwriting the terminating null byte ('\0') at the end of dest, and then adds a terminating null byte.
 ** The strings may not overlap, and the dest string must have enough space for the result.
 ** @return The strchr() functions return a pointer to the matched character or NULL if the character is not found.
 */
extern char *strcat(char *dest, const char *src);

/**
 ** @brief The strcat() function appends the src string to the dest string, overwriting the terminating null byte ('\0') at the end of dest, and then adds a terminating null byte.
 ** The strings may not overlap, and the dest string must have enough space for the result.
 ** @return The strchr() functions return a pointer to the matched character or NULL if the character is not found.
 */
extern char *strncat(char *__s1, const char *__s2, size_t __n);

extern char *strdup(const char *s);

extern int atoi(const char* a);

extern int64_t atoll(const char* a);

extern size_t strcspn (const char *p, const char *s);

#define isnum(c) ( (c)>='0' && (c)<='9' )
#define ishex(c) isnum(c) || ( toupper(c)>='A' && toupper(c)<='F' )
#define hex(c) ( (c)<0xa ? (c)+'0' : ((c)-0xa)+'A' )

#ifdef __cplusplus
}
#endif

#endif
