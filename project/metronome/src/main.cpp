// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
// BLUELIB
#define CONSOLE_COLOR_ENABLED
#define LOGGER_TIME_FORMAT "%f"
//
#include "audio.hpp"
#include "opus.hpp"

#include <margs/margs.hpp>

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

	{ // BLUE_START
		TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
		LOGINFO ("Application Statred!\n");
	}

	{
		ALCdevice* device;
		ALCcontext* context;

		ALuint buffer;
		ALuint source;

		AUDIO::LISTENER::Create (device, context);

		// Get us a buffer and a source to attach it to.
		alGenBuffers (1, &buffer);
		alGenSources (1, &source);

		AUDIO::LISTENER::SetPosition (0.0f, 0.0f, 0.0f);
		AUDIO::LISTENER::SetGain (1.0f);

		OPUS::Load (buffer, "res\\1.opus");

		AUDIO::SOURCE::SetBuffer (source, buffer);
		AUDIO::SOURCE::SetPosition (source, 0.0f, 0.0f, 0.0f);
		AUDIO::SOURCE::SetGain (source, 1.0f);

		AUDIO::SOURCE::Play (source);

		{ // Keep playing until we're finished.
			ALint sourceState;
			do {
				alGetSourcei (source, AL_SOURCE_STATE, &sourceState);
			} while (sourceState != AL_STOPPED);
		}

		alDeleteSources (1, &source);
		alDeleteBuffers (1, &buffer);

		AUDIO::LISTENER::Destroy (device, context);
	}
	

	{ // BLUE_EXIT
		LOGMEMORY ();
		LOGINFO ("Finalized Execution\n");
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
	}

	return 0;
}
