// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
// HACK. Ensure the following is always included first.
#include "bluelib.hpp"
//
#include "arguments.hpp"
#include "threads.hpp"
#include "global.hpp"
#include <blue/wave.hpp>


s32 main (s32 argumentsCount, c8** arguments) {

	ARGUMENTS::MAINARGS mainArgs {
		nullptr,
		METRONOME_ARGUMENT_DEFAULT_BPM,
		METRONOME_ARGUMENT_DEFAULT_WAIT,
		METRONOME_ARGUMENT_DEFAULT_VOLUME,
        METRONOME_ARGUMENT_DEFAULT_PATTERN,
	};


	ALCdevice* device;
	ALCcontext* context;
	ALuint buffer;
	ALuint source;


    { // BLUE START
        TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
        DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
        LOGINFO ("Application Statred!\n");
    }


	ARGUMENTS::Get (argumentsCount, arguments, mainArgs);


	const auto& filename 	= mainArgs.filename;
	const auto& bpm 		= mainArgs.bpm;
	const auto& wait 		= mainArgs.wait;
	const auto& volume 		= mainArgs.volume;
    auto& pattern 	        = mainArgs.pattern;


	LOGINFO (
		"filename: %s, bpm: %d, wait: %d, volume: %d, pattern: %d\n",
		filename, bpm, wait, volume, pattern
	);

    {
        // Offset
        // 1 means every 1byte which tlanslates to pattern iterator being always equal to 0.
        --pattern;
    }


	{ // OPENAL INIT
		AUDIO::LISTENER::Create (device, context);

		alGenBuffers (1, &buffer);
		alGenSources (1, &source);

		OPUS::Load (buffer, filename);

		{ // Release filepath.
			MEMORY::EXIT::POP ();
			FREE (1, filename);
		}

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
		THREADS::YIELDARGS args { wait, bpm, pattern, source };

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
