#include "Game.h"
#include "Resource.h"
#include "InputManager.h"

#define SECONDS 1000.0f

Game* Game::instance = nullptr;

void Game::CrashWithError(std::string msg, std::string error)
{
    std::cerr<<msg<<error<<std::endl;
    exit(EXIT_FAILURE);
}

Game& Game::GetInstance()
{
    if(not instance)
        instance = new Game("Rodrigo Santos 180027352", 1200, 900);
    return *instance;
}

Game::Game(std::string title, int width, int height):
	frameStart(0), storedState(nullptr)
{
    if(instance != nullptr)
    {
        CrashWithError("Jogo já aberto em outra instância", "");
    }

    instance = this;

    const char* audiodriver = SDL_getenv("SDL_AUDIODRIVER");
    if(not audiodriver) {
        if(SDL_setenv("SDL_AUDIODRIVER", "alsa", 1)!=0) {
            std::cerr<<"Erro ao setar AudioDriver";
        }
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        CrashWithError("Erro ao iniciar SDL: ", SDL_GetError());
    }

    int img_flags = IMG_INIT_PNG;
    if(not (IMG_Init(img_flags) & img_flags))
    {
        CrashWithError("Erro ao iniciar SDL_Image: ", IMG_GetError());
    }

    int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG ;
    if(not (Mix_Init(mix_flags) & mix_flags))
    {
        CrashWithError("Erro ao iniciar Mixer", Mix_GetError());
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        CrashWithError("Erro ao iniciar faixa de Audio: ", Mix_GetError());
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if(not window)
    {
        CrashWithError("Erro ao iniciar Window: ", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(not renderer)
    {
        CrashWithError("Erro ao iniciar Renderer: ", SDL_GetError());
    }
}

Game::~Game()
{
	if(storedState)
	{
		delete storedState;
		storedState = nullptr;
	}
	while(not stateStack.empty())
	{
		stateStack.pop();
	}
	Resource::ClearSounds();
	//Resource::ClearMusics();
    Mix_CloseAudio();
    Mix_Quit();
    Resource::ClearImages();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	instance = nullptr;
}

SDL_Renderer* Game::GetRenderer()
{
    return instance->renderer;
}

State& Game::GetCurrentState()
{
    return *instance->stateStack.top();
}

void Game::Push(State* state)
{
	storedState = state;
}

void Game::Run()
{
	InputManager& input = InputManager::GetInstance();

	if(storedState == nullptr)
	{
		CrashWithError("Nenhum estado foi carregado", "");
	}

	storedState->Start();
	stateStack.push(std::unique_ptr<State>(storedState));
	storedState = nullptr;

	while(not stateStack.empty() and not GetCurrentState().QuitRequested())
    {
		if(GetCurrentState().PopRequested())
		{
			stateStack.pop();
			if(not stateStack.empty())
			{
				GetCurrentState().Resume();
			}
			else
			{
				break;
			}
		}

		if(storedState != nullptr)
		{
			GetCurrentState().Pause();
			auto newState = std::unique_ptr<State>(storedState);
			stateStack.emplace(newState.release());
			GetCurrentState().Start();
			storedState = nullptr;
		}

		CalculateDeltaTime();
		input.Update();
        GetCurrentState().Update(dt);
        GetCurrentState().Render();
        SDL_RenderPresent(GetRenderer());
        SDL_Delay(0);
    }
	delete instance;
}


void Game::CalculateDeltaTime()
{
	unsigned int currentFrame = SDL_GetTicks();
	dt = (currentFrame - frameStart) / SECONDS;
	frameStart = currentFrame;
}

float Game::GetDeltaTime()
{
	return dt;
}
