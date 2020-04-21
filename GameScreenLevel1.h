#pragma once

#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include <iostream>
#include "character.h"


class Texture2D;
class Character;



class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
	Texture2D* mBackgroundTexture;

	Character* Mario;
	Character* Luigi;
};

#endif //_GAMESCREENLEVEL1_H