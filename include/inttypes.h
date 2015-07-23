#ifndef _NORLIT_LIBC_INTTYPES_H
#define _NORLIT_LIBC_INTTYPES_H

#include <stdint.h>

#include <norlit/header/start.h>
typedef struct { intmax_t quot, rem; } imaxdiv_t;

intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);

intmax_t strtoimax(const char *__restrict, char **__restrict, int);
uintmax_t strtoumax(const char *__restrict, char **__restrict, int);
#include <norlit/header/end.h>

#if UINTPTR_MAX == UINT64_MAX
#define _FORMAT_64  "l"
#define _FORMAT_PTR "l"
#else
#define _FORMAT_64  "ll"
#define _FORMAT_PTR ""
#endif

#define PRId8  "d"
#define PRId16 "d"
#define PRId32 "d"
#define PRId64 _FORMAT_64 "d"

#define PRIdLEAST8  "d"
#define PRIdLEAST16 "d"
#define PRIdLEAST32 "d"
#define PRIdLEAST64 _FORMAT_64 "d"

#define PRIdFAST8  "d"
#define PRIdFAST16 "d"
#define PRIdFAST32 "d"
#define PRIdFAST64 _FORMAT_64 "d"

#define PRIi8  "i"
#define PRIi16 "i"
#define PRIi32 "i"
#define PRIi64 _FORMAT_64 "i"

#define PRIiLEAST8  "i"
#define PRIiLEAST16 "i"
#define PRIiLEAST32 "i"
#define PRIiLEAST64 _FORMAT_64 "i"

#define PRIiFAST8  "i"
#define PRIiFAST16 "i"
#define PRIiFAST32 "i"
#define PRIiFAST64 _FORMAT_64 "i"

#define PRIo8  "o"
#define PRIo16 "o"
#define PRIo32 "o"
#define PRIo64 _FORMAT_64 "o"

#define PRIoLEAST8  "o"
#define PRIoLEAST16 "o"
#define PRIoLEAST32 "o"
#define PRIoLEAST64 _FORMAT_64 "o"

#define PRIoFAST8  "o"
#define PRIoFAST16 "o"
#define PRIoFAST32 "o"
#define PRIoFAST64 _FORMAT_64 "o"

#define PRIu8  "u"
#define PRIu16 "u"
#define PRIu32 "u"
#define PRIu64 _FORMAT_64 "u"

#define PRIuLEAST8  "u"
#define PRIuLEAST16 "u"
#define PRIuLEAST32 "u"
#define PRIuLEAST64 _FORMAT_64 "u"

#define PRIuFAST8  "u"
#define PRIuFAST16 "u"
#define PRIuFAST32 "u"
#define PRIuFAST64 _FORMAT_64 "u"

#define PRIx8  "x"
#define PRIx16 "x"
#define PRIx32 "x"
#define PRIx64 _FORMAT_64 "x"

#define PRIxLEAST8  "x"
#define PRIxLEAST16 "x"
#define PRIxLEAST32 "x"
#define PRIxLEAST64 _FORMAT_64 "x"

#define PRIxFAST8  "x"
#define PRIxFAST16 "x"
#define PRIxFAST32 "x"
#define PRIxFAST64 _FORMAT_64 "x"

#define PRIX8  "X"
#define PRIX16 "X"
#define PRIX32 "X"
#define PRIX64 _FORMAT_64 "X"

#define PRIXLEAST8  "X"
#define PRIXLEAST16 "X"
#define PRIXLEAST32 "X"
#define PRIXLEAST64 _FORMAT_64 "X"

#define PRIXFAST8  "X"
#define PRIXFAST16 "X"
#define PRIXFAST32 "X"
#define PRIXFAST64 _FORMAT_64 "X"

#define PRIdMAX _FORMAT_64 "d"
#define PRIiMAX _FORMAT_64 "i"
#define PRIoMAX _FORMAT_64 "o"
#define PRIuMAX _FORMAT_64 "u"
#define PRIxMAX _FORMAT_64 "x"
#define PRIXMAX _FORMAT_64 "X"

#define PRIdPTR _FORMAT_PTR "d"
#define PRIiPTR _FORMAT_PTR "i"
#define PRIoPTR _FORMAT_PTR "o"
#define PRIuPTR _FORMAT_PTR "u"
#define PRIxPTR _FORMAT_PTR "x"
#define PRIXPTR _FORMAT_PTR "X"

#define SCNd8   "hhd"
#define SCNd16  "hd"
#define SCNd32  "d"
#define SCNd64  _FORMAT_64 "d"

#define SCNdLEAST8  "hhd"
#define SCNdLEAST16 "hd"
#define SCNdLEAST32 "d"
#define SCNdLEAST64 _FORMAT_64 "d"

#define SCNdFAST8  "hhd"
#define SCNdFAST16 "d"
#define SCNdFAST32 "d"
#define SCNdFAST64 _FORMAT_64 "d"

#define SCNi8   "hhi"
#define SCNi16  "hi"
#define SCNi32  "i"
#define SCNi64  _FORMAT_64 "i"

#define SCNiLEAST8  "hhi"
#define SCNiLEAST16 "hi"
#define SCNiLEAST32 "i"
#define SCNiLEAST64 _FORMAT_64 "i"

#define SCNiFAST8  "hhi"
#define SCNiFAST16 "i"
#define SCNiFAST32 "i"
#define SCNiFAST64 _FORMAT_64 "i"

#define SCNu8   "hhu"
#define SCNu16  "hu"
#define SCNu32  "u"
#define SCNu64  _FORMAT_64 "u"

#define SCNuLEAST8  "hhu"
#define SCNuLEAST16 "hu"
#define SCNuLEAST32 "u"
#define SCNuLEAST64 _FORMAT_64 "u"

#define SCNuFAST8 "hhu"
#define SCNuFAST16 "u"
#define SCNuFAST32 "u"
#define SCNuFAST64 _FORMAT_64 "u"

#define SCNo8   "hho"
#define SCNo16  "ho"
#define SCNo32  "o"
#define SCNo64  _FORMAT_64 "o"

#define SCNoLEAST8  "hho"
#define SCNoLEAST16 "ho"
#define SCNoLEAST32 "o"
#define SCNoLEAST64 _FORMAT_64 "o"

#define SCNoFAST8  "hho"
#define SCNoFAST16 "o"
#define SCNoFAST32 "o"
#define SCNoFAST64 _FORMAT_64 "o"

#define SCNx8   "hhx"
#define SCNx16  "hx"
#define SCNx32  "x"
#define SCNx64  _FORMAT_64 "x"

#define SCNxLEAST8  "hhx"
#define SCNxLEAST16 "hx"
#define SCNxLEAST32 "x"
#define SCNxLEAST64 _FORMAT_64 "x"

#define SCNxFAST8  "hhx"
#define SCNxFAST16 "x"
#define SCNxFAST32 "x"
#define SCNxFAST64 _FORMAT_64 "x"

#define SCNdMAX _FORMAT_64 "d"
#define SCNiMAX _FORMAT_64 "i"
#define SCNoMAX _FORMAT_64 "o"
#define SCNuMAX _FORMAT_64 "u"
#define SCNxMAX _FORMAT_64 "x"

#define SCNdPTR _FORMAT_PTR "d"
#define SCNiPTR _FORMAT_PTR "i"
#define SCNoPTR _FORMAT_PTR "o"
#define SCNuPTR _FORMAT_PTR "u"
#define SCNxPTR _FORMAT_PTR "x"

#endif