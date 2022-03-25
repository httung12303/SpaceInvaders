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
		}
		file.close();
		std::cout << music.size() << std::endl;
		currentSong = 0;
		Mix_VolumeMusic(100);
	}
	void play() {
		if (Mix_PlayingMusic() == 0 || Mix_PausedMusic() == 1) {
			if (Mix_PlayMusic(music[currentSong], 0) < 0) {
				std::cout << Mix_GetError() << std::endl;
			}
			currentSong++;
			currentSong %= music.size();
		}
	}

private:
	std::vector<Mix_Music*> music;
	int currentSong = 0;
};