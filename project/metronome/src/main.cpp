// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
// HACK. Ensure the following is always included first.
#include "bluelib.hpp"
//
#include "threads.hpp"
#include "global.hpp"

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

s32 main (s32 argumentsCount, c8** arguments) {

	// TODO
	// arguments read.
	// START [IN PARAMS]
	const c8* const& fileName = METRONOME_TRACK_01_; 
	const u16 bmp = 120;
	const u16 wait = 1;
	const u16 volume = 75;
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

		OPUS::Load (buffer, fileName);

		AUDIO::LISTENER::SetPosition (0.0f, 0.0f, 0.0f);
		AUDIO::LISTENER::SetGain (volume / 100.0f);

		AUDIO::SOURCE::SetBuffer (source, buffer);
		AUDIO::SOURCE::SetPosition (source, 0.0f, 0.0f, 0.0f);
		AUDIO::SOURCE::SetGain (source, 1.0f);
	}

	{ // Future ERROR.
		MEMORY::EXIT::PUSH (AL_WRAPPER::DestroyBuffers, 1, &buffer);
		MEMORY::EXIT::PUSH (AL_WRAPPER::DestroySources, 1, &source);
	}


	{ // THREADING
		THREADS::YIELDARGS args { wait, bmp, source };

		thrd_t iThread, oThread;
		thrd_create (&oThread, THREADS::YIELD, &args);
		thrd_create (&iThread, THREADS::INPUT, NULL);

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
