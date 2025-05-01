// Created 2025.05.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
//
#define CONSOLE_COLOR_ENABLED
#define LOGGER_TIME_FORMAT "%f"
#define MEMORY_EXIT_SIZE 32
//
#define MEMORY_EXIT_ADDRESS 	1
#define MEMORY_EXIT_OPENAL		2
//
#include <blue/memory.hpp>
//
namespace MEMORY::EXIT {

	void TYPED_ATEXIT (u8 type, void* anyFunction, u32 size, void* memory) {
		switch (type) {

			MEMORY_EXIT_ADDRESS_CASE (anyFunction, size, memory);

			case MEMORY_EXIT_OPENAL: {
				auto&& _func = (void (*) (int n, const unsigned int *sources))anyFunction;
				auto&& _mem = (const unsigned int *)memory;
				_func (size, _mem);
			} break;

			MEMORY_EXIT_DEFAULT_CASE

		}
	}

}
