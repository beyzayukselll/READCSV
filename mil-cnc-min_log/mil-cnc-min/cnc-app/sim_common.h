#if !defined(SIM_COMMON_H)

#if defined(SIM_USESTDINT)
#include <stdint.h>
typedef int8_t				i8;
typedef int16_t				i16;
typedef int32_t				i32;
typedef int64_t				i64;

typedef uint8_t				u8;
typedef uint16_t			u16;
typedef uint32_t			u32;
typedef uint64_t			u64;
#else
typedef signed char			i8;
typedef signed short		i16;
typedef signed int			i32;
typedef signed long long	i64;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;
#endif

typedef float				r32;
typedef double				r64;

#define SIM_COMMON_H
#endif