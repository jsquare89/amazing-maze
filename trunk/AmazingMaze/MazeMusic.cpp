#include "Precompiled.hpp"
#include "MazeMusic.hpp"

namespace AmazingMaze
{
    CMazeMusic::CMazeMusic()
    {
	    soundFileName	= "";
	    soundVolume		= 0;
	    streamType		= true;
    }

    CMazeMusic::CMazeMusic(const char* fileName)
    {
	    soundFileName	= fileName;
	    soundVolume		= .5;
	    streamType		= true;

	    loadDevice();
	    loadSound();
    }

    CMazeMusic::CMazeMusic(const char* fileName, float volume)
    {
	    soundFileName	= fileName;
	    soundVolume		= volume;
	    streamType		= true;

	    loadDevice();
	    loadSound();
    }

    CMazeMusic::CMazeMusic(const char* fileName, float volume, bool stream)
    {
	    soundFileName	= fileName;
	    soundVolume		= volume;
	    streamType		= stream;

	    loadDevice();
	    loadSound();
    }

    SoundPtr CMazeMusic::getSoundObject ()
    {
	    return soundObject;
    }

    void CMazeMusic::setVolume (float volume)
    {
		     if (volume > 1) volume = 1;
	    else if (volume < 0) volume = 0;

	    soundVolume = volume;
	    soundObject ->setVolume(soundVolume);
    }

    static audiere::AudioDevicePtr  audiereDevice;  // the music player device
    static bool	deviceLoaded		= false;       // check for device load
    void CMazeMusic::loadDevice()
    {
	    if (!deviceLoaded)
	    {
		    audiereDevice = audiere::AudioDevicePtr (audiere::OpenDevice());
		    deviceLoaded = true;
	    }
    }

    void CMazeMusic::loadSound()
    {
	    if (audiereDevice)
		    soundObject = SoundPtr (audiere::OpenSound (audiereDevice, soundFileName, streamType));
    }
} // namespace 3DMaze