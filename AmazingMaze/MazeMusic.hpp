#pragma once

#include <audiere/audiere.h>

namespace AmazingMaze
{
    // type define for less typing
    typedef audiere::OutputStreamPtr SoundPtr;

    class CMazeMusic
    {
		public:
			CMazeMusic ();
			~CMazeMusic();
			CMazeMusic (const char* fileName);
			CMazeMusic (const char* fileName, float volume);
			CMazeMusic (const char* fileName, float volume, bool stream);

			SoundPtr	getSoundObject();			// returns the sound object
			float		setVolume(float volume);   // set the volume
			float		getVolume();			  // get the volume
			bool		isSoundLoaded();  	     // return m_soundLoaded

		private:
			void		loadDevice();
			void		loadSound();

			SoundPtr	m_pSoundObject;	     // sound object to play
			float		m_soundVolume;	    // volume of the sound
			const char* m_pSoundFileName;  // location of sound file
			bool		m_streamType;	  // stream it or not
			bool		m_soundLoaded;   // did it load?
    };
} // namespace AmazingMaze