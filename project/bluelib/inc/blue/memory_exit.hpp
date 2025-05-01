// Created 2025.05.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "memory.hpp"

#ifndef MEMORY_EXIT_ADDRESS

	#define MEMORY_EXIT_ADDRESS 1

	namespace MEMORY::EXIT {

		void TYPED_ATEXIT (u8 type, void* anyFunction, u32 size, void* memory) {
			switch (type) {
				MEMORY_EXIT_ADDRESS_CASE (anyFunction, size, memory);
				MEMORY_EXIT_DEFAULT_CASE
			}
		}

	}

#endif

namespace MEMORY::EXIT {

	u8 memoryCounter = 0;

	void* functions	[MEMORY_EXIT_SIZE];
	void* memories	[MEMORY_EXIT_SIZE];
	u32   sizes		[MEMORY_EXIT_SIZE];
	u8    types		[MEMORY_EXIT_SIZE];

	void ATEXIT () {
		for (u8 i = memoryCounter; i != 0; --i) {
			auto& func		= functions	[i - 1];
			auto& memory	= memories	[i - 1];
			auto& size		= sizes 	[i - 1];
			auto& type		= types 	[i - 1];
			TYPED_ATEXIT (type, func, size, memory);
		}
	}

	void PUSH (u8 type, void* function, u32 size, void* memory) {
		functions[memoryCounter] 	= function;
		memories[memoryCounter] 	= memory;
		sizes[memoryCounter] 		= size;
		types[memoryCounter] 		= type;

		++memoryCounter;
	}

	void POP () {
		--memoryCounter;
	}

}
