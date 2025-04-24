// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include <blue/error.hpp>
//
#include <opusfile/opusfile.h>
//
#include "audio.hpp"

#define METRONOME_MESSAGE_OPUS "[OPUS] "

namespace OPUS {

	// Followed an example:
	// Written by David Gow <david@ingeniumdigital.com>
	// https://davidgow.net/files/opusal.cpp

	// Convert an opus error code to a string.
	const c8* opus_error_to_string (
		IN		const s32& 				error
	) {
		switch (error) {
			case OP_FALSE: 			return "OP_FALSE"			": A request did not succeed.";
			case OP_HOLE: 			return "OP_HOLE"			": There was a hole in the page sequence numbers.";
			case OP_EREAD: 			return "OP_EREAD"			": An underlying read, seek or tell operation failed.";
			case OP_EFAULT: 		return "OP_EFAULT"			": A NULL pointer was passed where none was expected, or an internal library error was encountered.";
			case OP_EIMPL: 			return "OP_EIMPL"			": The stream used a feature which is not implemented.";
			case OP_EINVAL: 		return "OP_EINVAL"			": One or more parameters to a function were invalid.";
			case OP_ENOTFORMAT: 	return "OP_ENOTFORMAT"		": This is not a valid Ogg Opus stream.";
			case OP_EBADHEADER: 	return "OP_EBADHEADER"		": A required header packet was not properly formatted.";
			case OP_EVERSION: 		return "OP_EVERSION"		": The ID header contained an unrecognised version number.";
			case OP_EBADPACKET: 	return "OP_EBADPACKET"		": An audio packet failed to decode properly.";
			case OP_EBADLINK: 		return "OP_EBADLINK"		": We failed to find data we had seen before or the stream was sufficiently corrupt that seeking is impossible.";
			case OP_ENOSEEK: 		return "OP_ENOSEEK"			": An operation that requires seeking was requested on an unseekable stream.";
			case OP_EBADTIMESTAMP: 	return "OP_EBADTIMESTAMP"	": The first or last granule position of a link failed basic validity checks.";
			default: 				return 						"Unknown error.";
		}
	}


	// Load an ogg opus file into the given AL buffer
	void Load (
		INOUT 	const ALuint& 			buffer, 
		IN 		const c8* const& 		filename
	) {

		const u16 SAMPLING_RATE = 48000;

		ALenum format;
		int16_t* buf;
		s32 channels;
		s32 pcmSize;

		int totalSamplesRead = 0;
		int samplesRead = 0;
		s32 error = 0;

		// Open the file.
		OggOpusFile* file = op_open_file (filename, &error);

		if (error) ERROR (
			METRONOME_MESSAGE_OPUS "Failed to open file %s (%d: %s)", 
			filename, error, opus_error_to_string (error)
		);

		// Get the number of channels in the current link.
		channels = op_channel_count (file, -1);

		// Get the number of samples (per channel) in the current link.
		pcmSize = op_pcm_total (file, -1);

		LOGINFO (
			METRONOME_MESSAGE_OPUS 
			"%s: %d channels, %d samples (%d seconds)\n", 
			filename, channels, pcmSize, pcmSize / SAMPLING_RATE
		);

		// We only support stereo and mono, set the openAL format based on channels.
		// opus always uses signed 16-bit integers, unless the _float functions are called.
		
		switch (channels) {
			case 1: format = AL_FORMAT_MONO16; 		break;
			case 2: format = AL_FORMAT_STEREO16; 	break;
			default: ERROR (METRONOME_MESSAGE_OPUS "File contained more channels than we support (%d)", channels);
		}

		// Allocate a buffer big enough to store the entire uncompressed file.
		buf = new int16_t[pcmSize * channels];

		// Keep reading samples until we have them all.
		while (totalSamplesRead < pcmSize) {

			// 'op_read' returns number of samples read (per channel), and accepts 
			//  a number of samples which fit in the buffer, not number of bytes.
			samplesRead = op_read (file, buf + totalSamplesRead * channels, pcmSize * channels, 0);
			
			if (samplesRead < 0) ERROR (
				METRONOME_MESSAGE_OPUS "Couldn't decode at offset %d: Error %d (%s)", 
				totalSamplesRead, samplesRead, opus_error_to_string (samplesRead)
			);

			totalSamplesRead += samplesRead;

			LOGINFO ("Read %d (total %d) of %d samples (per channel)\n", samplesRead, totalSamplesRead, pcmSize);
		}

		// Close the opus file.
		op_free (file);

		// Send it to OpenAL (which takes bytes).
		alBufferData (buffer, format, buf, totalSamplesRead * channels * 2, SAMPLING_RATE);

		if (alGetError() == AL_NO_ERROR) { LOGINFO (METRONOME_MESSAGE_OPUS "Buffered data!\n"); }
		else { ERROR (METRONOME_MESSAGE_OPUS "Failed to buffer data!"); }
	}
}
