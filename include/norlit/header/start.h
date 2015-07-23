#ifdef __cplusplus
#define _Noreturn __attribute__((noreturn))
extern "C" {
#else
#define __restrict restrict
#endif