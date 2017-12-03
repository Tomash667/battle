#pragma once

//-----------------------------------------------------------------------------
// sanity checks
static_assert(sizeof(char) == 1, "invalid char size");
static_assert(sizeof(short) == 2, "invalid short size");
static_assert(sizeof(int) == 4, "invalid int size");
static_assert(sizeof(float) == 4, "invalid float size");
static_assert(sizeof(double) == 8, "invalid double size");
#ifdef X64
static_assert(sizeof(void*) == 8, "invalid pointer size");
#else
static_assert(sizeof(void*) == 4, "invalid pointer size");
#endif

//-----------------------------------------------------------------------------
// helper macros
#undef NULL
#define BIT(bit) (1<<(bit))
#define IS_SET(flaga,bit) (((flaga) & (bit)) != 0)
#define IS_CLEAR(flaga,bit) (((flaga) & (bit)) == 0)
#define IS_ALL_SET(flaga,bity) (((flaga) & (bity)) == (bity))
#define SET_BIT(flaga,bit) ((flaga) |= (bit))
#define CLEAR_BIT(flaga,bit) ((flaga) &= ~(bit))
#define SET_BIT_VALUE(flaga,bit,wartos) { if(wartos) SET_BIT(flaga,bit); else CLEAR_BIT(flaga,bit); }
#define COPY_BIT(flaga,flaga2,bit) { if(((flaga2) & (bit)) != 0) SET_BIT(flaga,bit); else CLEAR_BIT(flaga,bit); }
#define FLT10(x) (float(int((x)*10))/10)
template <typename T, size_t N>
char(&_ArraySizeHelper(T(&array)[N]))[N];
#define countof( array ) (sizeof( _ArraySizeHelper( array ) ))
#define random_string(ss) ((cstring)((ss)[Rand()%countof(ss)]))
#ifndef STRING
#	define _STRING(str) #str
#	define STRING(str) _STRING(str)
#endif
#define _JOIN(a,b) a##b
#define JOIN(a,b) _JOIN(a,b)

//-----------------------------------------------------------------------------
// typedefs
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int uint;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef const char* cstring;
#ifdef X64
typedef __int64 IntPointer;
typedef unsigned __int64 UIntPointer;
#else
typedef int IntPointer;
typedef unsigned int UIntPointer;
#endif

//-----------------------------------------------------------------------------
// Offset cast
template<typename T>
inline T& offset_cast(void* data, uint offset)
{
	byte* b = ((byte*)data) + offset;
	return *(T*)b;
}

// Cast using union
template<typename To, typename From>
inline To union_cast(const From& f)
{
	union
	{
		To to;
		From from;
	} a;

	a.from = f;
	return a.to;
}

template <typename destT, typename srcT>
destT& absolute_cast(srcT &v)
{
	return reinterpret_cast<destT&>(v);
}
template <typename destT, typename srcT>
const destT& absolute_cast(const srcT& v)
{
	return reinterpret_cast<const destT&>(v);
}

//-----------------------------------------------------------------------------
// more includes
#include "CoreMath.h"
