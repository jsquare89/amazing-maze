#pragma once

#include "MazeMusic.hpp"
#include <windows.h>
#include <string>
#include <list>

namespace AmazingMaze
{
	class CMazeMusicLibrary
	{
		public:
			CMazeMusicLibrary    ();
			~CMazeMusicLibrary   ();
			CMazeMusicLibrary    (const wchar_t*  folderName);
			CMazeMusicLibrary    (const wchar_t*  folderName,
										bool	  play      );

			std::list<CMazeMusic>::iterator getMusicIter();

			void populateLibrary  ();
			void playLibrary      ();
			void stopCurrentSong  ();
			void playCurrentSong  ();
			void playNextSong     ();
			void playPrevSong     ();
			void increaseVolume   ();
			void decreaseVolume   ();
			void setLibraryVolume (float volume);

		private:
			std::list<CMazeMusic>			m_musicLibrary;
			std::list<CMazeMusic>::iterator	m_musicIter;
			std::wstring					m_pFolder;
			float							m_volume;
			bool							m_play;
	};
} // namespace AmazingMaze