#include <SDL.H>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

GameScreenManager* gameScreenManager;
Uint32 gOldTime;

//Texture2D* gTexture = NULL;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly.
	if (InitSDL())
	{

		//Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();

		//Flag to check if we wish to quit.
		bool quit = false;

		//Game loop.
		while (!quit)
		{
			Render();
			quit = Update();
		}
		//Pause for a few seconds.
		//SDL_Delay(5000);
	}

	//Close Window and free resources.
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH,
									SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
		
			//Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_image could not initialise. Error: " << IMG_GetError();
			}
			//Load the background texture.
			//gTexture = new Texture2D(gRenderer);

			//if (!gTexture->LoadFromFile("Images/test.bmp"))
			//{
			//	return false;
			//}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	
	}
	return true;
}

void CloseSDL()
{
	//Destroy the game screen manager.
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release the texture.
	//delete gTexture;
	//gTexture = NULL;

	//Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	//Get the new time.
	Uint32 newTime = SDL_GetTicks();

	SDL_Event e;

	//Get the events.
	SDL_PollEvent(&e);

	//Handle any events.
	switch (e.type)
	{
		//Click the 'X' to quit.
		case SDL_QUIT:
			return true;
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
				case SDLK_q:
					return true;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
				case SDL_BUTTON_RIGHT:
					return true;
		break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//Set the current time to be the old time.
	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear the screen - Cyan
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();
	//gTexture->Render(Vector2D(), SDL_FLIP_NONE);

	//Update the screen.
	SDL_RenderPresent(gRenderer);
}