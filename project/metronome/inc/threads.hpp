// Created 2025.05.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include <threads.h>
//
#include "global.hpp"

namespace THREADS {

	struct YIELDARGS {
		u16 bmp;
		ALuint source;
	};

}


namespace THREADS {
	
	s32 INPUT (
		INOUT 	void* anyargs
	) {
	
		// TODO
		// This should error-out threadsafe way.
		DEBUG (DEBUG_FLAG_LOGGING) { 
			if (anyargs != nullptr) LOGWARN ("Arguments passed to 'ITHREAD'!");
		}
	
		c8 buffer[128];
		
		while (GLOBAL::isStopPlayback) {
		
			// TODO
			// Right now it waits for new-line. That's not needed. 
			if (fgets (buffer, sizeof (buffer), stdin)) {
				printf("You entered: %s", buffer);
				GLOBAL::isStopPlayback = false;
			}
		
		}
	
		return 0;
	}
	
	
	s32 YIELD (
		INOUT 	void* anyargs
	) {
	
		// TODO
		// This should error-out threadsafe way.
		DEBUG (DEBUG_FLAG_LOGGING) {
			if (anyargs == nullptr) LOGWARN ("No arguments passed to 'OTHREAD'!");
		}
	
		const auto args = *(YIELDARGS*)anyargs;
		GLOBAL::PlayBPM (args.bmp, args.source);
	
		return 0;
	}

}
