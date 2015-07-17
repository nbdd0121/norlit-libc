#ifndef _NORLIT_LIBC_MATH_H
#define _NORLIT_LIBC_MATH_H

typedef float float_t;
typedef double double_t;

#define NAN       __builtin_nanf("")
#define INFINITY  __builtin_inff()
#define HUGE_VALF __builtin_huge_valf()
#define HUGE_VAL  __builtin_huge_val()
#define HUGE_VALL __builtin_huge_vall()

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

// INT_MIN
#define FP_ILOGBNAN (1<<(sizeof(int)*8-1))
#define FP_ILOGB0 FP_ILOGBNAN

#define MATH_ERRNO          1
#define MATH_ERREXCEPT      2
#define math_errhandling    2

static inline unsigned __float_to_bits(float __f) {
	union {
		float __f;
		unsigned __i;
	} __u = {__f};
	return __u.__i;
}
static inline unsigned long long __double_to_bits(double __f) {
	union {
		double __f;
		unsigned long long __i;
	} __u = {__f};
	return __u.__i;
}

#define __generic_math(x, func) ( \
	sizeof(x) == sizeof(float) ? func##f(x) : \
	sizeof(x) == sizeof(double) ? func(x) : \
	func##l(x) )
#define __generic_math_2(x, y, func) ( \
	sizeof((x) + (y)) == sizeof(float) ? func##f(x, y) : \
	sizeof((x) + (y)) == sizeof(double) ? func(x, y) : \
	func##l(x, y) )

#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#define isinf(x) __builtin_fpclassify(0, 1, 0, 0, 0, x)
#define isnan(x) __builtin_fpclassify(1, 0, 0, 0, 0, x)
#define isnormal(x) __builtin_fpclassify(0, 0, 1, 0, 0, x)
#define isfinite(x) __builtin_fpclassify(0, 0, 1, 1, 1, x)

#define __signbitf(f) (int)(__float_to_bits(f)>>31)
#define __signbit(f) (int)(__double_to_bits(f)>>63)
int __signbitl(long double);

#define signbit(x) __generic_math(x, __signbit)
#define isunordered(x,y) (isnan(x) || isnan(y))

#define __define_relation_function(rel, op, type) \
	static inline int __is##rel(type __x, type __y) { \
		return !isunordered(__x,__y) && __x op __y; \
	}
#define __define_generic_rel_func(rel, op) \
	__define_relation_function(rel##f, op, float)\
	__define_relation_function(rel, op, double)\
	__define_relation_function(rel##l, op, long double)\

__define_generic_rel_func(lessf, < )
__define_generic_rel_func(lessequalf, <= )
__define_generic_rel_func(lessgreaterf, != )
__define_generic_rel_func(greaterf, > )
__define_generic_rel_func(greaterequalf, >= )

#define isless(x, y)            __generic_math_2(x, y, __isless)
#define islessequal(x, y)       __generic_math_2(x, y, __islessequal)
#define islessgreater(x, y)     __generic_math_2(x, y, __islessgreater)
#define isgreater(x, y)         __generic_math_2(x, y, __isgreater)
#define isgreaterequal(x, y)    __generic_math_2(x, y, __isgreaterequal)

// XSI Extensions
#define M_E             2.7182818284590452354
#define M_LOG2E         1.4426950408889634074
#define M_LOG10E        0.43429448190325182765
#define M_LN2           0.69314718055994530942
#define M_LN10          2.30258509299404568402
#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923
#define M_PI_4          0.78539816339744830962
#define M_1_PI          0.31830988618379067154
#define M_2_PI          0.63661977236758134308
#define M_2_SQRTPI      1.12837916709551257390
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.70710678118654752440

double      acos(double);
float       acosf(float);
double      acosh(double);
float       acoshf(float);
long double acoshl(long double);
long double acosl(long double);
double      asin(double);
float       asinf(float);
double      asinh(double);
float       asinhf(float);
long double asinhl(long double);
long double asinl(long double);
double      atan(double);
double      atan2(double, double);
float       atan2f(float, float);
long double atan2l(long double, long double);
float       atanf(float);
double      atanh(double);
float       atanhf(float);
long double atanhl(long double);
long double atanl(long double);
double      cbrt(double);
float       cbrtf(float);
long double cbrtl(long double);
double      ceil(double);
float       ceilf(float);
long double ceill(long double);
double      copysign(double, double);
float       copysignf(float, float);
long double copysignl(long double, long double);
double      cos(double);
float       cosf(float);
double      cosh(double);
float       coshf(float);
long double coshl(long double);
long double cosl(long double);
double      erf(double);
double      erfc(double);
float       erfcf(float);
long double erfcl(long double);
float       erff(float);
long double erfl(long double);
double      exp(double);
double      exp2(double);
float       exp2f(float);
long double exp2l(long double);
float       expf(float);
long double expl(long double);
double      expm1(double);
float       expm1f(float);
long double expm1l(long double);
double      fabs(double);
float       fabsf(float);
long double fabsl(long double);
double      fdim(double, double);
float       fdimf(float, float);
long double fdiml(long double, long double);
double      floor(double);
float       floorf(float);
long double floorl(long double);
double      fma(double, double, double);
float       fmaf(float, float, float);
long double fmal(long double, long double, long double);
double      fmax(double, double);
float       fmaxf(float, float);
long double fmaxl(long double, long double);
double      fmin(double, double);
float       fminf(float, float);
long double fminl(long double, long double);
double      fmod(double, double);
float       fmodf(float, float);
long double fmodl(long double, long double);
double      frexp(double, int *);
float       frexpf(float, int *);
long double frexpl(long double, int *);
double      hypot(double, double);
float       hypotf(float, float);
long double hypotl(long double, long double);
int         ilogb(double);
int         ilogbf(float);
int         ilogbl(long double);
double      ldexp(double, int);
float       ldexpf(float, int);
long double ldexpl(long double, int);
double      lgamma(double);
float       lgammaf(float);
long double lgammal(long double);
long long   llrint(double);
long long   llrintf(float);
long long   llrintl(long double);
long long   llround(double);
long long   llroundf(float);
long long   llroundl(long double);
double      log(double);
double      log10(double);
float       log10f(float);
long double log10l(long double);
double      log1p(double);
float       log1pf(float);
long double log1pl(long double);
double      log2(double);
float       log2f(float);
long double log2l(long double);
double      logb(double);
float       logbf(float);
long double logbl(long double);
float       logf(float);
long double logl(long double);
long        lrint(double);
long        lrintf(float);
long        lrintl(long double);
long        lround(double);
long        lroundf(float);
long        lroundl(long double);
double      modf(double, double *);
float       modff(float, float *);
long double modfl(long double, long double *);
double      nan(const char *);
float       nanf(const char *);
long double nanl(const char *);
double      nearbyint(double);
float       nearbyintf(float);
long double nearbyintl(long double);
double      nextafter(double, double);
float       nextafterf(float, float);
long double nextafterl(long double, long double);
double      nexttoward(double, long double);
float       nexttowardf(float, long double);
long double nexttowardl(long double, long double);
double      pow(double, double);
float       powf(float, float);
long double powl(long double, long double);
double      remainder(double, double);
float       remainderf(float, float);
long double remainderl(long double, long double);
double      remquo(double, double, int *);
float       remquof(float, float, int *);
long double remquol(long double, long double, int *);
double      rint(double);
float       rintf(float);
long double rintl(long double);
double      round(double);
float       roundf(float);
long double roundl(long double);
double      scalbln(double, long);
float       scalblnf(float, long);
long double scalblnl(long double, long);
double      scalbn(double, int);
float       scalbnf(float, int);
long double scalbnl(long double, int);
double      sin(double);
float       sinf(float);
double      sinh(double);
float       sinhf(float);
long double sinhl(long double);
long double sinl(long double);
double      sqrt(double);
float       sqrtf(float);
long double sqrtl(long double);
double      tan(double);
float       tanf(float);
double      tanh(double);
float       tanhf(float);
long double tanhl(long double);
long double tanl(long double);
double      tgamma(double);
float       tgammaf(float);
long double tgammal(long double);
double      trunc(double);
float       truncf(float);
long double truncl(long double);

// XSI Extensions
double      j0(double);
double      j1(double);
double      jn(int, double);
double      y0(double);
double      y1(double);
double      yn(int, double);

// XSI Extensions
extern int signgam;

#endif