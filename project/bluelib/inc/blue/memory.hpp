// Created 2024.11.13 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "debug.hpp"
//
#ifndef MEMORY_EXIT_SIZE
#define MEMORY_EXIT_SIZE 64
#endif

//  'About'
// - Implements a simple wrapper around 'malloc'
// - Implements a custom 'atexit' implementation that allows sending the parameter. 
//

#if DDEBUG (DEBUG_FLAG_MEMORY)

	s32 allocationsCounter = 0;

	#if DDEBUG (DEBUG_FLAG_LOGGING)

		#include "log.hpp"

		#define LOGMEMORY() { \
			LOGWARN ("Missed Deallocations: %d\n", allocationsCounter); \
		}

	#else
		#define LOGMEMORY() {} // dummy
	#endif

	#define INCALLOCCO() ++allocationsCounter;
	#define DECALLOCCO() --allocationsCounter;


	template <typename Type>
	void _ALLOCATE (Type*& address, const u64& size) {
		++allocationsCounter;
		address = (Type*) malloc (size);
	}

	#define ALLOCATE(type, address, size) _ALLOCATE<type> (address, size)

	void FREE (void* address) {
		--allocationsCounter;
		free (address);
	}

#else

	#define ALLOCATE(type, address, size) address = (type*) malloc (size)
	void FREE (void* address) { free (address); }
	#define LOGMEMORY() {} // dummy
	#define INCALLOCCO() // dummy
	#define DECALLOCCO() // dummy

#endif



namespace MEMORY {

	template <typename T>
	void Construct2 (
		OUT		T*& 				newArray, 
		IN		const u32& 			aArrayLength, 
		IN		const void* const& 	aArray, 
		IN		const u32& 			bArrayLength, 
		IN		const void* const& 	bArray
	) {
		ALLOCATE (T, newArray, aArrayLength + bArrayLength);
		memcpy (newArray, aArray, aArrayLength);
		memcpy (newArray + aArrayLength, bArray, bArrayLength);
	}

	template <typename T>
	void Construct3 (
		OUT		T*& 				newArray, 
		IN		const u32& 			aArrayLength, 
		IN		const void* const& 	aArray, 
		IN		const u32& 			bArrayLength, 
		IN		const void* const& 	bArray,
		IN		const u32& 			cArrayLength, 
		IN		const void* const& 	cArray
	) {
		ALLOCATE (T, newArray, aArrayLength + bArrayLength + cArrayLength);
		memcpy (newArray, aArray, aArrayLength);
		memcpy (newArray + aArrayLength, bArray, bArrayLength);
		memcpy (newArray + aArrayLength + bArrayLength, cArray, cArrayLength);
	}

}

//
// - PRE - MEMORY EXIT - DATA
//

//  ABOUT
// Later `memory_exit.hpp` is being linked and therefore the following defines are both available inside
//  `memory_exit.hpp` and other files that include said file. So for example when redefining `MEMORY_EXIT_TYPE_ATEXIT` 
//  function we can reference the defines below to do so more easly.

#define MEMORY_EXIT_ADDRESS_CASE(anyFunction, size, memory) { \
	case MEMORY_EXIT_ADDRESS: { \
		auto&& _func = (void (*) (void*))anyFunction; \
		_func (memory); \
	} break; \
}

#if DDEBUG (DEBUG_FLAG_LOGGING)

	#define MEMORY_EXIT_DEFAULT_CASE default: LOGWARN ("Unresolved MEMORY_EXIT_TYPE!\n");

#else 

	// TODO. This should be a very well documented error ! 
	#define MEMORY_EXIT_DEFAULT_CASE default: { /* exit(-2) */ };

#endif
