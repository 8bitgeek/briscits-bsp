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
#ifndef PID_H
#define PID_H

#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _pid_ 
{
	bool 			enabled;
		
	float* 			input; 			
	float* 			output; 		
	float* 			setpoint; 		
	
	float 			Kp; 				
	float 			Ki; 				
	float 			Kd; 				
	
	float 			omin; 			
	float 			omax; 			
	
	float 			iterm; 
	float 			lastin; 
	
	caribou_tick_t 	lasttime; 
	caribou_tick_t	sampletime; 
} pid_t;

/**
 * @brief Creates a new PID controller
 *
 * Creates a new pid controller and initializes it�s input, output and internal
 * variables. Also we set the tuning parameters
 *
 * @param pid A pointer to a pid_t
 * @param in Pointer to float value for the process input
 * @param out Poiter to put the controller output value
 * @param set Pointer float with the process setpoint value
 * @param kp Proportional gain
 * @param ki Integral gain
 * @param kd Diferential gain
 *
 * @return returns a pid_t controller handle
 */
void pid_create(pid_t* pid, float* in, float* out, float* set, float kp, float ki, float kd);

/**
 * @brief Service the PID loop
 * @return true of computation was run
 */
bool pid_service(pid_t* pid);

/**
 * @brief Sets new PID tuning parameters
 *
 * Sets the gain for the Proportional (Kp), Integral (Ki) and Derivative (Kd)
 * terms.
 *
 * @param pid The PID controller instance to modify
 * @param kp Proportional gain
 * @param ki Integral gain
 * @param kd Derivative gain
 */
void pid_tune(pid_t* pid, float kp, float ki, float kd);

/**
 * @brief Sets the pid algorithm period
 *
 * Changes the between PID control loop computations.
 *
 * @param pid The PID controller instance to modify
 * @param time The time in milliseconds between computations
 */
void pid_period(pid_t* pid, uint32_t time);

/**
 * @brief Sets the limits for the PID controller output
 *
 * @param pid The PID controller instance to modify
 * @param min The minimum output value for the PID controller
 * @param max The maximum output value for the PID controller
 */
void pid_limits(pid_t* pid, float min, float max);

/**
 * @brief Enables control using PID
 *
 * Enables or disables the PID control loop.
 *
 * @param pid The PID controller instance to enable
 * @param enable Enable or disable
 */
void pid_enable(pid_t* pid, bool enable);

bool pid_enabled( pid_t* pid );

#define pid_reset(pid) pid_enable(pid,false); pid_enable(pid,true)

#ifdef __cplusplus
}
#endif

#endif
