#include "Precompiled.hpp"
#include "MazeMusic.hpp"

#define BUFSIZE 256

using namespace std;

namespace AmazingMaze
{

	CMazeMusic::CMazeMusic ()
	{
		m_pSoundFileName	= new char[BUFSIZE];
		m_pSoundFileName	= "";
		m_soundVolume		= 1;
		m_streamType		= true;
		m_soundLoaded		= false;
	}

	CMazeMusic::CMazeMusic (const char* fileName)
	{
		m_pSoundFileName	= new char[BUFSIZE];
		m_pSoundFileName	= fileName;
		m_soundVolume		= 1;
		m_streamType		= true;
		m_soundLoaded		= false;

		loadDevice();
		loadSound();
	}

	CMazeMusic::CMazeMusic (const char* fileName, float volume)
	{
		m_pSoundFileName	= new char[BUFSIZE];
		m_pSoundFileName	= fileName;
		m_soundVolume		= volume;
		m_streamType		= true;
		m_soundLoaded		= false;

		loadDevice();
		loadSound();
	}

	CMazeMusic::CMazeMusic (const char* fileName, float volume, bool stream)
	{
		m_pSoundFileName	= new char[BUFSIZE];
		m_pSoundFileName	= fileName;
		m_soundVolume		= volume;
		m_streamType		= stream;
		m_soundLoaded		= false;

		loadDevice();
		loadSound();
	}

	CMazeMusic::~CMazeMusic ()
	{
		delete[] m_pSoundFileName;
	}

	SoundPtr CMazeMusic::getSoundObject ()
	{
		return m_pSoundObject;
	}

	bool CMazeMusic::isSoundLoaded ()
	{
		return m_soundLoaded;
	}

	float CMazeMusic::setVolume (float volume)
	{
			 if (volume > 1) volume = 1;
		else if (volume < 0) volume = 0;

		m_soundVolume = volume;
		m_pSoundObject->setVolume(m_soundVolume);

		return volume;
	}

	float CMazeMusic::getVolume ()
	{
		return m_pSoundObject->getVolume();
	}

	static audiere::AudioDevicePtr   audiereDevice;  // the music player device
	static bool 	 deviceLoaded   = false;         // check for device load
	void CMazeMusic::loadDevice()
	{
		if (!deviceLoaded || audiereDevice == NULL)
		{
			audiereDevice = audiere::AudioDevicePtr (audiere::OpenDevice());
			deviceLoaded = true;
		}
	}

	void CMazeMusic::loadSound ()
	{
		if (audiereDevice)
			m_pSoundObject = SoundPtr (audiere::OpenSound (audiereDevice, m_pSoundFileName, m_streamType));

		if (m_pSoundObject != NULL)
			m_soundLoaded = true;
	}
} // namespace AmazingMaze