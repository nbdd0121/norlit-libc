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