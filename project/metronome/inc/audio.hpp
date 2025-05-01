// Created 2025.04.22 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include <blue/error.hpp>
//
#include <AL/al.h>
#include <AL/alc.h>

#define METRONOME_MESSAGE_AUDIO "[AUDIO] "

namespace AL_WRAPPER {

	void CloseDevice (
		INOUT 	void* 			device
	) {
		alcCloseDevice ((ALCdevice*)device);
	}

	void DestroyContext (
		INOUT 	void* 			context
	) {
		alcMakeContextCurrent (0);
		alcDestroyContext ((ALCcontext*)context);
	}

}

namespace AUDIO::LISTENER {

	void Create (
		OUT 	ALCdevice*& 	device,
		OUT 	ALCcontext*& 	context
	) {
		device = alcOpenDevice (nullptr);

		if (device == nullptr) ERROR (METRONOME_MESSAGE_AUDIO "Couldn't create an OpenAL device.");

		context = alcCreateContext (device, nullptr);
		alcMakeContextCurrent (context);

		{ // Future ERROR.
			MEMORY::EXIT::PUSH (MEMORY_EXIT_ADDRESS, AL_WRAPPER::CloseDevice, 1, device);
		}

		if (context == nullptr) ERROR (METRONOME_MESSAGE_AUDIO "Couldn't create an OpenAL context.");

		{ // Future ERROR.
			MEMORY::EXIT::PUSH (MEMORY_EXIT_ADDRESS, AL_WRAPPER::DestroyContext, 1, context);
		}
	}

	void SetPosition (
		IN 		const ALfloat& 	x,
		IN 		const ALfloat& 	y,
		IN 		const ALfloat& 	z
	) {
		alListener3f (AL_POSITION, x, y, z);
	}

	void SetGain (
		IN 		const ALfloat& 	gain
	) {
		alListenerf (AL_GAIN, gain);
	}

	void Destroy (
		IN 		ALCdevice*& 	device,
		IN 		ALCcontext*& 	context
	) {
		AL_WRAPPER::DestroyContext (context);
		AL_WRAPPER::CloseDevice (device);
	}

}

namespace AUDIO::SOURCE {

	void SetBuffer (
		INOUT 	ALuint& 		source,
		IN		const ALuint& 	buffer
	) {
		alSourcei(source, AL_BUFFER, buffer);
		if (alGetError () != AL_NO_ERROR) ERROR (METRONOME_MESSAGE_AUDIO "Couldn't set the OpenAL source buffer.");
	}

	void SetPosition (
		INOUT 	ALuint& 		source,
		IN 		const ALfloat& 	x,
		IN 		const ALfloat& 	y,
		IN 		const ALfloat& 	z
	) {
		alSource3f (source, AL_POSITION, x, y, z);
	}
		
	void SetGain (
		INOUT 	ALuint& 		source,
		IN 		const ALfloat& 	gain
	) {
		alSourcef (source, AL_GAIN, gain);
	}

	void Play (
		IN 		const ALuint& 	source
	) {
		alSourcePlay (source);
		if (alGetError() != AL_NO_ERROR) ERROR (METRONOME_MESSAGE_AUDIO "Couldn't play the OpenAL source.");
	}

}
