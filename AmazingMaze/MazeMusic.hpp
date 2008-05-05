#pragma once

#include <list>
#include <audiere/audiere.h>

namespace AmazingMaze
{
    // type define for less typing
    typedef audiere::OutputStreamPtr SoundPtr;

    class CMazeMusic
    {
	    public:
		    CMazeMusic();
		    CMazeMusic(const char* fileName);
		    CMazeMusic(const char* fileName, float volume);
		    CMazeMusic(const char* fileName, float volume, bool stream);

		    SoundPtr	getSoundObject();	// returns the sound object
		    void		setVolume(float volume);

	    private:
		    void		loadDevice();
		    void		loadSound();

		    SoundPtr	soundObject;	   // sound object to play
		    float		soundVolume;	  // volume of the sound
		    const char* soundFileName;	 // location of sound file
		    bool		streamType;		// stream it or not
    };
} // namespace AmazingMaze