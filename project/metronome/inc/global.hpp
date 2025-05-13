// Created 2025.05.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
//
#include "resources.hpp"
#include "audio.hpp"
#include "opus.hpp"


namespace GLOBAL {

	u8 isStopPlayback = true;

}


namespace GLOBAL {

	void PlayBPM (
		IN 		const u16 bpm,
        IN 		const u8 pattern,
		IN		const ALuint source
	) {
		const r32 spb = 60.0 / bpm; // Seconds per beat
        u8 patternIterator = 0;

		// TODO
		// Due to underneeth implementation this might be quite slow.
		// TEST if it's actually fast or if it can be written as faster. 
		TIMESTAMP::Timestamp timestampCurrent = TIMESTAMP::GetCurrent ();
		while (isStopPlayback) {

			r32 timePassed = TIMESTAMP::GetElapsed (timestampCurrent);

			if (timePassed >= spb) {
				timestampCurrent = TIMESTAMP::GetCurrent ();
				//LOGINFO ("time: %f, spb: %f\n", timePassed, spb);

                // Every pattern note is louder.
                if (patternIterator < pattern) {
                    AUDIO::SOURCE::SetGain (source, 0.25f);
                    ++patternIterator;
                } else {
                    AUDIO::SOURCE::SetGain (source, 1.0f);
                    patternIterator = 0;
                }
                
				AUDIO::SOURCE::Play (source);
			}

		}

		{ // Wait for source to stop playing. 
			ALint sourceState;
			do {
				alGetSourcei (source, AL_SOURCE_STATE, &sourceState);
			} while (sourceState == AL_PLAYING);
		}
	}

}
