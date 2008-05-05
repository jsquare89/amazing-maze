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
	}

	CMazeMusicLibrary::CMazeMusicLibrary (const wchar_t* folderName)
	{
		m_volume  = 1;
		m_play    = true;
		m_pFolder.assign(folderName);

		populateLibrary ();
	}

	CMazeMusicLibrary::CMazeMusicLibrary (const wchar_t*  folderName,
											    bool	  play      )
	{
		m_volume  = 1;
		m_play    = play;
		m_pFolder.assign(folderName);

		populateLibrary ();
	}

	CMazeMusicLibrary::~CMazeMusicLibrary ()
	{
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
		char				match  [BUFSIZE] = "";

		fileHandler = FindFirstFileW (m_pFolder.c_str(), &fileData);

		if (fileHandler != INVALID_HANDLE_VALUE)
		{
			wstring	path			= m_pFolder;
			
			wstring	absName			= fileData.cFileName;

			path.replace(path.find(L"*",0), absName.length(), absName);

			CharToOemW (path.c_str(),match);
			CMazeMusic *song	= new CMazeMusic(match);

			if (song->isSoundLoaded())
				m_musicLibrary.push_front(*song);

			while (FindNextFileW (fileHandler, &fileData) != 0)
			{
				absName = fileData.cFileName;
				path	= m_pFolder;

				path.replace (path.find(L"*",0), absName.length(), absName);

				CharToOemW (path.c_str(),match);
				song	= new CMazeMusic(match);

				if (song->isSoundLoaded())
					m_musicLibrary.push_back(*song);
			}
			m_musicIter = m_musicLibrary.begin();
		}
	}

	void CMazeMusicLibrary::playLibrary ()
	{
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
		for (std::list<CMazeMusic>::iterator iter = m_musicLibrary.begin(); iter != m_musicLibrary.end(); iter++)
			iter->setVolume(m_volume);
	}

	void CMazeMusicLibrary::increaseVolume ()
	{
		float vol =	m_musicIter->getVolume() + 0.1;
		if (vol > 1) vol = 1;
		m_volume = vol;

		setLibraryVolume (m_volume);
	}

	void CMazeMusicLibrary::decreaseVolume ()
	{
		float vol =	m_musicIter->getVolume() - 0.1;
		if (vol < 0) vol = 0;
		m_volume = vol;

		setLibraryVolume (m_volume);
	}
} // namespace AmazingMaze