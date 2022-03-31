#pragma once
#include "BaseObject.h"
#include "BasicFunction.h"
#include <string>

class BackGroundMusic {
public:
	BackGroundMusic() {
		std::ifstream file("music/music.txt");
		std::string song;
		if (!file.is_open()) {
			std::cout << "music.txt" << std::endl;
			return;
		}
		while (std::getline(file, song)) {
			if(file)
				music.push_back(Mix_LoadMUS(song.c_str()));
			//std::cout << song << std::endl;
		}
		file.close();
		std::cout << music.size() << std::endl;
		currentSong = 0;
		Mix_VolumeMusic(100);
	}
	void play(const bool& musicPlaying) {
		if (musicPlaying) {
			if (Mix_PlayingMusic() == 0) {
				if (Mix_PlayMusic(music[currentSong], 0) < 0) {
					std::cout << 1 << Mix_GetError() << std::endl;
				}
				currentSong++;
				currentSong %= music.size();
			}
			if (Mix_PausedMusic()) {
				Mix_ResumeMusic();
			}
		}
		else {
			if (!Mix_PausedMusic()) {
				Mix_PauseMusic();
			}
		}
	}

private:
	std::vector<Mix_Music*> music;
	int currentSong = 0;
};