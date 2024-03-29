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
#include <string.h>
#include <heap.h>

/*****************************************************************************
 * void* memcpy(dst,src,count)												*
 *****************************************************************************/
void* memcpy(void* dst, const void* src, size_t size)
{
	if ( size > (sizeof(uint32_t)*2) )
	{
		/* handle unaligned address... */
		register char* p_dst_c = (char *)dst;
		register char* p_src_c = (char *)src;
		while (size  > 0 && ( ((uint32_t)p_dst_c & 0x03) || ((uint32_t)p_src_c & 0x03) ) )
		{
			*p_dst_c++ = *p_src_c++;
			--size;
		}

		/* handle aligned word writes... */
		register uint32_t* p_dst_w = (uint32_t*)p_dst_c;
		register uint32_t* p_src_w = (uint32_t*)p_src_c;
		while (size >= sizeof(uint32_t))
		{
			*p_dst_w++ = *p_src_w++;
			size-=sizeof(uint32_t);
		}

		/* handle remaining bytes... */
		p_dst_c = (char *)p_dst_w;
		p_src_c = (char *)p_src_w;
		while (size > 0)
		{
			*p_dst_c++ = *p_src_c++;
			--size;
		}
	}
	else
	{
		register char* p_dst = (char *)dst;
		register char* p_src = (char *)src;
		while (size > 0)
		{
			*p_dst++ = *p_src++;
			--size;
		}
	}
	return dst;
}

/*****************************************************************************
 * void* memcpy(dst,src,count)												*
 *****************************************************************************/
static void* memcpy_r(void* dst, const void* src, size_t size)
{
	src += size;
	dst += size;
	if ( size > (sizeof(uint32_t)*2) )
	{
		/* handle unaligned address... */
		register char* p_dst_c = (char *)dst;
		register char* p_src_c = (char *)src;
		while (size  > 0 && ( ((uint32_t)p_dst_c & 0x03) || ((uint32_t)p_src_c & 0x03) ) )
		{
			*--p_dst_c = *--p_src_c;
			--size;
		}

		/* handle aligned word writes... */
		register uint32_t* p_dst_w = (uint32_t*)p_dst_c;
		register uint32_t* p_src_w = (uint32_t*)p_src_c;
		while (size >= sizeof(uint32_t))
		{
			*--p_dst_w = *--p_src_w;
			size-=sizeof(uint32_t);
		}

		/* handle remaining bytes... */
		p_dst_c = (char *)p_dst_w;
		p_src_c = (char *)p_src_w;
		while (size > 0)
		{
			*--p_dst_c = *--p_src_c;
			--size;
		}
	}
	else
	{
		register char* p_dst = (char *)dst;
		register char* p_src = (char *)src;
		while (size > 0)
		{
			*--p_dst = *--p_src;
			--size;
		}
	}
	return dst;
}

/*****************************************************************************
 * void* memmove(dst,src,count)											   *
 *****************************************************************************/
void* memmove(void *vdst, const void *vsrc, size_t n)
{
	char* dst = (char*)vdst;
	char* src = (char*)vsrc;
	char* svdst;

	if ((dst > src) && (dst < src + n))
	{
		src += n;
		for (svdst = dst + n; n-- > 0; )
			*--svdst = *--src;
	}
	else
	{
		memcpy(vdst,vsrc,n);
	}
	return dst;
}

/*****************************************************************************
 * void* memset(dst,c,count)												  *
 *****************************************************************************/
void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--) *p++ = c;
	return s;
}

/*****************************************************************************
 * void* memcmp(s1,s2,count)												  *
 *****************************************************************************/
int memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t* p1 = (uint8_t*)s1;
	uint8_t* p2 = (uint8_t*)s2;
	while(n--)
	{
		int c1 = *p1++;
		int c2 = *p2++;
		if ( c1 != c2 )
		{
			return c1 - c2;
		}
	}
	return 0;
}

/*****************************************************************************
 * int strcpy(dest,src)														  *
 *****************************************************************************/
char* strcpy(char *dest, const char *src)
{
	char* p = dest; 
	while ( (*dest++ = *src++) != '\0' );
	return p;
}

/*****************************************************************************
 * char* strncpy(dest,src)													 *
 *****************************************************************************/
char* strncpy(char *dest, const char *src,size_t len)
{
	char* p = dest; 
	while ( len-- > 0 && (*dest++ = *src++) != '\0' );
	return p;
}


/*****************************************************************************
 * int strcmp(s1,s2)														  *
 *****************************************************************************/
int strcmp (const char * s1, const char * s2)
{
	for(; *s1 && (*s1 == *s2); ++s1, ++s2);
    if ( *s1 == '\0' && *s2 == '\0' )
        return 0;
    return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
}

/*****************************************************************************
 * int strcasecmp(s1,s2)													  *
 *****************************************************************************/
int strcasecmp (const char * s1, const char * s2)
{
	for(; *s1 && (caribou_toupper(*s1) == caribou_toupper(*s2)); ++s1, ++s2);
    if ( *s1 == '\0' && *s2 == '\0' )
    {
        return 0;
    }
	return caribou_toupper(*(unsigned char *)s1) < caribou_toupper(*(unsigned char *)s2) ? -1 : 1;
}

/*****************************************************************************
 * int strncmp(s1,s2,n)													   *
 *****************************************************************************/
int strncmp(const char* s1, const char* s2, size_t n)
{
	if (n)
	{
		while (--n && *s1 && (*s1 == *s2))
		{
			s1++;
			s2++;
		}
		return *(unsigned char *) s1 - *(unsigned char *) s2;
	}
	return 0;
}

/*****************************************************************************
 * int strncasecmp(s1,s2,n)													   *
 *****************************************************************************/
int strncasecmp(const char* s1, const char* s2, size_t n)
{
	register int f, l;
	do
	{
		if (((f = (unsigned char)(*(s1++))) >= 'A') && (f <= 'Z')) f -= 'A' - 'a';
		if (((l = (unsigned char)(*(s2++))) >= 'A') && (l <= 'Z')) l -= 'A' - 'a';
	} while ( --n && f && (f == l) );
	return f - l;
}

/*****************************************************************************
 * int strlen(s)															  *
 *****************************************************************************/
size_t strlen(const char * str)
{
	register size_t n=0;
    if ( str )
    {
		for( register char* p=(char*)str; *p++; n++ );
    }
	return n;
}

/*****************************************************************************
 * int strchr(s,c)															*
 *****************************************************************************/
char *strchr(const char *s, int c)
{
	while(*s)
	{
		if ( *s == c )
			return (char*)s;
		++s;
	}
	return NULL;
}

/*****************************************************************************
 * int strcat(d,s)															*
 *****************************************************************************/
char *strcat(char *dest, const char *src)
{
	char *p = dest;
	while(*p) ++p;
	do
	{
		*p++ = *src;
	} while(*src++);
	return dest;
}

/*****************************************************************************
 * int atoi(s)																*
 *****************************************************************************/
int atoi(const char* a)
{
	int rc=0;
	while( (*a && *a==' ') || *a=='\t') ++a;
	if ( *a )
	{
		register int digit=1;
		register int multiplier=1;
		while (isnum(a[digit]) || a[digit]=='-' || a[digit] == '.')
			++digit; // skip to last digit
		for(--digit; digit >= 0 && ( isnum(a[digit]) || a[digit] == '.' || a[digit]=='-' ); digit-- )
		{
			if ( a[digit] == '-' )
			{
				rc = -rc;
				break;
			}
			else if ( a[digit] == '.' ) // okay, we're converting from a real number
			{
				multiplier=1;
				rc=0;
			}
			else
			{
				rc += multiplier * (a[digit] - '0');
				multiplier *= 10;
			}
		}
	}
	return rc;
}


/*****************************************************************************
 * int atol(s)																*
 *****************************************************************************/
int64_t atoll(const char* a)
{
	int64_t rc=0L;
	while((*a && *a==' ') || *a=='\t') ++a;
	if ( *a )
	{
		register int64_t digit=1;
		register int64_t multiplier=1;
		while (isnum(a[digit]) || a[digit]=='-' || a[digit] == '.')
			++digit; // skip to last digit
		for(--digit; digit >= 0 && ( isnum(a[digit]) || a[digit] == '.' || a[digit]=='-' ); digit-- )
		{
			if ( a[digit] == '-' )
			{
				rc = -rc;
				break;
			}
			else if ( a[digit] == '.' ) // okay, we're converting from a real number
			{
				multiplier=1;
				rc=0;
			}
			else
			{
				rc += multiplier * (a[digit] - '0');
				multiplier *= 10;
			}
		}
	}
	return rc;
}


char *strdup(const char *s)
{
	char* other = (char*)malloc(strlen(s)+1);
	if ( other )
	{
		strcpy(other,s);
	}
	return other;
}

/*
 * Concatenate src on the end of dst.  At most strlen(dst)+n+1 bytes
 * are written at dst (at most n+1 bytes being appended).  Return dst.
 */
char* strncat(char *dst, const char* src, size_t n)
{
	if (n != 0) 
    {
		char *d = dst;
		const char *s = src;
		while (*d != 0)
			d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return (dst);
}

size_t strcspn (const char *p, const char *s)
{
	int i, j;

	for (i = 0; p[i]; i++) {
		for (j = 0; s[j]; j++) {
			if (s[j] == p[i])
				break;
		}
		if (s[j])
			break;
	}
	return (i);
}

