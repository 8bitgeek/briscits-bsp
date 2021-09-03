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
#include <pid.h>

#define pid_ticks() caribou_timer_ticks()

static bool pid_need_compute (pid_t* pid);
static void pid_compute      (pid_t* pid);

void pid_create(pid_t* pid, float* in, float* out, float* set, float kp, float ki, float kd)
{
	pid->input = in;
	pid->output = out;
	pid->setpoint = set;
	pid->enabled = false;

	pid_limits(pid, 0, 255);

	pid_period(pid, from_ms(100));

	pid_tune(pid, kp, ki, kd);

	pid->lasttime = pid_ticks() - pid->sampletime;
}

bool pid_service(pid_t* pid)
{
	if ( pid_need_compute(pid) )
	{
		pid_compute(pid);
		return true;
	}
	return false;
}

static bool pid_need_compute(pid_t* pid)
{
	return pid_ticks() - pid->lasttime >= pid->sampletime;
}

static void pid_compute(pid_t* pid)
{
	if (pid->enabled)
	{	
		float in = *(pid->input);
		
		float error = *(pid->setpoint) - in;
		
		pid->iterm += (pid->Ki * error);
		if (pid->iterm > pid->omax)
			pid->iterm = pid->omax;
		else if (pid->iterm < pid->omin)
			pid->iterm = pid->omin;
		
		float dinput = in - pid->lastin;
		
		float out = pid->Kp * error + pid->iterm - pid->Kd * dinput;
		
		if (out > pid->omax)
			out = pid->omax;
		else if (out < pid->omin)
			out = pid->omin;
		
		*(pid->output) = out;
		
		pid->lastin = in;
	}
	
	pid->lasttime = pid_ticks();
}

void pid_tune(pid_t* pid, float kp, float ki, float kd)
{
	if ( kp >= 0.0f && ki >= 0.0f && kd >= 0.0f )
	{
		float ssec = ((float) pid->sampletime) / ((float) HZ);

		pid->Kp = kp;
		pid->Ki = ki * ssec;
		pid->Kd = kd / ssec;
	}
}

void pid_period(pid_t* pid, uint32_t time)
{
	if (time > 0) 
	{
		float ratio = (float) (time * (HZ / 1000)) / (float) pid->sampletime;
		pid->Ki *= ratio;
		pid->Kd /= ratio;
		pid->sampletime = time * (HZ / 1000);
	}
}

void pid_limits(pid_t* pid, float min, float max)
{
	if (min >= max) return;
	pid->omin = min;
	pid->omax = max;
	
	if (pid->enabled) 
	{
		if (*(pid->output) > pid->omax)
			*(pid->output) = pid->omax;
		else if (*(pid->output) < pid->omin)
			*(pid->output) = pid->omin;

		if (pid->iterm > pid->omax)
			pid->iterm = pid->omax;
		else if (pid->iterm < pid->omin)
			pid->iterm = pid->omin;
	}
}

void pid_enable(pid_t* pid, bool enable)
{
	if ( enable )
	{
		if (!pid->enabled) {
			pid->iterm = *(pid->output);
			pid->lastin = *(pid->input);
			if (pid->iterm > pid->omax)
				pid->iterm = pid->omax;
			else if (pid->iterm < pid->omin)
				pid->iterm = pid->omin;
		}
		pid->enabled = true;
	}
	else
	{
		pid->enabled = false;
	}
}


bool pid_enabled(pid_t* pid)
{
	return pid->enabled;
}