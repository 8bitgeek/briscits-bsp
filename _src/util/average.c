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
#include <average.h>

extern void average_setup(average_t* a, float* samples, size_t size)
{
	a->samples = samples;
	a->size = size;
	a->next = 0;
	a->full = false;
	for(int n=0; n < size; n++)
	{
		samples[n] = 0.0;
	}
}

extern float average(average_t* a, float f)
{
	if ( a->size >= 1 )
	{
		register float* samples = a->samples;

		samples[a->next++] = f;
		if ( a->next >= a->size )
		{
			a->next=0;
			a->full=true;
		}
		return average_value(a);
	}
	return f;
}

extern float average_value(average_t* a)
{
	float t=0.0;
	size_t size;
	register float* samples = a->samples;

	/* Determine if the size for average is full or partial full */
	if ( a->full )
		size = a->size;
	else
		size = a->next;

	for(register size_t x=0; x < size; x++)
		t += samples[x];
	
	return (t/size);

}

extern void average_set_size(average_t* a, size_t size)
{
	if ( a->size != size )
	{
		a->size = size;
		a->full = false;
		if ( a->next >= a->size )
		{
			a->next = 0;
			a->full = true;
		}
	}
}

