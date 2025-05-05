// Created 2025.05.05 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
//
#include <blue/error.hpp>
//
#include <string>
//
// WARN `margs` uses the following names. We have to undefine them.
#undef max
#undef min
#undef near
#undef far
#undef str
//
#include <margs/margs.hpp>
//
#include "resources.hpp"


#define METRONOME_ARGUMENT_NAME_FILENAME 			"filename"
#define METRONOME_ARGUMENT_NAME_BPM 				"bpm"
#define METRONOME_ARGUMENT_NAME_WAIT 				"wait"
#define METRONOME_ARGUMENT_NAME_VOLUME 				"volume"

#define METRONOME_ARGUMENT_SHORT_FILENAME 			'f'
#define METRONOME_ARGUMENT_SHORT_BPM 				'b'
#define METRONOME_ARGUMENT_SHORT_WAIT 				'w'
#define METRONOME_ARGUMENT_SHORT_VOLUME 			'v'

#define METRONOME_ARGUMENT_DESCRIPTION_FILENAME 	"desc..."
#define METRONOME_ARGUMENT_DESCRIPTION_BPM 			"desc..."
#define METRONOME_ARGUMENT_DESCRIPTION_WAIT 		"desc..."
#define METRONOME_ARGUMENT_DESCRIPTION_VOLUME 		"desc..."

#define METRONOME_ARGUMENT_DEFAULT_FILENAME			METRONOME_TRACK_01_
#define METRONOME_ARGUMENT_DEFAULT_BPM 				120
#define METRONOME_ARGUMENT_DEFAULT_WAIT 			1
#define METRONOME_ARGUMENT_DEFAULT_VOLUME 			75



namespace ARGUMENTS::ARGUMENT {

	enum CONDITION: u8 {
		CONDITION_FILENAME 	= 1,
		CONDITION_BPM 		= 2,
		CONDITION_WAIT 		= 4,
		CONDITION_VOLUME 	= 8,
	};

	void GetFilename (
		IN 		const margs::args_map& map,
		OUT 	c8*& value
	) {
		const auto& string = map.get_value (METRONOME_ARGUMENT_NAME_FILENAME).as<std::string> ();

		// MEMORY ALLOCATION ! -> margs::args_map will deallocate at some point.
		const auto& length = string.length () + 1; // + null-term
		const auto&& buffer = string.c_str ();

		ALLOCATE (c8, value, length * sizeof (c8));
		std::memcpy (value, buffer, length * sizeof (c8));
		MEMORY::EXIT::PUSH (FREE, 1, value);

		// PARSING
		// TODO
		//
	}

	void GetBPM (
		IN 		const margs::args_map& map,
		OUT 	u16& value
	) {
		value = map.get_value (METRONOME_ARGUMENT_NAME_BPM).as<u16> ();

		// PARSING
		if (value > 440) 	{ LOGWARN ("'BPM' value exceeded MAX!\n"); value = 440; return; }
		if (value < 40) 	{ LOGWARN ("'BPM' value exceeded MIN!\n"); value = 40;  }
	}

	void GetWait (
		IN 		const margs::args_map& map,
		OUT 	u16& value
	) {
		value = map.get_value (METRONOME_ARGUMENT_NAME_WAIT).as<u16> ();

		// PARSING
		if (value > 10) 	{ LOGWARN ("'Wait' value exceeded MAX!\n"); value = 10; }
	}

	void GetVolume (
		IN 		const margs::args_map& map,
		OUT 	u16& value
	) {
		value = map.get_value (METRONOME_ARGUMENT_NAME_VOLUME).as<u16> ();

		// PARSING
		if (value > 100) 	{ LOGWARN ("'Volume' value exceeded MAX!\n"); value = 100; return; }
		if (value < 1) 		{ LOGWARN ("'Volume' value exceeded MIN!\n"); value = 1;  }
	}
	
}


namespace ARGUMENTS {

	struct MAINARGS {
		c8* 	filename; 
		u16 	bpm;
		u16 	wait;
		u16 	volume;
	};

	void Get (
		IN		const s32& 	argumentsCount, 
		IN		c8**		arguments,			// TODO
		OUT		MAINARGS& 	args
	) {

		auto& filename 	= args.filename;
		auto& bpm 		= args.bpm;
		auto& wait 		= args.wait;
		auto& volume 	= args.volume;

		using namespace margs;
		using namespace mstd;

		args_analizer analizer = args_analizer (

			help_data { .description = "Args analizer sample description" },

			args_builder::makeValue (

				METRONOME_ARGUMENT_NAME_FILENAME, METRONOME_ARGUMENT_SHORT_FILENAME, 1,  
				help_data { .description = METRONOME_ARGUMENT_DESCRIPTION_FILENAME}

			), 

			args_builder::makeValue (

				METRONOME_ARGUMENT_NAME_BPM, METRONOME_ARGUMENT_SHORT_BPM, 1,  
				help_data { .description = METRONOME_ARGUMENT_DESCRIPTION_BPM}

			), 

			args_builder::makeValue (

				METRONOME_ARGUMENT_NAME_WAIT, METRONOME_ARGUMENT_SHORT_WAIT, 1,  
				help_data { .description = METRONOME_ARGUMENT_DESCRIPTION_WAIT}

			), 

			args_builder::makeValue (

				METRONOME_ARGUMENT_NAME_VOLUME, METRONOME_ARGUMENT_SHORT_VOLUME, 1,  
				help_data { .description = METRONOME_ARGUMENT_DESCRIPTION_VOLUME}

			)

		);

		args_map values;
		std::string value;

		//  ABOUT
		// Get program args.
		//

		try { values = analizer.analize (argumentsCount, arguments);
		} catch (const args_exception& e) { ERROR ("Invalid argument passed, code: %s\n", e.what ()) }


		//u8 condition = 0;
		//condition += (values.contains_value (METRONOME_ARGUMENT_NAME_FILENAME) 	<< 0); // 1
		//condition += (values.contains_value (METRONOME_ARGUMENT_NAME_BPM) 		<< 1); // 2
		//condition += (values.contains_value (METRONOME_ARGUMENT_NAME_WAIT) 		<< 2); // 4
		//condition += (values.contains_value (METRONOME_ARGUMENT_NAME_VOLUME) 	<< 3); // 8
		//
		//// TODO
		//// 1. speed-test if fails do it normally.
		//// 2. Preprocessor use ?
		//switch (condition) {
		//
		//	case ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_BPM: {
		//		ARGUMENT::GetBPM (values, bpm);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_BPM + ARGUMENT::CONDITION_FILENAME: {	
		//		ARGUMENT::GetBPM (values, bpm);
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_WAIT: {
		//		ARGUMENT::GetWait (values, wait); 
		//	} break;
		//
		//	case ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_FILENAME: {	
		//		ARGUMENT::GetWait (values, wait); 
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_BPM: {
		//		ARGUMENT::GetWait (values, wait);  
		//		ARGUMENT::GetBPM (values, bpm);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_BPM + ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetWait (values, wait);  
		//		ARGUMENT::GetBPM (values, bpm);
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME: {
		//		ARGUMENT::GetVolume (values, volume); 
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_BPM: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetBPM (values, bpm);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_BPM + ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetBPM (values, bpm);
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_WAIT: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetWait (values, wait); 
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetWait (values, wait); 
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_BPM: {
		//		ARGUMENT::GetVolume (values, volume); 
		//		ARGUMENT::GetWait (values, wait); 
		//		ARGUMENT::GetBPM (values, bpm);
		//	} break;
		//
		//	case ARGUMENT::CONDITION_VOLUME + ARGUMENT::CONDITION_WAIT + ARGUMENT::CONDITION_BPM + ARGUMENT::CONDITION_FILENAME: {
		//		ARGUMENT::GetVolume (values, volume);  
		//		ARGUMENT::GetWait (values, wait); 
		//		ARGUMENT::GetBPM (values, bpm);
		//		ARGUMENT::GetFilename (values, filename);
		//	} break;
		//
		//}

		if (values.contains_value (METRONOME_ARGUMENT_NAME_FILENAME)) {
			ARGUMENT::GetFilename (values, filename);
		} else {

			// FILENAME -> SET DEFAULT
			const auto& length = sizeof (METRONOME_ARGUMENT_DEFAULT_FILENAME); // + null-term
			ALLOCATE (c8, filename, length * sizeof (c8));
			std::memcpy (filename, METRONOME_ARGUMENT_DEFAULT_FILENAME, length * sizeof (c8));
			MEMORY::EXIT::PUSH (FREE, 1, filename);

		}

		if (values.contains_value (METRONOME_ARGUMENT_NAME_BPM)) {
			ARGUMENT::GetBPM (values, bpm);
		}

		if (values.contains_value (METRONOME_ARGUMENT_NAME_WAIT)) {
			ARGUMENT::GetWait (values, wait);
		}

		if (values.contains_value (METRONOME_ARGUMENT_NAME_VOLUME)) {
			ARGUMENT::GetVolume (values, volume);
		}

		

	}


}
