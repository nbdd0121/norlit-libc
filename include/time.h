#ifndef _NORLIT_LIBC_TIME_H
#define _NORLIT_LIBC_TIME_H

#define __need_clock_t
#define __need_size_t
#define __need_time_t
#define __need_clockid_t
#define __need_timer_t
#define __need_locale_t
#define __need_pid_t
#include <norlit/alltypes.h>

#define __need_NULL
#include <stddef.h>

#define CLOCKS_PER_SEC ((clock_t)1000000)

// TODO: CLOCK_MONOTONIC
// TODO: CLOCK_PROCESS_CPUTIME_ID
// TODO: CLOCK_REALTIME
// TODO: CLOCK_THREAD_CPUTIME_ID

// TODO: TIMER_ABSTIME

// TODO: getdate_err

// TODO: sigevent

#include <norlit/header/start.h>
struct tm {
	int    tm_sec  ;
	int    tm_min  ;
	int    tm_hour ;
	int    tm_mday ;
	int    tm_mon  ;
	int    tm_year ;
	int    tm_wday ;
	int    tm_yday ;
	int    tm_isdst;
};

struct timespec {
	time_t  tv_sec ;
	long    tv_nsec;
};

struct itimerspec {
	struct timespec  it_interval;
	struct timespec  it_value   ;
};

char      *asctime(const struct tm *);
clock_t    clock(void);
char      *ctime(const time_t *);
double     difftime(time_t, time_t);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t     mktime(struct tm *);
size_t     strftime(char *__restrict, size_t, const char *__restrict,
                    const struct tm *__restrict);
time_t     time(time_t *);

// CX Extensions
char      *asctime_r(const struct tm *__restrict, char *__restrict);
char      *ctime_r(const time_t *, char *);
int        clock_getres(clockid_t, struct timespec *);
int        clock_gettime(clockid_t, struct timespec *);
int        clock_nanosleep(clockid_t, int, const struct timespec *,
                           struct timespec *);
int        clock_settime(clockid_t, const struct timespec *);
struct tm *gmtime_r(const time_t *__restrict, struct tm *__restrict);
struct tm *localtime_r(const time_t *__restrict, struct tm *__restrict);
int        nanosleep(const struct timespec *, struct timespec *);
size_t     strftime_l(char *__restrict, size_t, const char *__restrict,
                      const struct tm *__restrict, locale_t);
int        timer_create(clockid_t, struct sigevent *__restrict,
                        timer_t *__restrict);
int        timer_delete(timer_t);
int        timer_getoverrun(timer_t);
int        timer_gettime(timer_t, struct itimerspec *);
int        timer_settime(timer_t, int, const struct itimerspec *__restrict,
                         struct itimerspec *__restrict);
void       tzset(void);

// XSI Extensions
struct tm *getdate(const char *);
char      *strptime(const char *__restrict, const char *__restrict,
                    struct tm *__restrict);

// CPT Extension
int        clock_getcpuclockid(pid_t, clockid_t *);

// CX Extensions
extern char  *tzname[];

// XSI Extensions
extern int    daylight;
extern long   timezone;

#include <norlit/header/end.h>

#endif