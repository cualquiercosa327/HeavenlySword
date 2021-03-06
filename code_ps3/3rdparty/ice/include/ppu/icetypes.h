/*
 * Copyright (c) 2003-2005 Naughty Dog, Inc.
 * A Wholly Owned Subsidiary of Sony Computer Entertainment, Inc.
 * Use and distribution without consent strictly prohibited
 */

#ifndef ICE_TYPES
#define ICE_TYPES

#include <assert.h>
#ifndef __SPU__
#include <altivec.h>
#endif
#include <math.h>
#include <stdint.h>

// Base types for the PPU

// This file should be automatically included whenever source gets compiled.

// integer types
typedef unsigned char               U8;
typedef signed char                 I8;

typedef unsigned short              U16;
typedef signed short                I16;

typedef unsigned int                U32;
typedef signed int                  I32;

typedef unsigned long long          U64;
typedef signed long long            I64;

// floating point types
typedef signed short                F16;
typedef float                       F32;
typedef double                      F64;

// fast types
typedef unsigned long long          U32F;
typedef signed long long            I32F;

// vector types
// all vector types are 16-bytes in size
typedef vector unsigned char        VU8;    // 16 elements
typedef vector signed char          VI8;    // 16 elements

typedef vector unsigned short       VU16;   // 8 elements
typedef vector signed short         VI16;   // 8 elements

typedef vector unsigned int         VU32;   // 4 elements
typedef vector signed int           VI32;   // 4 elements

typedef vector signed short         VF16;   // 8 elements
typedef vector float                VF32;   // 4 elements

// NOTE: There are four other VMX vector data types which are
// not currently being included here.  They are:
// vector bool char
// vector bool short
// vector bool int
// vector pixel (which is 8 16-bit elements of the form 1/5/5/5)
// Perhaps they could be called VB8, VB16, VB32, and VP16 respectively.

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect((x), 0)
#define ICE_ALIGN(alignment) __attribute__((aligned(alignment)))
#define ICE_ALIGNED_MALLOC(size, alignment) memalign(alignment, size)

#endif
