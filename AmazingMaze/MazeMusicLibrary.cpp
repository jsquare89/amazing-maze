#include "Precompiled.hpp"
#include "MazeMusicLibrary.hpp"
#include "MazeMusic.hpp"
#include <windows.h>
#include <string>
#include <list>

using namespace std;

namespace AmazingMaze
{
	CMazeMusicLibrary::CMazeMusicLibrary ()
	{
		m_volume  = 1;
		m_play    = false;
		m_pFolder = new char[BUFSIZE];
	}

	CMazeMusicLibrary::CMazeMusicLibrary (const char* folderName)
	{
		m_volume  = 1;
		m_play    = true;
		m_pFolder = new char[BUFSIZE];

		strncpy_s (m_pFolder,BUFSIZE,folderName,BUFSIZE);

		populateLibrary ();
	}

	CMazeMusicLibrary::CMazeMusicLibrary (const char*  folderName,
											   bool  play      )
	{
		m_volume  = 1;
		m_play    = play;
		m_pFolder = new char[BUFSIZE];

		strncpy_s (m_pFolder,BUFSIZE,folderName,BUFSIZE);

		populateLibrary ();
	}

	CMazeMusicLibrary::~CMazeMusicLibrary ()
	{
		delete[] m_pFolder;
	}

	std::list<CMazeMusic>::iterator CMazeMusicLibrary::getMusicIter ()
	{
		return m_musicIter;
	}

	void CMazeMusicLibrary::populateLibrary ()
	{
		WIN32_FIND_DATAW	fileData;
		HANDLE				fileHandler;
		TCHAR				absPath[BUFSIZE] = TEXT("");
		WCHAR				match  [BUFSIZE] = L"";

		OemToCharW (m_pFolder,match);

		fileHandler = FindFirstFile ((LPCSTR) match, (LPWIN32_FIND_DATAA) &fileData);

		if (fileHandler != INVALID_HANDLE_VALUE)
		{
			string	*path			= new string(m_pFolder);
			char	fname[BUFSIZE]	= {0};

			CharToOemW (fileData.cFileName,fname);
			string	absName((string)fname);

			path->replace(path->find("*",0), absName.length(), absName);

			CMazeMusic *song	= new CMazeMusic(path->c_str());

			if (song->isSoundLoaded())
				m_musicLibrary.push_front(*song);

			while (FindNextFile(fileHandler,(LPWIN32_FIND_DATAA) &fileData) != 0)
			{
				CharToOemW (fileData.cFileName,fname);
				absName = (string) fname;
				path	= new string(m_pFolder);

				path->replace (path->find("*",0), absName.length(), absName);

				song	= new CMazeMusic(path->c_str());

				if (song->isSoundLoaded())
					m_musicLibrary.push_back(*song);
			}
			m_musicIter = m_musicLibrary.begin();
		}
	}

	void CMazeMusicLibrary::playLibrary ()
	{
		if ( abs((100*m_volume) - (100*(m_musicIter->getVolume()))) != 0)
			m_musicIter->setVolume(m_volume);

		if (!m_musicIter->getSoundObject()->isPlaying() && m_play)
		{
			m_musicIter++;
			if (m_musicIter != m_musicLibrary.end())
				m_musicIter->getSoundObject()->play();
			else
			{
				m_musicIter = m_musicLibrary.begin();
				m_musicIter->getSoundObject()->play();
			}
		}
	}

	void CMazeMusicLibrary::stopCurrentSong ()
	{
		m_musicIter->getSoundObject()->stop();
		m_play = false;
	}

	void CMazeMusicLibrary::playCurrentSong ()
	{
		m_musicIter->getSoundObject()->play();
		m_play = true;
	}

	void CMazeMusicLibrary::setLibraryVolume (float volume)
	{
		m_volume = volume;
	}

	void CMazeMusicLibrary::increaseVolume ()
	{
		float vol =	m_musicIter->getVolume() + 0.1;
		if (vol > 1) vol = 1;
		m_volume = vol;
	}

	void CMazeMusicLibrary::decreaseVolume ()
	{
		float vol =	m_musicIter->getVolume() - 0.1;
		if (vol < 0) vol = 0;
		m_volume = vol;
	}
} // namespace AmazingMaze