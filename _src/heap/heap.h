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

Copyright (c) 2022 Mike Sharkey

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
#ifndef BRISC_HEAP_H
#define BRISC_HEAP_H

#include <stdint.h>
#include <stddef.h>
#include <brisc_thread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(BRISC_ANSI_HEAP)
    #define BRISC_ANSI_HEAP 1
#endif

#if (!defined(BRISC_NUMHEAPS) || BRISC_NUMHEAPS == 0)
    #define BRISC_NUMHEAPS 1
#endif

/** BITMAP_HEAP state variables. */
typedef struct
{
    /** Pointer to the bitmap of free blocks, 0=free, 1=used */
    uint32_t*       heap_free_bitmap;       
        
    /** Pointer to the bitmap marking the last contiguous block in each allocation */
    uint32_t*       heap_last_bitmap;           

    /** The size of each heap bitmap in bytes */
    int32_t         heap_bitmap_size;           

    /** Pointer to the first bytes of the usable heap memory */
    uint8_t*        heap_area;                  

    /** The size of the heap in blocks */
    int32_t         heap_blocks;
        
    /** The number of blocks in use (for fast statistics) */
    int32_t         heap_blocks_allocated;

    /** The mpu heap region flags */
    uint32_t        heap_flags;

} brisc_heap_state_t;

#if !defined(BRISC_NULL_HEAP)
    extern brisc_heap_state_t brisc_heap_state[];
#endif

extern void*    brisc_heap_malloc(size_t sz);
extern void*    brisc_heap_realloc(void* p, size_t sz);
extern void*    brisc_heap_calloc(size_t nmemb, size_t size);
extern void     brisc_heap_free(void* p);
extern void     brisc_heap_init(void* heap_base, void* heap_end);
extern int32_t  brisc_heap_block_size(void);
extern int32_t  brisc_heap_blocks_allocated();
extern int32_t  brisc_heap_bytes_used();
extern int32_t  brisc_heap_bytes_free();
extern size_t   brisc_heap_sizeof(void* p);

#if BRISC_ANSI_HEAP
    extern void*    malloc(size_t sz);
    extern void*    realloc(void* p, size_t sz);
    extern void*    calloc(size_t nmemb, size_t size);
    extern void     free(void* p);
#endif

#ifdef __cplusplus
}
#endif

#endif /* BRISC_HEAP_H */
