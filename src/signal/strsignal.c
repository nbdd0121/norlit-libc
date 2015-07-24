/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#include <signal.h>

char *strsignal(int signum) {
	switch (signum) {
		case SIGABRT: return "Process abort signal";
		case SIGALRM: return "Alarm clock";
		case SIGBUS: return "Access to an undefined portion of a memory object";
		case SIGCHLD: return "Child process terminated, stopped, or continued";
		case SIGCONT: return "Continue executing, if stopped";
		case SIGFPE: return "Erroneous arithmetic operation";
		case SIGHUP: return "Hangup";
		case SIGILL: return "Illegal instruction";
		case SIGINT: return "Terminal interrupt signal";
		case SIGKILL: return "Kill (cannot be caught or ignored)";
		case SIGPIPE: return "Write on a pipe with no one to read it";
		case SIGQUIT: return "Terminal quit signal";
		case SIGSEGV: return "Invalid memory reference";
		case SIGSTOP: return "Stop executing (cannot be caught or ignored)";
		case SIGTERM: return "Termination signal";
		case SIGTSTP: return "Terminal stop signal";
		case SIGTTIN: return "Background process attempting read";
		case SIGTTOU: return "Background process attempting write";
		case SIGUSR1: return "User-defined signal 1";
		case SIGUSR2: return "User-defined signal 2";
		case SIGPOLL: return "Pollable event";
		case SIGPROF: return "Profiling timer expired";
		case SIGSYS: return "Bad system call";
		case SIGTRAP: return "Trace/breakpoint trap";
		case SIGURG: return "High bandwidth data is available at a socket";
		case SIGVTALRM: return "Virtual timer expired";
		case SIGXCPU: return "CPU time limit exceeded";
		case SIGXFSZ: return "File size limit exceeded";
		default: return "Unknown signal";
	}
}