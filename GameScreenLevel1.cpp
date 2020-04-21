#include <iostream>
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete Mario;
	Mario = NULL;
	delete Luigi;
	Luigi = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update the players.
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
}

void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	Mario->Render();
	Luigi->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	//Set up the player character.
	Mario = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	Luigi = new Character(mRenderer, "Images/Luigi.png", Vector2D(32, 330));

	return true;
}