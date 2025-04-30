// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
// BLUELIB
#define CONSOLE_COLOR_ENABLED
#define LOGGER_TIME_FORMAT "%f"
//
#include "resources.hpp"
#include "audio.hpp"
#include "opus.hpp"
//
#include <threads.h>
//
// ERRORS at \mstd\string.hpp
#undef max
#undef min
#undef near
#undef far
#undef str
#include <margs/margs.hpp>
//

//#include <iomanip>
//#include <algorithm>
//void ExampleMARGS () {
//    using namespace margs;
//
//	args_analizer args = args_analizer (
//
//        help_data { "Args analizer sample description" },
//
//        args_builder::makeValue (
//			"value", 'v', 1,
//			help_data {
//				"sample value description"
//			}
//        ), 
//
//        args_builder::makeFlag (
//			"flag", 'f',  
//            help_data { 
//				"sample flag description"
//			}
//        )
//
//        //margs::args_builder::makeGroup (
//		//	"group",
//		//
//        //    margs::help_data { 
//		//		"sample group description"
//		//	},
//		//
//        //    margs::args_builder::makeFlag (
//		//		"group-flag", 'f',
//        //        margs::help_data { 
//		//			"sample group flag description"
//		//		}
//        //    )
//		//
//        //)
//    );
//
//	// Get program args
//    args_map arg_values;
//
//    try {
//        arg_values = args.analize (argumentsCount, arguments);
//    } catch (const args_exception& e) {
//        ERROR ("%s\n", e.what ());
//        return 1;
//    }
//
//	// Get Value Arg 
//    std::string value;
//    if (arg_values.contains_value ("value")) { 
//        value = arg_values.get_value ("value").as<std::string> (); 
//    }
//
//    //if (arg_values.contains_flag("group::group-flag")) {
//    //    cout << "Group flag" << endl;
//    //}
//
//    //std::string sample ("Sample! Sample! Sample!");
//	//std::string other = mstd::trim (sample);
//
//	
//
//	//LOGINFO ("%s\n", other.c_str ());
//}


u8 isRunning = true;

void PlayBPM (
	IN 		const u16 bpm,
	IN		const ALuint source
) {
	const r32 spb = 60.0 / bpm; // Seconds per beat

	// TODO
	// Due to underneeth implementation this might be quite slow.
	// TEST if it's actually fast or if it can be written as faster. 
	TIMESTAMP::Timestamp timestampCurrent = TIMESTAMP::GetCurrent ();
	while (isRunning) {

		r32 timePassed = TIMESTAMP::GetElapsed (timestampCurrent);

		if (timePassed >= spb) {
			timestampCurrent = TIMESTAMP::GetCurrent ();
			//LOGINFO ("time: %f, spb: %f\n", timePassed, spb);
			AUDIO::SOURCE::Play (source);
		}

	}
	
	{ // Wait for source to stop playing. 
		ALint sourceState;
		do {
			alGetSourcei (source, AL_SOURCE_STATE, &sourceState);
		} while (sourceState != AL_STOPPED);
	}
}


struct OTHREADARGS {
	u16 bmp;
	ALuint source;
};


s32 ITHREAD (
	INOUT 	void* arguments
) {

	// TODO
	// This should error-out threadsafe way.
	DEBUG (DEBUG_FLAG_LOGGING) { 
		if (arguments != nullptr) LOGWARN ("Arguments passed to 'ITHREAD'!");
	}

	c8 buffer[128];
	
	while (isRunning) {
	
		// TODO
		// Right now it waits for new-line. That's not needed. 
		if (fgets (buffer, sizeof (buffer), stdin)) {
			printf("You entered: %s", buffer);
			isRunning = false;
		}
	
	}

    return 0;
}


s32 OTHREAD (
	INOUT 	void* arguments
) {

	// TODO
	// This should error-out threadsafe way.
	DEBUG (DEBUG_FLAG_LOGGING) {
		if (arguments == nullptr) LOGWARN ("No arguments passed to 'OTHREAD'!");
	}

	const auto args = *(OTHREADARGS*)arguments;
	PlayBPM (args.bmp, args.source);

    return 0;
}

s32 main (s32 argumentsCount, c8** arguments) {

	// TODO
	// arguments read.
	// START [IN PARAMS]
	const c8* const& fileName = METRONOME_TRACK_01_; 
	const u16 bmp = 120;
	// END [IN PARAMS]


	// START [AUDIO GLOBAL]
	ALCdevice* device;
	ALCcontext* context;
	ALuint buffer;
	ALuint source;
	// END [AUDIO GLOBAL]


	{ // BLUE START
		TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
		LOGINFO ("Application Statred!\n");
	}


	{ // OPENAL INIT
		AUDIO::LISTENER::Create (device, context);

		alGenBuffers (1, &buffer);
		alGenSources (1, &source);

		AUDIO::LISTENER::SetPosition (0.0f, 0.0f, 0.0f);
		AUDIO::LISTENER::SetGain (1.0f);

		OPUS::Load (buffer, fileName);

		AUDIO::SOURCE::SetBuffer (source, buffer);
		AUDIO::SOURCE::SetPosition (source, 0.0f, 0.0f, 0.0f);
		AUDIO::SOURCE::SetGain (source, 1.0f);
	}


	{ // THREADING
		OTHREADARGS args { bmp, source };

		thrd_t iThread, oThread;
		thrd_create (&oThread, OTHREAD, &args);
		thrd_create (&iThread, ITHREAD, NULL);

   		thrd_join (iThread, NULL);
		thrd_join (oThread, NULL);
	}


	{ // OPENAL EXIT
		alDeleteSources (1, &source);
		alDeleteBuffers (1, &buffer);

		AUDIO::LISTENER::Destroy (device, context);
	}
	

	{ // BLUE EXIT
		LOGMEMORY ();
		LOGINFO ("Finalized Execution\n");
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
	}

	return 0;
}
