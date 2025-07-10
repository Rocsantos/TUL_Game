#include "Resource.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resource::imageTable;
std::unordered_map<std::string, Mix_Music*> Resource::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resource::soundTable;

SDL_Texture* Resource::GetImage(std::string file)
{
	auto it_image = imageTable.find(file);
	if (it_image == imageTable.end())
	{
		SDL_Texture* img = IMG_LoadTexture(Game::GetRenderer(), file.c_str());
		if (img == nullptr)
		{
			Game::CrashWithError("Erro ao carregar imagem: " + file, IMG_GetError());
		}
		imageTable[file] = img;
	}
	return imageTable[file];
}

void Resource::ClearImages()
{
	for (auto& img : imageTable)
	{
		SDL_DestroyTexture(img.second);
	}
	imageTable.clear();
}

Mix_Music* Resource::GetMusic(std::string file)
{
	auto it_music = musicTable.find(file);
	if (it_music == musicTable.end())
	{
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if (music == nullptr)
		{
			Game::CrashWithError("Erro ao carregar música: " + file, Mix_GetError());
		}
		musicTable[file] = music;
	}
	return musicTable[file];
}

void Resource::ClearMusics()
{
	for (auto& music : musicTable)
	{
		Mix_FreeMusic(music.second);
	}
	musicTable.clear();
}

Mix_Chunk* Resource::GetSound(std::string file)
{
	auto it_sound = soundTable.find(file);
	if (it_sound == soundTable.end())
	{
		Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
		if (sound == nullptr)
		{
			Game::CrashWithError("Erro ao carregar som: " + file, Mix_GetError());
		}
		soundTable[file] = sound;
	}
	return soundTable[file];
}

void Resource::ClearSounds()
{
	for (auto& sound : soundTable)
	{
		Mix_FreeChunk(sound.second);
	}
	soundTable.clear();
}
