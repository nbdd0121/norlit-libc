#ifndef _NORLIT_LIBC_SIGNAL_H
#define _NORLIT_LIBC_SIGNAL_H

#define SIG_ERR  ((void (*)(int))-1)
#define SIG_DFL  ((void (*)(int)) 0)
#define SIG_IGN  ((void (*)(int)) 1)
#define SIG_HELD ((void (*)(int)) 2)

#define SIGABRT		1
#define SIGALRM		2
#define SIGBUS		3
#define SIGCHLD		4
#define SIGCONT		5
#define SIGFPE		6
#define SIGHUP		7
#define SIGILL		8
#define SIGINT		9
#define SIGKILL		10
#define SIGPIPE		11
#define SIGQUIT		12
#define SIGSEGV		13
#define SIGSTOP		14
#define SIGTERM		15
#define SIGTSTP		16
#define SIGTTIN		17
#define SIGTTOU		18
#define SIGUSR1		19
#define SIGUSR2		20
#define SIGPOLL		21
#define SIGPROF		22
#define SIGSYS		23
#define SIGTRAP		24
#define SIGURG		25
#define SIGVTALRM	26
#define SIGXCPU		27
#define SIGXFSZ		28

// TODO sigevent

// #define SIGEV_SIGNAL 0
// #define SIGEV_NONE 1
// #define SIGEV_THREAD 2

// union sigval {
// 	int    sival_int
// 	void  *sival_ptr;
// };

// TODO SIGRTMIN, SIGRTMAX

// struct sigaction {
// 	union {
// 		void   (*sa_handler)(int);
// 		void   (*sa_sigaction)(int, siginfo_t *, void *);
// 	};
// 	sigset_t sa_mask;
// 	int      sa_flags;
// };

// #define SIG_BLOCK     0
// #define SIG_UNBLOCK   1
// #define SIG_SETMASK   2

// TODO: More symbols defined in POSIX

#include <norlit/header/start.h>
// pthread_t, uid_t, size_t

typedef int sig_atomic_t;

// timespec, sigset_t, pid_t
// pthread_attr_t

int    raise(int);
void (*signal(int, void (*)(int)))(int);
#include <norlit/header/end.h>

// CX Extensions
// int    kill(pid_t, int);
// void   psiginfo(const siginfo_t *, const char *);
// void   psignal(int, const char *);
// int    pthread_kill(pthread_t, int);
// int    pthread_sigmask(int, const sigset_t *restrict,
//                        sigset_t *restrict);
// int    sigaction(int, const struct sigaction *restrict,
//                  struct sigaction *restrict);
// int    sigaddset(sigset_t *, int);
// int    sigdelset(sigset_t *, int);
// int    sigemptyset(sigset_t *);
// int    sigfillset(sigset_t *);
// int    sigismember(const sigset_t *, int);
// int    sigpending(sigset_t *);
// int    sigprocmask(int, const sigset_t *restrict, sigset_t *restrict);
// int    sigqueue(pid_t, int, const union sigval);
// int    sigsuspend(const sigset_t *);
// int    sigtimedwait(const sigset_t *restrict, siginfo_t *restrict,
//                     const struct timespec *restrict);
// int    sigwait(const sigset_t *restrict, int *restrict);
// int    sigwaitinfo(const sigset_t *restrict, siginfo_t *restrict);

// XSI Extensions
// int    killpg(pid_t, int);
// int    sigaltstack(const stack_t *restrict, stack_t *restrict);

// OB XSI
// int    sighold(int);
// int    sigignore(int);
// int    siginterrupt(int, int);
// int    sigpause(int);
// int    sigrelse(int);
// void (*sigset(int, void (*)(int)))(int);

#endif