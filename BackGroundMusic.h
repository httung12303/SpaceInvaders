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
		/*music.push_back(Mix_LoadMUS("music/Undertale OST- 055 - Can You Really Call This A Hotel I Didn't Receive A Mint On My Pillow (audio-extractor.net)_2.wav"));
		music.push_back(Mix_LoadMUS("music/Yu-Gi-Oh Dark Magician Theme Japanese version (audio-extractor.net)_2.wav"));
		music.push_back(Mix_LoadMUS("music/Marvel vs.Capcom 2 OST - Clock Tower Stage(audio - extractor.net).wav"));*/
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