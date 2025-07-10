#include "Music.h"
#include "Game.h"
#include "Resource.h"

/******************************************************************************
 * 
 * Music Class Definiton
 * 
*******************************************************************************/

Music::Music(): music(nullptr) {}

Music::Music(std::string file) : music(nullptr)
{
    Open(file);
}

Music::~Music()
{
    Mix_FreeMusic(music);
}

bool Music::IsOpen() const
{
    return (music != nullptr);
}

void Music::Open(std::string file)
{
    music = Resource::GetMusic(file);
}

void Music::Play(int times)
{
    if(not IsOpen())
    {
        Game::CrashWithError("Música não definida", Mix_GetError());
    }
    if(Mix_PlayMusic(music, times) == -1)
    {
        Game::CrashWithError("Erro ao tocar música", Mix_GetError());
    }
}

void Music::Stop(int msToStop=1500)
{
    Mix_FadeOutMusic(msToStop);
}

/******************************************************************************
 * 
 * Sound Class Definiton
 * 
*******************************************************************************/

Sound::Sound(): chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file): chunk(nullptr), channel(-1)
{
    Open(file);
}

Sound::~Sound() {}

void Sound::Play(int times)
{
    if(not IsOpen())
    {
        Game::CrashWithError("Tentativa de tocar um som não carregado!", Mix_GetError());
    }
    channel = Mix_PlayChannel(-1, chunk, times);
    if(channel == -1)
    {
        Game::CrashWithError("Erro ao tocar som", Mix_GetError());
    }
}
void Sound::Stop()
{
    if(channel == -1 or chunk != nullptr) return;
    Mix_HaltChannel(channel);
    channel = -1;
}

void Sound::Open(std::string file)
{
    chunk = Resource::GetSound(file);
}

bool Sound::IsOpen() const
{
    return (chunk != nullptr);
}
